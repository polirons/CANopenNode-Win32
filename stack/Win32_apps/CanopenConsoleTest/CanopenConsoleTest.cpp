// CanopenConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "CanOpen.h"
#include "CO_OD.h"
#include "SDO.h"
#include "libCanOpenNode.h"
#include <stdint.h>



struct sCO_OD_RAM * CO_OD_RAMp;
void __stdcall mscallback();


//#define CO_OD_RAM. CO_OD_RAMp->

void __stdcall SDOErrorCallback(uint32_t abortcode)
{
	fprintf(stdout, "SDO Error abortcode %x\n", abortcode);

}

void  __stdcall SDOFinishedCallback(void)
{
	fprintf(stdout, "SDO finished");
}

int main()
{
	fprintf(stdout, "Hello world");

	registerCallback1ms(mscallback);
	initCanOpenNodeStack(3);

	CO_OD_RAMp = (sCO_OD_RAM * ) getODRAM();

	UNSIGNED16 synclast = 0;

	Sleep(2000);

	printf("Resetting communications...");
	NMT_BusResetCommunications();

	Sleep(2000);

	printf("NMT Operational...");
	NMT_BusOperational();

	Sleep(2000);


	//printf("Sending SDO to node 2");
	uint8_t buff[4];
	buff[0] = 0x1;

	SDOMasterWrite(2, 0x6423, 0, buff, 1, SDOFinishedCallback, SDOErrorCallback);

	while (!SDOIsIdle())
		Sleep(1);

	buff[0] = 0x01;
	buff[1] = 0x00;
	SDOMasterWrite(2, 0x6426, 1, buff, 2, SDOFinishedCallback, SDOErrorCallback);

	while (!SDOIsIdle())
		Sleep(1);

	float val = 0;

	while (1)
	{
		//This code is async and you can do what you like
		//fprintf(stdout, "Write 8 bit out = %d\n", CO_OD_RAMp->writeOutput8Bit[0]);

		/*
		if (SDOIsIdle())
		{

			uint16_t * pdata = (uint16_t *)buff;

			fprintf(stdout,"Input is is %d\n",*pdata),
			SDOMasterRead(2, 0x6401, 1, buff, 2, SDOFinishedCallback, SDOErrorCallback);
		}
		*/

		float newval = (float)CO_OD_RAMp->tempsPDO[0] / 10.0;

		if (val != newval)
		{
		
			val = (float)CO_OD_RAMp->tempsPDO[0] / 10.0;

			printf("TEMP %f %f %f %f\n", (float)CO_OD_RAMp->tempsPDO[0] / 10.0, (float)CO_OD_RAMp->tempsPDO[1] / 10.0, (float)CO_OD_RAMp->tempsPDO[2] / 10.0, (float)CO_OD_RAMp->tempsPDO[3] / 10.0);
		}
		
		//fprintf(stdout, "Performance %d main = %d (%d) timer %d (%d)\n", CO_OD_RAMp->performance[0], CO_OD_RAMp->performance[1], CO_OD_RAMp->performance[2], CO_OD_RAMp->performance[3], CO_OD_RAMp->performance[4]);

		Sleep(1);
	}

    return 0;
}

void __stdcall mscallback()
{
	//This is a good place to check the OD for PDO updates as its called on the CanOpen 1ms timer
	//do not do any heavy processing here
}



