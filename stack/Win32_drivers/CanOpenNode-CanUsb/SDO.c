#include "libCanOpenNode.h"
#include "CANopen.h"
#include "SDO.h"

/* TODO In theory we should support as many masters as is defined in OD*/

typedef enum
{
	IDLE = 0,
	NEW_SLAVEUP,
	NEW_SLAVEDOWN,
	SEND_REQUP,
	WAIT_REPLYUP,
	SEND_REQDOWN,
	WAIT_REPLYDOWN,
	FINISHED,
	ERROR,

}SDO_MASTER_STATES;


uint32_t abortcodebuffer;
SDO_MASTER_STATES master_state;
uint8_t slavenode;
uint16_t slaveindex;
uint8_t  slavesubindex;
uint8_t * userrxbuffer;
uint8_t * usertxbuffer;
uint32_t datalen;
timercallback complete_func;
abortcallback error_func;

void canprocessSDOmaster(uint16_t time1msdiff)
{

	switch (master_state)
	{
	case IDLE:
		break;

	case NEW_SLAVEUP:
		CO_SDOclient_setup(CO->SDOclient, 0, 0, slavenode);
		master_state = SEND_REQUP;
		break;

	case SEND_REQUP:
		//fix me we should request the size of usertxbuffer and sent that to CO_SDOclientDownloadInitiate() as a saftey limit 
		CO_SDOclientDownloadInitiate(CO->SDOclient, slaveindex, slavesubindex, usertxbuffer, datalen, false);
		master_state = WAIT_REPLYUP;
		break;

	case WAIT_REPLYUP:
	{
		int ret = CO_SDOclientDownload(CO->SDOclient, time1msdiff, 1000, &abortcodebuffer);

		if (ret == 0)
		{
			master_state = FINISHED;
			if (complete_func != NULL)
				complete_func();
		}
		if (ret<0)
		{
			master_state = ERROR;
			if (complete_func != NULL)
				error_func(abortcodebuffer);
		}
	}
	break;

	case NEW_SLAVEDOWN:
		CO_SDOclient_setup(CO->SDOclient, 0, 0, slavenode);
		master_state = SEND_REQDOWN;
		break;

	case SEND_REQDOWN:
		CO_SDOclientUploadInitiate(CO->SDOclient, slaveindex, slavesubindex, userrxbuffer, datalen<4 ? 4 : datalen, false);
		master_state = WAIT_REPLYDOWN;
		break;

	case  WAIT_REPLYDOWN:
	{
		volatile int8_t ret = CO_SDOclientUpload(CO->SDOclient, time1msdiff, 1000, &datalen, &abortcodebuffer);

		if (ret == 0)
		{
			master_state = FINISHED;

			if (complete_func != NULL)
				complete_func();
		}
		if (ret<0)
		{
			master_state = ERROR;
			if (complete_func != NULL)
				error_func(abortcodebuffer);
		}
	}
	break;

	case FINISHED:
		CO_SDOclientClose(CO->SDOclient);
		master_state = IDLE;
		break;

	case ERROR:
		break;

	}
}


CANOPENNODECANUSB_API int SDOMasterWrite(uint8_t node, uint16_t index, uint8_t subindex, uint8_t * buffer, uint8_t len, timercallback func, timercallback error)
{
	if (master_state == IDLE)
	{
		slavenode = node;
		slaveindex = index;
		slavesubindex = subindex;
		datalen = len;
		usertxbuffer = buffer;
		master_state = NEW_SLAVEUP;
		complete_func = func;
		error_func = error;
	}

	return SDOIsIdle();
}


CANOPENNODECANUSB_API int SDOMasterRead(uint8_t node, uint16_t index, uint8_t subindex, uint8_t * buffer, uint8_t len, timercallback func, timercallback error)
{
	if (master_state == IDLE)
	{
		slavenode = node;
		slaveindex = index;
		slavesubindex = subindex;
		datalen = len;
		userrxbuffer = buffer;
		master_state = NEW_SLAVEDOWN;
		complete_func = func;
		error_func = error;
	}
	
	return SDOIsIdle();
}


CANOPENNODECANUSB_API void SDOMasterFinish()
{
	if (master_state == FINISHED || master_state == ERROR)
	{
		master_state = IDLE;
	}
}
CANOPENNODECANUSB_API bool SDOIsIdle()
{
	if (master_state == FINISHED || master_state == ERROR || master_state == IDLE)
	{
		master_state = IDLE;
		return true;
	}

	return false;
}

CANOPENNODECANUSB_API bool __stdcall SDOIsError()
{
	if (master_state == ERROR)
	{
		return true;
	}
	return false;
}

