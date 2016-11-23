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


#pragma once

/*******************************************************************************
   CANopen DATA DYPES
*******************************************************************************/
   typedef uint8_t      UNSIGNED8;
   typedef uint16_t     UNSIGNED16;
   typedef uint32_t     UNSIGNED32;
   typedef uint64_t     UNSIGNED64;
   typedef int8_t       INTEGER8;
   typedef int16_t      INTEGER16;
   typedef int32_t      INTEGER32;
   typedef int64_t      INTEGER64;
   typedef float32_t    REAL32;
   typedef float64_t    REAL64;
   typedef char_t       VISIBLE_STRING;
   typedef oChar_t      OCTET_STRING;
   typedef domain_t     DOMAIN;


/*******************************************************************************
   FILE INFO:
      FileName:     IO Example
      FileVersion:  0
      CreationTime: 18:04:29
      CreationDate: 2016-03-25
      CreatedBy:    JP
/******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     CANopenNode
      VendorNumber    0
      ProductName:    CANopenNode
      ProductNumber:  0
/******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
  #define CO_NO_SYNC                     1   //Associated objects: 1005-1007
  #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
  #define CO_NO_SDO_SERVER               1   //Associated objects: 1200-127F
  #define CO_NO_SDO_CLIENT               1   //Associated objects: 1280-12FF
  #define CO_NO_RPDO                     4   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     4   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               1


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             57


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;
/*1200    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               }              OD_SDOServerParameter_t;
/*1280    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOServer;
               }              OD_SDOClientParameter_t;
/*1400    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               }              OD_RPDOCommunicationParameter_t;
/*1600    */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_RPDOMappingParameter_t;
/*1800    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;
/*1a00    */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_TPDOMappingParameter_t;
/*2120    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER64      I64;
               UNSIGNED64     U64;
               REAL32         R32;
               REAL64         R64;
               DOMAIN         domain;
               }              OD_testVar_t;
/*2130    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               VISIBLE_STRING string[30];
               UNSIGNED64     epochTimeBaseMs;
               UNSIGNED32     epochTimeOffsetMs;
               }              OD_time_t;
/*2301    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     size;
               UNSIGNED8      axisNo;
               VISIBLE_STRING name[30];
               VISIBLE_STRING color[20];
               UNSIGNED32     map;
               UNSIGNED8      format;
               UNSIGNED8      trigger;
               INTEGER32      threshold;
               }              OD_traceConfig_t;
/*2401    */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     size;
               INTEGER32      value;
               INTEGER32      min;
               INTEGER32      max;
               DOMAIN         plot;
               UNSIGNED32     triggerTime;
               }              OD_trace_t;
/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1001      */ UNSIGNED8       errorRegister;
/*1002      */ UNSIGNED32      manufacturerStatusRegister;
/*1003      */ UNSIGNED32      preDefinedErrorField[8];
/*1010      */ UNSIGNED32      storeParameters[1];
/*1011      */ UNSIGNED32      restoreDefaultParameters[1];
/*1280      */ OD_SDOClientParameter_t SDOClientParameter[1];
/*2100      */ OCTET_STRING    errorStatusBits[10];
/*2103      */ UNSIGNED16      SYNCCounter;
/*2104      */ UNSIGNED16      SYNCTime;
/*2107      */ UNSIGNED16      performance[5];
/*2108      */ INTEGER16       temperature[1];
/*2109      */ INTEGER16       voltage[1];
/*2110      */ INTEGER32       variableInt32[16];
/*2120      */ OD_testVar_t    testVar;
/*2130      */ OD_time_t       time;
/*3000      */ INTEGER16       tempsPDO[4];
/*6000      */ UNSIGNED8       readInput8Bit[8];
/*6200      */ UNSIGNED8       writeOutput8Bit[8];
/*6401      */ INTEGER16       readAnalogueInput16Bit[12];
/*6411      */ INTEGER16       writeAnalogueOutput16Bit[8];

               UNSIGNED32     LastWord;
};
/***** Structure for EEPROM variables *****************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;



/*2106      */ UNSIGNED32      powerOnCounter;
/*2112      */ INTEGER32       variableNV_Int32[16];

               UNSIGNED32     LastWord;
};
/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;



/*1000      */ UNSIGNED32      deviceType;
/*1005      */ UNSIGNED32      COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32      communicationCyclePeriod;
/*1007      */ UNSIGNED32      synchronousWindowLength;
/*1008      */ VISIBLE_STRING  manufacturerDeviceName[11];
/*1009      */ VISIBLE_STRING  manufacturerHardwareVersion[4];
/*100a      */ VISIBLE_STRING  manufacturerSoftwareVersion[4];
/*1014      */ UNSIGNED32      COB_ID_EMCY;
/*1015      */ UNSIGNED16      inhibitTimeEMCY;
/*1016      */ UNSIGNED32      consumerHeartbeatTime[4];
/*1017      */ UNSIGNED16      producerHeartbeatTime;
/*1018      */ OD_identity_t   identity;
/*1019      */ UNSIGNED8       synchronousCounterOverflowValue;
/*1029      */ UNSIGNED8       errorBehavior[6];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[4];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[4];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[4];
/*1a00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[4];
/*1f80      */ UNSIGNED32      NMTStartup;
/*2101      */ UNSIGNED8       CANNodeID;
/*2102      */ UNSIGNED16      CANBitRate;
/*2111      */ INTEGER32       variableROM_Int32[16];

               UNSIGNED32     LastWord;
};
/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

extern struct sCO_OD_ROM CO_OD_ROM;


/*******************************************************************************
   ALIASES FOR OBJECT DICTIONARY VARIABLES
*******************************************************************************/
/*1000, Data Type: UNSIGNED32 */
        #define OD_deviceType                                      CO_OD_ROM.deviceType

/*1001, Data Type: UNSIGNED8 */
        #define OD_errorRegister                                   CO_OD_RAM.errorRegister

/*1002, Data Type: UNSIGNED32 */
        #define OD_manufacturerStatusRegister                      CO_OD_RAM.manufacturerStatusRegister

/*1003, Data Type: UNSIGNED32, Array[8] */
        #define OD_preDefinedErrorField                            CO_OD_RAM.preDefinedErrorField
        #define ODL_preDefinedErrorField_arrayLength               8

/*1005, Data Type: UNSIGNED32 */
        #define OD_COB_ID_SYNCMessage                              CO_OD_ROM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
        #define OD_communicationCyclePeriod                        CO_OD_ROM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
        #define OD_synchronousWindowLength                         CO_OD_ROM.synchronousWindowLength

/*1008, Data Type: VISIBLE_STRING */
        #define OD_manufacturerDeviceName                          CO_OD_ROM.manufacturerDeviceName
        #define ODL_manufacturerDeviceName_stringLength            11

/*1009, Data Type: VISIBLE_STRING */
        #define OD_manufacturerHardwareVersion                     CO_OD_ROM.manufacturerHardwareVersion
        #define ODL_manufacturerHardwareVersion_stringLength       4

/*100a, Data Type: VISIBLE_STRING */
        #define OD_manufacturerSoftwareVersion                     CO_OD_ROM.manufacturerSoftwareVersion
        #define ODL_manufacturerSoftwareVersion_stringLength       4

/*1010, Data Type: UNSIGNED32, Array[1] */
        #define OD_storeParameters                                 CO_OD_RAM.storeParameters
        #define ODL_storeParameters_arrayLength                    1
        #define ODA_storeParameters_saveAllParameters              0

/*1011, Data Type: UNSIGNED32, Array[1] */
        #define OD_restoreDefaultParameters                        CO_OD_RAM.restoreDefaultParameters
        #define ODL_restoreDefaultParameters_arrayLength           1
        #define ODA_restoreDefaultParameters_restoreAllDefaultParameters0

/*1014, Data Type: UNSIGNED32 */
        #define OD_COB_ID_EMCY                                     CO_OD_ROM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
        #define OD_inhibitTimeEMCY                                 CO_OD_ROM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[4] */
        #define OD_consumerHeartbeatTime                           CO_OD_ROM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength              4

/*1017, Data Type: UNSIGNED16 */
        #define OD_producerHeartbeatTime                           CO_OD_ROM.producerHeartbeatTime

/*1018, Data Type: UNKNOWN, Array[4] */
        #define OD_identity                                        CO_OD_ROM.identity
        #define ODL_identity_arrayLength                           4
        #define ODA_identity_vendorID                              1
        #define ODA_identity_productCode                           2
        #define ODA_identity_revisionNumber                        3
        #define ODA_identity_serialNumber                          4

/*1019, Data Type: UNSIGNED8 */
        #define OD_synchronousCounterOverflowValue                 CO_OD_ROM.synchronousCounterOverflowValue

/*1029, Data Type: UNSIGNED8, Array[6] */
        #define OD_errorBehavior                                   CO_OD_ROM.errorBehavior
        #define ODL_errorBehavior_arrayLength                      6
        #define ODA_errorBehavior_communication                    0
        #define ODA_errorBehavior_communicationOther               1
        #define ODA_errorBehavior_communicationPassive             2
        #define ODA_errorBehavior_generic                          3
        #define ODA_errorBehavior_deviceProfile                    4
        #define ODA_errorBehavior_manufacturerSpecific             5

/*1200, Data Type: UNKNOWN, Array[2] */
        #define OD_SDOServerParameter                              CO_OD_ROM.SDOServerParameter
        #define ODL_SDOServerParameter_arrayLength                 2
        #define ODA_SDOServerParameter_COB_IDClientToServer        1
        #define ODA_SDOServerParameter_COB_IDServerToClient        2

/*1280, Data Type: UNKNOWN, Array[3] */
        #define OD_SDOClientParameter                              CO_OD_RAM.SDOClientParameter
        #define ODL_SDOClientParameter_arrayLength                 3
        #define ODA_SDOClientParameter_COB_IDClientToServer        1
        #define ODA_SDOClientParameter_COB_IDServerToClient        2
        #define ODA_SDOClientParameter_nodeIDOfTheSDOServer        3

/*1400, Data Type: UNKNOWN, Array[2] */
        #define OD_RPDOCommunicationParameter                      CO_OD_ROM.RPDOCommunicationParameter
        #define ODL_RPDOCommunicationParameter_arrayLength         2
        #define ODA_RPDOCommunicationParameter_COB_IDUsedByRPDO    1
        #define ODA_RPDOCommunicationParameter_transmissionType    2

/*1401, Data Type: UNKNOWN, Array[2] */
        #define OD_RPDOCommunicationParameter                      CO_OD_ROM.RPDOCommunicationParameter
        #define ODL_RPDOCommunicationParameter_arrayLength         2
        #define ODA_RPDOCommunicationParameter_COB_IDUsedByRPDO    1
        #define ODA_RPDOCommunicationParameter_transmissionType    2

/*1402, Data Type: UNKNOWN, Array[2] */
        #define OD_RPDOCommunicationParameter                      CO_OD_ROM.RPDOCommunicationParameter
        #define ODL_RPDOCommunicationParameter_arrayLength         2
        #define ODA_RPDOCommunicationParameter_COB_IDUsedByRPDO    1
        #define ODA_RPDOCommunicationParameter_transmissionType    2

/*1403, Data Type: UNKNOWN, Array[2] */
        #define OD_RPDOCommunicationParameter                      CO_OD_ROM.RPDOCommunicationParameter
        #define ODL_RPDOCommunicationParameter_arrayLength         2
        #define ODA_RPDOCommunicationParameter_COB_IDUsedByRPDO    1
        #define ODA_RPDOCommunicationParameter_transmissionType    2

/*1404, Data Type: UNKNOWN, Array[2] */
        #define OD_RPDOCommunicationParameter                      CO_OD_ROM.RPDOCommunicationParameter
        #define ODL_RPDOCommunicationParameter_arrayLength         2
        #define ODA_RPDOCommunicationParameter_COB_IDUsedByRPDO    1
        #define ODA_RPDOCommunicationParameter_transmissionType    2

/*1600, Data Type: UNKNOWN, Array[8] */
        #define OD_RPDOMappingParameter                            CO_OD_ROM.RPDOMappingParameter
        #define ODL_RPDOMappingParameter_arrayLength               8
        #define ODA_RPDOMappingParameter_mappedObject1             1
        #define ODA_RPDOMappingParameter_mappedObject2             2
        #define ODA_RPDOMappingParameter_mappedObject3             3
        #define ODA_RPDOMappingParameter_mappedObject4             4
        #define ODA_RPDOMappingParameter_mappedObject5             5
        #define ODA_RPDOMappingParameter_mappedObject6             6
        #define ODA_RPDOMappingParameter_mappedObject7             7
        #define ODA_RPDOMappingParameter_mappedObject8             8

/*1601, Data Type: UNKNOWN, Array[8] */
        #define OD_RPDOMappingParameter                            CO_OD_ROM.RPDOMappingParameter
        #define ODL_RPDOMappingParameter_arrayLength               8
        #define ODA_RPDOMappingParameter_mappedObject1             1
        #define ODA_RPDOMappingParameter_mappedObject2             2
        #define ODA_RPDOMappingParameter_mappedObject3             3
        #define ODA_RPDOMappingParameter_mappedObject4             4
        #define ODA_RPDOMappingParameter_mappedObject5             5
        #define ODA_RPDOMappingParameter_mappedObject6             6
        #define ODA_RPDOMappingParameter_mappedObject7             7
        #define ODA_RPDOMappingParameter_mappedObject8             8

/*1602, Data Type: UNKNOWN, Array[8] */
        #define OD_RPDOMappingParameter                            CO_OD_ROM.RPDOMappingParameter
        #define ODL_RPDOMappingParameter_arrayLength               8
        #define ODA_RPDOMappingParameter_mappedObject1             1
        #define ODA_RPDOMappingParameter_mappedObject2             2
        #define ODA_RPDOMappingParameter_mappedObject3             3
        #define ODA_RPDOMappingParameter_mappedObject4             4
        #define ODA_RPDOMappingParameter_mappedObject5             5
        #define ODA_RPDOMappingParameter_mappedObject6             6
        #define ODA_RPDOMappingParameter_mappedObject7             7
        #define ODA_RPDOMappingParameter_mappedObject8             8

/*1603, Data Type: UNKNOWN, Array[8] */
        #define OD_RPDOMappingParameter                            CO_OD_ROM.RPDOMappingParameter
        #define ODL_RPDOMappingParameter_arrayLength               8
        #define ODA_RPDOMappingParameter_mappedObject1             1
        #define ODA_RPDOMappingParameter_mappedObject2             2
        #define ODA_RPDOMappingParameter_mappedObject3             3
        #define ODA_RPDOMappingParameter_mappedObject4             4
        #define ODA_RPDOMappingParameter_mappedObject5             5
        #define ODA_RPDOMappingParameter_mappedObject6             6
        #define ODA_RPDOMappingParameter_mappedObject7             7
        #define ODA_RPDOMappingParameter_mappedObject8             8

/*1604, Data Type: UNKNOWN, Array[8] */
        #define OD_RPDOMappingParameter                            CO_OD_ROM.RPDOMappingParameter
        #define ODL_RPDOMappingParameter_arrayLength               8
        #define ODA_RPDOMappingParameter_mappedObject1             1
        #define ODA_RPDOMappingParameter_mappedObject2             2
        #define ODA_RPDOMappingParameter_mappedObject3             3
        #define ODA_RPDOMappingParameter_mappedObject4             4
        #define ODA_RPDOMappingParameter_mappedObject5             5
        #define ODA_RPDOMappingParameter_mappedObject6             6
        #define ODA_RPDOMappingParameter_mappedObject7             7
        #define ODA_RPDOMappingParameter_mappedObject8             8

/*1800, Data Type: UNKNOWN, Array[6] */
        #define OD_TPDOCommunicationParameter                      CO_OD_ROM.TPDOCommunicationParameter
        #define ODL_TPDOCommunicationParameter_arrayLength         6
        #define ODA_TPDOCommunicationParameter_COB_IDUsedByTPDO    1
        #define ODA_TPDOCommunicationParameter_transmissionType    2
        #define ODA_TPDOCommunicationParameter_inhibitTime         3
        #define ODA_TPDOCommunicationParameter_compatibilityEntry  4
        #define ODA_TPDOCommunicationParameter_eventTimer          5
        #define ODA_TPDOCommunicationParameter_SYNCStartValue      6

/*1801, Data Type: UNKNOWN, Array[6] */
        #define OD_TPDOCommunicationParameter                      CO_OD_ROM.TPDOCommunicationParameter
        #define ODL_TPDOCommunicationParameter_arrayLength         6
        #define ODA_TPDOCommunicationParameter_COB_IDUsedByTPDO    1
        #define ODA_TPDOCommunicationParameter_transmissionType    2
        #define ODA_TPDOCommunicationParameter_inhibitTime         3
        #define ODA_TPDOCommunicationParameter_compatibilityEntry  4
        #define ODA_TPDOCommunicationParameter_eventTimer          5
        #define ODA_TPDOCommunicationParameter_SYNCStartValue      6

/*1802, Data Type: UNKNOWN, Array[6] */
        #define OD_TPDOCommunicationParameter                      CO_OD_ROM.TPDOCommunicationParameter
        #define ODL_TPDOCommunicationParameter_arrayLength         6
        #define ODA_TPDOCommunicationParameter_COB_IDUsedByTPDO    1
        #define ODA_TPDOCommunicationParameter_transmissionType    2
        #define ODA_TPDOCommunicationParameter_inhibitTime         3
        #define ODA_TPDOCommunicationParameter_compatibilityEntry  4
        #define ODA_TPDOCommunicationParameter_eventTimer          5
        #define ODA_TPDOCommunicationParameter_SYNCStartValue      6

/*1803, Data Type: UNKNOWN, Array[6] */
        #define OD_TPDOCommunicationParameter                      CO_OD_ROM.TPDOCommunicationParameter
        #define ODL_TPDOCommunicationParameter_arrayLength         6
        #define ODA_TPDOCommunicationParameter_COB_IDUsedByTPDO    1
        #define ODA_TPDOCommunicationParameter_transmissionType    2
        #define ODA_TPDOCommunicationParameter_inhibitTime         3
        #define ODA_TPDOCommunicationParameter_compatibilityEntry  4
        #define ODA_TPDOCommunicationParameter_eventTimer          5
        #define ODA_TPDOCommunicationParameter_SYNCStartValue      6

/*1804, Data Type: UNKNOWN, Array[6] */
        #define OD_TPDOCommunicationParameter                      CO_OD_ROM.TPDOCommunicationParameter
        #define ODL_TPDOCommunicationParameter_arrayLength         6
        #define ODA_TPDOCommunicationParameter_COB_IDUsedByTPDO    1
        #define ODA_TPDOCommunicationParameter_transmissionType    2
        #define ODA_TPDOCommunicationParameter_inhibitTime         3
        #define ODA_TPDOCommunicationParameter_compatibilityEntry  4
        #define ODA_TPDOCommunicationParameter_eventTimer          5
        #define ODA_TPDOCommunicationParameter_SYNCStartValue      6

/*1a00, Data Type: UNKNOWN, Array[8] */
        #define OD_TPDOMappingParameter                            CO_OD_ROM.TPDOMappingParameter
        #define ODL_TPDOMappingParameter_arrayLength               8
        #define ODA_TPDOMappingParameter_mappedObject1             1
        #define ODA_TPDOMappingParameter_mappedObject2             2
        #define ODA_TPDOMappingParameter_mappedObject3             3
        #define ODA_TPDOMappingParameter_mappedObject4             4
        #define ODA_TPDOMappingParameter_mappedObject5             5
        #define ODA_TPDOMappingParameter_mappedObject6             6
        #define ODA_TPDOMappingParameter_mappedObject7             7
        #define ODA_TPDOMappingParameter_mappedObject8             8

/*1a01, Data Type: UNKNOWN, Array[8] */
        #define OD_TPDOMappingParameter                            CO_OD_ROM.TPDOMappingParameter
        #define ODL_TPDOMappingParameter_arrayLength               8
        #define ODA_TPDOMappingParameter_mappedObject1             1
        #define ODA_TPDOMappingParameter_mappedObject2             2
        #define ODA_TPDOMappingParameter_mappedObject3             3
        #define ODA_TPDOMappingParameter_mappedObject4             4
        #define ODA_TPDOMappingParameter_mappedObject5             5
        #define ODA_TPDOMappingParameter_mappedObject6             6
        #define ODA_TPDOMappingParameter_mappedObject7             7
        #define ODA_TPDOMappingParameter_mappedObject8             8

/*1a02, Data Type: UNKNOWN, Array[8] */
        #define OD_TPDOMappingParameter                            CO_OD_ROM.TPDOMappingParameter
        #define ODL_TPDOMappingParameter_arrayLength               8
        #define ODA_TPDOMappingParameter_mappedObject1             1
        #define ODA_TPDOMappingParameter_mappedObject2             2
        #define ODA_TPDOMappingParameter_mappedObject3             3
        #define ODA_TPDOMappingParameter_mappedObject4             4
        #define ODA_TPDOMappingParameter_mappedObject5             5
        #define ODA_TPDOMappingParameter_mappedObject6             6
        #define ODA_TPDOMappingParameter_mappedObject7             7
        #define ODA_TPDOMappingParameter_mappedObject8             8

/*1a03, Data Type: UNKNOWN, Array[8] */
        #define OD_TPDOMappingParameter                            CO_OD_ROM.TPDOMappingParameter
        #define ODL_TPDOMappingParameter_arrayLength               8
        #define ODA_TPDOMappingParameter_mappedObject1             1
        #define ODA_TPDOMappingParameter_mappedObject2             2
        #define ODA_TPDOMappingParameter_mappedObject3             3
        #define ODA_TPDOMappingParameter_mappedObject4             4
        #define ODA_TPDOMappingParameter_mappedObject5             5
        #define ODA_TPDOMappingParameter_mappedObject6             6
        #define ODA_TPDOMappingParameter_mappedObject7             7
        #define ODA_TPDOMappingParameter_mappedObject8             8

/*1a04, Data Type: UNKNOWN, Array[8] */
        #define OD_TPDOMappingParameter                            CO_OD_ROM.TPDOMappingParameter
        #define ODL_TPDOMappingParameter_arrayLength               8
        #define ODA_TPDOMappingParameter_mappedObject1             1
        #define ODA_TPDOMappingParameter_mappedObject2             2
        #define ODA_TPDOMappingParameter_mappedObject3             3
        #define ODA_TPDOMappingParameter_mappedObject4             4
        #define ODA_TPDOMappingParameter_mappedObject5             5
        #define ODA_TPDOMappingParameter_mappedObject6             6
        #define ODA_TPDOMappingParameter_mappedObject7             7
        #define ODA_TPDOMappingParameter_mappedObject8             8

/*1f80, Data Type: UNSIGNED32 */
        #define OD_NMTStartup                                      CO_OD_ROM.NMTStartup

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                 CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                   10

/*2101, Data Type: UNSIGNED8 */
        #define OD_CANNodeID                                       CO_OD_ROM.CANNodeID

/*2102, Data Type: UNSIGNED16 */
        #define OD_CANBitRate                                      CO_OD_ROM.CANBitRate

/*2103, Data Type: UNSIGNED16 */
        #define OD_SYNCCounter                                     CO_OD_RAM.SYNCCounter

/*2104, Data Type: UNSIGNED16 */
        #define OD_SYNCTime                                        CO_OD_RAM.SYNCTime

/*2106, Data Type: UNSIGNED32 */
        #define OD_powerOnCounter                                  CO_OD_EEPROM.powerOnCounter

/*2107, Data Type: UNSIGNED16, Array[5] */
        #define OD_performance                                     CO_OD_RAM.performance
        #define ODL_performance_arrayLength                        5
        #define ODA_performance_cyclesPerSecond                    0
        #define ODA_performance_timerCycleTime                     1
        #define ODA_performance_timerCycleMaxTime                  2
        #define ODA_performance_mainCycleTime                      3
        #define ODA_performance_mainCycleMaxTime                   4

/*2108, Data Type: INTEGER16, Array[1] */
        #define OD_temperature                                     CO_OD_RAM.temperature
        #define ODL_temperature_arrayLength                        1
        #define ODA_temperature_mainPCB                            0

/*2109, Data Type: INTEGER16, Array[1] */
        #define OD_voltage                                         CO_OD_RAM.voltage
        #define ODL_voltage_arrayLength                            1
        #define ODA_voltage_mainPCBSupply                          0

/*2110, Data Type: INTEGER32, Array[16] */
        #define OD_variableInt32                                   CO_OD_RAM.variableInt32
        #define ODL_variableInt32_arrayLength                      16

/*2111, Data Type: INTEGER32, Array[16] */
        #define OD_variableROM_Int32                               CO_OD_ROM.variableROM_Int32
        #define ODL_variableROM_Int32_arrayLength                  16

/*2112, Data Type: INTEGER32, Array[16] */
        #define OD_variableNV_Int32                                CO_OD_EEPROM.variableNV_Int32
        #define ODL_variableNV_Int32_arrayLength                   16

/*2120, Data Type: UNKNOWN, Array[5] */
        #define OD_testVar                                         CO_OD_RAM.testVar
        #define ODL_testVar_arrayLength                            5
        #define ODA_testVar_I64                                    1
        #define ODA_testVar_U64                                    2
        #define ODA_testVar_R32                                    3
        #define ODA_testVar_R64                                    4
        #define ODA_testVar_domain                                 5

/*2130, Data Type: UNKNOWN, Array[3] */
        #define OD_time                                            CO_OD_RAM.time
        #define ODL_time_arrayLength                               3
        #define ODA_time_string                                    1
        #define ODA_time_epochTimeBaseMs                           2
        #define ODA_time_epochTimeOffsetMs                         3

/*2301, Data Type: UNKNOWN, Array[8] */
        #define OD_traceConfig                                     CO_OD_ROM.traceConfig
        #define ODL_traceConfig_arrayLength                        8
        #define ODA_traceConfig_size                               1
        #define ODA_traceConfig_axisNo                             2
        #define ODA_traceConfig_name                               3
        #define ODA_traceConfig_color                              4
        #define ODA_traceConfig_map                                5
        #define ODA_traceConfig_format                             6
        #define ODA_traceConfig_trigger                            7
        #define ODA_traceConfig_threshold                          8

/*2302, Data Type: UNKNOWN, Array[8] */
        #define OD_traceConfig                                     CO_OD_ROM.traceConfig
        #define ODL_traceConfig_arrayLength                        8
        #define ODA_traceConfig_size                               1
        #define ODA_traceConfig_axisNo                             2
        #define ODA_traceConfig_name                               3
        #define ODA_traceConfig_color                              4
        #define ODA_traceConfig_map                                5
        #define ODA_traceConfig_format                             6
        #define ODA_traceConfig_trigger                            7
        #define ODA_traceConfig_threshold                          8

/*2400, Data Type: UNSIGNED8 */
        #define OD_traceEnable                                     CO_OD_RAM.traceEnable

/*2401, Data Type: UNKNOWN, Array[6] */
        #define OD_trace                                           CO_OD_RAM.trace
        #define ODL_trace_arrayLength                              6
        #define ODA_trace_size                                     1
        #define ODA_trace_value                                    2
        #define ODA_trace_min                                      3
        #define ODA_trace_max                                      4
        #define ODA_trace_plot                                     5
        #define ODA_trace_triggerTime                              6

/*2402, Data Type: UNKNOWN, Array[6] */
        #define OD_trace                                           CO_OD_RAM.trace
        #define ODL_trace_arrayLength                              6
        #define ODA_trace_size                                     1
        #define ODA_trace_value                                    2
        #define ODA_trace_min                                      3
        #define ODA_trace_max                                      4
        #define ODA_trace_plot                                     5
        #define ODA_trace_triggerTime                              6

/*3000, Data Type: INTEGER16, Array[4] */
        #define OD_tempsPDO                                        CO_OD_RAM.tempsPDO
        #define ODL_tempsPDO_arrayLength                           4
        #define ODA_tempsPDO_temp1                                 0
        #define ODA_tempsPDO_temp2                                 1
        #define ODA_tempsPDO_temp3                                 2
        #define ODA_tempsPDO_temp4                                 3

/*6000, Data Type: UNSIGNED8, Array[8] */
        #define OD_readInput8Bit                                   CO_OD_RAM.readInput8Bit
        #define ODL_readInput8Bit_arrayLength                      8

/*6200, Data Type: UNSIGNED8, Array[8] */
        #define OD_writeOutput8Bit                                 CO_OD_RAM.writeOutput8Bit
        #define ODL_writeOutput8Bit_arrayLength                    8

/*6401, Data Type: INTEGER16, Array[12] */
        #define OD_readAnalogueInput16Bit                          CO_OD_RAM.readAnalogueInput16Bit
        #define ODL_readAnalogueInput16Bit_arrayLength             12

/*6411, Data Type: INTEGER16, Array[8] */
        #define OD_writeAnalogueOutput16Bit                        CO_OD_RAM.writeAnalogueOutput16Bit
        #define ODL_writeAnalogueOutput16Bit_arrayLength           8

