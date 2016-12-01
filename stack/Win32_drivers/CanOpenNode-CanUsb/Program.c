#include "windows.h"
#include "libCanOpenNode.h"
#include "CANopen.h"
#include "program.h"
#include "SDO.h"

void(*CanOpen_CallbackprogramStart)(void) = NULL;
void(*CanOpen_CallbackcommunicationReset)(void) = NULL;
void(*CanOpen_CallbackprogramAsync)(void) = NULL;
void(*CanOpen_CallbackprogramEnd)(void) = NULL;
void(*CanOpen_Callback1ms)(void) = NULL;

void programStart()
{
	if (CanOpen_CallbackprogramStart != NULL)
	{
		CanOpen_CallbackprogramStart();
	}
}

void communicationReset()
{
	if (CanOpen_CallbackcommunicationReset != NULL)
	{
		CanOpen_CallbackcommunicationReset();
	}
}

void programAsync(int timer1msDiff)
{	
	if (CanOpen_CallbackprogramAsync != NULL)
	{
		CanOpen_CallbackprogramAsync();
	}
}

void programEnd()
{
	if (CanOpen_CallbackprogramEnd != NULL)
	{
		CanOpen_CallbackprogramEnd();
	}
}

void program1ms()
{
	if (CanOpen_Callback1ms != NULL)
	{
		CanOpen_Callback1ms();
	}
}