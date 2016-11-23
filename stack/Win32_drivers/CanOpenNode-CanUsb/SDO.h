#pragma once

#include "libCanOpenNode.h"
#include <stdint.h>
#include <stdbool.h>

void canprocessSDOmaster(uint16_t time1msdiff);

CANOPENNODECANUSB_API int __stdcall SDOMasterWrite (uint8_t node, uint16_t index, uint8_t subindex, uint8_t * buffer, uint8_t len, timercallback func, abortcallback error);
CANOPENNODECANUSB_API int __stdcall SDOMasterRead  (uint8_t node, uint16_t index, uint8_t subindex, uint8_t * buffer, uint8_t len, timercallback funcL, abortcallback error);

CANOPENNODECANUSB_API void __stdcall SDOMasterFinish();
CANOPENNODECANUSB_API bool __stdcall SDOIsError();
CANOPENNODECANUSB_API bool __stdcall SDOIsIdle();



