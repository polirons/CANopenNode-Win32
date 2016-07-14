
#include "libCanOpenNode.h"
#include "CANopen.h"

CANOPENNODECANUSB_API void NMT_BusOperational()
{
	CO_sendNMTcommand(CO, CO_NMT_ENTER_OPERATIONAL, 0);
}

CANOPENNODECANUSB_API void NMT_BusPreoperational()
{
	CO_sendNMTcommand(CO, CO_NMT_ENTER_PRE_OPERATIONAL, 0);
}

CANOPENNODECANUSB_API void NMT_BusResetCommunications()
{
	CO_sendNMTcommand(CO, CO_NMT_RESET_COMMUNICATION, 0);
}