// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBCANOPENNODE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBCANOPENNODE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBCANOPENNODE_EXPORTS
#define LIBCANOPENNODE_API __declspec(dllexport)
#else
#define LIBCANOPENNODE_API extern "C"  __declspec(dllimport)
#endif

//extern LIBCANOPENNODE_API int nlibCanOpenNode;

LIBCANOPENNODE_API int __stdcall initCanOpenNodeStack(void);
