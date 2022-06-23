// libCanOpenNode.cpp : Defines the exported functions for the DLL application.
//
// This is the CanOpenNode start up code, it is completly based on the PIC32 example
// CANopenNode/blob/master/stack/PIC32/main_PIC32.c with approprate things changed
// for win32 API

#include "stdafx.h"
#include "libCanOpenNode.h"
#include "CANopen.h"
#include "eeprom.h" 
#include "Program.h"
#include <stdio.h>

double PCFreq = 0.0;
__int64 CounterStartTimer = 0;
__int64 CounterStartMain = 0;
LARGE_INTEGER li_timer;
LARGE_INTEGER li_main;


void CALLBACK TimerProc(void* lpParametar,
	BOOLEAN TimerOrWaitFired);


//fixme use this to inhibit the rx channel
bool CO_CAN_ISR_ENABLE;
bool CO_CAN_ISR2_ENABLE;

#define ADDR_CAN1 3 //use this for com port??


/* Global variables and objects */
volatile uint16_t CO_timer1ms = 0U; /* variable increments each millisecond */
//const CO_CANbitRateData_t   CO_CANbitRateData[8] = { CO_CANbitRateDataInitializers };
static uint32_t tmpU32;
HANDLE m_timerHandle;
CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

#ifdef USE_EEPROM
CO_EE_t                     CO_EEO;         /* Eeprom object */
#endif

/* helpers */
void CANrx_lockCbSync(bool_t syncReceived) {
	if (syncReceived) {
		CO_CAN_ISR_ENABLE = 0;
		CO_CAN_ISR2_ENABLE = 0;
	}
}

DWORD WINAPI CanOpen_run(LPVOID lpParam)
{
	

	/* initialize EEPROM - part 1 */
#ifdef USE_EEPROM
	CO_ReturnError_t eeStatus = CO_EE_init_1(&CO_EEO, (uint8_t*)&CO_OD_EEPROM, sizeof(CO_OD_EEPROM),
		(uint8_t*)&CO_OD_ROM, sizeof(CO_OD_ROM));
#endif

	programStart();

	/* increase variable each startup. Variable is stored in eeprom. */
	OD_powerOnCounter++;

	while (reset != CO_RESET_APP) {
		/* CANopen communication reset - initialize CANopen objects *******************/
		CO_ReturnError_t err;
		uint16_t timer1msPrevious;
		uint16_t TMR_TMR_PREV = 0;
		uint8_t nodeId;
		uint16_t CANBitRate;

		/* disable CAN and CAN interrupts */
		CO_CAN_ISR_ENABLE = 0;
		CO_CAN_ISR2_ENABLE = 0;

		/* Read CANopen Node-ID and CAN bit-rate from object dictionary */
		nodeId = OD_CANNodeID;
		if (nodeId<1 || nodeId>127) nodeId = 0x10;
		CANBitRate = OD_CANBitRate;/* in kbps */

								   /* initialize CANopen */
		err = CO_init(ADDR_CAN1, nodeId, CANBitRate);
		if (err != CO_ERROR_NO) {
			//FIXME do something here?
			/* CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err); */
		}


		/* initialize eeprom - part 2 */
#ifdef USE_EEPROM
		CO_EE_init_2(&CO_EEO, eeStatus, CO->SDO[0], CO->em);
#endif


		/* Configure callback functions */
		//CO_SYNC_initCallback(CO->SYNC, CANrx_lockCbSync);

		/* initialize variables */
		timer1msPrevious = CO_timer1ms;
		OD_performance[ODA_performance_mainCycleMaxTime] = 0;
		OD_performance[ODA_performance_timerCycleMaxTime] = 0;
		reset = CO_RESET_NOT;

		/* Configure Timer interrupt function for execution every 1 millisecond */
		/* Not sure if this is the best type of timer to use */
		/* The jitter on the timing is not great */
		BOOL success = CreateTimerQueueTimer(
			&m_timerHandle,
			NULL,
			TimerProc,
			NULL,
			0,
			1, //Period in ms
			WT_EXECUTEINTIMERTHREAD);

#if CO_PBCLK > 65000
#error wrong timer configuration
#endif
		communicationReset();

		/* start CAN and enable interrupts */
		CO_CANsetNormalMode(CO->CANmodule[0]);
		
#if CO_NO_CAN_MODULES >= 2
		CO_CANsetNormalMode(CO->CANmodule[1]);
		CO_CAN_ISR2_ENABLE = 1;
#endif


		while (reset == CO_RESET_NOT) {
			/* loop for normal program execution ******************************************/
			uint16_t timer1msCopy, timer1msDiff;

			/* calculate cycle time for performance measurement */
			
			timer1msCopy = CO_timer1ms;
			timer1msDiff = timer1msCopy - timer1msPrevious;
			timer1msPrevious = timer1msCopy;

			LARGE_INTEGER Frequency;
			LARGE_INTEGER StartingTime;
			LARGE_INTEGER ElapsedMicroseconds;

			QueryPerformanceFrequency(&Frequency);
			QueryPerformanceCounter(&StartingTime);
			ElapsedMicroseconds.QuadPart = StartingTime.QuadPart - li_main.QuadPart;
			ElapsedMicroseconds.QuadPart *= 1000000;
			ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

			double t = ElapsedMicroseconds.QuadPart / 1000.0;
			t = 1000.0 / t;

			OD_performance[ODA_performance_mainCycleTime] = t;

			if (t > OD_performance[ODA_performance_mainCycleMaxTime])
					OD_performance[ODA_performance_mainCycleMaxTime] = t;
	
			li_main = StartingTime;

			/* Application asynchronous program */
			programAsync(timer1msDiff);

			/* Pump the SDO master */
			/* TODO In theory we should support as many masters as is defined in OD*/
			canprocessSDOmaster(timer1msDiff);

			/* CANopen process */
			reset = CO_process(CO, timer1msDiff, NULL);

			Sleep(1); //add some grace time to the thread as we do not want to hammer the async thread at 100%

		}
#ifdef USE_EEPROM
			CO_EE_process(&CO_EEO);
#endif
		}

		/* program exit ***************************************************************/

		/* delete objects from memory */
		programEnd();
		CO_delete(ADDR_CAN1);

		// fix me graceful shutdown on win32
		return 0;
}


/* timer interrupt function executes every millisecond ************************/

void CALLBACK TimerProc(void* lpParametar,
	BOOLEAN TimerOrWaitFired)
{

	CO_timer1ms++;

	if (CO->CANmodule[0]->CANnormal) {
		bool_t syncWas;
		int i;

		/* Process Sync and read inputs */
		syncWas = CO_process_SYNC_RPDO(CO, 1000);

		/* Re-enable CANrx, if it was disabled by SYNC callback */
		CO_CAN_ISR_ENABLE = 1;
#if CO_NO_CAN_MODULES >= 2
		CO_CAN_ISR2_ENABLE = 1;
#endif

		/* Further I/O or nonblocking application code may go here. */
#if CO_NO_TRACE > 0
		OD_time.epochTimeOffsetMs++;
		for (i = 0; i<OD_traceEnable && i<CO_NO_TRACE; i++) {
			CO_trace_process(CO->trace[i], OD_time.epochTimeOffsetMs);
		}
#endif
		program1ms();

		/* Write outputs */
		CO_process_TPDO(CO, syncWas, 1000);

	}

	LARGE_INTEGER Frequency;
	LARGE_INTEGER StartingTime;
	LARGE_INTEGER ElapsedMicroseconds;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
	ElapsedMicroseconds.QuadPart = StartingTime.QuadPart - li_timer.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	double t = ElapsedMicroseconds.QuadPart / 1000.0;
	t = 1000.0 / t;

	OD_performance[ODA_performance_timerCycleTime] = t;

	if (t > OD_performance[ODA_performance_timerCycleMaxTime])
			OD_performance[ODA_performance_timerCycleMaxTime] = t;
	
	li_timer = StartingTime;

		
}

/* CAN interrupt function *****************************************************/
void CO_CAN_ISR() {
	CO_CANinterrupt(CO->CANmodule[0]);
	/* Clear combined Interrupt flag */
	//CO_CAN_ISR_FLAG = 0;
}

#if CO_NO_CAN_MODULES >= 2
void CO_CAN_ISR2() {
	CO_CANinterrupt(CO->CANmodule[1]);
	/* Clear combined Interrupt flag */
	CO_CAN_ISR2_FLAG = 0;
}
#endif
