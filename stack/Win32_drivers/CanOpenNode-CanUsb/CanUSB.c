#include "stdafx.h"
#include <stdio.h>
#include <stdbool.h>

#include "CanDriver.h"

//#include "CANopen.h"

HANDLE hComm;
HANDLE hreadThread;
BOOL threadrun;
DWORD WINAPI read_thread(LPVOID lpParam);
BOOL WriteSerialBuffer(char * lpBuf, DWORD dwToWrite);
BOOL WriteCanPacket(s_Message * TxPacket);
void close_port();

//BOOL WriteCanPacket(CO_CANrxMsg_t * TxPacket);

s_Message canpacket;

CANRECEIVE_DRIVER_PROC rxcallback;

#define READ_BUF_SIZE	  20
char lpBuf[READ_BUF_SIZE];


CANSEND_DRIVER_PROC can_driver_send(void* inst, const s_Message *m)
{
	WriteCanPacket(m);
}

CANOPEN_DRIVER_PROC can_driver_open(s_BOARD *board)
{
	drv_open_port(board->busname,board->baudrate);
}

CANCLOSE_DRIVER_PROC can_driver_close(void* inst)
{
	drv_close_port();
}

CANCHANGEBAUDRATE_DRIVER_PROC can_driver_change_baudrate(void* fd, char* baud)
{
	if (strcmp(baud, "10k") == 0)
		WriteSerialBuffer("C\rS0\rO\r", 7);
	if (strcmp(baud, "20k") == 0)
		WriteSerialBuffer("C\rS1\rO\r", 7);
	if (strcmp(baud, "50k") == 0)
		WriteSerialBuffer("C\rS2\rO\r", 7);
	if (strcmp(baud, "100k") == 0)
		WriteSerialBuffer("C\rS3\rO\r", 7);
	if (strcmp(baud, "125k") == 0)
		WriteSerialBuffer("C\rS4\rO\r", 7);
	if (strcmp(baud, "250k") == 0)
		WriteSerialBuffer("C\rS5\rO\r", 7);
	if (strcmp(baud, "500k") == 0)
		WriteSerialBuffer("C\rS6\rO\r", 7);
	if (strcmp(baud, "800k") == 0)
		WriteSerialBuffer("C\rS7\rO\r", 7);
	if (strcmp(baud, "1000k") == 0)
		WriteSerialBuffer("C\rS8\rO\r", 7);
}

CANREGRXCALLBACK can_driver_register_rx_callback(CANRECEIVE_DRIVER_PROC rxproc)
{
	rxcallback = rxproc;
}


int drv_open_port(char * bus,char * baud)
{
	//char portstr[20];
	
	//sprintf_s(portstr, 20, "\\\\.\\COM%d", port);

	hComm = CreateFileA(bus,
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

	if (strcmp(baud, "10k") == 0)
		WriteSerialBuffer("C\rS0\rO\r", 7);
	if (strcmp(baud, "20k") == 0)
		WriteSerialBuffer("C\rS1\rO\r", 7);
	if (strcmp(baud, "50k") == 0)
		WriteSerialBuffer("C\rS2\rO\r", 7);
	if(strcmp(baud,"100k")==0)
		WriteSerialBuffer("C\rS3\rO\r", 7);
	if (strcmp(baud, "125k") == 0)
		WriteSerialBuffer("C\rS4\rO\r", 7);
	if (strcmp(baud, "250k") == 0)
		WriteSerialBuffer("C\rS5\rO\r", 7);
	if(strcmp(baud,"500k")==0)
		WriteSerialBuffer("C\rS6\rO\r", 7);
	if (strcmp(baud, "800k") == 0)
		WriteSerialBuffer("C\rS7\rO\r", 7);
	if (strcmp(baud, "1000k") == 0)
		WriteSerialBuffer("C\rS8\rO\r", 7);

	Sleep(100);

	PurgeComm(hComm, PURGE_RXCLEAR);

	hreadThread = CreateThread(NULL, 0, read_thread, NULL, 0, NULL);

	return 0;
}

void drv_close_port()
{
	threadrun = FALSE;
}

void HandleASuccessfulRead(char * lpBuf, DWORD dwRead)
{

	if (isringfull() ==TRUE)
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
		memset(&canpacket, 0, sizeof(s_Message));
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
				d = c[0] - 0x57;
			if (c[0] >= 0x41 && c[0] <= 0x46)
				d = c[0] - 0x37;

			if (count < 4)
			{
				
				canpacket.cob_id <<= 4;
				canpacket.cob_id |= d;
			}
			else 
			if (count == 4)
			{
				canpacket.len = d;
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

		//CO_CAN_ISR(); //canpacket is loaded up with the data to process
		//Invoke the callback

		rxcallback(NULL, &canpacket);

		//OutputDebugStringA("\n");
	}

}

OVERLAPPED osReader = { 0 };



DWORD WINAPI read_thread(LPVOID lpParam)
{
		init_ringbuffer();
	
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


BOOL WriteCanPacket(s_Message * TxPacket)
{

	//int bcount = (TxPacket->ident >> 12);
	int bcount = (TxPacket->len);
	int len = 5 + 2 * bcount;
	char txbuf[23];
	memset(txbuf, 0, 23);

	int * data = (int*)&TxPacket->data;
	sprintf_s(txbuf, 23, "t%03x%01x", 0x7FF & TxPacket->cob_id, bcount);

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

void closeall()
{
	
	threadrun = false;
	CloseHandle(osReader.hEvent);
	CloseHandle(hComm);

	//should we wait here for single object?
	CloseHandle(hreadThread);

}