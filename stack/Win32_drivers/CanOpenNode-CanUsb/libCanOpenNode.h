// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBCANOPENNODE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBCANOPENNODE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include <stdint.h>
#include <stdbool.h>

#ifdef CANOPENNODECANUSB_EXPORTS
#define CANOPENNODECANUSB_API __declspec(dllexport)
#else
#define CANOPENNODECANUSB_API extern "C"  __declspec(dllimport) 
#endif

// Main stack commands

CANOPENNODECANUSB_API int __stdcall initCanOpenNodeStack(char * driver,char * bus, char * baud);
CANOPENNODECANUSB_API int __stdcall closeCanOpenNodeStack(void);

//Callbacks 

typedef void(__stdcall *timercallback)(void);
typedef void(__stdcall *abortcallback)(uint32_t);
CANOPENNODECANUSB_API void __stdcall registerCallback1ms(timercallback fnptr);
CANOPENNODECANUSB_API void __stdcall registerCallbackprogramEnd(timercallback fnptr);
CANOPENNODECANUSB_API void __stdcall registerCallbackprogramAsync(timercallback fnptr);
CANOPENNODECANUSB_API void __stdcall registerCallbackcommunicationsReset(timercallback fnptr);
CANOPENNODECANUSB_API void __stdcall registerCallbackprogramStart(timercallback fnptr);

// NMT COMMANDS

CANOPENNODECANUSB_API void __stdcall NMT_BusPreoperational(void);
CANOPENNODECANUSB_API void __stdcall NMT_BusOperational(void);
CANOPENNODECANUSB_API void __stdcall NMT_BusResetCommunications(void);

//OD Access

CANOPENNODECANUSB_API void * __stdcall getODRAM();
CANOPENNODECANUSB_API void * __stdcall getODROM();
CANOPENNODECANUSB_API void * __stdcall getODEEPROM();


