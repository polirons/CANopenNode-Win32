#pragma once

void programStart();
void communicationReset();
void programAsync(int timer1msDiff);
void programEnd();
void program1ms();

extern void(*CanOpen_Callback1ms)(void);
extern void(*CanOpen_CallbackprogramStart)(void);
extern void(*CanOpen_CallbackcommunicationReset)(void);
extern void(*CanOpen_CallbackprogramAsync)(void);
extern void(*CanOpen_CallbackprogramEnd)(void);
