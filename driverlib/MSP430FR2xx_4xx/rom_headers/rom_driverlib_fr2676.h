//*****************************************************************************
//
// rom_driverlib_fr2676.h 
// Macros to facilitate calling functions in the ROM for
// MSP430FR2676, MSP430FR2675, MSP430FR2673, MSP430FR2672
//
// Copyright (c) 2018 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************

#if defined(__TI_COMPILER_VERSION__)
#if __TI_COMPILER_VERSION__ >= 18001001
#define __cc_rom __attribute__((call_conv("cc_rom")))
#else
#error "The cc_rom attribute requires MSP TI COMPILER 18.1.1.LTS or more recent."
#endif  // __TI_COMPILER_VERSION__ >= 
#endif  // (defined(__TI_COMPILER_VERSION__))18001001

#if __REGISTER_R4__ != __REGISTER_FREE__
#error "Incorrect setting for R4, expected it to be free."
#endif

#if __REGISTER_R5__ != __REGISTER_FREE__
#error "Incorrect setting for R5, expected it to be free."
#endif

// Suppress type conversion warning
#ifdef __TI_COMPILER_VERSION__
#pragma diag_suppress 173
#endif

#if (defined(__TI_COMPILER_VERSION__) && !defined(__LARGE_DATA_MODEL__)) || \
(defined(__IAR_SYSTEMS_ICC__) && (__DATA_MODEL__!=__DATA_MODEL_LARGE__))
#error "Only large data model supported for this ROM."
#endif

#ifndef __ROM_DRIVERLIB_H__
#define __ROM_DRIVERLIB_H__

#if (defined(__TI_COMPILER_VERSION__) && defined(__LARGE_CODE_MODEL__)) || \
   (defined(__IAR_SYSTEMS_ICC__) && (__CODE_MODEL__==__CODE_MODEL_LARGE__))
//*****************************************************************************
//
// Pointer to the main API tables.
//
//*****************************************************************************
#ifndef ROM_TABLE
#define ROM_TABLE                      ((uint32_t *)ROMLIB_START)
#endif
#define ROM_DRIVERLIB_APITABLE         ((uint32_t *)ROM_TABLE[1])
#define ROM_DRIVERLIB_VERSION          ((uint32_t)ROM_DRIVERLIB_APITABLE[0])
#define ROM_CSTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[1]))
#define ROM_EUSCI_A_SPITABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[2]))
#define ROM_EUSCI_A_UARTTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[3]))
#define ROM_EUSCI_B_I2CTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[4]))
#define ROM_EUSCI_B_SPITABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[5]))
#define ROM_GPIOTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[6]))
#define ROM_PMMTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[7]))
#define ROM_SFRTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[8]))
#define ROM_SYSCTLTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[9]))
#define ROM_TIMER_BTABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[10]))
#define ROM_WDT_ATABLE        ((uint32_t *)(ROM_DRIVERLIB_APITABLE[11]))

#define ROM_DRIVERLIB_getVersion()     ((uint32_t)(ROM_DRIVERLIB_VERSION))
#ifndef ROM_getVersion
#define ROM_getVersion()               ((uint32_t)(ROMLIB_START[0]))
#endif
//*****************************************************************************
//
// Macros for calling ROM functions in the CS API.
//
//*****************************************************************************
#define ROM_CS_initClockSignal	\
     ((void (__cc_rom *)( uint8_t selectedClockSignal,	\
                               uint16_t clockSource,	\
                               uint16_t clockSourceDivider))ROM_CSTABLE[0])
#define ROM_CS_turnOnXT1LF	\
     ((void (__cc_rom *)( uint16_t xt1Drive))ROM_CSTABLE[1])
#define ROM_CS_bypassXT1	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[2])
#define ROM_CS_turnOnXT1LFWithTimeout	\
     ((bool (__cc_rom *)( uint16_t xt1Drive,	\
                                      uint16_t timeout))ROM_CSTABLE[3])
#define ROM_CS_bypassXT1WithTimeout	\
     ((bool (__cc_rom *)( uint16_t timeout))ROM_CSTABLE[4])
#define ROM_CS_turnOffXT1	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[5])
#define ROM_CS_turnOnXT1HF	\
     ((void (__cc_rom *)( uint16_t xt1Drive,	\
                           uint16_t xt1HFFreq))ROM_CSTABLE[6])
#define ROM_CS_turnOnXT1HFWithTimeout	\
     ((bool (__cc_rom *)( uint16_t xt1Drive,	\
                                      uint16_t xt1HFFreq,	\
                                      uint16_t timeout))ROM_CSTABLE[7])
#define ROM_CS_turnOnSMCLK	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[8])
#define ROM_CS_turnOffSMCLK	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[9])
#define ROM_CS_enableVLOAutoOff	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[10])
#define ROM_CS_disableVLOAutoOff	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[11])
#define ROM_CS_initFLLSettle	\
     ((bool (__cc_rom *)( uint16_t fsystem,	\
                             uint16_t ratio))ROM_CSTABLE[12])
/* Removed due to bug fix for MSPDVRLIB-185
#define ROM_CS_initFLL	\
     ((bool (__cc_rom *)( uint16_t fsystem,	\
                       uint16_t ratio))ROM_CSTABLE[13])
*/
/* Removed due to bug fix for MSPDVRLIB-185
#define ROM_CS_initFLLLoadTrim	\
     ((bool (__cc_rom *)( uint16_t fsystem,	\
                               uint16_t ratio,	\
                               CS_initFLLParam *param))ROM_CSTABLE[14])
*/
#define ROM_CS_enableClockRequest	\
     ((void (__cc_rom *)( uint8_t selectClock))ROM_CSTABLE[15])
#define ROM_CS_disableClockRequest	\
     ((void (__cc_rom *)( uint8_t selectClock))ROM_CSTABLE[16])
#define ROM_CS_getFaultFlagStatus	\
     ((uint8_t (__cc_rom *)( uint8_t mask))ROM_CSTABLE[17])
#define ROM_CS_clearFaultFlag	\
     ((void (__cc_rom *)( uint8_t mask))ROM_CSTABLE[18])
#define ROM_CS_clearAllOscFlagsWithTimeout	\
     ((uint16_t (__cc_rom *)( uint16_t timeout))ROM_CSTABLE[19])
#define ROM_CS_enableXT1AutomaticGainControl	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[20])
#define ROM_CS_disableXT1AutomaticGainControl	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[21])
#define ROM_CS_enableFLLUnlock	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[22])
#define ROM_CS_disableFLLUnlock	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[23])
#define ROM_CS_enableREFOLP	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[24])
#define ROM_CS_disableREFOLP	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[25])
#define ROM_CS_getREFOLP	\
     ((bool (__cc_rom *)( void))ROM_CSTABLE[26])
#define ROM_CS_enableXT1FaultOff	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[27])
#define ROM_CS_disableXT1FaultOff	\
     ((void (__cc_rom *)( void))ROM_CSTABLE[28])
#define ROM_CS_getXT1FaultOff	\
     ((bool (__cc_rom *)( void))ROM_CSTABLE[29])
#define ROM_CS_getREFOReady	\
     ((bool (__cc_rom *)( void))ROM_CSTABLE[30])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCI_A_SPI API.
//
//*****************************************************************************
#define ROM_EUSCI_A_SPI_initMaster	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                   EUSCI_A_SPI_initMasterParam *param))ROM_EUSCI_A_SPITABLE[0])
#define ROM_EUSCI_A_SPI_select4PinFunctionality	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                uint8_t select4PinFunctionality))ROM_EUSCI_A_SPITABLE[1])
#define ROM_EUSCI_A_SPI_changeMasterClock	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                          EUSCI_A_SPI_changeMasterClockParam *param))ROM_EUSCI_A_SPITABLE[2])
#define ROM_EUSCI_A_SPI_initSlave	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                  EUSCI_A_SPI_initSlaveParam *param))ROM_EUSCI_A_SPITABLE[3])
#define ROM_EUSCI_A_SPI_changeClockPhasePolarity	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                 uint16_t clockPhase,	\
                                                 uint16_t clockPolarity))ROM_EUSCI_A_SPITABLE[4])
#define ROM_EUSCI_A_SPI_transmitData	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                     uint8_t transmitData))ROM_EUSCI_A_SPITABLE[5])
#define ROM_EUSCI_A_SPI_receiveData	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_SPITABLE[6])
#define ROM_EUSCI_A_SPI_enableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                        uint8_t mask))ROM_EUSCI_A_SPITABLE[7])
#define ROM_EUSCI_A_SPI_disableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                         uint8_t mask))ROM_EUSCI_A_SPITABLE[8])
#define ROM_EUSCI_A_SPI_getInterruptStatus	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress,	\
                                              uint8_t mask))ROM_EUSCI_A_SPITABLE[9])
#define ROM_EUSCI_A_SPI_clearInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                       uint8_t mask))ROM_EUSCI_A_SPITABLE[10])
#define ROM_EUSCI_A_SPI_enable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_SPITABLE[11])
#define ROM_EUSCI_A_SPI_disable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_SPITABLE[12])
#define ROM_EUSCI_A_SPI_getReceiveBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_SPITABLE[13])
#define ROM_EUSCI_A_SPI_getTransmitBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_SPITABLE[14])
#define ROM_EUSCI_A_SPI_isBusy	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_SPITABLE[15])
#define ROM_EUSCI_A_SPI_remapPins	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                  uint8_t pinsSelect))ROM_EUSCI_A_SPITABLE[16])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCI_A_UART API.
//
//*****************************************************************************
#define ROM_EUSCI_A_UART_init	\
     ((bool (__cc_rom *)( uint16_t baseAddress,	\
                              EUSCI_A_UART_initParam *param))ROM_EUSCI_A_UARTTABLE[0])
#define ROM_EUSCI_A_UART_transmitData	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                      uint8_t transmitData))ROM_EUSCI_A_UARTTABLE[1])
#define ROM_EUSCI_A_UART_receiveData	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[2])
#define ROM_EUSCI_A_UART_enableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                         uint8_t mask))ROM_EUSCI_A_UARTTABLE[3])
#define ROM_EUSCI_A_UART_disableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                          uint8_t mask))ROM_EUSCI_A_UARTTABLE[4])
#define ROM_EUSCI_A_UART_getInterruptStatus	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress,	\
                                               uint8_t mask))ROM_EUSCI_A_UARTTABLE[5])
#define ROM_EUSCI_A_UART_clearInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                        uint8_t mask))ROM_EUSCI_A_UARTTABLE[6])
#define ROM_EUSCI_A_UART_enable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[7])
#define ROM_EUSCI_A_UART_disable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[8])
#define ROM_EUSCI_A_UART_queryStatusFlags	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress,	\
                                             uint8_t mask))ROM_EUSCI_A_UARTTABLE[9])
#define ROM_EUSCI_A_UART_setDormant	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[10])
#define ROM_EUSCI_A_UART_resetDormant	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[11])
#define ROM_EUSCI_A_UART_transmitAddress	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                         uint8_t transmitAddress))ROM_EUSCI_A_UARTTABLE[12])
#define ROM_EUSCI_A_UART_transmitBreak	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[13])
#define ROM_EUSCI_A_UART_getReceiveBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[14])
#define ROM_EUSCI_A_UART_getTransmitBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_A_UARTTABLE[15])
#define ROM_EUSCI_A_UART_selectDeglitchTime	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                            uint16_t deglitchTime))ROM_EUSCI_A_UARTTABLE[16])
#define ROM_EUSCI_A_UART_remapPins	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                   uint8_t pinsSelect))ROM_EUSCI_A_UARTTABLE[17])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCI_B_I2C API.
//
//*****************************************************************************
#define ROM_EUSCI_B_I2C_initMaster	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                   EUSCI_B_I2C_initMasterParam *param))ROM_EUSCI_B_I2CTABLE[0])
#define ROM_EUSCI_B_I2C_initSlave	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                  EUSCI_B_I2C_initSlaveParam *param))ROM_EUSCI_B_I2CTABLE[1])
#define ROM_EUSCI_B_I2C_enable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[2])
#define ROM_EUSCI_B_I2C_disable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[3])
#define ROM_EUSCI_B_I2C_setSlaveAddress	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                        uint8_t slaveAddress))ROM_EUSCI_B_I2CTABLE[4])
#define ROM_EUSCI_B_I2C_setMode	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                uint8_t mode))ROM_EUSCI_B_I2CTABLE[5])
#define ROM_EUSCI_B_I2C_getMode	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[6])
#define ROM_EUSCI_B_I2C_slavePutData	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                     uint8_t transmitData))ROM_EUSCI_B_I2CTABLE[7])
#define ROM_EUSCI_B_I2C_slaveGetData	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[8])
#define ROM_EUSCI_B_I2C_isBusBusy	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[9])
#define ROM_EUSCI_B_I2C_masterIsStopSent	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[10])
#define ROM_EUSCI_B_I2C_masterIsStartSent	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[11])
#define ROM_EUSCI_B_I2C_enableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                        uint16_t mask))ROM_EUSCI_B_I2CTABLE[12])
#define ROM_EUSCI_B_I2C_disableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                         uint16_t mask))ROM_EUSCI_B_I2CTABLE[13])
#define ROM_EUSCI_B_I2C_clearInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                       uint16_t mask))ROM_EUSCI_B_I2CTABLE[14])
#define ROM_EUSCI_B_I2C_getInterruptStatus	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress,	\
                                               uint16_t mask))ROM_EUSCI_B_I2CTABLE[15])
#define ROM_EUSCI_B_I2C_masterSendSingleByte	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                             uint8_t txData))ROM_EUSCI_B_I2CTABLE[16])
#define ROM_EUSCI_B_I2C_masterReceiveSingleByte	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[17])
#define ROM_EUSCI_B_I2C_masterSendSingleByteWithTimeout	\
     ((bool (__cc_rom *)( uint16_t baseAddress,	\
                                                        uint8_t txData,	\
                                                        uint32_t timeout))ROM_EUSCI_B_I2CTABLE[18])
#define ROM_EUSCI_B_I2C_masterSendMultiByteStart	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                 uint8_t txData))ROM_EUSCI_B_I2CTABLE[19])
#define ROM_EUSCI_B_I2C_masterSendMultiByteStartWithTimeout	\
     ((bool (__cc_rom *)( uint16_t baseAddress,	\
                                                            uint8_t txData,	\
                                                            uint32_t timeout))ROM_EUSCI_B_I2CTABLE[20])
#define ROM_EUSCI_B_I2C_masterSendMultiByteNext	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                uint8_t txData))ROM_EUSCI_B_I2CTABLE[21])
#define ROM_EUSCI_B_I2C_masterSendMultiByteNextWithTimeout	\
     ((bool (__cc_rom *)( uint16_t baseAddress,	\
                                                           uint8_t txData,	\
                                                           uint32_t timeout))ROM_EUSCI_B_I2CTABLE[22])
#define ROM_EUSCI_B_I2C_masterSendMultiByteFinish	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                  uint8_t txData))ROM_EUSCI_B_I2CTABLE[23])
#define ROM_EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout	\
     ((bool (__cc_rom *)( uint16_t baseAddress,	\
                                                             uint8_t txData,	\
                                                             uint32_t timeout))ROM_EUSCI_B_I2CTABLE[24])
#define ROM_EUSCI_B_I2C_masterSendStart	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[25])
#define ROM_EUSCI_B_I2C_masterSendMultiByteStop	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[26])
#define ROM_EUSCI_B_I2C_masterReceiveStart	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[27])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteNext	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[28])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteFinish	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[29])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout	\
     ((bool (__cc_rom *)( uint16_t baseAddress,	\
                                                                uint8_t *txData,	\
                                                                uint32_t timeout))ROM_EUSCI_B_I2CTABLE[30])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteStop	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[31])
#define ROM_EUSCI_B_I2C_enableMultiMasterMode	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[32])
#define ROM_EUSCI_B_I2C_disableMultiMasterMode	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[33])
#define ROM_EUSCI_B_I2C_masterReceiveSingle	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[34])
#define ROM_EUSCI_B_I2C_getReceiveBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[35])
#define ROM_EUSCI_B_I2C_getTransmitBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_I2CTABLE[36])
#define ROM_EUSCI_B_I2C_remapPins	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                  uint8_t pinsSelect))ROM_EUSCI_B_I2CTABLE[37])
#define ROM_EUSCI_B_I2C_setTimeout	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                   uint16_t timeout))ROM_EUSCI_B_I2CTABLE[38])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCI_B_SPI API.
//
//*****************************************************************************
#define ROM_EUSCI_B_SPI_initMaster	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                   EUSCI_B_SPI_initMasterParam *param))ROM_EUSCI_B_SPITABLE[0])
#define ROM_EUSCI_B_SPI_select4PinFunctionality	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                uint8_t select4PinFunctionality))ROM_EUSCI_B_SPITABLE[1])
#define ROM_EUSCI_B_SPI_changeMasterClock	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                          EUSCI_B_SPI_changeMasterClockParam *param))ROM_EUSCI_B_SPITABLE[2])
#define ROM_EUSCI_B_SPI_initSlave	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                  EUSCI_B_SPI_initSlaveParam *param))ROM_EUSCI_B_SPITABLE[3])
#define ROM_EUSCI_B_SPI_changeClockPhasePolarity	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                 uint16_t clockPhase,	\
                                                 uint16_t clockPolarity))ROM_EUSCI_B_SPITABLE[4])
#define ROM_EUSCI_B_SPI_transmitData	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                     uint8_t transmitData))ROM_EUSCI_B_SPITABLE[5])
#define ROM_EUSCI_B_SPI_receiveData	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_SPITABLE[6])
#define ROM_EUSCI_B_SPI_enableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                        uint8_t mask))ROM_EUSCI_B_SPITABLE[7])
#define ROM_EUSCI_B_SPI_disableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                         uint8_t mask))ROM_EUSCI_B_SPITABLE[8])
#define ROM_EUSCI_B_SPI_getInterruptStatus	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress,	\
                                              uint8_t mask))ROM_EUSCI_B_SPITABLE[9])
#define ROM_EUSCI_B_SPI_clearInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                       uint8_t mask))ROM_EUSCI_B_SPITABLE[10])
#define ROM_EUSCI_B_SPI_enable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_SPITABLE[11])
#define ROM_EUSCI_B_SPI_disable	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_SPITABLE[12])
#define ROM_EUSCI_B_SPI_getReceiveBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_SPITABLE[13])
#define ROM_EUSCI_B_SPI_getTransmitBufferAddress	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_SPITABLE[14])
#define ROM_EUSCI_B_SPI_isBusy	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress))ROM_EUSCI_B_SPITABLE[15])
#define ROM_EUSCI_B_SPI_remapPins	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                  uint8_t pinsSelect))ROM_EUSCI_B_SPITABLE[16])

//*****************************************************************************
//
// Macros for calling ROM functions in the GPIO API.
//
//*****************************************************************************
#define ROM_GPIO_setAsOutputPin	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                uint16_t selectedPins))ROM_GPIOTABLE[0])
#define ROM_GPIO_setAsInputPin	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                               uint16_t selectedPins))ROM_GPIOTABLE[1])
#define ROM_GPIO_setAsPeripheralModuleFunctionOutputPin	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                                        uint16_t selectedPins,	\
                                                        uint8_t mode))ROM_GPIOTABLE[2])
#define ROM_GPIO_setAsPeripheralModuleFunctionInputPin	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                                       uint16_t selectedPins,	\
                                                       uint8_t mode))ROM_GPIOTABLE[3])
#define ROM_GPIO_setOutputHighOnPin	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                    uint16_t selectedPins))ROM_GPIOTABLE[4])
#define ROM_GPIO_setOutputLowOnPin	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                   uint16_t selectedPins))ROM_GPIOTABLE[5])
#define ROM_GPIO_toggleOutputOnPin	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                   uint16_t selectedPins))ROM_GPIOTABLE[6])
#define ROM_GPIO_setAsInputPinWithPullDownResistor	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                                   uint16_t selectedPins))ROM_GPIOTABLE[7])
#define ROM_GPIO_setAsInputPinWithPullUpResistor	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                                 uint16_t selectedPins))ROM_GPIOTABLE[8])
#define ROM_GPIO_getInputPinValue	\
     ((uint8_t (__cc_rom *)( uint8_t selectedPort,	\
                                     uint16_t selectedPins))ROM_GPIOTABLE[9])
#define ROM_GPIO_enableInterrupt	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                 uint16_t selectedPins))ROM_GPIOTABLE[10])
#define ROM_GPIO_disableInterrupt	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                  uint16_t selectedPins))ROM_GPIOTABLE[11])
#define ROM_GPIO_getInterruptStatus	\
     ((uint16_t (__cc_rom *)( uint8_t selectedPort,	\
                                        uint16_t selectedPins))ROM_GPIOTABLE[12])
#define ROM_GPIO_clearInterrupt	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                uint16_t selectedPins))ROM_GPIOTABLE[13])
#define ROM_GPIO_selectInterruptEdge	\
     ((void (__cc_rom *)( uint8_t selectedPort,	\
                                     uint16_t selectedPins,	\
                                     uint8_t edgeSelect))ROM_GPIOTABLE[14])

//*****************************************************************************
//
// Macros for calling ROM functions in the PMM API.
//
//*****************************************************************************
#define ROM_PMM_enableSVSH	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[0])
#define ROM_PMM_disableSVSH	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[1])
#define ROM_PMM_turnOnRegulator	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[2])
#define ROM_PMM_turnOffRegulator	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[3])
#define ROM_PMM_trigPOR	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[4])
#define ROM_PMM_trigBOR	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[5])
#define ROM_PMM_clearInterrupt	\
     ((void (__cc_rom *)( uint16_t mask))ROM_PMMTABLE[6])
#define ROM_PMM_getInterruptStatus	\
     ((uint16_t (__cc_rom *)( uint16_t mask))ROM_PMMTABLE[7])
#define ROM_PMM_unlockLPM5	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[8])
#define ROM_PMM_getBandgapMode	\
     ((uint16_t (__cc_rom *)( void))ROM_PMMTABLE[9])
#define ROM_PMM_isBandgapActive	\
     ((uint16_t (__cc_rom *)( void))ROM_PMMTABLE[10])
#define ROM_PMM_isRefGenActive	\
     ((uint16_t (__cc_rom *)( void))ROM_PMMTABLE[11])
#define ROM_PMM_getBufferedBandgapVoltageStatus	\
     ((uint16_t (__cc_rom *)( void))ROM_PMMTABLE[12])
#define ROM_PMM_getVariableReferenceVoltageStatus	\
     ((uint16_t (__cc_rom *)( void))ROM_PMMTABLE[13])
#define ROM_PMM_disableTempSensor	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[14])
#define ROM_PMM_enableTempSensor	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[15])
#define ROM_PMM_disableExternalReference	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[16])
#define ROM_PMM_enableExternalReference	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[17])
#define ROM_PMM_disableInternalReference	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[18])
#define ROM_PMM_enableInternalReference	\
     ((void (__cc_rom *)( void))ROM_PMMTABLE[19])
#define ROM_PMM_selectVoltageReference	\
     ((void (__cc_rom *)( uint8_t refV))ROM_PMMTABLE[20])
#define ROM_PMM_setPowerMode	\
     ((void (__cc_rom *)( uint8_t mode))ROM_PMMTABLE[21])

//*****************************************************************************
//
// Macros for calling ROM functions in the SFR API.
//
//*****************************************************************************
#define ROM_SFR_enableInterrupt	\
     ((void (__cc_rom *)( uint8_t interruptMask))ROM_SFRTABLE[0])
#define ROM_SFR_disableInterrupt	\
     ((void (__cc_rom *)( uint8_t interruptMask))ROM_SFRTABLE[1])
#define ROM_SFR_getInterruptStatus	\
     ((uint8_t (__cc_rom *)( uint8_t interruptFlagMask))ROM_SFRTABLE[2])
#define ROM_SFR_clearInterrupt	\
     ((void (__cc_rom *)( uint8_t interruptFlagMask))ROM_SFRTABLE[3])
#define ROM_SFR_setResetPinPullResistor	\
     ((void (__cc_rom *)( uint16_t pullResistorSetup))ROM_SFRTABLE[4])
#define ROM_SFR_setNMIEdge	\
     ((void (__cc_rom *)( uint16_t edgeDirection))ROM_SFRTABLE[5])
#define ROM_SFR_setResetNMIPinFunction	\
     ((void (__cc_rom *)( uint8_t resetPinFunction))ROM_SFRTABLE[6])

//*****************************************************************************
//
// Macros for calling ROM functions in the SYSCTL API.
//
//*****************************************************************************
#define ROM_SysCtl_enableDedicatedJTAGPins	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[0])
#define ROM_SysCtl_getBSLEntryIndication	\
     ((uint8_t (__cc_rom *)( void))ROM_SYSCTLTABLE[1])
#define ROM_SysCtl_enablePMMAccessProtect	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[2])
#define ROM_SysCtl_enableRAMBasedInterruptVectors	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[3])
#define ROM_SysCtl_disableRAMBasedInterruptVectors	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[4])
#define ROM_SysCtl_enableBSLProtect	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[5])
#define ROM_SysCtl_disableBSLProtect	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[6])
#define ROM_SysCtl_enableBSLMemory	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[7])
#define ROM_SysCtl_disableBSLMemory	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[8])
#define ROM_SysCtl_setRAMAssignedToBSL	\
     ((void (__cc_rom *)( uint8_t BSLRAMAssignment))ROM_SYSCTLTABLE[9])
#define ROM_SysCtl_initJTAGMailbox	\
     ((void (__cc_rom *)( uint8_t mailboxSizeSelect,	\
                                   uint8_t autoClearInboxFlagSelect))ROM_SYSCTLTABLE[10])
#define ROM_SysCtl_getJTAGMailboxFlagStatus	\
     ((uint8_t (__cc_rom *)( uint8_t mailboxFlagMask))ROM_SYSCTLTABLE[11])
#define ROM_SysCtl_clearJTAGMailboxFlagStatus	\
     ((void (__cc_rom *)( uint8_t mailboxFlagMask))ROM_SYSCTLTABLE[12])
#define ROM_SysCtl_getJTAGInboxMessage16Bit	\
     ((uint16_t (__cc_rom *)( uint8_t inboxSelect))ROM_SYSCTLTABLE[13])
#define ROM_SysCtl_getJTAGInboxMessage32Bit	\
     ((uint32_t (__cc_rom *)( void))ROM_SYSCTLTABLE[14])
#define ROM_SysCtl_setJTAGOutgoingMessage16Bit	\
     ((void (__cc_rom *)( uint8_t outboxSelect,	\
                                               uint16_t outgoingMessage))ROM_SYSCTLTABLE[15])
#define ROM_SysCtl_setJTAGOutgoingMessage32Bit	\
     ((void (__cc_rom *)( uint32_t outgoingMessage))ROM_SYSCTLTABLE[16])
#define ROM_SysCtl_protectFRAMWrite	\
     ((void (__cc_rom *)( uint8_t writeProtect))ROM_SYSCTLTABLE[17])
#define ROM_SysCtl_enableFRAMWrite	\
     ((void (__cc_rom *)( uint8_t writeEnable))ROM_SYSCTLTABLE[18])
#define ROM_SysCtl_setInfraredConfig	\
     ((void (__cc_rom *)( uint8_t dataSource,	\
                                     uint8_t mode,	\
                                     uint8_t polarity))ROM_SYSCTLTABLE[19])
#define ROM_SysCtl_enableInfrared	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[20])
#define ROM_SysCtl_disableInfrared	\
     ((void (__cc_rom *)( void))ROM_SYSCTLTABLE[21])
#define ROM_SysCtl_getInfraredData	\
     ((uint8_t (__cc_rom *)( void))ROM_SYSCTLTABLE[22])
#define ROM_SysCtl_setFRWPOA	\
     ((void (__cc_rom *)( uint8_t offsetAddress))ROM_SYSCTLTABLE[23])

//*****************************************************************************
//
// Macros for calling ROM functions in the TIMER_B API.
//
//*****************************************************************************
#define ROM_Timer_B_startCounter	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                 uint16_t timerMode))ROM_TIMER_BTABLE[0])
#define ROM_Timer_B_initContinuousMode	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                       Timer_B_initContinuousModeParam *param))ROM_TIMER_BTABLE[1])
#define ROM_Timer_B_initUpMode	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                               Timer_B_initUpModeParam *param))ROM_TIMER_BTABLE[2])
#define ROM_Timer_B_initUpDownMode	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                   Timer_B_initUpDownModeParam *param))ROM_TIMER_BTABLE[3])
#define ROM_Timer_B_initCaptureMode	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                    Timer_B_initCaptureModeParam *param))ROM_TIMER_BTABLE[4])
#define ROM_Timer_B_initCompareMode	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                    Timer_B_initCompareModeParam *param))ROM_TIMER_BTABLE[5])
#define ROM_Timer_B_enableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_TIMER_BTABLE[6])
#define ROM_Timer_B_disableInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_TIMER_BTABLE[7])
#define ROM_Timer_B_getInterruptStatus	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress))ROM_TIMER_BTABLE[8])
#define ROM_Timer_B_enableCaptureCompareInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                  uint16_t captureCompareRegister))ROM_TIMER_BTABLE[9])
#define ROM_Timer_B_disableCaptureCompareInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                   uint16_t captureCompareRegister))ROM_TIMER_BTABLE[10])
#define ROM_Timer_B_getCaptureCompareInterruptStatus	\
     ((uint32_t (__cc_rom *)( uint16_t baseAddress,	\
                                                         uint16_t captureCompareRegister,	\
                                                         uint16_t mask))ROM_TIMER_BTABLE[11])
#define ROM_Timer_B_clear	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_TIMER_BTABLE[12])
#define ROM_Timer_B_getSynchronizedCaptureCompareInput	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress,	\
                                                          uint16_t captureCompareRegister,	\
                                                          uint16_t synchronized))ROM_TIMER_BTABLE[13])
#define ROM_Timer_B_getOutputForOutputModeOutBitValue	\
     ((uint8_t (__cc_rom *)( uint16_t baseAddress,	\
                                                         uint16_t captureCompareRegister))ROM_TIMER_BTABLE[14])
#define ROM_Timer_B_getCaptureCompareCount	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress,	\
                                               uint16_t captureCompareRegister))ROM_TIMER_BTABLE[15])
#define ROM_Timer_B_setOutputForOutputModeOutBitValue	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                      uint16_t captureCompareRegister,	\
                                                      uint8_t outputModeOutBitValue))ROM_TIMER_BTABLE[16])
#define ROM_Timer_B_outputPWM	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                              Timer_B_outputPWMParam *param))ROM_TIMER_BTABLE[17])
#define ROM_Timer_B_stop	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_TIMER_BTABLE[18])
#define ROM_Timer_B_setCompareValue	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                    uint16_t compareRegister,	\
                                    uint16_t compareValue))ROM_TIMER_BTABLE[19])
#define ROM_Timer_B_clearTimerInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_TIMER_BTABLE[20])
#define ROM_Timer_B_clearCaptureCompareInterrupt	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                 uint16_t captureCompareRegister))ROM_TIMER_BTABLE[21])
#define ROM_Timer_B_selectCounterLength	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                        uint16_t counterLength))ROM_TIMER_BTABLE[22])
#define ROM_Timer_B_selectLatchingGroup	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                        uint16_t groupLatch))ROM_TIMER_BTABLE[23])
#define ROM_Timer_B_initCompareLatchLoadEvent	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                              uint16_t compareRegister,	\
                                              uint16_t compareLatchLoadEvent))ROM_TIMER_BTABLE[24])
#define ROM_Timer_B_getCounterValue	\
     ((uint16_t (__cc_rom *)( uint16_t baseAddress))ROM_TIMER_BTABLE[25])
#define ROM_Timer_B_setOutputMode	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                  uint16_t compareRegister,	\
                                  uint16_t compareOutputMode))ROM_TIMER_BTABLE[26])
#define ROM_Timer_B_selectOutputHighImpedanceTrigger	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                                     uint8_t triggerSelect))ROM_TIMER_BTABLE[27])
#define ROM_Timer_B_remapPins	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                              uint8_t pinsSelect))ROM_TIMER_BTABLE[28])

//*****************************************************************************
//
// Macros for calling ROM functions in the WDT_A API.
//
//*****************************************************************************
#define ROM_WDT_A_hold	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_WDT_ATABLE[0])
#define ROM_WDT_A_start	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_WDT_ATABLE[1])
#define ROM_WDT_A_resetTimer	\
     ((void (__cc_rom *)( uint16_t baseAddress))ROM_WDT_ATABLE[2])
#define ROM_WDT_A_initWatchdogTimer	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                    uint8_t clockSelect,	\
                                    uint8_t clockDivider))ROM_WDT_ATABLE[3])
#define ROM_WDT_A_initIntervalTimer	\
     ((void (__cc_rom *)( uint16_t baseAddress,	\
                                    uint8_t clockSelect,	\
                                    uint8_t clockDivider))ROM_WDT_ATABLE[4])


#else
#error "Small code model is not supported because ROM lives above 64k memory."
#endif	// large model only
#endif	// __ROM_DRIVERLIB_H__
