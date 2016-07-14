#pragma once

int open_port();
BOOL WriteABuffer(char * lpBuf, DWORD dwToWrite);


int getfreebufferspace();
void writebuffer(char * byte);
void HandleASuccessfulRead(char * lpBuf, DWORD dwRead);