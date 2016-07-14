// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "libCanOpenNode.h"
#include "CanDriver.h"
#include "CANopen.h"
#include "program.h"

DWORD WINAPI CanOpen_run(LPVOID lpParam);
extern CO_NMT_reset_cmd_t reset;
HANDLE thread;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		reset = CO_RESET_QUIT;
		break;
	}
	return TRUE;
}


CANOPENNODECANUSB_API int initCanOpenNodeStack(char * driver,char * bus,char * baud)
{

	LoadCanDriver(driver);

	if (open_port(bus,baud) == -1)
	{
		return;
	}

	thread = CreateThread(NULL, 0, CanOpen_run, NULL, 0, NULL);
	
	return 0;
}


CANOPENNODECANUSB_API void * getODRAM()
{
	return &CO_OD_RAM;
}

CANOPENNODECANUSB_API void * getODROM()
{
	return &CO_OD_ROM;
}

CANOPENNODECANUSB_API void * getODEEPROM()
{
	return &CO_OD_EEPROM;
}

CANOPENNODECANUSB_API void registerCallback1ms(timercallback fnptr)
{
	CanOpen_Callback1ms = fnptr;
}

CANOPENNODECANUSB_API void registerCallbackprogramStart(timercallback fnptr)
{
	CanOpen_CallbackprogramStart = fnptr;
}

CANOPENNODECANUSB_API void registerCallbackcommunicationsReset(timercallback fnptr)
{
	CanOpen_CallbackcommunicationReset = fnptr;
}

CANOPENNODECANUSB_API void registerCallbackprogramAsync(timercallback fnptr)
{
	CanOpen_CallbackprogramAsync = fnptr;
}

CANOPENNODECANUSB_API void registerCallbackprogramEnd(timercallback fnptr)
{
	CanOpen_CallbackprogramEnd = fnptr;
}


CANOPENNODECANUSB_API int closeCanOpenNodeStack(void)
{
	//closeall();
}
