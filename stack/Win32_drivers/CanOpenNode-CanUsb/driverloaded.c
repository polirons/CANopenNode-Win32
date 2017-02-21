
#include <windows.h>
#include <stdio.h>
#include "CanDriver.h"
#include "CanOpen.h"

#include "InterfaceBoundary.h"

CANREGRXCALLBACK m_canReceive;
CANSEND_DRIVER_PROC m_canSend;
CANOPEN_DRIVER_PROC m_canOpen;
CANCLOSE_DRIVER_PROC m_canClose;
CANCHANGEBAUDRATE_DRIVER_PROC m_canChangeBaudRate;
CANGETFILTERS_DRIVER_PROC m_canGetFilters;
CANSETFILTER_DRIVER_PROC m_canSetFilter;

// GetProcAddress doesn't have an UNICODE version for NT
#ifdef UNDER_CE
#define myTEXT(str) TEXT(str)
#else
#define myTEXT(str) str
#endif

/* Interface boundary */
/* These functions below are the trampoline functions that call the actuall DLL */

CO_CANrxMsg_t canpacket;

void WriteCanPacket(CO_CANtx_t *buffer)
{
	s_Message m;
	m.cob_id = buffer->ident;
	
	m.len = (buffer->ident >> 12);

	m.data[0] = buffer->data[0];
	m.data[1] = buffer->data[1];
	m.data[2] = buffer->data[2];
	m.data[3] = buffer->data[3];
	m.data[4] = buffer->data[4];
	m.data[5] = buffer->data[5];
	m.data[6] = buffer->data[6];
	m.data[7] = buffer->data[7];

	m_canSend(NULL, &m);
}

CANRECEIVE_DRIVER_PROC recieve(void* inst, s_Message *m)
{
	canpacket.ident = m->cob_id;
	canpacket.DLC = m->len;

	canpacket.data[0] = m->data[0];
	canpacket.data[1] = m->data[1];
	canpacket.data[2] = m->data[2];
	canpacket.data[3] = m->data[3];
	canpacket.data[4] = m->data[4];
	canpacket.data[5] = m->data[5];
	canpacket.data[6] = m->data[6];
	canpacket.data[7] = m->data[7];

	uint32_t * data = (uint32_t*)canpacket.data;

	fprintf(stderr, "%x %x %x\n", m->cob_id, m->len, *data);

	CO_CAN_ISR(); //canpacket is loaded up with the data to process

	return 0;
}

void open_port(char * bus, char * baud)
{
	s_BOARD b;
	b.baudrate = malloc(10);
	b.busname = malloc(20);

	strcpy_s(b.baudrate,10, baud);
	strcpy_s(b.busname,20, bus);
	m_canOpen(&b);

	free(b.baudrate);
	free(b.busname);

}

void close_port()
{
	m_canClose(NULL);
	
}

int getNoSupportedFilters()
{
	return m_canGetFilters();
}

void SetCanFilter(uint32_t ident, uint32_t mask)
{
	m_canSetFilter(ident, mask);
}

/* End of Interface boundary */

LIB_HANDLE LoadCanDriver(LPCSTR driver_name)
{
	// driver module handle
	LIB_HANDLE handle = NULL;

	handle = LoadLibraryA(driver_name);

	if (!handle)
	{
		fprintf(stderr, "LoadLibrary error : %d\n", GetLastError());
		return NULL;
	}

	m_canReceive = (CANREGRXCALLBACK)GetProcAddress(handle, myTEXT("can_driver_register_rx_callback"));
	m_canSend = (CANSEND_DRIVER_PROC)GetProcAddress(handle, myTEXT("can_driver_send"));
	m_canOpen = (CANOPEN_DRIVER_PROC)GetProcAddress(handle, myTEXT("can_driver_open"));
	m_canClose = (CANCLOSE_DRIVER_PROC)GetProcAddress(handle, myTEXT("can_driver_close"));
	m_canChangeBaudRate = (CANCHANGEBAUDRATE_DRIVER_PROC)GetProcAddress(handle, myTEXT("can_driver_change_baudrate"));
	m_canGetFilters = (CANGETFILTERS_DRIVER_PROC)GetProcAddress(handle, myTEXT("can_driver_get_filters"));
	m_canSetFilter = (CANSETFILTER_DRIVER_PROC)GetProcAddress(handle, myTEXT("can_driver_set_filter"));

	if (m_canReceive == NULL || m_canSend == NULL || m_canOpen == NULL || m_canClose == NULL 
		|| m_canChangeBaudRate == NULL || m_canGetFilters == NULL || m_canSetFilter == NULL)
	{
		m_canReceive = NULL;
		m_canSend = NULL;
		m_canOpen = NULL;
		m_canClose = NULL;
		m_canChangeBaudRate = NULL;
		m_canGetFilters = NULL;
		m_canSetFilter = NULL;
		FreeLibrary(handle);
		fprintf(stderr, "GetProc error : %d\n", GetLastError());
		return NULL;
	}

	//register the rx callback hook
	m_canReceive(recieve);

	return handle;
}
