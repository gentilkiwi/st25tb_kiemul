//*****************************************************************************
//
// rom_driverlib_fr235x.h - Macros to facilitate calling functions in ROM for
// MSP430FR2355, FR2353, FR2153, FR2155
//
// Copyright (c) 2017 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************
//

#if defined(__TI_COMPILER_VERSION__)
#if __TI_COMPILER_VERSION__ >= 18001001
#define __cc_rom __attribute__((call_conv("cc_rom")))
#else
#error "The cc_rom attribute requires MSP TI COMPILER 18.1.1.LTS or more recent."
#endif  // __TI_COMPILER_VERSION__ >= 
#endif  // (defined(__TI_COMPILER_VERSION__))18001001

#if defined(__IAR_SYSTEMS_ICC__) && (__VER__ < 650)
#error "The __cc_rom attribute requires IAR version 6.50 or more recent."
#endif

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
// Pointers to the main API tables.
//
//*****************************************************************************
#ifndef ROM_TABLE
#define ROM_TABLE                      ((uint32_t *)ROMLIB_START)
#endif
#define ROM_DRIVERLIB_APITABLE         ((uint32_t *)&ROM_TABLE[2])
#define ROM_DRIVERLIB_VERSIONL         (ROM_DRIVERLIB_APITABLE[0])
#define ROM_DRIVERLIB_VERSIONH         (ROM_DRIVERLIB_APITABLE[1])
#define ROM_ADCTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[2]))
#define ROM_CRCTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[3]))
#define ROM_CSTABLE                    ((uint32_t *)(ROM_DRIVERLIB_APITABLE[4]))
#define ROM_ECOMPTABLE                 ((uint32_t *)(ROM_DRIVERLIB_APITABLE[5]))
#define ROM_EUSCIASPITABLE             ((uint32_t *)(ROM_DRIVERLIB_APITABLE[6]))
#define ROM_EUSCIAUARTTABLE            ((uint32_t *)(ROM_DRIVERLIB_APITABLE[7]))
#define ROM_EUSCIBI2CTABLE             ((uint32_t *)(ROM_DRIVERLIB_APITABLE[8]))
#define ROM_EUSCIBSPITABLE             ((uint32_t *)(ROM_DRIVERLIB_APITABLE[9]))
#define ROM_FRAMCTLTABLE               ((uint32_t *)(ROM_DRIVERLIB_APITABLE[10]))
#define ROM_GPIOTABLE                  ((uint32_t *)(ROM_DRIVERLIB_APITABLE[11]))
#define ROM_ICCTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[12]))
#define ROM_MPY32TABLE                 ((uint32_t *)(ROM_DRIVERLIB_APITABLE[14]))
#define ROM_PMMTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[15]))
#define ROM_RTCTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[16]))
#define ROM_SACTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[17]))
#define ROM_SFRTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[18]))
#define ROM_SYSCTLTABLE                ((uint32_t *)(ROM_DRIVERLIB_APITABLE[19]))
#define ROM_TIMER_BTABLE               ((uint32_t *)(ROM_DRIVERLIB_APITABLE[22]))
#define ROM_TLVTABLE                   ((uint32_t *)(ROM_DRIVERLIB_APITABLE[23]))
#define ROM_WDTATABLE                  ((uint32_t *)(ROM_DRIVERLIB_APITABLE[24]))

#define ROM_DRIVERLIB_getVersion()     ((uint32_t)ROM_DRIVERLIB_VERSIONH<<16|\
                                            ROM_DRIVERLIB_VERSIONL)
#ifndef ROM_getVersion
#define ROM_getVersion()               ((uint32_t)(ROMLIB_START[0]))
#endif

//*****************************************************************************
//
// Macros for calling ROM functions in the ADC API.
//
//*****************************************************************************

#define ROM_ADC_init                                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t sampleHoldSignalSourceSelect,           \
                             uint8_t clockSourceSelect,                       \
                             uint16_t clockSourceDivider))ROM_ADCTABLE[0])

#define ROM_ADC_enable                                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ADCTABLE[1])

#define ROM_ADC_disable                                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ADCTABLE[2])

#define ROM_ADC_setupSamplingTimer                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t clockCycleHoldCount,                    \
                             uint16_t multipleSamplesEnabled))ROM_ADCTABLE[3])

#define ROM_ADC_disableSamplingTimer                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ADCTABLE[4])

#define ROM_ADC_configureMemory                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t inputSourceSelect,                       \
                             uint8_t positiveRefVoltageSourceSelect,          \
                             uint8_t negativeRefVoltageSourceSelect))ROM_ADCTABLE[5])

#define ROM_ADC_enableInterrupt                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t interruptMask))ROM_ADCTABLE[6])

#define ROM_ADC_disableInterrupt                                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t interruptMask))ROM_ADCTABLE[7])

#define ROM_ADC_clearInterrupt                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t interruptFlagMask))ROM_ADCTABLE[8])

#define ROM_ADC_getInterruptStatus                                            \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint8_t interruptFlagMask))ROM_ADCTABLE[9])

#define ROM_ADC_startConversion                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t conversionSequenceModeSelect))ROM_ADCTABLE[10])

#define ROM_ADC_disableConversions                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             bool preempt))ROM_ADCTABLE[11])

#define ROM_ADC_getResults                                                    \
        ((int16_t ( __cc_rom *)(uint16_t baseAddress))ROM_ADCTABLE[12])

#define ROM_ADC_setResolution                                                 \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t resolutionSelect))ROM_ADCTABLE[13])

#define ROM_ADC_setSampleHoldSignalInversion                                  \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t invertedSignal))ROM_ADCTABLE[14])

#define ROM_ADC_setDataReadBackFormat                                         \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t readBackFormat))ROM_ADCTABLE[15])

#define ROM_ADC_setReferenceBufferSamplingRate                                \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t samplingRateSelect))ROM_ADCTABLE[16])

#define ROM_ADC_setWindowComp                                                 \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t highThreshold,                          \
                             uint16_t lowThreshold))ROM_ADCTABLE[17])

#define ROM_ADC_getMemoryAddressForDMA                                        \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_ADCTABLE[18])

#define ROM_ADC_isBusy                                                        \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_ADCTABLE[19])

//*****************************************************************************
//
// Macros for calling ROM functions in the CRC API.
//
//*****************************************************************************

#define ROM_CRC_setSeed                                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t seed))ROM_CRCTABLE[0])

#define ROM_CRC_set16BitData                                                  \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t dataIn))ROM_CRCTABLE[1])

#define ROM_CRC_set8BitData                                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t dataIn))ROM_CRCTABLE[2])

#define ROM_CRC_set16BitDataReversed                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t dataIn))ROM_CRCTABLE[3])

#define ROM_CRC_set8BitDataReversed                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t dataIn))ROM_CRCTABLE[4])

#define ROM_CRC_getData                                                       \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_CRCTABLE[5])

#define ROM_CRC_getResult                                                     \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_CRCTABLE[6])

#define ROM_CRC_getResultBitsReversed                                         \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_CRCTABLE[7])

//*****************************************************************************
//
// Macros for calling ROM functions in the CS API.
//
//*****************************************************************************

#define ROM_CS_initClockSignal                                                \
        ((void ( __cc_rom *)(uint8_t selectedClockSignal,                     \
                             uint16_t clockSource,                            \
                             uint16_t clockSourceDivider))ROM_CSTABLE[1])

#define ROM_CS_turnOnXT1LF                                                    \
        ((void ( __cc_rom *)(uint16_t xt1Drive))ROM_CSTABLE[2])

#define ROM_CS_bypassXT1                                                      \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[3])

#define ROM_CS_turnOnXT1LFWithTimeout                                         \
        ((bool ( __cc_rom *)(uint16_t xt1Drive,                               \
                             uint16_t timeout))ROM_CSTABLE[4])

#define ROM_CS_bypassXT1WithTimeout                                           \
        ((bool ( __cc_rom *)(uint16_t timeout))ROM_CSTABLE[5])

#define ROM_CS_turnOffXT1                                                     \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[6])

#define ROM_CS_turnOnXT1HF                                                    \
        ((void ( __cc_rom *)(uint16_t xt1Drive,                               \
                             uint16_t xt1HFFreq))ROM_CSTABLE[7])

#define ROM_CS_turnOnXT1HFWithTimeout                                         \
        ((bool ( __cc_rom *)(uint16_t xt1Drive,                               \
                             uint16_t xt1HFFreq,                              \
                             uint16_t timeout))ROM_CSTABLE[8])

#define ROM_CS_turnOnSMCLK                                                    \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[9])

#define ROM_CS_turnOffSMCLK                                                   \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[10])

#define ROM_CS_enableVLOAutoOff                                               \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[11])

#define ROM_CS_disableVLOAutoOff                                              \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[12])

#define ROM_CS_initFLLSettle                                                  \
        ((bool ( __cc_rom *)(uint16_t fsystem,                                \
                             uint16_t ratio))ROM_CSTABLE[13])
/* Removed due to bug fix for MSPDVRLIB-185
#define ROM_CS_initFLL                                                        \
        ((bool ( __cc_rom *)(uint16_t fsystem,                                \
                             uint16_t ratio))ROM_CSTABLE[14])
*/
/* Removed due to bug fix for MSPDVRLIB-185
#define ROM_CS_initFLLLoadTrim                                                \
        ((bool ( __cc_rom *)(uint16_t fsystem,                                \
                             uint16_t ratio,                                  \
                             CS_initFLLParam *param))ROM_CSTABLE[16])
*/
#define ROM_CS_enableClockRequest                                             \
        ((void ( __cc_rom *)(uint8_t selectClock))ROM_CSTABLE[17])

#define ROM_CS_disableClockRequest                                            \
        ((void ( __cc_rom *)(uint8_t selectClock))ROM_CSTABLE[18])

#define ROM_CS_getFaultFlagStatus                                             \
        ((uint8_t ( __cc_rom *)(uint8_t mask))ROM_CSTABLE[19])

#define ROM_CS_clearFaultFlag                                                 \
        ((void ( __cc_rom *)(uint8_t mask))ROM_CSTABLE[20])

#define ROM_CS_clearAllOscFlagsWithTimeout                                    \
        ((uint16_t ( __cc_rom *)(uint16_t timeout))ROM_CSTABLE[24])

#define ROM_CS_enableXT1AutomaticGainControl                                  \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[25])

#define ROM_CS_disableXT1AutomaticGainControl                                 \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[26])

#define ROM_CS_enableFLLUnlock                                                \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[27])

#define ROM_CS_disableFLLUnlock                                               \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[28])

#define ROM_CS_enableREFOLP                                                   \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[29])

#define ROM_CS_disableREFOLP                                                  \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[30])

#define ROM_CS_getREFOLP                                                      \
        ((bool ( __cc_rom *)(void))ROM_CSTABLE[31])

#define ROM_CS_enableXT1FaultOff                                              \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[32])

#define ROM_CS_disableXT1FaultOff                                             \
        ((void ( __cc_rom *)(void))ROM_CSTABLE[33])

#define ROM_CS_getXT1FaultOff                                                 \
        ((bool ( __cc_rom *)(void))ROM_CSTABLE[34])

#define ROM_CS_getREFOReady                                                   \
        ((bool ( __cc_rom *)(void))ROM_CSTABLE[35])

//*****************************************************************************
//
// Macros for calling ROM functions in the ECOMP API.
//
//*****************************************************************************

#define ROM_EComp_init                                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EComp_initParam *param))ROM_ECOMPTABLE[0])

#define ROM_EComp_selectHysteresisMode                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t hysteresisMode))ROM_ECOMPTABLE[1])

#define ROM_EComp_selectPowerMode                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t powerMode))ROM_ECOMPTABLE[2])

#define ROM_EComp_enable                                                      \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ECOMPTABLE[3])

#define ROM_EComp_disable                                                     \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ECOMPTABLE[4])

#define ROM_EComp_enableInterrupt                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t interruptMask))ROM_ECOMPTABLE[5])

#define ROM_EComp_disableInterrupt                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t interruptMask))ROM_ECOMPTABLE[6])

#define ROM_EComp_clearInterrupt                                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t interruptFlagMask))ROM_ECOMPTABLE[7])

#define ROM_EComp_getInterruptStatus                                          \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint16_t interruptFlagMask))ROM_ECOMPTABLE[8])

#define ROM_EComp_setInterruptEdgeDirection                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t edgeDirection))ROM_ECOMPTABLE[9])

#define ROM_EComp_toggleInterruptEdgeDirection                                \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ECOMPTABLE[10])

#define ROM_EComp_outputValue                                                 \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_ECOMPTABLE[11])

#define ROM_EComp_configureDAC                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EComp_configureDACParam *param))ROM_ECOMPTABLE[12])

#define ROM_EComp_enableDAC                                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ECOMPTABLE[13])

#define ROM_EComp_disableDAC                                                  \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_ECOMPTABLE[14])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIASPI API.
//
//*****************************************************************************

#define ROM_EUSCI_A_SPI_initMaster                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_A_SPI_initMasterParam *param))ROM_EUSCIASPITABLE[0])

#define ROM_EUSCI_A_SPI_select4PinFunctionality                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t select4PinFunctionality))ROM_EUSCIASPITABLE[1])

#define ROM_EUSCI_A_SPI_changeMasterClock                                     \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_A_SPI_changeMasterClockParam *param))ROM_EUSCIASPITABLE[2])

#define ROM_EUSCI_A_SPI_initSlave                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_A_SPI_initSlaveParam *param))ROM_EUSCIASPITABLE[3])

#define ROM_EUSCI_A_SPI_changeClockPhasePolarity                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t clockPhase,                             \
                             uint16_t clockPolarity))ROM_EUSCIASPITABLE[4])

#define ROM_EUSCI_A_SPI_transmitData                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t transmitData))ROM_EUSCIASPITABLE[5])

#define ROM_EUSCI_A_SPI_receiveData                                           \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIASPITABLE[6])

#define ROM_EUSCI_A_SPI_enableInterrupt                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIASPITABLE[7])

#define ROM_EUSCI_A_SPI_disableInterrupt                                      \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIASPITABLE[8])

#define ROM_EUSCI_A_SPI_getInterruptStatus                                    \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint8_t mask))ROM_EUSCIASPITABLE[9])

#define ROM_EUSCI_A_SPI_clearInterrupt                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIASPITABLE[10])

#define ROM_EUSCI_A_SPI_enable                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIASPITABLE[11])

#define ROM_EUSCI_A_SPI_disable                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIASPITABLE[12])

#define ROM_EUSCI_A_SPI_getReceiveBufferAddress                               \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIASPITABLE[13])

#define ROM_EUSCI_A_SPI_isBusy                                                \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIASPITABLE[14])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIAUART API.
//
//*****************************************************************************

#define ROM_EUSCI_A_UART_init                                                 \
        ((bool ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_A_UART_initParam *param))ROM_EUSCIAUARTTABLE[0])

#define ROM_EUSCI_A_UART_transmitData                                         \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t transmitData))ROM_EUSCIAUARTTABLE[1])

#define ROM_EUSCI_A_UART_receiveData                                          \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[2])

#define ROM_EUSCI_A_UART_enableInterrupt                                      \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIAUARTTABLE[3])

#define ROM_EUSCI_A_UART_disableInterrupt                                     \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIAUARTTABLE[4])

#define ROM_EUSCI_A_UART_getInterruptStatus                                   \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint8_t mask))ROM_EUSCIAUARTTABLE[5])

#define ROM_EUSCI_A_UART_clearInterrupt                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIAUARTTABLE[6])

#define ROM_EUSCI_A_UART_enable                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[7])

#define ROM_EUSCI_A_UART_disable                                              \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[8])

#define ROM_EUSCI_A_UART_queryStatusFlags                                     \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint8_t mask))ROM_EUSCIAUARTTABLE[9])

#define ROM_EUSCI_A_UART_setDormant                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[10])

#define ROM_EUSCI_A_UART_resetDormant                                         \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[11])

#define ROM_EUSCI_A_UART_transmitAddress                                      \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t transmitAddress))ROM_EUSCIAUARTTABLE[12])

#define ROM_EUSCI_A_UART_transmitBreak                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[13])

#define ROM_EUSCI_A_UART_getReceiveBufferAddress                              \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[14])

#define ROM_EUSCI_A_UART_getTransmitBufferAddress                             \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[15])

#define ROM_EUSCI_A_UART_selectDeglitchTime                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t deglitchTime))ROM_EUSCIAUARTTABLE[16])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIBI2C API.
//
//*****************************************************************************

#define ROM_EUSCI_B_I2C_initMaster                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_B_I2C_initMasterParam *param))ROM_EUSCIBI2CTABLE[0])

#define ROM_EUSCI_B_I2C_initSlave                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_B_I2C_initSlaveParam *param))ROM_EUSCIBI2CTABLE[1])

#define ROM_EUSCI_B_I2C_enable                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[2])

#define ROM_EUSCI_B_I2C_disable                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[3])

#define ROM_EUSCI_B_I2C_setSlaveAddress                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t slaveAddress))ROM_EUSCIBI2CTABLE[4])

#define ROM_EUSCI_B_I2C_setMode                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mode))ROM_EUSCIBI2CTABLE[5])

#define ROM_EUSCI_B_I2C_getMode                                               \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[6])

#define ROM_EUSCI_B_I2C_slavePutData                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t transmitData))ROM_EUSCIBI2CTABLE[7])

#define ROM_EUSCI_B_I2C_slaveGetData                                          \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[8])

#define ROM_EUSCI_B_I2C_isBusBusy                                             \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[9])

#define ROM_EUSCI_B_I2C_masterIsStopSent                                      \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[10])

#define ROM_EUSCI_B_I2C_masterReceiveSingleByte                               \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[11])

#define ROM_EUSCI_B_I2C_masterIsStartSent                                     \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[12])

#define ROM_EUSCI_B_I2C_enableInterrupt                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t mask))ROM_EUSCIBI2CTABLE[13])

#define ROM_EUSCI_B_I2C_disableInterrupt                                      \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t mask))ROM_EUSCIBI2CTABLE[14])

#define ROM_EUSCI_B_I2C_clearInterrupt                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t mask))ROM_EUSCIBI2CTABLE[15])

#define ROM_EUSCI_B_I2C_getInterruptStatus                                    \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress,                        \
                                 uint16_t mask))ROM_EUSCIBI2CTABLE[16])

#define ROM_EUSCI_B_I2C_masterSendSingleByte                                  \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData))ROM_EUSCIBI2CTABLE[17])

#define ROM_EUSCI_B_I2C_masterSendSingleByteWithTimeout                       \
        ((bool ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData,                                  \
                             uint32_t timeout))ROM_EUSCIBI2CTABLE[18])

#define ROM_EUSCI_B_I2C_masterSendMultiByteStart                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData))ROM_EUSCIBI2CTABLE[19])

#define ROM_EUSCI_B_I2C_masterSendMultiByteStartWithTimeout                   \
        ((bool ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData,                                  \
                             uint32_t timeout))ROM_EUSCIBI2CTABLE[20])

#define ROM_EUSCI_B_I2C_masterSendMultiByteNext                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData))ROM_EUSCIBI2CTABLE[21])

#define ROM_EUSCI_B_I2C_masterSendMultiByteNextWithTimeout                    \
        ((bool ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData,                                  \
                             uint32_t timeout))ROM_EUSCIBI2CTABLE[22])

#define ROM_EUSCI_B_I2C_masterSendMultiByteFinish                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData))ROM_EUSCIBI2CTABLE[23])

#define ROM_EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout                  \
        ((bool ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t txData,                                  \
                             uint32_t timeout))ROM_EUSCIBI2CTABLE[24])

#define ROM_EUSCI_B_I2C_masterSendStart                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[25])

#define ROM_EUSCI_B_I2C_masterSendMultiByteStop                               \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[26])

#define ROM_EUSCI_B_I2C_masterReceiveStart                                    \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[28])

#define ROM_EUSCI_B_I2C_masterReceiveMultiByteNext                            \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[29])

#define ROM_EUSCI_B_I2C_masterReceiveMultiByteFinish                          \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[30])

#define ROM_EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout               \
        ((bool ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t *txData,                                 \
                             uint32_t timeout))ROM_EUSCIBI2CTABLE[31])

#define ROM_EUSCI_B_I2C_masterReceiveMultiByteStop                            \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[32])

#define ROM_EUSCI_B_I2C_enableMultiMasterMode                                 \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[33])

#define ROM_EUSCI_B_I2C_disableMultiMasterMode                                \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[34])

#define ROM_EUSCI_B_I2C_masterReceiveSingle                                   \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[35])

#define ROM_EUSCI_B_I2C_getReceiveBufferAddress                               \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[36])

#define ROM_EUSCI_B_I2C_getTransmitBufferAddress                              \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[37])

#define ROM_EUSCI_B_I2C_remapPins                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t pinsSelect))ROM_EUSCIBI2CTABLE[38])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIBSPI API.
//
//*****************************************************************************

#define ROM_EUSCI_B_SPI_initMaster                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_B_SPI_initMasterParam *param))ROM_EUSCIBSPITABLE[0])

#define ROM_EUSCI_B_SPI_select4PinFunctionality                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t select4PinFunctionality))ROM_EUSCIBSPITABLE[1])

#define ROM_EUSCI_B_SPI_changeMasterClock                                     \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_B_SPI_changeMasterClockParam *param))ROM_EUSCIBSPITABLE[2])

#define ROM_EUSCI_B_SPI_initSlave                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             EUSCI_B_SPI_initSlaveParam *param))ROM_EUSCIBSPITABLE[3])

#define ROM_EUSCI_B_SPI_changeClockPhasePolarity                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t clockPhase,                             \
                             uint16_t clockPolarity))ROM_EUSCIBSPITABLE[4])

#define ROM_EUSCI_B_SPI_transmitData                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t transmitData))ROM_EUSCIBSPITABLE[5])

#define ROM_EUSCI_B_SPI_receiveData                                           \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[6])

#define ROM_EUSCI_B_SPI_enableInterrupt                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIBSPITABLE[7])

#define ROM_EUSCI_B_SPI_disableInterrupt                                      \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIBSPITABLE[8])

#define ROM_EUSCI_B_SPI_getInterruptStatus                                    \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint8_t mask))ROM_EUSCIBSPITABLE[9])

#define ROM_EUSCI_B_SPI_clearInterrupt                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mask))ROM_EUSCIBSPITABLE[10])

#define ROM_EUSCI_B_SPI_enable                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[11])

#define ROM_EUSCI_B_SPI_disable                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[12])

#define ROM_EUSCI_B_SPI_getReceiveBufferAddress                               \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[13])

#define ROM_EUSCI_B_SPI_getTransmitBufferAddress                              \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[14])

#define ROM_EUSCI_B_SPI_isBusy                                                \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[15])

#define ROM_EUSCI_B_SPI_remapPins                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t pinsSelect))ROM_EUSCIBSPITABLE[16])

//*****************************************************************************
//
// Macros for calling ROM functions in the FRAMCTL API.
//
//*****************************************************************************

#define ROM_FRAMCtl_write8                                                    \
        ((void ( __cc_rom *)(uint8_t *dataPtr,                                \
                             uint8_t *framPtr,                                \
                             uint16_t numberOfBytes))ROM_FRAMCTLTABLE[0])

#define ROM_FRAMCtl_write16                                                   \
        ((void ( __cc_rom *)(uint16_t *dataPtr,                               \
                             uint16_t *framPtr,                               \
                             uint16_t numberOfWords))ROM_FRAMCTLTABLE[1])

#define ROM_FRAMCtl_write32                                                   \
        ((void ( __cc_rom *)(uint32_t *dataPtr,                               \
                             uint32_t *framPtr,                               \
                             uint16_t count))ROM_FRAMCTLTABLE[2])

#define ROM_FRAMCtl_fillMemory32                                              \
        ((void ( __cc_rom *)(uint32_t value,                                  \
                             uint32_t *framPtr,                               \
                             uint16_t count))ROM_FRAMCTLTABLE[3])

#define ROM_FRAMCtl_enableInterrupt                                           \
        ((void ( __cc_rom *)(uint8_t interruptMask))ROM_FRAMCTLTABLE[4])

#define ROM_FRAMCtl_getInterruptStatus                                        \
        ((uint8_t ( __cc_rom *)(uint16_t interruptFlagMask))ROM_FRAMCTLTABLE[5])

#define ROM_FRAMCtl_disableInterrupt                                          \
        ((void ( __cc_rom *)(uint16_t interruptMask))ROM_FRAMCTLTABLE[6])

#define ROM_FRAMCtl_configureWaitStateControl                                 \
        ((void ( __cc_rom *)(uint8_t waitState))ROM_FRAMCTLTABLE[7])

#define ROM_FRAMCtl_delayPowerUpFromLPM                                       \
        ((void ( __cc_rom *)(uint8_t delayStatus))ROM_FRAMCTLTABLE[8])

//*****************************************************************************
//
// Macros for calling ROM functions in the GPIO API.
//
//*****************************************************************************

#define ROM_GPIO_setAsOutputPin                                               \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[0])

#define ROM_GPIO_setAsInputPin                                                \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[1])

#define ROM_GPIO_setAsPeripheralModuleFunctionOutputPin                       \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins,                           \
                             uint8_t mode))ROM_GPIOTABLE[2])

#define ROM_GPIO_setAsPeripheralModuleFunctionInputPin                        \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins,                           \
                             uint8_t mode))ROM_GPIOTABLE[3])

#define ROM_GPIO_setOutputHighOnPin                                           \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[4])

#define ROM_GPIO_setOutputLowOnPin                                            \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[5])

#define ROM_GPIO_toggleOutputOnPin                                            \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[6])

#define ROM_GPIO_setAsInputPinWithPullDownResistor                            \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[7])

#define ROM_GPIO_setAsInputPinWithPullUpResistor                              \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[8])

#define ROM_GPIO_getInputPinValue                                             \
        ((uint8_t ( __cc_rom *)(uint8_t selectedPort,                         \
                                uint16_t selectedPins))ROM_GPIOTABLE[9])

#define ROM_GPIO_enableInterrupt                                              \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[10])

#define ROM_GPIO_disableInterrupt                                             \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[11])

#define ROM_GPIO_getInterruptStatus                                           \
        ((uint16_t ( __cc_rom *)(uint8_t selectedPort,                        \
                                 uint16_t selectedPins))ROM_GPIOTABLE[12])

#define ROM_GPIO_clearInterrupt                                               \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins))ROM_GPIOTABLE[13])

#define ROM_GPIO_selectInterruptEdge                                          \
        ((void ( __cc_rom *)(uint8_t selectedPort,                            \
                             uint16_t selectedPins,                           \
                             uint8_t edgeSelect))ROM_GPIOTABLE[14])

//*****************************************************************************
//
// Macros for calling ROM functions in the ICC API.
//
//*****************************************************************************

#define ROM_ICC_enable                                                        \
        ((void ( __cc_rom *)(void))ROM_ICCTABLE[0])

#define ROM_ICC_disable                                                       \
        ((void ( __cc_rom *)(void))ROM_ICCTABLE[1])

#define ROM_ICC_setInterruptLevel                                             \
        ((void ( __cc_rom *)(uint32_t ILSRmask,                               \
                             uint8_t interruptLevel))ROM_ICCTABLE[2])

#define ROM_ICC_getInterruptLevel                                             \
        ((uint8_t ( __cc_rom *)(uint32_t interruptSource))ROM_ICCTABLE[3])

#define ROM_ICC_isVirtualStackEmpty                                           \
        ((bool ( __cc_rom *)(void))ROM_ICCTABLE[4])

#define ROM_ICC_isVirtualStackFull                                            \
        ((bool ( __cc_rom *)(void))ROM_ICCTABLE[5])

#define ROM_ICC_getCurrentICM                                                 \
        ((uint8_t ( __cc_rom *)(void))ROM_ICCTABLE[6])

#define ROM_ICC_getMVSStackPointer                                            \
        ((uint8_t ( __cc_rom *)(void))ROM_ICCTABLE[7])

#define ROM_ICC_getICM3                                                       \
        ((uint8_t ( __cc_rom *)(void))ROM_ICCTABLE[8])

#define ROM_ICC_getICM2                                                       \
        ((uint8_t ( __cc_rom *)(void))ROM_ICCTABLE[9])

#define ROM_ICC_getICM1                                                       \
        ((uint8_t ( __cc_rom *)(void))ROM_ICCTABLE[10])

#define ROM_ICC_getICM0                                                       \
        ((uint8_t ( __cc_rom *)(void))ROM_ICCTABLE[11])

//*****************************************************************************
//
// Macros for calling ROM functions in the MPY32 API.
//
//*****************************************************************************

#define ROM_MPY32_setWriteDelay                                               \
        ((void ( __cc_rom *)(uint16_t writeDelaySelect))ROM_MPY32TABLE[0])

#define ROM_MPY32_enableSaturationMode                                        \
        ((void ( __cc_rom *)(void))ROM_MPY32TABLE[1])

#define ROM_MPY32_disableSaturationMode                                       \
        ((void ( __cc_rom *)(void))ROM_MPY32TABLE[2])

#define ROM_MPY32_getSaturationMode                                           \
        ((uint8_t ( __cc_rom *)(void))ROM_MPY32TABLE[3])

#define ROM_MPY32_enableFractionalMode                                        \
        ((void ( __cc_rom *)(void))ROM_MPY32TABLE[4])

#define ROM_MPY32_disableFractionalMode                                       \
        ((void ( __cc_rom *)(void))ROM_MPY32TABLE[5])

#define ROM_MPY32_getFractionalMode                                           \
        ((uint8_t ( __cc_rom *)(void))ROM_MPY32TABLE[6])

#define ROM_MPY32_setOperandOne8Bit                                           \
        ((void ( __cc_rom *)(uint8_t multiplicationType,                      \
                             uint8_t operand))ROM_MPY32TABLE[7])

#define ROM_MPY32_setOperandOne16Bit                                          \
        ((void ( __cc_rom *)(uint8_t multiplicationType,                      \
                             uint16_t operand))ROM_MPY32TABLE[8])

#define ROM_MPY32_setOperandTwo8Bit                                           \
        ((void ( __cc_rom *)(uint8_t operand))ROM_MPY32TABLE[11])

#define ROM_MPY32_setOperandTwo16Bit                                          \
        ((void ( __cc_rom *)(uint16_t operand))ROM_MPY32TABLE[12])

#define ROM_MPY32_setOperandTwo24Bit                                          \
        ((void ( __cc_rom *)(uint32_t operand))ROM_MPY32TABLE[13])

#define ROM_MPY32_setOperandTwo32Bit                                          \
        ((void ( __cc_rom *)(uint32_t operand))ROM_MPY32TABLE[14])

#define ROM_MPY32_getResult                                                   \
        ((uint64_t ( __cc_rom *)(void))ROM_MPY32TABLE[15])

#define ROM_MPY32_getSumExtension                                             \
        ((uint16_t ( __cc_rom *)(void))ROM_MPY32TABLE[16])

#define ROM_MPY32_getCarryBitValue                                            \
        ((uint16_t ( __cc_rom *)(void))ROM_MPY32TABLE[17])

#define ROM_MPY32_clearCarryBitValue                                          \
        ((void ( __cc_rom *)(void))ROM_MPY32TABLE[18])

#define ROM_MPY32_preloadResult                                               \
        ((void ( __cc_rom *)(uint64_t result))ROM_MPY32TABLE[19])

//*****************************************************************************
//
// Macros for calling ROM functions in the PMM API.
//
//*****************************************************************************

#define ROM_PMM_enableSVSH                                                    \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[0])

#define ROM_PMM_disableSVSH                                                   \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[1])

#define ROM_PMM_turnOnRegulator                                               \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[2])

#define ROM_PMM_turnOffRegulator                                              \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[3])

#define ROM_PMM_trigPOR                                                       \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[4])

#define ROM_PMM_trigBOR                                                       \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[5])

#define ROM_PMM_clearInterrupt                                                \
        ((void ( __cc_rom *)(uint16_t mask))ROM_PMMTABLE[6])

#define ROM_PMM_getInterruptStatus                                            \
        ((uint16_t ( __cc_rom *)(uint16_t mask))ROM_PMMTABLE[7])

#define ROM_PMM_unlockLPM5                                                    \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[8])

#define ROM_PMM_getBandgapMode                                                \
        ((uint16_t ( __cc_rom *)(void))ROM_PMMTABLE[9])

#define ROM_PMM_isBandgapActive                                               \
        ((uint16_t ( __cc_rom *)(void))ROM_PMMTABLE[10])

#define ROM_PMM_isRefGenActive                                                \
        ((uint16_t ( __cc_rom *)(void))ROM_PMMTABLE[11])

#define ROM_PMM_getBufferedBandgapVoltageStatus                               \
        ((uint16_t ( __cc_rom *)(void))ROM_PMMTABLE[12])

#define ROM_PMM_getVariableReferenceVoltageStatus                             \
        ((uint16_t ( __cc_rom *)(void))ROM_PMMTABLE[13])

#define ROM_PMM_disableTempSensor                                             \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[14])

#define ROM_PMM_enableTempSensor                                              \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[15])

#define ROM_PMM_disableExternalReference                                      \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[16])

#define ROM_PMM_enableExternalReference                                       \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[17])

#define ROM_PMM_disableInternalReference                                      \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[18])

#define ROM_PMM_enableInternalReference                                       \
        ((void ( __cc_rom *)(void))ROM_PMMTABLE[19])

#define ROM_PMM_selectVoltageReference                                        \
        ((void ( __cc_rom *)(uint8_t refV))ROM_PMMTABLE[20])

#define ROM_PMM_setPowerMode                                                  \
        ((void ( __cc_rom *)(uint8_t mode))ROM_PMMTABLE[21])

//*****************************************************************************
//
// Macros for calling ROM functions in the RTC API.
//
//*****************************************************************************

#define ROM_RTC_init                                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t modulo,                                 \
                             uint16_t clockPredivider))ROM_RTCTABLE[0])

#define ROM_RTC_start                                                         \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t clockSource))ROM_RTCTABLE[1])

#define ROM_RTC_stop                                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_RTCTABLE[2])

#define ROM_RTC_setModulo                                                     \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t modulo))ROM_RTCTABLE[3])

#define ROM_RTC_enableInterrupt                                               \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t interruptMask))ROM_RTCTABLE[4])

#define ROM_RTC_disableInterrupt                                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t interruptMask))ROM_RTCTABLE[5])

#define ROM_RTC_getInterruptStatus                                            \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint8_t interruptFlagMask))ROM_RTCTABLE[6])

#define ROM_RTC_clearInterrupt                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             int8_t interruptFlagMask))ROM_RTCTABLE[7])

//*****************************************************************************
//
// Macros for calling ROM functions in the SAC API.
//
//*****************************************************************************

// The following devices in this family do not have this module
#if !defined(__MSP430FR2153__) && !defined(__MSP430FR2155__)
#define ROM_SAC_OA_init                                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t positiveInput,                          \
                             uint16_t negativeInput))ROM_SACTABLE[0])

#define ROM_SAC_OA_selectPowerMode                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t powerMode))ROM_SACTABLE[1])

#define ROM_SAC_OA_enable                                                     \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[2])

#define ROM_SAC_OA_disable                                                    \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[3])

#define ROM_SAC_enable                                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[4])

#define ROM_SAC_disable                                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[5])

#define ROM_SAC_PGA_setMode                                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t mode))ROM_SACTABLE[6])

#define ROM_SAC_PGA_setGain                                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t gain))ROM_SACTABLE[7])

#define ROM_SAC_DAC_enable                                                    \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[8])

#define ROM_SAC_DAC_disable                                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[9])

#define ROM_SAC_DAC_interruptEnable                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[10])

#define ROM_SAC_DAC_interruptDisable                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[11])

#define ROM_SAC_DAC_DMARequestEnable                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[12])

#define ROM_SAC_DAC_DMARequestDisable                                         \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[13])

#define ROM_SAC_DAC_selectLoad                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t load))ROM_SACTABLE[14])

#define ROM_SAC_DAC_selectRefVoltage                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t reference))ROM_SACTABLE[15])

#define ROM_SAC_DAC_getData                                                   \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[16])

#define ROM_SAC_DAC_setData                                                   \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t data))ROM_SACTABLE[17])

#define ROM_SAC_DAC_getIFG                                                    \
        ((bool ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[18])

#define ROM_SAC_DAC_clearIFG                                                  \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[19])

#define ROM_SAC_getInterruptVector                                            \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_SACTABLE[20])
#endif  // !defined __MSP430FR2153__ __MSP430FR2155__

//*****************************************************************************
//
// Macros for calling ROM functions in the SFR API.
//
//*****************************************************************************

#define ROM_SFR_enableInterrupt                                               \
        ((void ( __cc_rom *)(uint8_t interruptMask))ROM_SFRTABLE[0])

#define ROM_SFR_disableInterrupt                                              \
        ((void ( __cc_rom *)(uint8_t interruptMask))ROM_SFRTABLE[1])

#define ROM_SFR_getInterruptStatus                                            \
        ((uint8_t ( __cc_rom *)(uint8_t interruptFlagMask))ROM_SFRTABLE[2])

#define ROM_SFR_clearInterrupt                                                \
        ((void ( __cc_rom *)(uint8_t interruptFlagMask))ROM_SFRTABLE[3])

#define ROM_SFR_setResetPinPullResistor                                       \
        ((void ( __cc_rom *)(uint16_t pullResistorSetup))ROM_SFRTABLE[4])

#define ROM_SFR_setNMIEdge                                                    \
        ((void ( __cc_rom *)(uint16_t edgeDirection))ROM_SFRTABLE[5])

#define ROM_SFR_setResetNMIPinFunction                                        \
        ((void ( __cc_rom *)(uint8_t resetPinFunction))ROM_SFRTABLE[6])

//*****************************************************************************
//
// Macros for calling ROM functions in the SYSCTL API.
//
//*****************************************************************************

#define ROM_SysCtl_enableDedicatedJTAGPins                                    \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[0])

#define ROM_SysCtl_getBSLEntryIndication                                      \
        ((uint8_t ( __cc_rom *)(void))ROM_SYSCTLTABLE[1])

#define ROM_SysCtl_enablePMMAccessProtect                                     \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[2])

#define ROM_SysCtl_enableRAMBasedInterruptVectors                             \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[3])

#define ROM_SysCtl_disableRAMBasedInterruptVectors                            \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[4])

#define ROM_SysCtl_enableBSLProtect                                           \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[5])

#define ROM_SysCtl_disableBSLProtect                                          \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[6])

#define ROM_SysCtl_enableBSLMemory                                            \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[7])

#define ROM_SysCtl_disableBSLMemory                                           \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[8])

#define ROM_SysCtl_setRAMAssignedToBSL                                        \
        ((void ( __cc_rom *)(uint8_t BSLRAMAssignment))ROM_SYSCTLTABLE[9])

#define ROM_SysCtl_initJTAGMailbox                                            \
        ((void ( __cc_rom *)(uint8_t mailboxSizeSelect,                       \
                             uint8_t autoClearInboxFlagSelect))ROM_SYSCTLTABLE[10])

#define ROM_SysCtl_getJTAGMailboxFlagStatus                                   \
        ((uint8_t ( __cc_rom *)(uint8_t mailboxFlagMask))ROM_SYSCTLTABLE[11])

#define ROM_SysCtl_clearJTAGMailboxFlagStatus                                 \
        ((void ( __cc_rom *)(uint8_t mailboxFlagMask))ROM_SYSCTLTABLE[12])

#define ROM_SysCtl_getJTAGInboxMessage16Bit                                   \
        ((uint16_t ( __cc_rom *)(uint8_t inboxSelect))ROM_SYSCTLTABLE[13])

#define ROM_SysCtl_getJTAGInboxMessage32Bit                                   \
        ((uint32_t ( __cc_rom *)(void))ROM_SYSCTLTABLE[14])

#define ROM_SysCtl_setJTAGOutgoingMessage16Bit                                \
        ((void ( __cc_rom *)(uint8_t outboxSelect,                            \
                             uint16_t outgoingMessage))ROM_SYSCTLTABLE[15])

#define ROM_SysCtl_setJTAGOutgoingMessage32Bit                                \
        ((void ( __cc_rom *)(uint32_t outgoingMessage))ROM_SYSCTLTABLE[16])

#define ROM_SysCtl_protectFRAMWrite                                           \
        ((void ( __cc_rom *)(uint8_t writeProtect))ROM_SYSCTLTABLE[17])

#define ROM_SysCtl_enableFRAMWrite                                            \
        ((void ( __cc_rom *)(uint8_t writeEnable))ROM_SYSCTLTABLE[18])

#define ROM_SysCtl_setInfraredConfig                                          \
        ((void ( __cc_rom *)(uint8_t dataSource,                              \
                             uint8_t mode,                                    \
                             uint8_t polarity))ROM_SYSCTLTABLE[19])

#define ROM_SysCtl_enableInfrared                                             \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[20])

#define ROM_SysCtl_disableInfrared                                            \
        ((void ( __cc_rom *)(void))ROM_SYSCTLTABLE[21])

#define ROM_SysCtl_getInfraredData                                            \
        ((uint8_t ( __cc_rom *)(void))ROM_SYSCTLTABLE[22])

#define ROM_SysCtl_setFRWPOA                                                  \
        ((void ( __cc_rom *)(uint8_t offsetAddress))ROM_SYSCTLTABLE[23])

#define ROM_SysCtl_setHARTCLK                                                 \
        ((void ( __cc_rom *)(uint8_t clockSource))ROM_SYSCTLTABLE[24])

#define ROM_SysCtl_setHARTMOD                                                 \
        ((void ( __cc_rom *)(uint8_t mode))ROM_SYSCTLTABLE[25])

//*****************************************************************************
//
// Macros for calling ROM functions in the TIMERB API.
//
//*****************************************************************************

#define ROM_Timer_B_startCounter                                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t timerMode))ROM_TIMER_BTABLE[0])

#define ROM_Timer_B_initContinuousMode                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             Timer_B_initContinuousModeParam *param))ROM_TIMER_BTABLE[1])

#define ROM_Timer_B_initUpMode                                                \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             Timer_B_initUpModeParam *param))ROM_TIMER_BTABLE[2])

#define ROM_Timer_B_initUpDownMode                                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             Timer_B_initUpDownModeParam *param))ROM_TIMER_BTABLE[3])

#define ROM_Timer_B_initCaptureMode                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             Timer_B_initCaptureModeParam *param))ROM_TIMER_BTABLE[4])

#define ROM_Timer_B_initCompareMode                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             Timer_B_initCompareModeParam *param))ROM_TIMER_BTABLE[5])

#define ROM_Timer_B_enableInterrupt                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_TIMER_BTABLE[6])

#define ROM_Timer_B_disableInterrupt                                          \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_TIMER_BTABLE[7])

#define ROM_Timer_B_getInterruptStatus                                        \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress))ROM_TIMER_BTABLE[8])

#define ROM_Timer_B_enableCaptureCompareInterrupt                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t captureCompareRegister))ROM_TIMER_BTABLE[9])

#define ROM_Timer_B_disableCaptureCompareInterrupt                            \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t captureCompareRegister))ROM_TIMER_BTABLE[10])

#define ROM_Timer_B_getCaptureCompareInterruptStatus                          \
        ((uint32_t ( __cc_rom *)(uint16_t baseAddress,                        \
                                 uint16_t captureCompareRegister,             \
                                 uint16_t mask))ROM_TIMER_BTABLE[11])

#define ROM_Timer_B_clear                                                     \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_TIMER_BTABLE[12])

#define ROM_Timer_B_getSynchronizedCaptureCompareInput                        \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint16_t captureCompareRegister,              \
                                uint16_t synchronized))ROM_TIMER_BTABLE[13])

#define ROM_Timer_B_getOutputForOutputModeOutBitValue                         \
        ((uint8_t ( __cc_rom *)(uint16_t baseAddress,                         \
                                uint16_t captureCompareRegister))ROM_TIMER_BTABLE[14])

#define ROM_Timer_B_getCaptureCompareCount                                    \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress,                        \
                                 uint16_t captureCompareRegister))ROM_TIMER_BTABLE[15])

#define ROM_Timer_B_setOutputForOutputModeOutBitValue                         \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t captureCompareRegister,                 \
                             uint8_t outputModeOutBitValue))ROM_TIMER_BTABLE[16])

#define ROM_Timer_B_outputPWM                                                 \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             Timer_B_outputPWMParam *param))ROM_TIMER_BTABLE[17])

#define ROM_Timer_B_stop                                                      \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_TIMER_BTABLE[18])

#define ROM_Timer_B_setCompareValue                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t compareRegister,                        \
                             uint16_t compareValue))ROM_TIMER_BTABLE[19])

#define ROM_Timer_B_clearTimerInterrupt                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_TIMER_BTABLE[20])

#define ROM_Timer_B_clearCaptureCompareInterrupt                              \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t captureCompareRegister))ROM_TIMER_BTABLE[21])

#define ROM_Timer_B_selectCounterLength                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t counterLength))ROM_TIMER_BTABLE[22])

#define ROM_Timer_B_selectLatchingGroup                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t groupLatch))ROM_TIMER_BTABLE[23])

#define ROM_Timer_B_initCompareLatchLoadEvent                                 \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t compareRegister,                        \
                             uint16_t compareLatchLoadEvent))ROM_TIMER_BTABLE[24])

#define ROM_Timer_B_getCounterValue                                           \
        ((uint16_t ( __cc_rom *)(uint16_t baseAddress))ROM_TIMER_BTABLE[25])

#define ROM_Timer_B_setOutputMode                                             \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint16_t compareRegister,                        \
                             uint16_t compareOutputMode))ROM_TIMER_BTABLE[26])

#define ROM_Timer_B_selectOutputHighImpedanceTrigger                          \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t triggerSelect))ROM_TIMER_BTABLE[27])

//*****************************************************************************
//
// Macros for calling ROM functions in the TLV API.
//
//*****************************************************************************

#define ROM_TLV_getInfo                                                       \
        ((void ( __cc_rom *)(uint8_t tag,                                     \
                             uint8_t instance,                                \
                             uint8_t *length,                                 \
                             uint16_t **data_address))ROM_TLVTABLE[0])

#define ROM_TLV_getDeviceType                                                 \
        ((uint16_t ( __cc_rom *)(void))ROM_TLVTABLE[1])

#define ROM_TLV_getMemory                                                     \
        ((uint16_t ( __cc_rom *)(uint8_t instance))ROM_TLVTABLE[2])

#define ROM_TLV_getPeripheral                                                 \
        ((uint16_t ( __cc_rom *)(uint8_t tag,                                 \
                                 uint8_t instance))ROM_TLVTABLE[3])

#define ROM_TLV_getInterrupt                                                  \
        ((uint8_t ( __cc_rom *)(uint8_t tag))ROM_TLVTABLE[4])

//*****************************************************************************
//
// Macros for calling ROM functions in the WDTA API.
//
//*****************************************************************************

#define ROM_WDT_A_hold                                                        \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_WDTATABLE[0])

#define ROM_WDT_A_start                                                       \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_WDTATABLE[1])

#define ROM_WDT_A_resetTimer                                                  \
        ((void ( __cc_rom *)(uint16_t baseAddress))ROM_WDTATABLE[2])

#define ROM_WDT_A_initWatchdogTimer                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t clockSelect,                             \
                             uint8_t clockDivider))ROM_WDTATABLE[3])

#define ROM_WDT_A_initIntervalTimer                                           \
        ((void ( __cc_rom *)(uint16_t baseAddress,                            \
                             uint8_t clockSelect,                             \
                             uint8_t clockDivider))ROM_WDTATABLE[4])

#else
#error "Small code model is not supported because ROM lives above 64k memory."
#endif

#endif // __ROM_DRIVERLIB_H__

