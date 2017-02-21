#include "stdafx.h"
#include <stdio.h>
#include <stdbool.h>
#include "CANopen.h"

HANDLE hComm;
HANDLE hreadThread;
BOOL threadrun;
DWORD WINAPI read_thread(LPVOID lpParam);

BOOL WriteSerialBuffer(char * lpBuf, DWORD dwToWrite);
BOOL WriteCanPacket(CO_CANrxMsg_t * TxPacket);

int open_port(int port)
{
	char portstr[20];
	
	sprintf_s(portstr, 20, "\\\\.\\COM%d", port);

	hComm = CreateFileA(port,
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		0);

	if (hComm == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("Error opening com port");
		return -1;

		// error opening port; abort
	}

	DCB dcb;

	FillMemory(&dcb, sizeof(dcb), 0);
	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = 115200;
	dcb.Parity = 0;
	dcb.StopBits = 1;
	dcb.ByteSize = 8;
	dcb.fBinary = TRUE;

	SetCommState(hComm, &dcb);

	threadrun = TRUE;

	WriteSerialBuffer("C\rS6\rO\r", 7);

	Sleep(100);

	PurgeComm(hComm, PURGE_RXCLEAR);

	hreadThread = CreateThread(NULL, 0, read_thread, NULL, 0, NULL);


	return 0;
}

void close_port()
{
	threadrun = FALSE;
}

#define READ_TIMEOUT      500      // milliseconds
#define READ_BUF_SIZE	  20
#define CUR_BUF_SIZE	500


char lpBuf[READ_BUF_SIZE];

char cirbuffer[CUR_BUF_SIZE];
char * readptr;
char * writeptr;
char * bufend;
char * bufstart;

bool bufffull;

#define MAX_PACKET_SIZE 25

CO_CANrxMsg_t canpacket;

int getfreebufferspace()
{
	if (readptr == writeptr)
		return CUR_BUF_SIZE;

	if (writeptr > readptr) //write ptr is ahead of read in a normal way
		return writeptr - readptr;
	else // writeptr has wrapped around the queue and is approaching read from the rear
		return readptr - writeptr;
}

void writebuffer(char * byte)
{
	*writeptr = byte;

	writeptr += 1;

	if (writeptr == bufend)
		writeptr = bufstart;

	if (writeptr == readptr)
		bufffull = TRUE;
	else
		bufffull = FALSE;

}

char readbuffer()
{
	char ret = *readptr;

	readptr += 1;

	if (readptr == bufend)
		readptr = bufstart;

	bufffull = FALSE;
	
	return ret;

}

int peekbufferfindterminator()
{
	char * tempbuf;
	int count = 1;

	tempbuf = readptr;

	while (tempbuf != writeptr)
	{
		
		if (tempbuf == bufend)
			tempbuf = bufstart;

		if (*tempbuf == '\r')
			return count;

		count++;
		tempbuf++;
	}

	return 0;

}

void HandleASuccessfulRead(char * lpBuf, DWORD dwRead)
{

	if (bufffull)
	{
		OutputDebugStringA("Out of ring buffer space\n");
	}

	DWORD count = 0;

	while (count != dwRead)
	{
		writebuffer(*(lpBuf + count));
		count++;
	}

	count = 0;

	int term = peekbufferfindterminator();
	if (term > 0)
	{
		memset(&canpacket, 0, sizeof(CO_CANrxMsg_t));
		while (count < term - 1)
		{
			char c[2];
			c[0] = readbuffer();
			c[1] = 0;

			//if we have a z its a successful TX process but it will be \r terminated so eat that and return;
			if (c[0] == 'z')
			{
				readbuffer(); //eat the extra \r
				return; //return don't call the interrupt handler
			}

			if (count == 0 && c[0] == 't')
			{
				count++;
				continue;
			}

			int d = 0;
			if (c[0] >= 0x30 && c[0] <= 0x39)
				d = c[0] - 0x30;
			if (c[0] >= 0x61 && c[0] <= 0x66)
				d = c[0] - 0x61;
			if (c[0] >= 0x41 && c[0] <= 0x46)
				d = c[0] - 0x41;

			if (count < 4)
			{
				canpacket.ident <<= 4;
				canpacket.ident |= d;
			}
			else 
			if (count == 4)
			{
				canpacket.DLC = d;
			}
			else
			{
				int byte = (count - 5) / 2;
				int shift = 4-(4 * ((count - 5) % 2));
				canpacket.data[byte] += d << shift;
			}

			count++;
		}

		//dummy ready to clear trailing \r from ringbuffer
		readbuffer();

		CO_CAN_ISR(); //canpacket is loaded up with the data to process

		OutputDebugStringA("\n");
	}

}

DWORD WINAPI read_thread(LPVOID lpParam)
{

		OVERLAPPED osReader = { 0 };

		bufend = &cirbuffer[0] + CUR_BUF_SIZE;
		bufstart = &cirbuffer[0];

		readptr = bufstart;
		writeptr = bufstart;
	
		DWORD dwRead;
		BOOL fWaitingOnRead = FALSE;

		// Create the overlapped event. Must be closed before exiting
		// to avoid a handle leak.
		osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		if (osReader.hEvent == NULL)
		{
			// Error creating overlapped event; abort.
			OutputDebugStringA("Error creating overlapped event; abort.");
			return 0;
		}

		DWORD dwCommEvent = 0;

		while (threadrun)
		{
			if (!fWaitingOnRead)
			{

				COMSTAT comStat;
				DWORD   dwErrors;

				// Get and clear current errors on the port.
				//if (!ClearCommError(hComm, &dwErrors, &comStat))
				//{
				//	// Report error in ClearCommError.
				//	return FALSE;
				//}

				//if (comStat.cbInQue == 0)
				//	continue;

				// Issue read operation.
				if (!ReadFile(hComm, lpBuf, 1 /*comStat.cbInQue < READ_BUF_SIZE ? comStat.cbInQue : READ_BUF_SIZE*/, &dwRead, &osReader))
				{
					if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
					{
						OutputDebugStringA("GetLastError() != ERROR_IO_PENDING");
					}												// Error in communications; report it.
					else
					{
						fWaitingOnRead = TRUE;
					}
				}
				else
				{
					// read completed immediately
					HandleASuccessfulRead(lpBuf, dwRead);
					fWaitingOnRead = FALSE;
				}
			}

			DWORD dwRes;

			if (fWaitingOnRead) {
				dwRes = WaitForSingleObject(osReader.hEvent, INFINITE);
				switch (dwRes)
				{
					// Read completed.
				case WAIT_OBJECT_0:
					if (!GetOverlappedResult(hComm, &osReader, &dwRead, FALSE))
					{
						// Error in communications; report it.
						OutputDebugStringA("// Error in communications; report it.");
					}
					else
					{
						// Read completed successfully.
						HandleASuccessfulRead(lpBuf, dwRead);
						
					}

					fWaitingOnRead = FALSE;

					break;

				case WAIT_TIMEOUT:
					// Operation isn't complete yet. fWaitingOnRead flag isn't
					// changed since I'll loop back around, and I don't want
					// to issue another read until the first one finishes.
					//
					// This is a good time to do some background work.

					OutputDebugStringA("TIMEOUT!!!");
					break;

				default:
					// Error in the WaitForSingleObject; abort.
					// This indicates a problem with the OVERLAPPED structure's
					// event handle.

					OutputDebugStringA("Error in the WaitForSingleObject; abort.");
					return FALSE;
				}
			}

		}

	return 0;

}


BOOL WriteCanPacket(CO_CANrxMsg_t * TxPacket)
{

	int bcount = (TxPacket->ident >> 12);
	int len = 5 + 2 * bcount;
	char txbuf[23];
	memset(txbuf, 0, 23);

	int * data = (int*)&TxPacket->data;
	sprintf_s(txbuf, 23, "t%03x%01x", 0x7FF & TxPacket->ident, bcount);

	for (int x = 0; x < bcount; x++)
	{
		char c = 0x0F & (TxPacket->data[x] >> 4);
		if (c >= 0 && c <= 9)
			c = c + 0x30;
		if (c >= 0x0a && c <= 0x0f)
			c = c += 0x57;

		txbuf[5 + 2 * x] = c;

		c = 0x0f & TxPacket->data[x];
		if (c >= 0 && c <= 9)
			c = c + 0x30;
		if (c >= 0x0a && c <= 0x0f)
			c = c += 0x57;

		txbuf[6 + 2 * x] = c;

	}

	txbuf[5 + 2 * bcount] = '\r';

	WriteSerialBuffer(txbuf, len + 1);
}

BOOL WriteSerialBuffer(char * lpBuf, DWORD dwToWrite)
{

		OVERLAPPED osWrite = { 0 };
		DWORD dwWritten;
		BOOL fRes;

		// Create this writes OVERLAPPED structure hEvent.
		osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (osWrite.hEvent == NULL)
		{
			OutputDebugStringA("Error creating overlappde event");
			return FALSE;
		}

		// Issue write.
		if (!WriteFile(hComm, lpBuf, dwToWrite, &dwWritten, &osWrite)) {
			if (GetLastError() != ERROR_IO_PENDING) {
				// WriteFile failed, but it isn't delayed. Report error and abort.
				OutputDebugStringA("WriteFile failed, but it isn't delayed. Report error and abort.");
				fRes = FALSE;
			}
			else {
				// Write is pending.
				if (!GetOverlappedResult(hComm, &osWrite, &dwWritten, TRUE))
				{
					OutputDebugStringA("Write is pending");
					fRes = FALSE;
				}
				else
					// Write operation completed successfully.
					fRes = TRUE;
			}
		}
		else
		{
			fRes = TRUE;
		}

		CloseHandle(osWrite.hEvent);
		return fRes;
	}

