#pragma once

#include <stdint.h>
#include <stdbool.h>

#define CALLBACK __stdcall
typedef HINSTANCE LIB_HANDLE;

//Gracefully borrowed these ideads from CanFestival

struct struct_s_BOARD {
	char * busname;  /**< The bus name on which the CAN board is connected */
	char * baudrate; /**< The board baudrate */
};

/**
* @brief The CAN message structure
* @ingroup can
*/
struct struct_s_Message {
	uint16_t cob_id;	/**< message's ID */
	uint8_t rtr;		/**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
	uint8_t len;		/**< message's length (0 to 8) */
	uint8_t data[8]; /**< message's datas */
};


typedef struct struct_s_Message s_Message;
typedef struct struct_s_BOARD s_BOARD;

typedef uint8_t(CALLBACK* CANRECEIVE_DRIVER_PROC)(void* inst, s_Message *m);
typedef uint8_t(CALLBACK* CANSEND_DRIVER_PROC)(void* inst, const s_Message *m);
typedef void* (CALLBACK* CANOPEN_DRIVER_PROC)(s_BOARD *board);
typedef int (CALLBACK* CANCLOSE_DRIVER_PROC)(void* inst);
typedef uint8_t(CALLBACK* CANCHANGEBAUDRATE_DRIVER_PROC)(void* fd, char* baud);
typedef uint16_t (CALLBACK* CANGETFILTERS_DRIVER_PROC)();
typedef void (CALLBACK* CANSETFILTER_DRIVER_PROC)(uint32_t ident, uint32_t mask);

typedef void (CALLBACK * CANREGRXCALLBACK)(CANRECEIVE_DRIVER_PROC rxproc);


LIB_HANDLE LoadCanDriver(LPCSTR driver_name);
int drv_open_port(char * bus, char * baud);
void drv_close_port();
