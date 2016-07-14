#include <stdint.h>
#include <stdbool.h>
#define FALSE false
#define TRUE true

#include "ringbuffer.h"


#define CUR_BUF_SIZE	500




char cirbuffer[CUR_BUF_SIZE];
char * readptr;
char * writeptr;
char * bufend;
char * bufstart;

bool bufffull;

#define MAX_PACKET_SIZE 25

void init_ringbuffer()
{
	bufend = &cirbuffer[0] + CUR_BUF_SIZE;
	bufstart = &cirbuffer[0];

	readptr = bufstart;
	writeptr = bufstart;
}

bool isringfull()
{
	return bufffull;
}

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


