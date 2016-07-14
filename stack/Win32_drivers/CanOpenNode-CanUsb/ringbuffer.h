
#pragma once

int getfreebufferspace();
void writebuffer(char * byte);
char readbuffer();
int peekbufferfindterminator();
bool isringfull();
void init_ringbuffer();