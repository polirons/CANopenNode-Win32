// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "CANopen.h"
#include "libCanOpenNode.h"

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


LIBCANOPENNODE_API int initCanOpenNodeStack(void)
{

	if (open_port() == -1)
	{
		return;
	}

	thread = CreateThread(NULL, 0, CanOpen_run, NULL, 0, NULL);

	return 0;
}

