#pragma once

extern CO_CANrxMsg_t canpacket;
void WriteCanPacket(CO_CANtx_t * TxPacket);
void SetCanFilter(uint32_t ident,uint32_t mask);
int getNoSupportedFilters();