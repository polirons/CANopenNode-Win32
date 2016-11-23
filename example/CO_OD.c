/*******************************************************************************

   File - CO_OD.c/CO_OD.h
   CANopen Object Dictionary.

   Copyright (C) 2004-2008 Janez Paternoster

   License: GNU Lesser General Public License (LGPL).

   <http://canopennode.sourceforge.net>

   (For more information see <CO_SDO.h>.)
*/
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.


   Original Author: Janez Paternoster


   This file was automatically generated with libedssharp Object
   Dictionary Editor. DON'T EDIT THIS FILE MANUALLY !!!!

*******************************************************************************/


#include "CO_driver.h"
#include "CO_OD.h"
#include "CO_SDO.h"


/*******************************************************************************
   DEFINITION AND INITIALIZATION OF OBJECT DICTIONARY VARIABLES
*******************************************************************************/

/***** Definition for RAM variables *******************************************/
struct sCO_OD_RAM CO_OD_RAM = {
           CO_OD_FIRST_LAST_WORD,

/*1001*/ 0x0L,
/*1002*/ 0x0000L,
/*1003*/ {0, 0, 0, 0, 0, 0, 0, 0},
/*1010*/ {0x00000003},
/*1011*/ {0x00000001},
/*1280*/ {{3, 0, 0, 0}},
/*2100*/ 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L,
/*2103*/ 0x00,
/*2104*/ 0x00,
/*2107*/ {1000, 0, 0, 0, 0},
/*2108*/ {0},
/*2109*/ {0},
/*2110*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*2120*/ {0x5L, 0x1234567890abcdefL, 0x234567890abcdef1L, 12.345, 456.789, 0},
/*2130*/ {0x3L, {'-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', }, 0x00000000L, 0x0000L},
/*3000*/ {0x00, 0x00, 0x00, 0x00},
/*6000*/ {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
/*6200*/ {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
/*6401*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*6411*/ {0, 0, 0, 0, 0, 0, 0, 0},

           CO_OD_FIRST_LAST_WORD,
};

/***** Definition for EEPROM variables ****************************************/
struct sCO_OD_EEPROM CO_OD_EEPROM = {
           CO_OD_FIRST_LAST_WORD,

/*2106*/ 0x0000L,
/*2112*/ {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  CO_OD_FIRST_LAST_WORD,
};


/***** Definition for ROM variables *******************************************/
struct sCO_OD_ROM CO_OD_ROM = {    //constant variables, stored in flash
           CO_OD_FIRST_LAST_WORD,


/*1000*/ 0x0000L,
/*1005*/ 0x0080L,
/*1006*/ 0x0000L,
/*1007*/ 0x0000L,
/*1008*/ {'C', 'A', 'N', 'o', 'p', 'e', 'n', 'N', 'o', 'd', 'e', },
/*1009*/ {'3', '.', '0', '0', },
/*100a*/ {'3', '.', '0', '0', },
/*1014*/ 0x0080L,
/*1015*/ 0x64,
/*1016*/ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1017*/ 0x3e8,
/*1018*/ {4, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1019*/ 0x0L,
/*1029*/ {0x00, 0x00, 0x01, 0x00, 0x00, 0x00},
/*1200*/ {{2, 0x600, 0x580}},
/*1400*/ {{2, 0x282, 255},
/*1401*/ {2, 0x300, 254},
/*1402*/ {2, 0x400, 254},
/*1403*/ {2, 0x500, 254}},
/*1600*/ {{4, 0x30000110, 0x30000210, 0x30000310, 0x30000410, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1601*/ {0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1602*/ {0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1603*/ {0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}},
/*1800*/ {{6, 0x180, 255, 100, 0, 0, 0},
/*1801*/ {6, 0x280, 254, 0, 0, 0, 0},
/*1802*/ {6, 0x380, 254, 0, 0, 0, 0},
/*1803*/ {6, 0x480, 254, 0, 0, 0, 0}},
/*1a00*/ {{4, 0x30000110, 0x30000210, 0x30000310, 0x30000410, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1a01*/ {0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1a02*/ {0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1a03*/ {0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}},
/*1f80*/ 0x0001L,
/*2101*/ 0x30L,
/*2102*/ 0xfa,
/*2111*/ {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},


           CO_OD_FIRST_LAST_WORD
};


/*******************************************************************************
   STRUCTURES FOR RECORD TYPE OBJECTS
*******************************************************************************/


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
const CO_OD_entry_t CO_OD[66] = {

{0x1000, 0x00, 0x85, 4, (void*)&CO_OD_ROM.deviceType},
{0x1001, 0x00, 0x36, 1, (void*)&CO_OD_RAM.errorRegister},
{0x1002, 0x00, 0xb6, 4, (void*)&CO_OD_RAM.manufacturerStatusRegister},
{0x1003, 0x09, 0x86, 4, (void*)&CO_OD_RAM.preDefinedErrorField[0]},
{0x1005, 0x00, 0x8d, 4, (void*)&CO_OD_ROM.COB_ID_SYNCMessage},
{0x1006, 0x00, 0x8d, 4, (void*)&CO_OD_ROM.communicationCyclePeriod},
{0x1007, 0x00, 0x8d, 4, (void*)&CO_OD_ROM.synchronousWindowLength},
{0x1008, 0x00, 0x85, 11, (void*)&CO_OD_ROM.manufacturerDeviceName},
{0x1009, 0x00, 0x85, 4, (void*)&CO_OD_ROM.manufacturerHardwareVersion},
{0x100a, 0x00, 0x85, 4, (void*)&CO_OD_ROM.manufacturerSoftwareVersion},
{0x1010, 0x02, 0x8e, 4, (void*)&CO_OD_RAM.storeParameters[0]},
{0x1011, 0x02, 0x8e, 4, (void*)&CO_OD_RAM.restoreDefaultParameters[0]},
{0x1014, 0x00, 0x85, 4, (void*)&CO_OD_ROM.COB_ID_EMCY},
{0x1015, 0x00, 0x8d, 2, (void*)&CO_OD_ROM.inhibitTimeEMCY},
{0x1016, 0x05, 0x8d, 4, (void*)&CO_OD_ROM.consumerHeartbeatTime[0]},
{0x1017, 0x00, 0x8d, 2, (void*)&CO_OD_ROM.producerHeartbeatTime},
{0x1018, 0x05, 0x0d, 0, (void*)&CO_OD_ROM.identity},
{0x1019, 0x00, 0x0d, 1, (void*)&CO_OD_ROM.synchronousCounterOverflowValue},
{0x1029, 0x07, 0x0d, 1, (void*)&CO_OD_ROM.errorBehavior[0]},
{0x1200, 0x03, 0x0d, 0, (void*)&CO_OD_ROM.SDOServerParameter[0]},
{0x1280, 0x04, 0x0e, 0, (void*)&CO_OD_RAM.SDOClientParameter[0]},
{0x1400, 0x03, 0x0d, 0, (void*)&CO_OD_ROM.RPDOCommunicationParameter[0]},
{0x1401, 0x03, 0x0d, 0, (void*)&CO_OD_ROM.RPDOCommunicationParameter[1]},
{0x1402, 0x03, 0x0d, 0, (void*)&CO_OD_ROM.RPDOCommunicationParameter[2]},
{0x1403, 0x03, 0x0d, 0, (void*)&CO_OD_ROM.RPDOCommunicationParameter[3]},
{0x1600, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.RPDOMappingParameter[0]},
{0x1601, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.RPDOMappingParameter[1]},
{0x1602, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.RPDOMappingParameter[2]},
{0x1603, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.RPDOMappingParameter[3]},
{0x1800, 0x07, 0x0d, 0, (void*)&CO_OD_ROM.TPDOCommunicationParameter[0]},
{0x1801, 0x07, 0x0d, 0, (void*)&CO_OD_ROM.TPDOCommunicationParameter[1]},
{0x1802, 0x07, 0x0d, 0, (void*)&CO_OD_ROM.TPDOCommunicationParameter[2]},
{0x1803, 0x07, 0x0d, 0, (void*)&CO_OD_ROM.TPDOCommunicationParameter[3]},
{0x1a00, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.TPDOMappingParameter[0]},
{0x1a01, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.TPDOMappingParameter[1]},
{0x1a02, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.TPDOMappingParameter[2]},
{0x1a03, 0x09, 0x0d, 0, (void*)&CO_OD_ROM.TPDOMappingParameter[3]},
{0x1f80, 0x00, 0x8d, 4, (void*)&CO_OD_ROM.NMTStartup},
{0x2100, 0x00, 0xb6, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x2101, 0x00, 0x0d, 1, (void*)&CO_OD_ROM.CANNodeID},
{0x2102, 0x00, 0x8d, 2, (void*)&CO_OD_ROM.CANBitRate},
{0x2103, 0x00, 0x8e, 2, (void*)&CO_OD_RAM.SYNCCounter},
{0x2104, 0x00, 0x86, 2, (void*)&CO_OD_RAM.SYNCTime},
{0x2106, 0x00, 0x87, 4, (void*)&CO_OD_EEPROM.powerOnCounter},
{0x2107, 0x06, 0xbe, 2, (void*)&CO_OD_RAM.performance[0]},
{0x2108, 0x02, 0xb6, 2, (void*)&CO_OD_RAM.temperature[0]},
{0x2109, 0x02, 0xb6, 2, (void*)&CO_OD_RAM.voltage[0]},
{0x2110, 0x11, 0xbe, 4, (void*)&CO_OD_RAM.variableInt32[0]},
{0x2111, 0x11, 0xbd, 4, (void*)&CO_OD_ROM.variableROM_Int32[0]},
{0x2112, 0x11, 0xbf, 4, (void*)&CO_OD_EEPROM.variableNV_Int32[0]},
{0x2120, 0x06, 0x0e, 0, (void*)&CO_OD_RAM.testVar},
{0x2130, 0x04, 0x0e, 0, (void*)&CO_OD_RAM.time},
{0x3000, 0x05, 0xbe, 2, (void*)&CO_OD_RAM.tempsPDO[0]},
{0x6000, 0x09, 0x36, 1, (void*)&CO_OD_RAM.readInput8Bit[0]},
{0x6200, 0x09, 0x3e, 1, (void*)&CO_OD_RAM.writeOutput8Bit[0]},
{0x6401, 0x0d, 0xb6, 2, (void*)&CO_OD_RAM.readAnalogueInput16Bit[0]},
{0x6411, 0x09, 0xbe, 2, (void*)&CO_OD_RAM.writeAnalogueOutput16Bit[0]},
};
