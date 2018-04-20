/*
* CANopen main program file.
*
* This file is a template for other microcontrollers.
*
* @file        main_generic.c
* @author      Janez Paternoster
* @copyright   2004 - 2015 Janez Paternoster
*
* This file is part of CANopenNode, an opensource CANopen Stack.
* Project home page is <https://github.com/CANopenNode/CANopenNode>.
* For more information on CANopen see <http://www.can-cia.org/>.
*
* CANopenNode is free and open source software: you can redistribute
* it and/or modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation, either version 2 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Following clarification and special exception to the GNU General Public
* License is included to the distribution terms of CANopenNode:
*
* Linking this library statically or dynamically with other modules is
* making a combined work based on this library. Thus, the terms and
* conditions of the GNU General Public License cover the whole combination.
*
* As a special exception, the copyright holders of this library give
* you permission to link this library with independent modules to
* produce an executable, regardless of the license terms of these
* independent modules, and to copy and distribute the resulting
* executable under terms of your choice, provided that you also meet,
* for each linked independent module, the terms and conditions of the
* license of that module. An independent module is a module which is
* not derived from or based on this library. If you modify this
* library, you may extend this exception to your version of the
* library, but you are not obliged to do so. If you do not wish
* to do so, delete this exception statement from your version.
*/



//#define NN_STATIC_LIB
#include "windows.h"
#include "CANopen.h"

#include <assert.h>
//#include <libc.h>
#include <stdio.h>
#include <nn.h>
#include <bus.h>

#include <stdint.h>

#define packetdebug
#define bufsize 50

void RxCanPacket();

#define TMR_TASK_INTERVAL   (1000)          /* Interval of tmrTask thread in microseconds */
#define INCREMENT_1MS(var)  (var++)         /* Increment 1ms variable in tmrTask */

void CALLBACK TimerProc(void* lpParametar,
	BOOLEAN TimerOrWaitFired);


/* Global variables and objects */
volatile uint16_t   CO_timer1ms = 0U;   /* variable increments each millisecond */
HANDLE m_timerHandle;
int sock;

int brokersock;

CO_CANrxMsg_t canpacket;

#define PACKED
#pragma pack(push,1)
typedef struct {
	uint16_t cob_id;	/**< message's ID */
	uint8_t rtr;		/**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
	uint8_t len;		/**< message's length (0 to 8) */
	uint8_t data[8]; /**< message's datas */
} Message;
#pragma pack(pop)
#undef PACKED


int count;


int nodeid = 1;

/* main ***********************************************************************/

int main(const int argc, const char **argv) {
	CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

	/* Configure microcontroller. */

	if (argc == 2)
	{
		sscanf_s(argv[1], "%d", &nodeid);
	}
	else
	{
		
		printf("Usage: CanOpenNodeWin32NanoMsg.exe <nodeid>\r\n");
		return;
	}

	//Use the node id from the command line

	printf("Starting on noide id %d\n", nodeid);
	CO_OD_ROM.CANNodeID = nodeid;

	//Create a nano msg socket.
	sock = nn_socket(AF_SP, NN_BUS);
	assert(sock >= 0);

	//Bind that socket to an address that is can_id<nodeid>
	//Every node requires one of these
	char ipcbuf[bufsize];
	sprintf_s(ipcbuf, bufsize, "ipc://can_id%d", nodeid);
	printf("Binding to %s\n", ipcbuf);
	assert(nn_bind(sock, ipcbuf) >= 0);

	
	//now try to connect to every other possible node, all 127 of them
	//but skip us
	for (int x=1; x < 127; x++)
	{
		if (x == nodeid)
			continue;

		sprintf_s(ipcbuf, bufsize, "ipc://can_id%d", x);
		printf("Connecting to %s\n", ipcbuf);
		assert(nn_connect(sock, ipcbuf) >= 0);
	}
	
	//Normal canopennode start up below
	

	/* initialize EEPROM */


	/* increase variable each startup. Variable is stored in EEPROM. */
	OD_powerOnCounter++;


	while (reset != CO_RESET_APP) {

		Sleep(0);



		/* CANopen communication reset - initialize CANopen objects *******************/
		CO_ReturnError_t err;
		uint16_t timer1msPrevious;

		/* disable CAN and CAN interrupts */


		/* initialize CANopen */
		err = CO_init(0/* CAN module address */, CO_OD_ROM.CANNodeID, 125 /* bit rate */);
		if (err != CO_ERROR_NO) {
			while (1);
			/* CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err); */
		}


		/* Configure Timer interrupt function for execution every 1 millisecond */

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


		/* Configure CAN transmit and receive interrupt */


		/* start CAN */
		CO_CANsetNormalMode(CO->CANmodule[0]);

		reset = CO_RESET_NOT;
		timer1msPrevious = CO_timer1ms;


		count = 0;
		while (reset == CO_RESET_NOT) {
			/* loop for normal program execution ******************************************/
			uint16_t timer1msCopy, timer1msDiff;

			timer1msCopy = CO_timer1ms;
			timer1msDiff = timer1msCopy - timer1msPrevious;
			timer1msPrevious = timer1msCopy;


			/* CANopen process */
			reset = CO_process(CO, timer1msDiff, NULL);

			/* Nonblocking application code may go here. */

			if (count == 100 && CO_OD_ROM.CANNodeID == 5)
			{
				//CO_OD_RAM.testX++;
				//count = 0;
			}
			/* Process EEPROM */
		}
	}


	/* program exit ***************************************************************/
	/* stop threads */


	/* delete objects from memory */
	CO_delete(0/* CAN module address */);


	/* reset */
	return 0;
}



/* timer thread executes in constant intervals ********************************/
void CALLBACK TimerProc(void* lpParametar,
	BOOLEAN TimerOrWaitFired) {

	count++;
	RxCanPacket();

	/* sleep for interval */

	INCREMENT_1MS(CO_timer1ms);

	if (CO->CANmodule[0]->CANnormal) {
		bool_t syncWas;

		/* Process Sync and read inputs */
		syncWas = CO_process_SYNC_RPDO(CO, TMR_TASK_INTERVAL);

		/* Further I/O or nonblocking application code may go here. */

		/* Write outputs */
		CO_process_TPDO(CO, syncWas, TMR_TASK_INTERVAL);

		/* verify timer overflow */
		if (0) {
			CO_errorReport(CO->em, CO_EM_ISR_TIMER_OVERFLOW, CO_EMC_SOFTWARE_INTERNAL, 0U);
		}
	}
}


/* CAN interrupt function *****************************************************/
void /* interrupt */ CO_CAN1InterruptHandler(void) {
	CO_CANinterrupt(CO->CANmodule[0]);


	/* clear interrupt flag */
}


void debugprintCanMessage(char * dir, Message * m)
{
#ifdef packetdebug
	char buf[bufsize];

	sprintf_s(buf, bufsize, "%s 0x%3x (%d) ",dir, m->cob_id, m->len);
	char * bufpos = buf;
	bufpos += strlen(dir)+11;

	for (int p = 0; p < m->len; p++)
	{
		sprintf_s(bufpos, bufsize - (bufpos - buf), "0x%02x ", m->data[p]);
		bufpos += 5;
	}

	sprintf_s(bufpos, bufsize - (bufpos - buf), "\r\n");


	printf(buf);
#endif

}

void WriteCanPacket(CO_CANtx_t * TxPacket)
{

	//printf("SEND TO BUS %x %x\n",TxPacket->ident, TxPacket->data[0]);
	//int send = nn_send(sock, TxPacket, sizeof(CO_CANtx_t), 0);

	Message m;

	memset(&m, 0, sizeof(Message));

	m.cob_id = TxPacket->ident & 0x0FFF; //0x1705
	m.len = (TxPacket->ident >> 12);

	for (int p = 0; p<m.len; p++)
		m.data[p] = TxPacket->data[p];

	m.rtr = 0;

	debugprintCanMessage("TX: ",&m);

	int send = nn_send(sock, &m, sizeof(Message), 0);

}


void RxCanPacket()
{

	Message m;

	int recv = nn_recv(sock, &m, sizeof(Message), NN_DONTWAIT);
	
	if (recv >= 0)
	{
#ifdef packetdebug

		memset(&canpacket, 0, sizeof(CO_CANtx_t));

		canpacket.ident = m.cob_id;
		canpacket.ident |= (m.len << 12);

		for (int p = 0; p < m.len; p++)
		{
			canpacket.data[p] = m.data[0];
		}

		canpacket.DLC = 0;
	
		debugprintCanMessage("RX: ", &m);

#endif

		CO_CANinterrupt(CO->CANmodule[0]);
	}

}



void SetCanFilter(uint32_t ident, uint32_t mask)
{

}

int getNoSupportedFilters()
{
	return 0;
}
