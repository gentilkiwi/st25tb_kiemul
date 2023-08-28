//*****************************************************************************
//
// rom_map_driverlib.h - Macros to facilitate calling DriverLib functions in
//             ROM when they are available and in FRAM otherwise.
//
// Copyright (c) 2017 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//
//*****************************************************************************

#ifndef __ROM_MAP_DRIVERLIB_H__
#define __ROM_MAP_DRIVERLIB_H__

//*****************************************************************************
//
// Macros for the ADC API.
//
//*****************************************************************************
#ifdef ROM_ADC_init
#define MAP_ADC_init                                                          \
        ROM_ADC_init
#else
#define MAP_ADC_init                                                          \
        ADC_init
#endif
#ifdef ROM_ADC_enable
#define MAP_ADC_enable                                                        \
        ROM_ADC_enable
#else
#define MAP_ADC_enable                                                        \
        ADC_enable
#endif
#ifdef ROM_ADC_disable
#define MAP_ADC_disable                                                       \
        ROM_ADC_disable
#else
#define MAP_ADC_disable                                                       \
        ADC_disable
#endif
#ifdef ROM_ADC_setupSamplingTimer
#define MAP_ADC_setupSamplingTimer                                            \
        ROM_ADC_setupSamplingTimer
#else
#define MAP_ADC_setupSamplingTimer                                            \
        ADC_setupSamplingTimer
#endif
#ifdef ROM_ADC_disableSamplingTimer
#define MAP_ADC_disableSamplingTimer                                          \
        ROM_ADC_disableSamplingTimer
#else
#define MAP_ADC_disableSamplingTimer                                          \
        ADC_disableSamplingTimer
#endif
#ifdef ROM_ADC_configureMemory
#define MAP_ADC_configureMemory                                               \
        ROM_ADC_configureMemory
#else
#define MAP_ADC_configureMemory                                               \
        ADC_configureMemory
#endif
#ifdef ROM_ADC_enableInterrupt
#define MAP_ADC_enableInterrupt                                               \
        ROM_ADC_enableInterrupt
#else
#define MAP_ADC_enableInterrupt                                               \
        ADC_enableInterrupt
#endif
#ifdef ROM_ADC_disableInterrupt
#define MAP_ADC_disableInterrupt                                              \
        ROM_ADC_disableInterrupt
#else
#define MAP_ADC_disableInterrupt                                              \
        ADC_disableInterrupt
#endif
#ifdef ROM_ADC_clearInterrupt
#define MAP_ADC_clearInterrupt                                                \
        ROM_ADC_clearInterrupt
#else
#define MAP_ADC_clearInterrupt                                                \
        ADC_clearInterrupt
#endif
#ifdef ROM_ADC_getInterruptStatus
#define MAP_ADC_getInterruptStatus                                            \
        ROM_ADC_getInterruptStatus
#else
#define MAP_ADC_getInterruptStatus                                            \
        ADC_getInterruptStatus
#endif
#ifdef ROM_ADC_startConversion
#define MAP_ADC_startConversion                                               \
        ROM_ADC_startConversion
#else
#define MAP_ADC_startConversion                                               \
        ADC_startConversion
#endif
#ifdef ROM_ADC_disableConversions
#define MAP_ADC_disableConversions                                            \
        ROM_ADC_disableConversions
#else
#define MAP_ADC_disableConversions                                            \
        ADC_disableConversions
#endif
#ifdef ROM_ADC_getResults
#define MAP_ADC_getResults                                                    \
        ROM_ADC_getResults
#else
#define MAP_ADC_getResults                                                    \
        ADC_getResults
#endif
#ifdef ROM_ADC_setResolution
#define MAP_ADC_setResolution                                                 \
        ROM_ADC_setResolution
#else
#define MAP_ADC_setResolution                                                 \
        ADC_setResolution
#endif
#ifdef ROM_ADC_setSampleHoldSignalInversion
#define MAP_ADC_setSampleHoldSignalInversion                                  \
        ROM_ADC_setSampleHoldSignalInversion
#else
#define MAP_ADC_setSampleHoldSignalInversion                                  \
        ADC_setSampleHoldSignalInversion
#endif
#ifdef ROM_ADC_setDataReadBackFormat
#define MAP_ADC_setDataReadBackFormat                                         \
        ROM_ADC_setDataReadBackFormat
#else
#define MAP_ADC_setDataReadBackFormat                                         \
        ADC_setDataReadBackFormat
#endif
#ifdef ROM_ADC_setReferenceBufferSamplingRate
#define MAP_ADC_setReferenceBufferSamplingRate                                \
        ROM_ADC_setReferenceBufferSamplingRate
#else
#define MAP_ADC_setReferenceBufferSamplingRate                                \
        ADC_setReferenceBufferSamplingRate
#endif
#ifdef ROM_ADC_setWindowComp
#define MAP_ADC_setWindowComp                                                 \
        ROM_ADC_setWindowComp
#else
#define MAP_ADC_setWindowComp                                                 \
        ADC_setWindowComp
#endif
#ifdef ROM_ADC_getMemoryAddressForDMA
#define MAP_ADC_getMemoryAddressForDMA                                        \
        ROM_ADC_getMemoryAddressForDMA
#else
#define MAP_ADC_getMemoryAddressForDMA                                        \
        ADC_getMemoryAddressForDMA
#endif
#ifdef ROM_ADC_isBusy
#define MAP_ADC_isBusy                                                        \
        ROM_ADC_isBusy
#else
#define MAP_ADC_isBusy                                                        \
        ADC_isBusy
#endif

//*****************************************************************************
//
// Macros for the CRC API.
//
//*****************************************************************************
#ifdef ROM_CRC_setSeed
#define MAP_CRC_setSeed                                                       \
        ROM_CRC_setSeed
#else
#define MAP_CRC_setSeed                                                       \
        CRC_setSeed
#endif
#ifdef ROM_CRC_set16BitData
#define MAP_CRC_set16BitData                                                  \
        ROM_CRC_set16BitData
#else
#define MAP_CRC_set16BitData                                                  \
        CRC_set16BitData
#endif
#ifdef ROM_CRC_set8BitData
#define MAP_CRC_set8BitData                                                   \
        ROM_CRC_set8BitData
#else
#define MAP_CRC_set8BitData                                                   \
        CRC_set8BitData
#endif
#ifdef ROM_CRC_set16BitDataReversed
#define MAP_CRC_set16BitDataReversed                                          \
        ROM_CRC_set16BitDataReversed
#else
#define MAP_CRC_set16BitDataReversed                                          \
        CRC_set16BitDataReversed
#endif
#ifdef ROM_CRC_set8BitDataReversed
#define MAP_CRC_set8BitDataReversed                                           \
        ROM_CRC_set8BitDataReversed
#else
#define MAP_CRC_set8BitDataReversed                                           \
        CRC_set8BitDataReversed
#endif
#ifdef ROM_CRC_getData
#define MAP_CRC_getData                                                       \
        ROM_CRC_getData
#else
#define MAP_CRC_getData                                                       \
        CRC_getData
#endif
#ifdef ROM_CRC_getResult
#define MAP_CRC_getResult                                                     \
        ROM_CRC_getResult
#else
#define MAP_CRC_getResult                                                     \
        CRC_getResult
#endif
#ifdef ROM_CRC_getResultBitsReversed
#define MAP_CRC_getResultBitsReversed                                         \
        ROM_CRC_getResultBitsReversed
#else
#define MAP_CRC_getResultBitsReversed                                         \
        CRC_getResultBitsReversed
#endif

//*****************************************************************************
//
// Macros for the CS API.
//
//*****************************************************************************
#ifdef ROM_CS_setExternalClockSource
#define MAP_CS_setExternalClockSource                                         \
        ROM_CS_setExternalClockSource
#else
#define MAP_CS_setExternalClockSource                                         \
        CS_setExternalClockSource
#endif
#ifdef ROM_CS_initClockSignal
#define MAP_CS_initClockSignal                                                \
        ROM_CS_initClockSignal
#else
#define MAP_CS_initClockSignal                                                \
        CS_initClockSignal
#endif
#ifdef ROM_CS_turnOnXT1LF
#define MAP_CS_turnOnXT1LF                                                    \
        ROM_CS_turnOnXT1LF
#else
#define MAP_CS_turnOnXT1LF                                                    \
        CS_turnOnXT1LF
#endif
#ifdef ROM_CS_bypassXT1
#define MAP_CS_bypassXT1                                                      \
        ROM_CS_bypassXT1
#else
#define MAP_CS_bypassXT1                                                      \
        CS_bypassXT1
#endif
#ifdef ROM_CS_turnOnXT1LFWithTimeout
#define MAP_CS_turnOnXT1LFWithTimeout                                         \
        ROM_CS_turnOnXT1LFWithTimeout
#else
#define MAP_CS_turnOnXT1LFWithTimeout                                         \
        CS_turnOnXT1LFWithTimeout
#endif
#ifdef ROM_CS_bypassXT1WithTimeout
#define MAP_CS_bypassXT1WithTimeout                                           \
        ROM_CS_bypassXT1WithTimeout
#else
#define MAP_CS_bypassXT1WithTimeout                                           \
        CS_bypassXT1WithTimeout
#endif
#ifdef ROM_CS_turnOffXT1
#define MAP_CS_turnOffXT1                                                     \
        ROM_CS_turnOffXT1
#else
#define MAP_CS_turnOffXT1                                                     \
        CS_turnOffXT1
#endif
#ifdef ROM_CS_turnOnXT1HF
#define MAP_CS_turnOnXT1HF                                                    \
        ROM_CS_turnOnXT1HF
#else
#define MAP_CS_turnOnXT1HF                                                    \
        CS_turnOnXT1HF
#endif
#ifdef ROM_CS_turnOnXT1HFWithTimeout
#define MAP_CS_turnOnXT1HFWithTimeout                                         \
        ROM_CS_turnOnXT1HFWithTimeout
#else
#define MAP_CS_turnOnXT1HFWithTimeout                                         \
        CS_turnOnXT1HFWithTimeout
#endif
#ifdef ROM_CS_turnOnSMCLK
#define MAP_CS_turnOnSMCLK                                                    \
        ROM_CS_turnOnSMCLK
#else
#define MAP_CS_turnOnSMCLK                                                    \
        CS_turnOnSMCLK
#endif
#ifdef ROM_CS_turnOffSMCLK
#define MAP_CS_turnOffSMCLK                                                   \
        ROM_CS_turnOffSMCLK
#else
#define MAP_CS_turnOffSMCLK                                                   \
        CS_turnOffSMCLK
#endif
#ifdef ROM_CS_enableVLOAutoOff
#define MAP_CS_enableVLOAutoOff                                               \
        ROM_CS_enableVLOAutoOff
#else
#define MAP_CS_enableVLOAutoOff                                               \
        CS_enableVLOAutoOff
#endif
#ifdef ROM_CS_disableVLOAutoOff
#define MAP_CS_disableVLOAutoOff                                              \
        ROM_CS_disableVLOAutoOff
#else
#define MAP_CS_disableVLOAutoOff                                              \
        CS_disableVLOAutoOff
#endif
#ifdef ROM_CS_initFLLSettle
#define MAP_CS_initFLLSettle                                                  \
        ROM_CS_initFLLSettle
#else
#define MAP_CS_initFLLSettle                                                  \
        CS_initFLLSettle
#endif
#ifdef ROM_CS_initFLL
#define MAP_CS_initFLL                                                        \
        ROM_CS_initFLL
#else
#define MAP_CS_initFLL                                                        \
        CS_initFLL
#endif
#ifdef ROM_CS_initFLLCalculateTrim
#define MAP_CS_initFLLCalculateTrim                                           \
        ROM_CS_initFLLCalculateTrim
#else
#define MAP_CS_initFLLCalculateTrim                                           \
        CS_initFLLCalculateTrim
#endif
#ifdef ROM_CS_initFLLLoadTrim
#define MAP_CS_initFLLLoadTrim                                                \
        ROM_CS_initFLLLoadTrim
#else
#define MAP_CS_initFLLLoadTrim                                                \
        CS_initFLLLoadTrim
#endif
#ifdef ROM_CS_enableClockRequest
#define MAP_CS_enableClockRequest                                             \
        ROM_CS_enableClockRequest
#else
#define MAP_CS_enableClockRequest                                             \
        CS_enableClockRequest
#endif
#ifdef ROM_CS_disableClockRequest
#define MAP_CS_disableClockRequest                                            \
        ROM_CS_disableClockRequest
#else
#define MAP_CS_disableClockRequest                                            \
        CS_disableClockRequest
#endif
#ifdef ROM_CS_getFaultFlagStatus
#define MAP_CS_getFaultFlagStatus                                             \
        ROM_CS_getFaultFlagStatus
#else
#define MAP_CS_getFaultFlagStatus                                             \
        CS_getFaultFlagStatus
#endif
#ifdef ROM_CS_clearFaultFlag
#define MAP_CS_clearFaultFlag                                                 \
        ROM_CS_clearFaultFlag
#else
#define MAP_CS_clearFaultFlag                                                 \
        CS_clearFaultFlag
#endif
#ifdef ROM_CS_getACLK
#define MAP_CS_getACLK                                                        \
        ROM_CS_getACLK
#else
#define MAP_CS_getACLK                                                        \
        CS_getACLK
#endif
#ifdef ROM_CS_getSMCLK
#define MAP_CS_getSMCLK                                                       \
        ROM_CS_getSMCLK
#else
#define MAP_CS_getSMCLK                                                       \
        CS_getSMCLK
#endif
#ifdef ROM_CS_getMCLK
#define MAP_CS_getMCLK                                                        \
        ROM_CS_getMCLK
#else
#define MAP_CS_getMCLK                                                        \
        CS_getMCLK
#endif
#ifdef ROM_CS_clearAllOscFlagsWithTimeout
#define MAP_CS_clearAllOscFlagsWithTimeout                                    \
        ROM_CS_clearAllOscFlagsWithTimeout
#else
#define MAP_CS_clearAllOscFlagsWithTimeout                                    \
        CS_clearAllOscFlagsWithTimeout
#endif
#ifdef ROM_CS_enableXT1AutomaticGainControl
#define MAP_CS_enableXT1AutomaticGainControl                                  \
        ROM_CS_enableXT1AutomaticGainControl
#else
#define MAP_CS_enableXT1AutomaticGainControl                                  \
        CS_enableXT1AutomaticGainControl
#endif
#ifdef ROM_CS_disableXT1AutomaticGainControl
#define MAP_CS_disableXT1AutomaticGainControl                                 \
        ROM_CS_disableXT1AutomaticGainControl
#else
#define MAP_CS_disableXT1AutomaticGainControl                                 \
        CS_disableXT1AutomaticGainControl
#endif
#ifdef ROM_CS_enableFLLUnlock
#define MAP_CS_enableFLLUnlock                                                \
        ROM_CS_enableFLLUnlock
#else
#define MAP_CS_enableFLLUnlock                                                \
        CS_enableFLLUnlock
#endif
#ifdef ROM_CS_disableFLLUnlock
#define MAP_CS_disableFLLUnlock                                               \
        ROM_CS_disableFLLUnlock
#else
#define MAP_CS_disableFLLUnlock                                               \
        CS_disableFLLUnlock
#endif
#ifdef ROM_CS_enableREFOLP
#define MAP_CS_enableREFOLP                                                   \
        ROM_CS_enableREFOLP
#else
#define MAP_CS_enableREFOLP                                                   \
        CS_enableREFOLP
#endif
#ifdef ROM_CS_disableREFOLP
#define MAP_CS_disableREFOLP                                                  \
        ROM_CS_disableREFOLP
#else
#define MAP_CS_disableREFOLP                                                  \
        CS_disableREFOLP
#endif
#ifdef ROM_CS_getREFOLP
#define MAP_CS_getREFOLP                                                      \
        ROM_CS_getREFOLP
#else
#define MAP_CS_getREFOLP                                                      \
        CS_getREFOLP
#endif
#ifdef ROM_CS_enableXT1FaultOff
#define MAP_CS_enableXT1FaultOff                                              \
        ROM_CS_enableXT1FaultOff
#else
#define MAP_CS_enableXT1FaultOff                                              \
        CS_enableXT1FaultOff
#endif
#ifdef ROM_CS_disableXT1FaultOff
#define MAP_CS_disableXT1FaultOff                                             \
        ROM_CS_disableXT1FaultOff
#else
#define MAP_CS_disableXT1FaultOff                                             \
        CS_disableXT1FaultOff
#endif
#ifdef ROM_CS_getXT1FaultOff
#define MAP_CS_getXT1FaultOff                                                 \
        ROM_CS_getXT1FaultOff
#else
#define MAP_CS_getXT1FaultOff                                                 \
        CS_getXT1FaultOff
#endif
#ifdef ROM_CS_getREFOReady
#define MAP_CS_getREFOReady                                                   \
        ROM_CS_getREFOReady
#else
#define MAP_CS_getREFOReady                                                   \
        CS_getREFOReady
#endif

//*****************************************************************************
//
// Macros for the ECOMP API.
//
//*****************************************************************************
#ifdef ROM_EComp_init
#define MAP_EComp_init                                                        \
        ROM_EComp_init
#else
#define MAP_EComp_init                                                        \
        EComp_init
#endif
#ifdef ROM_EComp_selectHysteresisMode
#define MAP_EComp_selectHysteresisMode                                        \
        ROM_EComp_selectHysteresisMode
#else
#define MAP_EComp_selectHysteresisMode                                        \
        EComp_selectHysteresisMode
#endif
#ifdef ROM_EComp_selectPowerMode
#define MAP_EComp_selectPowerMode                                             \
        ROM_EComp_selectPowerMode
#else
#define MAP_EComp_selectPowerMode                                             \
        EComp_selectPowerMode
#endif
#ifdef ROM_EComp_enable
#define MAP_EComp_enable                                                      \
        ROM_EComp_enable
#else
#define MAP_EComp_enable                                                      \
        EComp_enable
#endif
#ifdef ROM_EComp_disable
#define MAP_EComp_disable                                                     \
        ROM_EComp_disable
#else
#define MAP_EComp_disable                                                     \
        EComp_disable
#endif
#ifdef ROM_EComp_enableInterrupt
#define MAP_EComp_enableInterrupt                                             \
        ROM_EComp_enableInterrupt
#else
#define MAP_EComp_enableInterrupt                                             \
        EComp_enableInterrupt
#endif
#ifdef ROM_EComp_disableInterrupt
#define MAP_EComp_disableInterrupt                                            \
        ROM_EComp_disableInterrupt
#else
#define MAP_EComp_disableInterrupt                                            \
        EComp_disableInterrupt
#endif
#ifdef ROM_EComp_clearInterrupt
#define MAP_EComp_clearInterrupt                                              \
        ROM_EComp_clearInterrupt
#else
#define MAP_EComp_clearInterrupt                                              \
        EComp_clearInterrupt
#endif
#ifdef ROM_EComp_getInterruptStatus
#define MAP_EComp_getInterruptStatus                                          \
        ROM_EComp_getInterruptStatus
#else
#define MAP_EComp_getInterruptStatus                                          \
        EComp_getInterruptStatus
#endif
#ifdef ROM_EComp_setInterruptEdgeDirection
#define MAP_EComp_setInterruptEdgeDirection                                   \
        ROM_EComp_setInterruptEdgeDirection
#else
#define MAP_EComp_setInterruptEdgeDirection                                   \
        EComp_setInterruptEdgeDirection
#endif
#ifdef ROM_EComp_toggleInterruptEdgeDirection
#define MAP_EComp_toggleInterruptEdgeDirection                                \
        ROM_EComp_toggleInterruptEdgeDirection
#else
#define MAP_EComp_toggleInterruptEdgeDirection                                \
        EComp_toggleInterruptEdgeDirection
#endif
#ifdef ROM_EComp_outputValue
#define MAP_EComp_outputValue                                                 \
        ROM_EComp_outputValue
#else
#define MAP_EComp_outputValue                                                 \
        EComp_outputValue
#endif
#ifdef ROM_EComp_configureDAC
#define MAP_EComp_configureDAC                                                \
        ROM_EComp_configureDAC
#else
#define MAP_EComp_configureDAC                                                \
        EComp_configureDAC
#endif
#ifdef ROM_EComp_enableDAC
#define MAP_EComp_enableDAC                                                   \
        ROM_EComp_enableDAC
#else
#define MAP_EComp_enableDAC                                                   \
        EComp_enableDAC
#endif
#ifdef ROM_EComp_disableDAC
#define MAP_EComp_disableDAC                                                  \
        ROM_EComp_disableDAC
#else
#define MAP_EComp_disableDAC                                                  \
        EComp_disableDAC
#endif

//*****************************************************************************
//
// Macros for the EUSCI_A_SPI API.
//
//*****************************************************************************
#ifdef ROM_EUSCI_A_SPI_initMaster
#define MAP_EUSCI_A_SPI_initMaster                                            \
        ROM_EUSCI_A_SPI_initMaster
#else
#define MAP_EUSCI_A_SPI_initMaster                                            \
        EUSCI_A_SPI_initMaster
#endif
#ifdef ROM_EUSCI_A_SPI_select4PinFunctionality
#define MAP_EUSCI_A_SPI_select4PinFunctionality                               \
        ROM_EUSCI_A_SPI_select4PinFunctionality
#else
#define MAP_EUSCI_A_SPI_select4PinFunctionality                               \
        EUSCI_A_SPI_select4PinFunctionality
#endif
#ifdef ROM_EUSCI_A_SPI_changeMasterClock
#define MAP_EUSCI_A_SPI_changeMasterClock                                     \
        ROM_EUSCI_A_SPI_changeMasterClock
#else
#define MAP_EUSCI_A_SPI_changeMasterClock                                     \
        EUSCI_A_SPI_changeMasterClock
#endif
#ifdef ROM_EUSCI_A_SPI_initSlave
#define MAP_EUSCI_A_SPI_initSlave                                             \
        ROM_EUSCI_A_SPI_initSlave
#else
#define MAP_EUSCI_A_SPI_initSlave                                             \
        EUSCI_A_SPI_initSlave
#endif
#ifdef ROM_EUSCI_A_SPI_changeClockPhasePolarity
#define MAP_EUSCI_A_SPI_changeClockPhasePolarity                              \
        ROM_EUSCI_A_SPI_changeClockPhasePolarity
#else
#define MAP_EUSCI_A_SPI_changeClockPhasePolarity                              \
        EUSCI_A_SPI_changeClockPhasePolarity
#endif
#ifdef ROM_EUSCI_A_SPI_transmitData
#define MAP_EUSCI_A_SPI_transmitData                                          \
        ROM_EUSCI_A_SPI_transmitData
#else
#define MAP_EUSCI_A_SPI_transmitData                                          \
        EUSCI_A_SPI_transmitData
#endif
#ifdef ROM_EUSCI_A_SPI_receiveData
#define MAP_EUSCI_A_SPI_receiveData                                           \
        ROM_EUSCI_A_SPI_receiveData
#else
#define MAP_EUSCI_A_SPI_receiveData                                           \
        EUSCI_A_SPI_receiveData
#endif
#ifdef ROM_EUSCI_A_SPI_enableInterrupt
#define MAP_EUSCI_A_SPI_enableInterrupt                                       \
        ROM_EUSCI_A_SPI_enableInterrupt
#else
#define MAP_EUSCI_A_SPI_enableInterrupt                                       \
        EUSCI_A_SPI_enableInterrupt
#endif
#ifdef ROM_EUSCI_A_SPI_disableInterrupt
#define MAP_EUSCI_A_SPI_disableInterrupt                                      \
        ROM_EUSCI_A_SPI_disableInterrupt
#else
#define MAP_EUSCI_A_SPI_disableInterrupt                                      \
        EUSCI_A_SPI_disableInterrupt
#endif
#ifdef ROM_EUSCI_A_SPI_getInterruptStatus
#define MAP_EUSCI_A_SPI_getInterruptStatus                                    \
        ROM_EUSCI_A_SPI_getInterruptStatus
#else
#define MAP_EUSCI_A_SPI_getInterruptStatus                                    \
        EUSCI_A_SPI_getInterruptStatus
#endif
#ifdef ROM_EUSCI_A_SPI_clearInterrupt
#define MAP_EUSCI_A_SPI_clearInterrupt                                        \
        ROM_EUSCI_A_SPI_clearInterrupt
#else
#define MAP_EUSCI_A_SPI_clearInterrupt                                        \
        EUSCI_A_SPI_clearInterrupt
#endif
#ifdef ROM_EUSCI_A_SPI_enable
#define MAP_EUSCI_A_SPI_enable                                                \
        ROM_EUSCI_A_SPI_enable
#else
#define MAP_EUSCI_A_SPI_enable                                                \
        EUSCI_A_SPI_enable
#endif
#ifdef ROM_EUSCI_A_SPI_disable
#define MAP_EUSCI_A_SPI_disable                                               \
        ROM_EUSCI_A_SPI_disable
#else
#define MAP_EUSCI_A_SPI_disable                                               \
        EUSCI_A_SPI_disable
#endif
#ifdef ROM_EUSCI_A_SPI_getReceiveBufferAddress
#define MAP_EUSCI_A_SPI_getReceiveBufferAddress                               \
        ROM_EUSCI_A_SPI_getReceiveBufferAddress
#else
#define MAP_EUSCI_A_SPI_getReceiveBufferAddress                               \
        EUSCI_A_SPI_getReceiveBufferAddress
#endif
#ifdef ROM_EUSCI_A_SPI_getTransmitBufferAddress
#define MAP_EUSCI_A_SPI_getTransmitBufferAddress \
    ROM_EUSCI_A_SPI_getTransmitBufferAddress
#else
#define MAP_EUSCI_A_SPI_getTransmitBufferAddress \
    EUSCI_A_SPI_getTransmitBufferAddress
#endif
#ifdef ROM_EUSCI_A_SPI_isBusy
#define MAP_EUSCI_A_SPI_isBusy                                                \
        ROM_EUSCI_A_SPI_isBusy
#else
#define MAP_EUSCI_A_SPI_isBusy                                                \
        EUSCI_A_SPI_isBusy
#endif
#ifdef ROM_EUSCI_A_SPI_remapPins
#define MAP_EUSCI_A_SPI_remapPins                                             \
        ROM_EUSCI_A_SPI_remapPins
#else
#define MAP_EUSCI_A_SPI_remapPins                                             \
        EUSCI_A_SPI_remapPins
#endif

//*****************************************************************************
//
// Macros for the EUSCI_A_UART API.
//
//*****************************************************************************
#ifdef ROM_EUSCI_A_UART_init
#define MAP_EUSCI_A_UART_init                                                 \
        ROM_EUSCI_A_UART_init
#else
#define MAP_EUSCI_A_UART_init                                                 \
        EUSCI_A_UART_init
#endif
#ifdef ROM_EUSCI_A_UART_transmitData
#define MAP_EUSCI_A_UART_transmitData                                         \
        ROM_EUSCI_A_UART_transmitData
#else
#define MAP_EUSCI_A_UART_transmitData                                         \
        EUSCI_A_UART_transmitData
#endif
#ifdef ROM_EUSCI_A_UART_receiveData
#define MAP_EUSCI_A_UART_receiveData                                          \
        ROM_EUSCI_A_UART_receiveData
#else
#define MAP_EUSCI_A_UART_receiveData                                          \
        EUSCI_A_UART_receiveData
#endif
#ifdef ROM_EUSCI_A_UART_enableInterrupt
#define MAP_EUSCI_A_UART_enableInterrupt                                      \
        ROM_EUSCI_A_UART_enableInterrupt
#else
#define MAP_EUSCI_A_UART_enableInterrupt                                      \
        EUSCI_A_UART_enableInterrupt
#endif
#ifdef ROM_EUSCI_A_UART_disableInterrupt
#define MAP_EUSCI_A_UART_disableInterrupt                                     \
        ROM_EUSCI_A_UART_disableInterrupt
#else
#define MAP_EUSCI_A_UART_disableInterrupt                                     \
        EUSCI_A_UART_disableInterrupt
#endif
#ifdef ROM_EUSCI_A_UART_getInterruptStatus
#define MAP_EUSCI_A_UART_getInterruptStatus                                   \
        ROM_EUSCI_A_UART_getInterruptStatus
#else
#define MAP_EUSCI_A_UART_getInterruptStatus                                   \
        EUSCI_A_UART_getInterruptStatus
#endif
#ifdef ROM_EUSCI_A_UART_clearInterrupt
#define MAP_EUSCI_A_UART_clearInterrupt                                       \
        ROM_EUSCI_A_UART_clearInterrupt
#else
#define MAP_EUSCI_A_UART_clearInterrupt                                       \
        EUSCI_A_UART_clearInterrupt
#endif
#ifdef ROM_EUSCI_A_UART_enable
#define MAP_EUSCI_A_UART_enable                                               \
        ROM_EUSCI_A_UART_enable
#else
#define MAP_EUSCI_A_UART_enable                                               \
        EUSCI_A_UART_enable
#endif
#ifdef ROM_EUSCI_A_UART_disable
#define MAP_EUSCI_A_UART_disable                                              \
        ROM_EUSCI_A_UART_disable
#else
#define MAP_EUSCI_A_UART_disable                                              \
        EUSCI_A_UART_disable
#endif
#ifdef ROM_EUSCI_A_UART_queryStatusFlags
#define MAP_EUSCI_A_UART_queryStatusFlags                                     \
        ROM_EUSCI_A_UART_queryStatusFlags
#else
#define MAP_EUSCI_A_UART_queryStatusFlags                                     \
        EUSCI_A_UART_queryStatusFlags
#endif
#ifdef ROM_EUSCI_A_UART_setDormant
#define MAP_EUSCI_A_UART_setDormant                                           \
        ROM_EUSCI_A_UART_setDormant
#else
#define MAP_EUSCI_A_UART_setDormant                                           \
        EUSCI_A_UART_setDormant
#endif
#ifdef ROM_EUSCI_A_UART_resetDormant
#define MAP_EUSCI_A_UART_resetDormant                                         \
        ROM_EUSCI_A_UART_resetDormant
#else
#define MAP_EUSCI_A_UART_resetDormant                                         \
        EUSCI_A_UART_resetDormant
#endif
#ifdef ROM_EUSCI_A_UART_transmitAddress
#define MAP_EUSCI_A_UART_transmitAddress                                      \
        ROM_EUSCI_A_UART_transmitAddress
#else
#define MAP_EUSCI_A_UART_transmitAddress                                      \
        EUSCI_A_UART_transmitAddress
#endif
#ifdef ROM_EUSCI_A_UART_transmitBreak
#define MAP_EUSCI_A_UART_transmitBreak                                        \
        ROM_EUSCI_A_UART_transmitBreak
#else
#define MAP_EUSCI_A_UART_transmitBreak                                        \
        EUSCI_A_UART_transmitBreak
#endif
#ifdef ROM_EUSCI_A_UART_getReceiveBufferAddress
#define MAP_EUSCI_A_UART_getReceiveBufferAddress                              \
        ROM_EUSCI_A_UART_getReceiveBufferAddress
#else
#define MAP_EUSCI_A_UART_getReceiveBufferAddress                              \
        EUSCI_A_UART_getReceiveBufferAddress
#endif
#ifdef ROM_EUSCI_A_UART_getTransmitBufferAddress
#define MAP_EUSCI_A_UART_getTransmitBufferAddress                             \
        ROM_EUSCI_A_UART_getTransmitBufferAddress
#else
#define MAP_EUSCI_A_UART_getTransmitBufferAddress                             \
        EUSCI_A_UART_getTransmitBufferAddress
#endif
#ifdef ROM_EUSCI_A_UART_selectDeglitchTime
#define MAP_EUSCI_A_UART_selectDeglitchTime                                   \
        ROM_EUSCI_A_UART_selectDeglitchTime
#else
#define MAP_EUSCI_A_UART_selectDeglitchTime                                   \
        EUSCI_A_UART_selectDeglitchTime
#endif
#ifdef ROM_EUSCI_A_UART_remapPins
#define MAP_EUSCI_A_UART_remapPins                                            \
        ROM_EUSCI_A_UART_remapPins
#else
#define MAP_EUSCI_A_UART_remapPins                                            \
        EUSCI_A_UART_remapPins
#endif

//*****************************************************************************
//
// Macros for the EUSCI_B_I2C API.
//
//*****************************************************************************
#ifdef ROM_EUSCI_B_I2C_initMaster
#define MAP_EUSCI_B_I2C_initMaster                                            \
        ROM_EUSCI_B_I2C_initMaster
#else
#define MAP_EUSCI_B_I2C_initMaster                                            \
        EUSCI_B_I2C_initMaster
#endif
#ifdef ROM_EUSCI_B_I2C_initSlave
#define MAP_EUSCI_B_I2C_initSlave                                             \
        ROM_EUSCI_B_I2C_initSlave
#else
#define MAP_EUSCI_B_I2C_initSlave                                             \
        EUSCI_B_I2C_initSlave
#endif
#ifdef ROM_EUSCI_B_I2C_enable
#define MAP_EUSCI_B_I2C_enable                                                \
        ROM_EUSCI_B_I2C_enable
#else
#define MAP_EUSCI_B_I2C_enable                                                \
        EUSCI_B_I2C_enable
#endif
#ifdef ROM_EUSCI_B_I2C_disable
#define MAP_EUSCI_B_I2C_disable                                               \
        ROM_EUSCI_B_I2C_disable
#else
#define MAP_EUSCI_B_I2C_disable                                               \
        EUSCI_B_I2C_disable
#endif
#ifdef ROM_EUSCI_B_I2C_setSlaveAddress
#define MAP_EUSCI_B_I2C_setSlaveAddress                                       \
        ROM_EUSCI_B_I2C_setSlaveAddress
#else
#define MAP_EUSCI_B_I2C_setSlaveAddress                                       \
        EUSCI_B_I2C_setSlaveAddress
#endif
#ifdef ROM_EUSCI_B_I2C_setMode
#define MAP_EUSCI_B_I2C_setMode                                               \
        ROM_EUSCI_B_I2C_setMode
#else
#define MAP_EUSCI_B_I2C_setMode                                               \
        EUSCI_B_I2C_setMode
#endif
#ifdef ROM_EUSCI_B_I2C_getMode
#define MAP_EUSCI_B_I2C_getMode                                               \
        ROM_EUSCI_B_I2C_getMode
#else
#define MAP_EUSCI_B_I2C_getMode                                               \
        EUSCI_B_I2C_getMode
#endif
#ifdef ROM_EUSCI_B_I2C_slavePutData
#define MAP_EUSCI_B_I2C_slavePutData                                          \
        ROM_EUSCI_B_I2C_slavePutData
#else
#define MAP_EUSCI_B_I2C_slavePutData                                          \
        EUSCI_B_I2C_slavePutData
#endif
#ifdef ROM_EUSCI_B_I2C_slaveGetData
#define MAP_EUSCI_B_I2C_slaveGetData                                          \
        ROM_EUSCI_B_I2C_slaveGetData
#else
#define MAP_EUSCI_B_I2C_slaveGetData                                          \
        EUSCI_B_I2C_slaveGetData
#endif
#ifdef ROM_EUSCI_B_I2C_isBusBusy
#define MAP_EUSCI_B_I2C_isBusBusy                                             \
        ROM_EUSCI_B_I2C_isBusBusy
#else
#define MAP_EUSCI_B_I2C_isBusBusy                                             \
        EUSCI_B_I2C_isBusBusy
#endif
#ifdef ROM_EUSCI_B_I2C_masterIsStopSent
#define MAP_EUSCI_B_I2C_masterIsStopSent                                      \
        ROM_EUSCI_B_I2C_masterIsStopSent
#else
#define MAP_EUSCI_B_I2C_masterIsStopSent                                      \
        EUSCI_B_I2C_masterIsStopSent
#endif
#ifdef ROM_EUSCI_B_I2C_masterIsStartSent
#define MAP_EUSCI_B_I2C_masterIsStartSent                                     \
        ROM_EUSCI_B_I2C_masterIsStartSent
#else
#define MAP_EUSCI_B_I2C_masterIsStartSent                                     \
        EUSCI_B_I2C_masterIsStartSent
#endif
#ifdef ROM_EUSCI_B_I2C_enableInterrupt
#define MAP_EUSCI_B_I2C_enableInterrupt                                       \
        ROM_EUSCI_B_I2C_enableInterrupt
#else
#define MAP_EUSCI_B_I2C_enableInterrupt                                       \
        EUSCI_B_I2C_enableInterrupt
#endif
#ifdef ROM_EUSCI_B_I2C_disableInterrupt
#define MAP_EUSCI_B_I2C_disableInterrupt                                      \
        ROM_EUSCI_B_I2C_disableInterrupt
#else
#define MAP_EUSCI_B_I2C_disableInterrupt                                      \
        EUSCI_B_I2C_disableInterrupt
#endif
#ifdef ROM_EUSCI_B_I2C_clearInterrupt
#define MAP_EUSCI_B_I2C_clearInterrupt                                        \
        ROM_EUSCI_B_I2C_clearInterrupt
#else
#define MAP_EUSCI_B_I2C_clearInterrupt                                        \
        EUSCI_B_I2C_clearInterrupt
#endif
#ifdef ROM_EUSCI_B_I2C_getInterruptStatus
#define MAP_EUSCI_B_I2C_getInterruptStatus                                    \
        ROM_EUSCI_B_I2C_getInterruptStatus
#else
#define MAP_EUSCI_B_I2C_getInterruptStatus                                    \
        EUSCI_B_I2C_getInterruptStatus
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendSingleByte
#define MAP_EUSCI_B_I2C_masterSendSingleByte                                  \
        ROM_EUSCI_B_I2C_masterSendSingleByte
#else
#define MAP_EUSCI_B_I2C_masterSendSingleByte                                  \
        EUSCI_B_I2C_masterSendSingleByte
#endif
#ifdef ROM_EUSCI_B_I2C_masterReceiveSingleByte
#define MAP_EUSCI_B_I2C_masterReceiveSingleByte \
    ROM_EUSCI_B_I2C_masterReceiveSingleByte
#else
#define MAP_EUSCI_B_I2C_masterReceiveSingleByte \
    EUSCI_B_I2C_masterReceiveSingleByte
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendSingleByteWithTimeout
#define MAP_EUSCI_B_I2C_masterSendSingleByteWithTimeout                       \
        ROM_EUSCI_B_I2C_masterSendSingleByteWithTimeout
#else
#define MAP_EUSCI_B_I2C_masterSendSingleByteWithTimeout                       \
        EUSCI_B_I2C_masterSendSingleByteWithTimeout
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteStart
#define MAP_EUSCI_B_I2C_masterSendMultiByteStart                              \
        ROM_EUSCI_B_I2C_masterSendMultiByteStart
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteStart                              \
        EUSCI_B_I2C_masterSendMultiByteStart
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteStartWithTimeout
#define MAP_EUSCI_B_I2C_masterSendMultiByteStartWithTimeout                   \
        ROM_EUSCI_B_I2C_masterSendMultiByteStartWithTimeout
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteStartWithTimeout                   \
        EUSCI_B_I2C_masterSendMultiByteStartWithTimeout
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteNext
#define MAP_EUSCI_B_I2C_masterSendMultiByteNext                               \
        ROM_EUSCI_B_I2C_masterSendMultiByteNext
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteNext                               \
        EUSCI_B_I2C_masterSendMultiByteNext
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteNextWithTimeout
#define MAP_EUSCI_B_I2C_masterSendMultiByteNextWithTimeout                    \
        ROM_EUSCI_B_I2C_masterSendMultiByteNextWithTimeout
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteNextWithTimeout                    \
        EUSCI_B_I2C_masterSendMultiByteNextWithTimeout
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteFinish
#define MAP_EUSCI_B_I2C_masterSendMultiByteFinish                             \
        ROM_EUSCI_B_I2C_masterSendMultiByteFinish
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteFinish                             \
        EUSCI_B_I2C_masterSendMultiByteFinish
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout
#define MAP_EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout                  \
        ROM_EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout                  \
        EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendStart
#define MAP_EUSCI_B_I2C_masterSendStart                                       \
        ROM_EUSCI_B_I2C_masterSendStart
#else
#define MAP_EUSCI_B_I2C_masterSendStart                                       \
        EUSCI_B_I2C_masterSendStart
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteStop
#define MAP_EUSCI_B_I2C_masterSendMultiByteStop                               \
        ROM_EUSCI_B_I2C_masterSendMultiByteStop
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteStop                               \
        EUSCI_B_I2C_masterSendMultiByteStop
#endif
#ifdef ROM_EUSCI_B_I2C_masterSendMultiByteStopWithTimeout
#define MAP_EUSCI_B_I2C_masterSendMultiByteStopWithTimeout                    \
        ROM_EUSCI_B_I2C_masterSendMultiByteStopWithTimeout
#else
#define MAP_EUSCI_B_I2C_masterSendMultiByteStopWithTimeout                    \
        EUSCI_B_I2C_masterSendMultiByteStopWithTimeout
#endif
#ifdef ROM_EUSCI_B_I2C_masterReceiveStart
#define MAP_EUSCI_B_I2C_masterReceiveStart                                    \
        ROM_EUSCI_B_I2C_masterReceiveStart
#else
#define MAP_EUSCI_B_I2C_masterReceiveStart                                    \
        EUSCI_B_I2C_masterReceiveStart
#endif
#ifdef ROM_EUSCI_B_I2C_masterReceiveMultiByteNext
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteNext                            \
        ROM_EUSCI_B_I2C_masterReceiveMultiByteNext
#else
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteNext                            \
        EUSCI_B_I2C_masterReceiveMultiByteNext
#endif
#ifdef ROM_EUSCI_B_I2C_masterReceiveMultiByteFinish
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteFinish                          \
        ROM_EUSCI_B_I2C_masterReceiveMultiByteFinish
#else
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteFinish                          \
        EUSCI_B_I2C_masterReceiveMultiByteFinish
#endif
#ifdef ROM_EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout               \
        ROM_EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout
#else
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout               \
        EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout
#endif
#ifdef ROM_EUSCI_B_I2C_masterReceiveMultiByteStop
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteStop                            \
        ROM_EUSCI_B_I2C_masterReceiveMultiByteStop
#else
#define MAP_EUSCI_B_I2C_masterReceiveMultiByteStop                            \
        EUSCI_B_I2C_masterReceiveMultiByteStop
#endif
#ifdef ROM_EUSCI_B_I2C_enableMultiMasterMode
#define MAP_EUSCI_B_I2C_enableMultiMasterMode                                 \
        ROM_EUSCI_B_I2C_enableMultiMasterMode
#else
#define MAP_EUSCI_B_I2C_enableMultiMasterMode                                 \
        EUSCI_B_I2C_enableMultiMasterMode
#endif
#ifdef ROM_EUSCI_B_I2C_disableMultiMasterMode
#define MAP_EUSCI_B_I2C_disableMultiMasterMode                                \
        ROM_EUSCI_B_I2C_disableMultiMasterMode
#else
#define MAP_EUSCI_B_I2C_disableMultiMasterMode                                \
        EUSCI_B_I2C_disableMultiMasterMode
#endif
#ifdef ROM_EUSCI_B_I2C_masterReceiveSingle
#define MAP_EUSCI_B_I2C_masterReceiveSingle                                   \
        ROM_EUSCI_B_I2C_masterReceiveSingle
#else
#define MAP_EUSCI_B_I2C_masterReceiveSingle                                   \
        EUSCI_B_I2C_masterReceiveSingle
#endif
#ifdef ROM_EUSCI_B_I2C_getReceiveBufferAddress
#define MAP_EUSCI_B_I2C_getReceiveBufferAddress                               \
        ROM_EUSCI_B_I2C_getReceiveBufferAddress
#else
#define MAP_EUSCI_B_I2C_getReceiveBufferAddress                               \
        EUSCI_B_I2C_getReceiveBufferAddress
#endif
#ifdef ROM_EUSCI_B_I2C_getTransmitBufferAddress
#define MAP_EUSCI_B_I2C_getTransmitBufferAddress                              \
        ROM_EUSCI_B_I2C_getTransmitBufferAddress
#else
#define MAP_EUSCI_B_I2C_getTransmitBufferAddress                              \
        EUSCI_B_I2C_getTransmitBufferAddress
#endif
#ifdef ROM_EUSCI_B_I2C_remapPins
#define MAP_EUSCI_B_I2C_remapPins                                             \
        ROM_EUSCI_B_I2C_remapPins
#else
#define MAP_EUSCI_B_I2C_remapPins                                             \
        EUSCI_B_I2C_remapPins
#endif
#ifdef ROM_EUSCI_B_I2C_setTimeout
#define MAP_EUSCI_B_I2C_setTimeout                                            \
        ROM_EUSCI_B_I2C_setTimeout
#else
#define MAP_EUSCI_B_I2C_setTimeout                                            \
        EUSCI_B_I2C_setTimeout
#endif

//*****************************************************************************
//
// Macros for the EUSCI_B_SPI API.
//
//*****************************************************************************
#ifdef ROM_EUSCI_B_SPI_initMaster
#define MAP_EUSCI_B_SPI_initMaster                                            \
        ROM_EUSCI_B_SPI_initMaster
#else
#define MAP_EUSCI_B_SPI_initMaster                                            \
        EUSCI_B_SPI_initMaster
#endif
#ifdef ROM_EUSCI_B_SPI_select4PinFunctionality
#define MAP_EUSCI_B_SPI_select4PinFunctionality                               \
        ROM_EUSCI_B_SPI_select4PinFunctionality
#else
#define MAP_EUSCI_B_SPI_select4PinFunctionality                               \
        EUSCI_B_SPI_select4PinFunctionality
#endif
#ifdef ROM_EUSCI_B_SPI_changeMasterClock
#define MAP_EUSCI_B_SPI_changeMasterClock                                     \
        ROM_EUSCI_B_SPI_changeMasterClock
#else
#define MAP_EUSCI_B_SPI_changeMasterClock                                     \
        EUSCI_B_SPI_changeMasterClock
#endif
#ifdef ROM_EUSCI_B_SPI_initSlave
#define MAP_EUSCI_B_SPI_initSlave                                             \
        ROM_EUSCI_B_SPI_initSlave
#else
#define MAP_EUSCI_B_SPI_initSlave                                             \
        EUSCI_B_SPI_initSlave
#endif
#ifdef ROM_EUSCI_B_SPI_changeClockPhasePolarity
#define MAP_EUSCI_B_SPI_changeClockPhasePolarity                              \
        ROM_EUSCI_B_SPI_changeClockPhasePolarity
#else
#define MAP_EUSCI_B_SPI_changeClockPhasePolarity                              \
        EUSCI_B_SPI_changeClockPhasePolarity
#endif
#ifdef ROM_EUSCI_B_SPI_transmitData
#define MAP_EUSCI_B_SPI_transmitData                                          \
        ROM_EUSCI_B_SPI_transmitData
#else
#define MAP_EUSCI_B_SPI_transmitData                                          \
        EUSCI_B_SPI_transmitData
#endif
#ifdef ROM_EUSCI_B_SPI_receiveData
#define MAP_EUSCI_B_SPI_receiveData                                           \
        ROM_EUSCI_B_SPI_receiveData
#else
#define MAP_EUSCI_B_SPI_receiveData                                           \
        EUSCI_B_SPI_receiveData
#endif
#ifdef ROM_EUSCI_B_SPI_enableInterrupt
#define MAP_EUSCI_B_SPI_enableInterrupt                                       \
        ROM_EUSCI_B_SPI_enableInterrupt
#else
#define MAP_EUSCI_B_SPI_enableInterrupt                                       \
        EUSCI_B_SPI_enableInterrupt
#endif
#ifdef ROM_EUSCI_B_SPI_disableInterrupt
#define MAP_EUSCI_B_SPI_disableInterrupt                                      \
        ROM_EUSCI_B_SPI_disableInterrupt
#else
#define MAP_EUSCI_B_SPI_disableInterrupt                                      \
        EUSCI_B_SPI_disableInterrupt
#endif
#ifdef ROM_EUSCI_B_SPI_getInterruptStatus
#define MAP_EUSCI_B_SPI_getInterruptStatus                                    \
        ROM_EUSCI_B_SPI_getInterruptStatus
#else
#define MAP_EUSCI_B_SPI_getInterruptStatus                                    \
        EUSCI_B_SPI_getInterruptStatus
#endif
#ifdef ROM_EUSCI_B_SPI_clearInterrupt
#define MAP_EUSCI_B_SPI_clearInterrupt                                        \
        ROM_EUSCI_B_SPI_clearInterrupt
#else
#define MAP_EUSCI_B_SPI_clearInterrupt                                        \
        EUSCI_B_SPI_clearInterrupt
#endif
#ifdef ROM_EUSCI_B_SPI_enable
#define MAP_EUSCI_B_SPI_enable                                                \
        ROM_EUSCI_B_SPI_enable
#else
#define MAP_EUSCI_B_SPI_enable                                                \
        EUSCI_B_SPI_enable
#endif
#ifdef ROM_EUSCI_B_SPI_disable
#define MAP_EUSCI_B_SPI_disable                                               \
        ROM_EUSCI_B_SPI_disable
#else
#define MAP_EUSCI_B_SPI_disable                                               \
        EUSCI_B_SPI_disable
#endif
#ifdef ROM_EUSCI_B_SPI_getReceiveBufferAddress
#define MAP_EUSCI_B_SPI_getReceiveBufferAddress                               \
        ROM_EUSCI_B_SPI_getReceiveBufferAddress
#else
#define MAP_EUSCI_B_SPI_getReceiveBufferAddress                               \
        EUSCI_B_SPI_getReceiveBufferAddress
#endif
#ifdef ROM_EUSCI_B_SPI_getTransmitBufferAddress
#define MAP_EUSCI_B_SPI_getTransmitBufferAddress                              \
        ROM_EUSCI_B_SPI_getTransmitBufferAddress
#else
#define MAP_EUSCI_B_SPI_getTransmitBufferAddress                              \
        EUSCI_B_SPI_getTransmitBufferAddress
#endif
#ifdef ROM_EUSCI_B_SPI_isBusy
#define MAP_EUSCI_B_SPI_isBusy                                                \
        ROM_EUSCI_B_SPI_isBusy
#else
#define MAP_EUSCI_B_SPI_isBusy                                                \
        EUSCI_B_SPI_isBusy
#endif
#ifdef ROM_EUSCI_B_SPI_remapPins
#define MAP_EUSCI_B_SPI_remapPins                                             \
        ROM_EUSCI_B_SPI_remapPins
#else
#define MAP_EUSCI_B_SPI_remapPins                                             \
        EUSCI_B_SPI_remapPins
#endif

//*****************************************************************************
//
// Macros for the FRAMCTL API.
//
//*****************************************************************************
#ifdef ROM_FRAMCtl_write8
#define MAP_FRAMCtl_write8                                                    \
        ROM_FRAMCtl_write8
#else
#define MAP_FRAMCtl_write8                                                    \
        FRAMCtl_write8
#endif
#ifdef ROM_FRAMCtl_write16
#define MAP_FRAMCtl_write16                                                   \
        ROM_FRAMCtl_write16
#else
#define MAP_FRAMCtl_write16                                                   \
        FRAMCtl_write16
#endif
#ifdef ROM_FRAMCtl_write32
#define MAP_FRAMCtl_write32                                                   \
        ROM_FRAMCtl_write32
#else
#define MAP_FRAMCtl_write32                                                   \
        FRAMCtl_write32
#endif
#ifdef ROM_FRAMCtl_fillMemory32
#define MAP_FRAMCtl_fillMemory32                                              \
        ROM_FRAMCtl_fillMemory32
#else
#define MAP_FRAMCtl_fillMemory32                                              \
        FRAMCtl_fillMemory32
#endif
#ifdef ROM_FRAMCtl_enableInterrupt
#define MAP_FRAMCtl_enableInterrupt                                           \
        ROM_FRAMCtl_enableInterrupt
#else
#define MAP_FRAMCtl_enableInterrupt                                           \
        FRAMCtl_enableInterrupt
#endif
#ifdef ROM_FRAMCtl_getInterruptStatus
#define MAP_FRAMCtl_getInterruptStatus                                        \
        ROM_FRAMCtl_getInterruptStatus
#else
#define MAP_FRAMCtl_getInterruptStatus                                        \
        FRAMCtl_getInterruptStatus
#endif
#ifdef ROM_FRAMCtl_disableInterrupt
#define MAP_FRAMCtl_disableInterrupt                                          \
        ROM_FRAMCtl_disableInterrupt
#else
#define MAP_FRAMCtl_disableInterrupt                                          \
        FRAMCtl_disableInterrupt
#endif
#ifdef ROM_FRAMCtl_configureWaitStateControl
#define MAP_FRAMCtl_configureWaitStateControl                                 \
        ROM_FRAMCtl_configureWaitStateControl
#else
#define MAP_FRAMCtl_configureWaitStateControl                                 \
        FRAMCtl_configureWaitStateControl
#endif
#ifdef ROM_FRAMCtl_delayPowerUpFromLPM
#define MAP_FRAMCtl_delayPowerUpFromLPM                                       \
        ROM_FRAMCtl_delayPowerUpFromLPM
#else
#define MAP_FRAMCtl_delayPowerUpFromLPM                                       \
        FRAMCtl_delayPowerUpFromLPM
#endif

//*****************************************************************************
//
// Macros for the GPIO API.
//
//*****************************************************************************
#ifdef ROM_GPIO_setAsOutputPin
#define MAP_GPIO_setAsOutputPin                                               \
        ROM_GPIO_setAsOutputPin
#else
#define MAP_GPIO_setAsOutputPin                                               \
        GPIO_setAsOutputPin
#endif
#ifdef ROM_GPIO_setAsInputPin
#define MAP_GPIO_setAsInputPin                                                \
        ROM_GPIO_setAsInputPin
#else
#define MAP_GPIO_setAsInputPin                                                \
        GPIO_setAsInputPin
#endif
#ifdef ROM_GPIO_setAsPeripheralModuleFunctionOutputPin
#define MAP_GPIO_setAsPeripheralModuleFunctionOutputPin                       \
        ROM_GPIO_setAsPeripheralModuleFunctionOutputPin
#else
#define MAP_GPIO_setAsPeripheralModuleFunctionOutputPin                       \
        GPIO_setAsPeripheralModuleFunctionOutputPin
#endif
#ifdef ROM_GPIO_setAsPeripheralModuleFunctionInputPin
#define MAP_GPIO_setAsPeripheralModuleFunctionInputPin                        \
        ROM_GPIO_setAsPeripheralModuleFunctionInputPin
#else
#define MAP_GPIO_setAsPeripheralModuleFunctionInputPin                        \
        GPIO_setAsPeripheralModuleFunctionInputPin
#endif
#ifdef ROM_GPIO_setOutputHighOnPin
#define MAP_GPIO_setOutputHighOnPin                                           \
        ROM_GPIO_setOutputHighOnPin
#else
#define MAP_GPIO_setOutputHighOnPin                                           \
        GPIO_setOutputHighOnPin
#endif
#ifdef ROM_GPIO_setOutputLowOnPin
#define MAP_GPIO_setOutputLowOnPin                                            \
        ROM_GPIO_setOutputLowOnPin
#else
#define MAP_GPIO_setOutputLowOnPin                                            \
        GPIO_setOutputLowOnPin
#endif
#ifdef ROM_GPIO_toggleOutputOnPin
#define MAP_GPIO_toggleOutputOnPin                                            \
        ROM_GPIO_toggleOutputOnPin
#else
#define MAP_GPIO_toggleOutputOnPin                                            \
        GPIO_toggleOutputOnPin
#endif
#ifdef ROM_GPIO_setAsInputPinWithPullDownResistor
#define MAP_GPIO_setAsInputPinWithPullDownResistor                            \
        ROM_GPIO_setAsInputPinWithPullDownResistor
#else
#define MAP_GPIO_setAsInputPinWithPullDownResistor                            \
        GPIO_setAsInputPinWithPullDownResistor
#endif
#ifdef ROM_GPIO_setAsInputPinWithPullUpResistor
#define MAP_GPIO_setAsInputPinWithPullUpResistor                              \
        ROM_GPIO_setAsInputPinWithPullUpResistor
#else
#define MAP_GPIO_setAsInputPinWithPullUpResistor                              \
        GPIO_setAsInputPinWithPullUpResistor
#endif
#ifdef ROM_GPIO_getInputPinValue
#define MAP_GPIO_getInputPinValue                                             \
        ROM_GPIO_getInputPinValue
#else
#define MAP_GPIO_getInputPinValue                                             \
        GPIO_getInputPinValue
#endif
#ifdef ROM_GPIO_enableInterrupt
#define MAP_GPIO_enableInterrupt                                              \
        ROM_GPIO_enableInterrupt
#else
#define MAP_GPIO_enableInterrupt                                              \
        GPIO_enableInterrupt
#endif
#ifdef ROM_GPIO_disableInterrupt
#define MAP_GPIO_disableInterrupt                                             \
        ROM_GPIO_disableInterrupt
#else
#define MAP_GPIO_disableInterrupt                                             \
        GPIO_disableInterrupt
#endif
#ifdef ROM_GPIO_getInterruptStatus
#define MAP_GPIO_getInterruptStatus                                           \
        ROM_GPIO_getInterruptStatus
#else
#define MAP_GPIO_getInterruptStatus                                           \
        GPIO_getInterruptStatus
#endif
#ifdef ROM_GPIO_clearInterrupt
#define MAP_GPIO_clearInterrupt                                               \
        ROM_GPIO_clearInterrupt
#else
#define MAP_GPIO_clearInterrupt                                               \
        GPIO_clearInterrupt
#endif
#ifdef ROM_GPIO_selectInterruptEdge
#define MAP_GPIO_selectInterruptEdge                                          \
        ROM_GPIO_selectInterruptEdge
#else
#define MAP_GPIO_selectInterruptEdge                                          \
        GPIO_selectInterruptEdge
#endif

//*****************************************************************************
//
// Macros for the ICC API.
//
//*****************************************************************************
#ifdef ROM_ICC_enable
#define MAP_ICC_enable                                                        \
        ROM_ICC_enable
#else
#define MAP_ICC_enable                                                        \
        ICC_enable
#endif
#ifdef ROM_ICC_disable
#define MAP_ICC_disable                                                       \
        ROM_ICC_disable
#else
#define MAP_ICC_disable                                                       \
        ICC_disable
#endif
#ifdef ROM_ICC_setInterruptLevel
#define MAP_ICC_setInterruptLevel                                             \
        ROM_ICC_setInterruptLevel
#else
#define MAP_ICC_setInterruptLevel                                             \
        ICC_setInterruptLevel
#endif
#ifdef ROM_ICC_getInterruptLevel
#define MAP_ICC_getInterruptLevel                                             \
        ROM_ICC_getInterruptLevel
#else
#define MAP_ICC_getInterruptLevel                                             \
        ICC_getInterruptLevel
#endif
#ifdef ROM_ICC_isVirtualStackEmpty
#define MAP_ICC_isVirtualStackEmpty                                           \
        ROM_ICC_isVirtualStackEmpty
#else
#define MAP_ICC_isVirtualStackEmpty                                           \
        ICC_isVirtualStackEmpty
#endif
#ifdef ROM_ICC_isVirtualStackFull
#define MAP_ICC_isVirtualStackFull                                            \
        ROM_ICC_isVirtualStackFull
#else
#define MAP_ICC_isVirtualStackFull                                            \
        ICC_isVirtualStackFull
#endif
#ifdef ROM_ICC_getCurrentICM
#define MAP_ICC_getCurrentICM                                                 \
        ROM_ICC_getCurrentICM
#else
#define MAP_ICC_getCurrentICM                                                 \
        ICC_getCurrentICM
#endif
#ifdef ROM_ICC_getMVSStackPointer
#define MAP_ICC_getMVSStackPointer                                            \
        ROM_ICC_getMVSStackPointer
#else
#define MAP_ICC_getMVSStackPointer                                            \
        ICC_getMVSStackPointer
#endif
#ifdef ROM_ICC_getICM3
#define MAP_ICC_getICM3                                                       \
        ROM_ICC_getICM3
#else
#define MAP_ICC_getICM3                                                       \
        ICC_getICM3
#endif
#ifdef ROM_ICC_getICM2
#define MAP_ICC_getICM2                                                       \
        ROM_ICC_getICM2
#else
#define MAP_ICC_getICM2                                                       \
        ICC_getICM2
#endif
#ifdef ROM_ICC_getICM1
#define MAP_ICC_getICM1                                                       \
        ROM_ICC_getICM1
#else
#define MAP_ICC_getICM1                                                       \
        ICC_getICM1
#endif
#ifdef ROM_ICC_getICM0
#define MAP_ICC_getICM0                                                       \
        ROM_ICC_getICM0
#else
#define MAP_ICC_getICM0                                                       \
        ICC_getICM0
#endif

//*****************************************************************************
//
// Macros for the LCD_E API.
//
//*****************************************************************************
#ifdef ROM_LCD_E_initParam
#define MAP_LCD_E_initParam \
    ROM_LCD_E_initParam
#else
#define MAP_LCD_E_initParam \
    LCD_E_initParam
#endif
#ifdef ROM_LCD_E_init
#define MAP_LCD_E_init \
    ROM_LCD_E_init
#else
#define MAP_LCD_E_init \
    LCD_E_init
#endif
#ifdef ROM_LCD_E_on
#define MAP_LCD_E_on \
    ROM_LCD_E_on
#else
#define MAP_LCD_E_on \
    LCD_E_on
#endif
#ifdef ROM_LCD_E_off
#define MAP_LCD_E_off \
    ROM_LCD_E_off
#else
#define MAP_LCD_E_off \
    LCD_E_off
#endif
#ifdef ROM_LCD_E_clearInterrupt
#define MAP_LCD_E_clearInterrupt \
    ROM_LCD_E_clearInterrupt
#else
#define MAP_LCD_E_clearInterrupt \
    LCD_E_clearInterrupt
#endif
#ifdef ROM_LCD_E_getInterruptStatus
#define MAP_LCD_E_getInterruptStatus \
    ROM_LCD_E_getInterruptStatus
#else
#define MAP_LCD_E_getInterruptStatus \
    LCD_E_getInterruptStatus
#endif
#ifdef ROM_LCD_E_enableInterrupt
#define MAP_LCD_E_enableInterrupt \
    ROM_LCD_E_enableInterrupt
#else
#define MAP_LCD_E_enableInterrupt \
    LCD_E_enableInterrupt
#endif
#ifdef ROM_LCD_E_disableInterrupt
#define MAP_LCD_E_disableInterrupt \
    ROM_LCD_E_disableInterrupt
#else
#define MAP_LCD_E_disableInterrupt \
    LCD_E_disableInterrupt
#endif
#ifdef ROM_LCD_E_clearAllMemory
#define MAP_LCD_E_clearAllMemory \
    ROM_LCD_E_clearAllMemory
#else
#define MAP_LCD_E_clearAllMemory \
    LCD_E_clearAllMemory
#endif
#ifdef ROM_LCD_E_clearAllBlinkingMemory
#define MAP_LCD_E_clearAllBlinkingMemory \
    ROM_LCD_E_clearAllBlinkingMemory
#else
#define MAP_LCD_E_clearAllBlinkingMemory \
    LCD_E_clearAllBlinkingMemory
#endif
#ifdef ROM_LCD_E_selectDisplayMemory
#define MAP_LCD_E_selectDisplayMemory \
    ROM_LCD_E_selectDisplayMemory
#else
#define MAP_LCD_E_selectDisplayMemory \
    LCD_E_selectDisplayMemory
#endif
#ifdef ROM_LCD_E_setBlinkingControl
#define MAP_LCD_E_setBlinkingControl \
    ROM_LCD_E_setBlinkingControl
#else
#define MAP_LCD_E_setBlinkingControl \
    LCD_E_setBlinkingControl
#endif
#ifdef ROM_LCD_E_enableChargePump
#define MAP_LCD_E_enableChargePump \
    ROM_LCD_E_enableChargePump
#else
#define MAP_LCD_E_enableChargePump \
    LCD_E_enableChargePump
#endif
#ifdef ROM_LCD_E_disableChargePump
#define MAP_LCD_E_disableChargePump \
    ROM_LCD_E_disableChargePump
#else
#define MAP_LCD_E_disableChargePump \
    LCD_E_disableChargePump
#endif
#ifdef ROM_LCD_E_setChargePumpFreq
#define MAP_LCD_E_setChargePumpFreq \
    ROM_LCD_E_setChargePumpFreq
#else
#define MAP_LCD_E_setChargePumpFreq \
    LCD_E_setChargePumpFreq
#endif
#ifdef ROM_LCD_E_setVLCDSource
#define MAP_LCD_E_setVLCDSource \
    ROM_LCD_E_setVLCDSource
#else
#define MAP_LCD_E_setVLCDSource \
    LCD_E_setVLCDSource
#endif
#ifdef ROM_LCD_E_setVLCDVoltage
#define MAP_LCD_E_setVLCDVoltage \
    ROM_LCD_E_setVLCDVoltage
#else
#define MAP_LCD_E_setVLCDVoltage \
    LCD_E_setVLCDVoltage
#endif
#ifdef ROM_LCD_E_setReferenceMode
#define MAP_LCD_E_setReferenceMode \
    ROM_LCD_E_setReferenceMode
#else
#define MAP_LCD_E_setReferenceMode \
    LCD_E_setReferenceMode
#endif
#ifdef ROM_LCD_E_setPinAsLCDFunction
#define MAP_LCD_E_setPinAsLCDFunction \
    ROM_LCD_E_setPinAsLCDFunction
#else
#define MAP_LCD_E_setPinAsLCDFunction \
    LCD_E_setPinAsLCDFunction
#endif
#ifdef ROM_LCD_E_setPinAsPortFunction
#define MAP_LCD_E_setPinAsPortFunction \
    ROM_LCD_E_setPinAsPortFunction
#else
#define MAP_LCD_E_setPinAsPortFunction \
    LCD_E_setPinAsPortFunction
#endif
#ifdef ROM_LCD_E_setPinAsLCDFunctionEx
#define MAP_LCD_E_setPinAsLCDFunctionEx \
    ROM_LCD_E_setPinAsLCDFunctionEx
#else
#define MAP_LCD_E_setPinAsLCDFunctionEx \
    LCD_E_setPinAsLCDFunctionEx
#endif
#ifdef ROM_LCD_E_setPinAsCOM
#define MAP_LCD_E_setPinAsCOM \
    ROM_LCD_E_setPinAsCOM
#else
#define MAP_LCD_E_setPinAsCOM \
    LCD_E_setPinAsCOM
#endif
#ifdef ROM_LCD_E_setPinAsSEG
#define MAP_LCD_E_setPinAsSEG \
    ROM_LCD_E_setPinAsSEG
#else
#define MAP_LCD_E_setPinAsSEG \
    LCD_E_setPinAsSEG
#endif
#ifdef ROM_LCD_E_setMemory
#define MAP_LCD_E_setMemory \
    ROM_LCD_E_setMemory
#else
#define MAP_LCD_E_setMemory \
    LCD_E_setMemory
#endif
#ifdef ROM_LCD_E_updateMemory
#define MAP_LCD_E_updateMemory \
    ROM_LCD_E_updateMemory
#else
#define MAP_LCD_E_updateMemory \
    LCD_E_updateMemory
#endif
#ifdef ROM_LCD_E_toggleMemory
#define MAP_LCD_E_toggleMemory \
    ROM_LCD_E_toggleMemory
#else
#define MAP_LCD_E_toggleMemory \
    LCD_E_toggleMemory
#endif
#ifdef ROM_LCD_E_clearMemory
#define MAP_LCD_E_clearMemory \
    ROM_LCD_E_clearMemory
#else
#define MAP_LCD_E_clearMemory \
    LCD_E_clearMemory
#endif
#ifdef ROM_LCD_E_setBlinkingMemory
#define MAP_LCD_E_setBlinkingMemory \
    ROM_LCD_E_setBlinkingMemory
#else
#define MAP_LCD_E_setBlinkingMemory \
    LCD_E_setBlinkingMemory
#endif
#ifdef ROM_LCD_E_updateBlinkingMemory
#define MAP_LCD_E_updateBlinkingMemory \
    ROM_LCD_E_updateBlinkingMemory
#else
#define MAP_LCD_E_updateBlinkingMemory \
    LCD_E_updateBlinkingMemory
#endif
#ifdef ROM_LCD_E_toggleBlinkingMemory
#define MAP_LCD_E_toggleBlinkingMemory \
    ROM_LCD_E_toggleBlinkingMemory
#else
#define MAP_LCD_E_toggleBlinkingMemory \
    LCD_E_toggleBlinkingMemory
#endif
#ifdef ROM_LCD_E_clearBlinkingMemory
#define MAP_LCD_E_clearBlinkingMemory \
    ROM_LCD_E_clearBlinkingMemory
#else
#define MAP_LCD_E_clearBlinkingMemory \
    LCD_E_clearBlinkingMemory
#endif

//*****************************************************************************
//
// Macros for the MPY32 API.
//
//*****************************************************************************
#ifdef ROM_MPY32_setWriteDelay
#define MAP_MPY32_setWriteDelay                                               \
        ROM_MPY32_setWriteDelay
#else
#define MAP_MPY32_setWriteDelay                                               \
        MPY32_setWriteDelay
#endif
#ifdef ROM_MPY32_enableSaturationMode
#define MAP_MPY32_enableSaturationMode                                        \
        ROM_MPY32_enableSaturationMode
#else
#define MAP_MPY32_enableSaturationMode                                        \
        MPY32_enableSaturationMode
#endif
#ifdef ROM_MPY32_disableSaturationMode
#define MAP_MPY32_disableSaturationMode                                       \
        ROM_MPY32_disableSaturationMode
#else
#define MAP_MPY32_disableSaturationMode                                       \
        MPY32_disableSaturationMode
#endif
#ifdef ROM_MPY32_getSaturationMode
#define MAP_MPY32_getSaturationMode                                           \
        ROM_MPY32_getSaturationMode
#else
#define MAP_MPY32_getSaturationMode                                           \
        MPY32_getSaturationMode
#endif
#ifdef ROM_MPY32_enableFractionalMode
#define MAP_MPY32_enableFractionalMode                                        \
        ROM_MPY32_enableFractionalMode
#else
#define MAP_MPY32_enableFractionalMode                                        \
        MPY32_enableFractionalMode
#endif
#ifdef ROM_MPY32_disableFractionalMode
#define MAP_MPY32_disableFractionalMode                                       \
        ROM_MPY32_disableFractionalMode
#else
#define MAP_MPY32_disableFractionalMode                                       \
        MPY32_disableFractionalMode
#endif
#ifdef ROM_MPY32_getFractionalMode
#define MAP_MPY32_getFractionalMode                                           \
        ROM_MPY32_getFractionalMode
#else
#define MAP_MPY32_getFractionalMode                                           \
        MPY32_getFractionalMode
#endif
#ifdef ROM_MPY32_setOperandOne8Bit
#define MAP_MPY32_setOperandOne8Bit                                           \
        ROM_MPY32_setOperandOne8Bit
#else
#define MAP_MPY32_setOperandOne8Bit                                           \
        MPY32_setOperandOne8Bit
#endif
#ifdef ROM_MPY32_setOperandOne16Bit
#define MAP_MPY32_setOperandOne16Bit                                          \
        ROM_MPY32_setOperandOne16Bit
#else
#define MAP_MPY32_setOperandOne16Bit                                          \
        MPY32_setOperandOne16Bit
#endif
#ifdef ROM_MPY32_setOperandOne24Bit
#define MAP_MPY32_setOperandOne24Bit                                          \
        ROM_MPY32_setOperandOne24Bit
#else
#define MAP_MPY32_setOperandOne24Bit                                          \
        MPY32_setOperandOne24Bit
#endif
#ifdef ROM_MPY32_setOperandOne32Bit
#define MAP_MPY32_setOperandOne32Bit                                          \
        ROM_MPY32_setOperandOne32Bit
#else
#define MAP_MPY32_setOperandOne32Bit                                          \
        MPY32_setOperandOne32Bit
#endif
#ifdef ROM_MPY32_setOperandTwo8Bit
#define MAP_MPY32_setOperandTwo8Bit                                           \
        ROM_MPY32_setOperandTwo8Bit
#else
#define MAP_MPY32_setOperandTwo8Bit                                           \
        MPY32_setOperandTwo8Bit
#endif
#ifdef ROM_MPY32_setOperandTwo16Bit
#define MAP_MPY32_setOperandTwo16Bit                                          \
        ROM_MPY32_setOperandTwo16Bit
#else
#define MAP_MPY32_setOperandTwo16Bit                                          \
        MPY32_setOperandTwo16Bit
#endif
#ifdef ROM_MPY32_setOperandTwo24Bit
#define MAP_MPY32_setOperandTwo24Bit                                          \
        ROM_MPY32_setOperandTwo24Bit
#else
#define MAP_MPY32_setOperandTwo24Bit                                          \
        MPY32_setOperandTwo24Bit
#endif
#ifdef ROM_MPY32_setOperandTwo32Bit
#define MAP_MPY32_setOperandTwo32Bit                                          \
        ROM_MPY32_setOperandTwo32Bit
#else
#define MAP_MPY32_setOperandTwo32Bit                                          \
        MPY32_setOperandTwo32Bit
#endif
#ifdef ROM_MPY32_getResult
#define MAP_MPY32_getResult                                                   \
        ROM_MPY32_getResult
#else
#define MAP_MPY32_getResult                                                   \
        MPY32_getResult
#endif
#ifdef ROM_MPY32_getSumExtension
#define MAP_MPY32_getSumExtension                                             \
        ROM_MPY32_getSumExtension
#else
#define MAP_MPY32_getSumExtension                                             \
        MPY32_getSumExtension
#endif
#ifdef ROM_MPY32_getCarryBitValue
#define MAP_MPY32_getCarryBitValue                                            \
        ROM_MPY32_getCarryBitValue
#else
#define MAP_MPY32_getCarryBitValue                                            \
        MPY32_getCarryBitValue
#endif
#ifdef ROM_MPY32_clearCarryBitValue
#define MAP_MPY32_clearCarryBitValue                                          \
        ROM_MPY32_clearCarryBitValue
#else
#define MAP_MPY32_clearCarryBitValue                                          \
        MPY32_clearCarryBitValue
#endif
#ifdef ROM_MPY32_preloadResult
#define MAP_MPY32_preloadResult                                               \
        ROM_MPY32_preloadResult
#else
#define MAP_MPY32_preloadResult                                               \
        MPY32_preloadResult
#endif

//*****************************************************************************
//
// Macros for the PMM API.
//
//*****************************************************************************
#ifdef ROM_PMM_enableSVSH
#define MAP_PMM_enableSVSH                                                    \
        ROM_PMM_enableSVSH
#else
#define MAP_PMM_enableSVSH                                                    \
        PMM_enableSVSH
#endif
#ifdef ROM_PMM_disableSVSH
#define MAP_PMM_disableSVSH                                                   \
        ROM_PMM_disableSVSH
#else
#define MAP_PMM_disableSVSH                                                   \
        PMM_disableSVSH
#endif
#ifdef ROM_PMM_turnOnRegulator
#define MAP_PMM_turnOnRegulator                                               \
        ROM_PMM_turnOnRegulator
#else
#define MAP_PMM_turnOnRegulator                                               \
        PMM_turnOnRegulator
#endif
#ifdef ROM_PMM_turnOffRegulator
#define MAP_PMM_turnOffRegulator                                              \
        ROM_PMM_turnOffRegulator
#else
#define MAP_PMM_turnOffRegulator                                              \
        PMM_turnOffRegulator
#endif
#ifdef ROM_PMM_trigPOR
#define MAP_PMM_trigPOR                                                       \
        ROM_PMM_trigPOR
#else
#define MAP_PMM_trigPOR                                                       \
        PMM_trigPOR
#endif
#ifdef ROM_PMM_trigBOR
#define MAP_PMM_trigBOR                                                       \
        ROM_PMM_trigBOR
#else
#define MAP_PMM_trigBOR                                                       \
        PMM_trigBOR
#endif
#ifdef ROM_PMM_clearInterrupt
#define MAP_PMM_clearInterrupt                                                \
        ROM_PMM_clearInterrupt
#else
#define MAP_PMM_clearInterrupt                                                \
        PMM_clearInterrupt
#endif
#ifdef ROM_PMM_getInterruptStatus
#define MAP_PMM_getInterruptStatus                                            \
        ROM_PMM_getInterruptStatus
#else
#define MAP_PMM_getInterruptStatus                                            \
        PMM_getInterruptStatus
#endif
#ifdef ROM_PMM_unlockLPM5
#define MAP_PMM_unlockLPM5                                                    \
        ROM_PMM_unlockLPM5
#else
#define MAP_PMM_unlockLPM5                                                    \
        PMM_unlockLPM5
#endif
#ifdef ROM_PMM_getBandgapMode
#define MAP_PMM_getBandgapMode                                                \
        ROM_PMM_getBandgapMode
#else
#define MAP_PMM_getBandgapMode                                                \
        PMM_getBandgapMode
#endif
#ifdef ROM_PMM_isBandgapActive
#define MAP_PMM_isBandgapActive                                               \
        ROM_PMM_isBandgapActive
#else
#define MAP_PMM_isBandgapActive                                               \
        PMM_isBandgapActive
#endif
#ifdef ROM_PMM_isRefGenActive
#define MAP_PMM_isRefGenActive                                                \
        ROM_PMM_isRefGenActive
#else
#define MAP_PMM_isRefGenActive                                                \
        PMM_isRefGenActive
#endif
#ifdef ROM_PMM_getBufferedBandgapVoltageStatus
#define MAP_PMM_getBufferedBandgapVoltageStatus                               \
        ROM_PMM_getBufferedBandgapVoltageStatus
#else
#define MAP_PMM_getBufferedBandgapVoltageStatus                               \
        PMM_getBufferedBandgapVoltageStatus
#endif
#ifdef ROM_PMM_getVariableReferenceVoltageStatus
#define MAP_PMM_getVariableReferenceVoltageStatus                             \
        ROM_PMM_getVariableReferenceVoltageStatus
#else
#define MAP_PMM_getVariableReferenceVoltageStatus                             \
        PMM_getVariableReferenceVoltageStatus
#endif
#ifdef ROM_PMM_disableTempSensor
#define MAP_PMM_disableTempSensor                                             \
        ROM_PMM_disableTempSensor
#else
#define MAP_PMM_disableTempSensor                                             \
        PMM_disableTempSensor
#endif
#ifdef ROM_PMM_enableTempSensor
#define MAP_PMM_enableTempSensor                                              \
        ROM_PMM_enableTempSensor
#else
#define MAP_PMM_enableTempSensor                                              \
        PMM_enableTempSensor
#endif
#ifdef ROM_PMM_disableExternalReference
#define MAP_PMM_disableExternalReference                                      \
        ROM_PMM_disableExternalReference
#else
#define MAP_PMM_disableExternalReference                                      \
        PMM_disableExternalReference
#endif
#ifdef ROM_PMM_enableExternalReference
#define MAP_PMM_enableExternalReference                                       \
        ROM_PMM_enableExternalReference
#else
#define MAP_PMM_enableExternalReference                                       \
        PMM_enableExternalReference
#endif
#ifdef ROM_PMM_disableInternalReference
#define MAP_PMM_disableInternalReference                                      \
        ROM_PMM_disableInternalReference
#else
#define MAP_PMM_disableInternalReference                                      \
        PMM_disableInternalReference
#endif
#ifdef ROM_PMM_enableInternalReference
#define MAP_PMM_enableInternalReference                                       \
        ROM_PMM_enableInternalReference
#else
#define MAP_PMM_enableInternalReference                                       \
        PMM_enableInternalReference
#endif
#ifdef ROM_PMM_selectVoltageReference
#define MAP_PMM_selectVoltageReference                                        \
        ROM_PMM_selectVoltageReference
#else
#define MAP_PMM_selectVoltageReference                                        \
        PMM_selectVoltageReference
#endif
#ifdef ROM_PMM_setPowerMode
#define MAP_PMM_setPowerMode                                                  \
        ROM_PMM_setPowerMode
#else
#define MAP_PMM_setPowerMode                                                  \
        PMM_setPowerMode
#endif

//*****************************************************************************
//
// Macros for the RTC API.
//
//*****************************************************************************
#ifdef ROM_RTC_init
#define MAP_RTC_init                                                          \
        ROM_RTC_init
#else
#define MAP_RTC_init                                                          \
        RTC_init
#endif
#ifdef ROM_RTC_start
#define MAP_RTC_start                                                         \
        ROM_RTC_start
#else
#define MAP_RTC_start                                                         \
        RTC_start
#endif
#ifdef ROM_RTC_stop
#define MAP_RTC_stop                                                          \
        ROM_RTC_stop
#else
#define MAP_RTC_stop                                                          \
        RTC_stop
#endif
#ifdef ROM_RTC_setModulo
#define MAP_RTC_setModulo                                                     \
        ROM_RTC_setModulo
#else
#define MAP_RTC_setModulo                                                     \
        RTC_setModulo
#endif
#ifdef ROM_RTC_enableInterrupt
#define MAP_RTC_enableInterrupt                                               \
        ROM_RTC_enableInterrupt
#else
#define MAP_RTC_enableInterrupt                                               \
        RTC_enableInterrupt
#endif
#ifdef ROM_RTC_disableInterrupt
#define MAP_RTC_disableInterrupt                                              \
        ROM_RTC_disableInterrupt
#else
#define MAP_RTC_disableInterrupt                                              \
        RTC_disableInterrupt
#endif
#ifdef ROM_RTC_getInterruptStatus
#define MAP_RTC_getInterruptStatus                                            \
        ROM_RTC_getInterruptStatus
#else
#define MAP_RTC_getInterruptStatus                                            \
        RTC_getInterruptStatus
#endif
#ifdef ROM_RTC_clearInterrupt
#define MAP_RTC_clearInterrupt                                                \
        ROM_RTC_clearInterrupt
#else
#define MAP_RTC_clearInterrupt                                                \
        RTC_clearInterrupt
#endif

//*****************************************************************************
//
// Macros for the SAC API.
//
//*****************************************************************************
#ifdef ROM_SAC_OA_init
#define MAP_SAC_OA_init                                                       \
        ROM_SAC_OA_init
#else
#define MAP_SAC_OA_init                                                       \
        SAC_OA_init
#endif
#ifdef ROM_SAC_OA_selectPowerMode
#define MAP_SAC_OA_selectPowerMode                                            \
        ROM_SAC_OA_selectPowerMode
#else
#define MAP_SAC_OA_selectPowerMode                                            \
        SAC_OA_selectPowerMode
#endif
#ifdef ROM_SAC_OA_enable
#define MAP_SAC_OA_enable                                                     \
        ROM_SAC_OA_enable
#else
#define MAP_SAC_OA_enable                                                     \
        SAC_OA_enable
#endif
#ifdef ROM_SAC_OA_disable
#define MAP_SAC_OA_disable                                                    \
        ROM_SAC_OA_disable
#else
#define MAP_SAC_OA_disable                                                    \
        SAC_OA_disable
#endif
#ifdef ROM_SAC_enable
#define MAP_SAC_enable                                                        \
        ROM_SAC_enable
#else
#define MAP_SAC_enable                                                        \
        SAC_enable
#endif
#ifdef ROM_SAC_disable
#define MAP_SAC_disable                                                       \
        ROM_SAC_disable
#else
#define MAP_SAC_disable                                                       \
        SAC_disable
#endif
#ifdef ROM_SAC_PGA_setMode
#define MAP_SAC_PGA_setMode                                                   \
        ROM_SAC_PGA_setMode
#else
#define MAP_SAC_PGA_setMode                                                   \
        SAC_PGA_setMode
#endif
#ifdef ROM_SAC_PGA_setGain
#define MAP_SAC_PGA_setGain                                                   \
        ROM_SAC_PGA_setGain
#else
#define MAP_SAC_PGA_setGain                                                   \
        SAC_PGA_setGain
#endif
#ifdef ROM_SAC_DAC_enable
#define MAP_SAC_DAC_enable                                                    \
        ROM_SAC_DAC_enable
#else
#define MAP_SAC_DAC_enable                                                    \
        SAC_DAC_enable
#endif
#ifdef ROM_SAC_DAC_disable
#define MAP_SAC_DAC_disable                                                   \
        ROM_SAC_DAC_disable
#else
#define MAP_SAC_DAC_disable                                                   \
        SAC_DAC_disable
#endif
#ifdef ROM_SAC_DAC_interruptEnable
#define MAP_SAC_DAC_interruptEnable                                           \
        ROM_SAC_DAC_interruptEnable
#else
#define MAP_SAC_DAC_interruptEnable                                           \
        SAC_DAC_interruptEnable
#endif
#ifdef ROM_SAC_DAC_interruptDisable
#define MAP_SAC_DAC_interruptDisable                                          \
        ROM_SAC_DAC_interruptDisable
#else
#define MAP_SAC_DAC_interruptDisable                                          \
        SAC_DAC_interruptDisable
#endif
#ifdef ROM_SAC_DAC_DMARequestEnable
#define MAP_SAC_DAC_DMARequestEnable                                          \
        ROM_SAC_DAC_DMARequestEnable
#else
#define MAP_SAC_DAC_DMARequestEnable                                          \
        SAC_DAC_DMARequestEnable
#endif
#ifdef ROM_SAC_DAC_DMARequestDisable
#define MAP_SAC_DAC_DMARequestDisable                                         \
        ROM_SAC_DAC_DMARequestDisable
#else
#define MAP_SAC_DAC_DMARequestDisable                                         \
        SAC_DAC_DMARequestDisable
#endif
#ifdef ROM_SAC_DAC_selectLoad
#define MAP_SAC_DAC_selectLoad                                                \
        ROM_SAC_DAC_selectLoad
#else
#define MAP_SAC_DAC_selectLoad                                                \
        SAC_DAC_selectLoad
#endif
#ifdef ROM_SAC_DAC_selectRefVoltage
#define MAP_SAC_DAC_selectRefVoltage                                          \
        ROM_SAC_DAC_selectRefVoltage
#else
#define MAP_SAC_DAC_selectRefVoltage                                          \
        SAC_DAC_selectRefVoltage
#endif
#ifdef ROM_SAC_DAC_getData
#define MAP_SAC_DAC_getData                                                   \
        ROM_SAC_DAC_getData
#else
#define MAP_SAC_DAC_getData                                                   \
        SAC_DAC_getData
#endif
#ifdef ROM_SAC_DAC_setData
#define MAP_SAC_DAC_setData                                                   \
        ROM_SAC_DAC_setData
#else
#define MAP_SAC_DAC_setData                                                   \
        SAC_DAC_setData
#endif
#ifdef ROM_SAC_DAC_getIFG
#define MAP_SAC_DAC_getIFG                                                    \
        ROM_SAC_DAC_getIFG
#else
#define MAP_SAC_DAC_getIFG                                                    \
        SAC_DAC_getIFG
#endif
#ifdef ROM_SAC_DAC_clearIFG
#define MAP_SAC_DAC_clearIFG                                                  \
        ROM_SAC_DAC_clearIFG
#else
#define MAP_SAC_DAC_clearIFG                                                  \
        SAC_DAC_clearIFG
#endif
#ifdef ROM_SAC_getInterruptVector
#define MAP_SAC_getInterruptVector                                            \
        ROM_SAC_getInterruptVector
#else
#define MAP_SAC_getInterruptVector                                            \
        SAC_getInterruptVector
#endif

//*****************************************************************************
//
// Macros for the SFR API.
//
//*****************************************************************************
#ifdef ROM_SFR_enableInterrupt
#define MAP_SFR_enableInterrupt                                               \
        ROM_SFR_enableInterrupt
#else
#define MAP_SFR_enableInterrupt                                               \
        SFR_enableInterrupt
#endif
#ifdef ROM_SFR_disableInterrupt
#define MAP_SFR_disableInterrupt                                              \
        ROM_SFR_disableInterrupt
#else
#define MAP_SFR_disableInterrupt                                              \
        SFR_disableInterrupt
#endif
#ifdef ROM_SFR_getInterruptStatus
#define MAP_SFR_getInterruptStatus                                            \
        ROM_SFR_getInterruptStatus
#else
#define MAP_SFR_getInterruptStatus                                            \
        SFR_getInterruptStatus
#endif
#ifdef ROM_SFR_clearInterrupt
#define MAP_SFR_clearInterrupt                                                \
        ROM_SFR_clearInterrupt
#else
#define MAP_SFR_clearInterrupt                                                \
        SFR_clearInterrupt
#endif
#ifdef ROM_SFR_setResetPinPullResistor
#define MAP_SFR_setResetPinPullResistor                                       \
        ROM_SFR_setResetPinPullResistor
#else
#define MAP_SFR_setResetPinPullResistor                                       \
        SFR_setResetPinPullResistor
#endif
#ifdef ROM_SFR_setNMIEdge
#define MAP_SFR_setNMIEdge                                                    \
        ROM_SFR_setNMIEdge
#else
#define MAP_SFR_setNMIEdge                                                    \
        SFR_setNMIEdge
#endif
#ifdef ROM_SFR_setResetNMIPinFunction
#define MAP_SFR_setResetNMIPinFunction                                        \
        ROM_SFR_setResetNMIPinFunction
#else
#define MAP_SFR_setResetNMIPinFunction                                        \
        SFR_setResetNMIPinFunction
#endif

//*****************************************************************************
//
// Macros for the SYSCTL API.
//
//*****************************************************************************
#ifdef ROM_SysCtl_enableDedicatedJTAGPins
#define MAP_SysCtl_enableDedicatedJTAGPins                                    \
        ROM_SysCtl_enableDedicatedJTAGPins
#else
#define MAP_SysCtl_enableDedicatedJTAGPins                                    \
        SysCtl_enableDedicatedJTAGPins
#endif
#ifdef ROM_SysCtl_getBSLEntryIndication
#define MAP_SysCtl_getBSLEntryIndication                                      \
        ROM_SysCtl_getBSLEntryIndication
#else
#define MAP_SysCtl_getBSLEntryIndication                                      \
        SysCtl_getBSLEntryIndication
#endif
#ifdef ROM_SysCtl_enablePMMAccessProtect
#define MAP_SysCtl_enablePMMAccessProtect                                     \
        ROM_SysCtl_enablePMMAccessProtect
#else
#define MAP_SysCtl_enablePMMAccessProtect                                     \
        SysCtl_enablePMMAccessProtect
#endif
#ifdef ROM_SysCtl_enableRAMBasedInterruptVectors
#define MAP_SysCtl_enableRAMBasedInterruptVectors                             \
        ROM_SysCtl_enableRAMBasedInterruptVectors
#else
#define MAP_SysCtl_enableRAMBasedInterruptVectors                             \
        SysCtl_enableRAMBasedInterruptVectors
#endif
#ifdef ROM_SysCtl_disableRAMBasedInterruptVectors
#define MAP_SysCtl_disableRAMBasedInterruptVectors                            \
        ROM_SysCtl_disableRAMBasedInterruptVectors
#else
#define MAP_SysCtl_disableRAMBasedInterruptVectors                            \
        SysCtl_disableRAMBasedInterruptVectors
#endif
#ifdef ROM_SysCtl_enableBSLProtect
#define MAP_SysCtl_enableBSLProtect                                           \
        ROM_SysCtl_enableBSLProtect
#else
#define MAP_SysCtl_enableBSLProtect                                           \
        SysCtl_enableBSLProtect
#endif
#ifdef ROM_SysCtl_disableBSLProtect
#define MAP_SysCtl_disableBSLProtect                                          \
        ROM_SysCtl_disableBSLProtect
#else
#define MAP_SysCtl_disableBSLProtect                                          \
        SysCtl_disableBSLProtect
#endif
#ifdef ROM_SysCtl_enableBSLMemory
#define MAP_SysCtl_enableBSLMemory                                            \
        ROM_SysCtl_enableBSLMemory
#else
#define MAP_SysCtl_enableBSLMemory                                            \
        SysCtl_enableBSLMemory
#endif
#ifdef ROM_SysCtl_disableBSLMemory
#define MAP_SysCtl_disableBSLMemory                                           \
        ROM_SysCtl_disableBSLMemory
#else
#define MAP_SysCtl_disableBSLMemory                                           \
        SysCtl_disableBSLMemory
#endif
#ifdef ROM_SysCtl_setRAMAssignedToBSL
#define MAP_SysCtl_setRAMAssignedToBSL                                        \
        ROM_SysCtl_setRAMAssignedToBSL
#else
#define MAP_SysCtl_setRAMAssignedToBSL                                        \
        SysCtl_setRAMAssignedToBSL
#endif
#ifdef ROM_SysCtl_initJTAGMailbox
#define MAP_SysCtl_initJTAGMailbox                                            \
        ROM_SysCtl_initJTAGMailbox
#else
#define MAP_SysCtl_initJTAGMailbox                                            \
        SysCtl_initJTAGMailbox
#endif
#ifdef ROM_SysCtl_getJTAGMailboxFlagStatus
#define MAP_SysCtl_getJTAGMailboxFlagStatus                                   \
        ROM_SysCtl_getJTAGMailboxFlagStatus
#else
#define MAP_SysCtl_getJTAGMailboxFlagStatus                                   \
        SysCtl_getJTAGMailboxFlagStatus
#endif
#ifdef ROM_SysCtl_clearJTAGMailboxFlagStatus
#define MAP_SysCtl_clearJTAGMailboxFlagStatus                                 \
        ROM_SysCtl_clearJTAGMailboxFlagStatus
#else
#define MAP_SysCtl_clearJTAGMailboxFlagStatus                                 \
        SysCtl_clearJTAGMailboxFlagStatus
#endif
#ifdef ROM_SysCtl_getJTAGInboxMessage16Bit
#define MAP_SysCtl_getJTAGInboxMessage16Bit                                   \
        ROM_SysCtl_getJTAGInboxMessage16Bit
#else
#define MAP_SysCtl_getJTAGInboxMessage16Bit                                   \
        SysCtl_getJTAGInboxMessage16Bit
#endif
#ifdef ROM_SysCtl_getJTAGInboxMessage32Bit
#define MAP_SysCtl_getJTAGInboxMessage32Bit                                   \
        ROM_SysCtl_getJTAGInboxMessage32Bit
#else
#define MAP_SysCtl_getJTAGInboxMessage32Bit                                   \
        SysCtl_getJTAGInboxMessage32Bit
#endif
#ifdef ROM_SysCtl_setJTAGOutgoingMessage16Bit
#define MAP_SysCtl_setJTAGOutgoingMessage16Bit                                \
        ROM_SysCtl_setJTAGOutgoingMessage16Bit
#else
#define MAP_SysCtl_setJTAGOutgoingMessage16Bit                                \
        SysCtl_setJTAGOutgoingMessage16Bit
#endif
#ifdef ROM_SysCtl_setJTAGOutgoingMessage32Bit
#define MAP_SysCtl_setJTAGOutgoingMessage32Bit                                \
        ROM_SysCtl_setJTAGOutgoingMessage32Bit
#else
#define MAP_SysCtl_setJTAGOutgoingMessage32Bit                                \
        SysCtl_setJTAGOutgoingMessage32Bit
#endif
#ifdef ROM_SysCtl_protectFRAMWrite
#define MAP_SysCtl_protectFRAMWrite                                           \
        ROM_SysCtl_protectFRAMWrite
#else
#define MAP_SysCtl_protectFRAMWrite                                           \
        SysCtl_protectFRAMWrite
#endif
#ifdef ROM_SysCtl_enableFRAMWrite
#define MAP_SysCtl_enableFRAMWrite                                            \
        ROM_SysCtl_enableFRAMWrite
#else
#define MAP_SysCtl_enableFRAMWrite                                            \
        SysCtl_enableFRAMWrite
#endif
#ifdef ROM_SysCtl_setInfraredConfig
#define MAP_SysCtl_setInfraredConfig                                          \
        ROM_SysCtl_setInfraredConfig
#else
#define MAP_SysCtl_setInfraredConfig                                          \
        SysCtl_setInfraredConfig
#endif
#ifdef ROM_SysCtl_enableInfrared
#define MAP_SysCtl_enableInfrared                                             \
        ROM_SysCtl_enableInfrared
#else
#define MAP_SysCtl_enableInfrared                                             \
        SysCtl_enableInfrared
#endif
#ifdef ROM_SysCtl_disableInfrared
#define MAP_SysCtl_disableInfrared                                            \
        ROM_SysCtl_disableInfrared
#else
#define MAP_SysCtl_disableInfrared                                            \
        SysCtl_disableInfrared
#endif
#ifdef ROM_SysCtl_getInfraredData
#define MAP_SysCtl_getInfraredData                                            \
        ROM_SysCtl_getInfraredData
#else
#define MAP_SysCtl_getInfraredData                                            \
        SysCtl_getInfraredData
#endif
#ifdef ROM_SysCtl_setFRWPOA
#define MAP_SysCtl_setFRWPOA                                                  \
        ROM_SysCtl_setFRWPOA
#else
#define MAP_SysCtl_setFRWPOA                                                  \
        SysCtl_setFRWPOA
#endif
#ifdef ROM_SysCtl_setHARTCLK
#define MAP_SysCtl_setHARTCLK                                                 \
        ROM_SysCtl_setHARTCLK
#else
#define MAP_SysCtl_setHARTCLK                                                 \
        SysCtl_setHARTCLK
#endif
#ifdef ROM_SysCtl_setHARTMOD
#define MAP_SysCtl_setHARTMOD                                                 \
        ROM_SysCtl_setHARTMOD
#else
#define MAP_SysCtl_setHARTMOD                                                 \
        SysCtl_setHARTMOD
#endif

//*****************************************************************************
//
// Macros for the TIA API.
//
//*****************************************************************************
#ifdef ROM_TIA_selectPositiveInput
#define MAP_TIA_selectPositiveInput \
    ROM_TIA_selectPositiveInput
#else
#define MAP_TIA_selectPositiveInput \
    TIA_selectPositiveInput
#endif
#ifdef ROM_TIA_selectPowerMode
#define MAP_TIA_selectPowerMode \
    ROM_TIA_selectPowerMode
#else
#define MAP_TIA_selectPowerMode \
    TIA_selectPowerMode
#endif
#ifdef ROM_TIA_enable
#define MAP_TIA_enable \
    ROM_TIA_enable
#else
#define MAP_TIA_enable \
    TIA_enable
#endif
#ifdef ROM_TIA_disable
#define MAP_TIA_disable \
    ROM_TIA_disable
#else
#define MAP_TIA_disable \
    TIA_disable
#endif

//*****************************************************************************
//
// Macros for the TIMER_A API.
//
//*****************************************************************************
#ifdef ROM_Timer_A_startCounter
#define MAP_Timer_A_startCounter \
    ROM_Timer_A_startCounter
#else
#define MAP_Timer_A_startCounter \
    Timer_A_startCounter
#endif
#ifdef ROM_Timer_A_initContinuousMode
#define MAP_Timer_A_initContinuousMode \
    ROM_Timer_A_initContinuousMode
#else
#define MAP_Timer_A_initContinuousMode \
    Timer_A_initContinuousMode
#endif
#ifdef ROM_Timer_A_initUpMode
#define MAP_Timer_A_initUpMode \
    ROM_Timer_A_initUpMode
#else
#define MAP_Timer_A_initUpMode \
    Timer_A_initUpMode
#endif
#ifdef ROM_Timer_A_initUpDownMode
#define MAP_Timer_A_initUpDownMode \
    ROM_Timer_A_initUpDownMode
#else
#define MAP_Timer_A_initUpDownMode \
    Timer_A_initUpDownMode
#endif
#ifdef ROM_Timer_A_initCaptureMode
#define MAP_Timer_A_initCaptureMode \
    ROM_Timer_A_initCaptureMode
#else
#define MAP_Timer_A_initCaptureMode \
    Timer_A_initCaptureMode
#endif
#ifdef ROM_Timer_A_initCompareMode
#define MAP_Timer_A_initCompareMode \
    ROM_Timer_A_initCompareMode
#else
#define MAP_Timer_A_initCompareMode \
    Timer_A_initCompareMode
#endif
#ifdef ROM_Timer_A_enableInterrupt
#define MAP_Timer_A_enableInterrupt \
    ROM_Timer_A_enableInterrupt
#else
#define MAP_Timer_A_enableInterrupt \
    Timer_A_enableInterrupt
#endif
#ifdef ROM_Timer_A_disableInterrupt
#define MAP_Timer_A_disableInterrupt \
    ROM_Timer_A_disableInterrupt
#else
#define MAP_Timer_A_disableInterrupt \
    Timer_A_disableInterrupt
#endif
#ifdef ROM_Timer_A_getInterruptStatus
#define MAP_Timer_A_getInterruptStatus \
    ROM_Timer_A_getInterruptStatus
#else
#define MAP_Timer_A_getInterruptStatus \
    Timer_A_getInterruptStatus
#endif
#ifdef ROM_Timer_A_enableCaptureCompareInterrupt
#define MAP_Timer_A_enableCaptureCompareInterrupt \
    ROM_Timer_A_enableCaptureCompareInterrupt
#else
#define MAP_Timer_A_enableCaptureCompareInterrupt \
    Timer_A_enableCaptureCompareInterrupt
#endif
#ifdef ROM_Timer_A_disableCaptureCompareInterrupt
#define MAP_Timer_A_disableCaptureCompareInterrupt \
    ROM_Timer_A_disableCaptureCompareInterrupt
#else
#define MAP_Timer_A_disableCaptureCompareInterrupt \
    Timer_A_disableCaptureCompareInterrupt
#endif
#ifdef ROM_Timer_A_getCaptureCompareInterruptStatus
#define MAP_Timer_A_getCaptureCompareInterruptStatus \
    ROM_Timer_A_getCaptureCompareInterruptStatus
#else
#define MAP_Timer_A_getCaptureCompareInterruptStatus \
    Timer_A_getCaptureCompareInterruptStatus
#endif
#ifdef ROM_Timer_A_clear
#define MAP_Timer_A_clear \
    ROM_Timer_A_clear
#else
#define MAP_Timer_A_clear \
    Timer_A_clear
#endif
#ifdef ROM_Timer_A_getSynchronizedCaptureCompareInput
#define MAP_Timer_A_getSynchronizedCaptureCompareInput \
    ROM_Timer_A_getSynchronizedCaptureCompareInput
#else
#define MAP_Timer_A_getSynchronizedCaptureCompareInput \
    Timer_A_getSynchronizedCaptureCompareInput
#endif
#ifdef ROM_Timer_A_getOutputForOutputModeOutBitValue
#define MAP_Timer_A_getOutputForOutputModeOutBitValue \
    ROM_Timer_A_getOutputForOutputModeOutBitValue
#else
#define MAP_Timer_A_getOutputForOutputModeOutBitValue \
    Timer_A_getOutputForOutputModeOutBitValue
#endif
#ifdef ROM_Timer_A_getCaptureCompareCount
#define MAP_Timer_A_getCaptureCompareCount \
    ROM_Timer_A_getCaptureCompareCount
#else
#define MAP_Timer_A_getCaptureCompareCount \
    Timer_A_getCaptureCompareCount
#endif
#ifdef ROM_Timer_A_setOutputForOutputModeOutBitValue
#define MAP_Timer_A_setOutputForOutputModeOutBitValue \
    ROM_Timer_A_setOutputForOutputModeOutBitValue
#else
#define MAP_Timer_A_setOutputForOutputModeOutBitValue \
    Timer_A_setOutputForOutputModeOutBitValue
#endif
#ifdef ROM_Timer_A_outputPWM
#define MAP_Timer_A_outputPWM \
    ROM_Timer_A_outputPWM
#else
#define MAP_Timer_A_outputPWM \
    Timer_A_outputPWM
#endif
#ifdef ROM_Timer_A_stop
#define MAP_Timer_A_stop \
    ROM_Timer_A_stop
#else
#define MAP_Timer_A_stop \
    Timer_A_stop
#endif
#ifdef ROM_Timer_A_setCompareValue
#define MAP_Timer_A_setCompareValue \
    ROM_Timer_A_setCompareValue
#else
#define MAP_Timer_A_setCompareValue \
    Timer_A_setCompareValue
#endif
#ifdef ROM_Timer_A_setOutputMode
#define MAP_Timer_A_setOutputMode \
    ROM_Timer_A_setOutputMode
#else
#define MAP_Timer_A_setOutputMode \
    Timer_A_setOutputMode
#endif
#ifdef ROM_Timer_A_clearTimerInterrupt
#define MAP_Timer_A_clearTimerInterrupt \
    ROM_Timer_A_clearTimerInterrupt
#else
#define MAP_Timer_A_clearTimerInterrupt \
    Timer_A_clearTimerInterrupt
#endif
#ifdef ROM_Timer_A_clearCaptureCompareInterrupt
#define MAP_Timer_A_clearCaptureCompareInterrupt \
    ROM_Timer_A_clearCaptureCompareInterrupt
#else
#define MAP_Timer_A_clearCaptureCompareInterrupt \
    Timer_A_clearCaptureCompareInterrupt
#endif
#ifdef ROM_Timer_A_getCounterValue
#define MAP_Timer_A_getCounterValue \
    ROM_Timer_A_getCounterValue
#else
#define MAP_Timer_A_getCounterValue \
    Timer_A_getCounterValue
#endif

//*****************************************************************************
//
// Macros for the TIMER_B API.
//
//*****************************************************************************
#ifdef ROM_Timer_B_startCounter
#define MAP_Timer_B_startCounter                                              \
        ROM_Timer_B_startCounter
#else
#define MAP_Timer_B_startCounter                                              \
        Timer_B_startCounter
#endif
#ifdef ROM_Timer_B_initContinuousMode
#define MAP_Timer_B_initContinuousMode                                        \
        ROM_Timer_B_initContinuousMode
#else
#define MAP_Timer_B_initContinuousMode                                        \
        Timer_B_initContinuousMode
#endif
#ifdef ROM_Timer_B_initUpMode
#define MAP_Timer_B_initUpMode                                                \
        ROM_Timer_B_initUpMode
#else
#define MAP_Timer_B_initUpMode                                                \
        Timer_B_initUpMode
#endif
#ifdef ROM_Timer_B_initUpDownMode
#define MAP_Timer_B_initUpDownMode                                            \
        ROM_Timer_B_initUpDownMode
#else
#define MAP_Timer_B_initUpDownMode                                            \
        Timer_B_initUpDownMode
#endif
#ifdef ROM_Timer_B_initCaptureMode
#define MAP_Timer_B_initCaptureMode                                           \
        ROM_Timer_B_initCaptureMode
#else
#define MAP_Timer_B_initCaptureMode                                           \
        Timer_B_initCaptureMode
#endif
#ifdef ROM_Timer_B_initCompareMode
#define MAP_Timer_B_initCompareMode                                           \
        ROM_Timer_B_initCompareMode
#else
#define MAP_Timer_B_initCompareMode                                           \
        Timer_B_initCompareMode
#endif
#ifdef ROM_Timer_B_enableInterrupt
#define MAP_Timer_B_enableInterrupt                                           \
        ROM_Timer_B_enableInterrupt
#else
#define MAP_Timer_B_enableInterrupt                                           \
        Timer_B_enableInterrupt
#endif
#ifdef ROM_Timer_B_disableInterrupt
#define MAP_Timer_B_disableInterrupt                                          \
        ROM_Timer_B_disableInterrupt
#else
#define MAP_Timer_B_disableInterrupt                                          \
        Timer_B_disableInterrupt
#endif
#ifdef ROM_Timer_B_getInterruptStatus
#define MAP_Timer_B_getInterruptStatus                                        \
        ROM_Timer_B_getInterruptStatus
#else
#define MAP_Timer_B_getInterruptStatus                                        \
        Timer_B_getInterruptStatus
#endif
#ifdef ROM_Timer_B_enableCaptureCompareInterrupt
#define MAP_Timer_B_enableCaptureCompareInterrupt                             \
        ROM_Timer_B_enableCaptureCompareInterrupt
#else
#define MAP_Timer_B_enableCaptureCompareInterrupt                             \
        Timer_B_enableCaptureCompareInterrupt
#endif
#ifdef ROM_Timer_B_disableCaptureCompareInterrupt
#define MAP_Timer_B_disableCaptureCompareInterrupt                            \
        ROM_Timer_B_disableCaptureCompareInterrupt
#else
#define MAP_Timer_B_disableCaptureCompareInterrupt                            \
        Timer_B_disableCaptureCompareInterrupt
#endif
#ifdef ROM_Timer_B_getCaptureCompareInterruptStatus
#define MAP_Timer_B_getCaptureCompareInterruptStatus                          \
        ROM_Timer_B_getCaptureCompareInterruptStatus
#else
#define MAP_Timer_B_getCaptureCompareInterruptStatus                          \
        Timer_B_getCaptureCompareInterruptStatus
#endif
#ifdef ROM_Timer_B_clear
#define MAP_Timer_B_clear                                                     \
        ROM_Timer_B_clear
#else
#define MAP_Timer_B_clear                                                     \
        Timer_B_clear
#endif
#ifdef ROM_Timer_B_getSynchronizedCaptureCompareInput
#define MAP_Timer_B_getSynchronizedCaptureCompareInput                        \
        ROM_Timer_B_getSynchronizedCaptureCompareInput
#else
#define MAP_Timer_B_getSynchronizedCaptureCompareInput                        \
        Timer_B_getSynchronizedCaptureCompareInput
#endif
#ifdef ROM_Timer_B_getOutputForOutputModeOutBitValue
#define MAP_Timer_B_getOutputForOutputModeOutBitValue                         \
        ROM_Timer_B_getOutputForOutputModeOutBitValue
#else
#define MAP_Timer_B_getOutputForOutputModeOutBitValue                         \
        Timer_B_getOutputForOutputModeOutBitValue
#endif
#ifdef ROM_Timer_B_getCaptureCompareCount
#define MAP_Timer_B_getCaptureCompareCount                                    \
        ROM_Timer_B_getCaptureCompareCount
#else
#define MAP_Timer_B_getCaptureCompareCount                                    \
        Timer_B_getCaptureCompareCount
#endif
#ifdef ROM_Timer_B_setOutputForOutputModeOutBitValue
#define MAP_Timer_B_setOutputForOutputModeOutBitValue                         \
        ROM_Timer_B_setOutputForOutputModeOutBitValue
#else
#define MAP_Timer_B_setOutputForOutputModeOutBitValue                         \
        Timer_B_setOutputForOutputModeOutBitValue
#endif
#ifdef ROM_Timer_B_outputPWM
#define MAP_Timer_B_outputPWM                                                 \
        ROM_Timer_B_outputPWM
#else
#define MAP_Timer_B_outputPWM                                                 \
        Timer_B_outputPWM
#endif
#ifdef ROM_Timer_B_stop
#define MAP_Timer_B_stop                                                      \
        ROM_Timer_B_stop
#else
#define MAP_Timer_B_stop                                                      \
        Timer_B_stop
#endif
#ifdef ROM_Timer_B_setCompareValue
#define MAP_Timer_B_setCompareValue                                           \
        ROM_Timer_B_setCompareValue
#else
#define MAP_Timer_B_setCompareValue                                           \
        Timer_B_setCompareValue
#endif
#ifdef ROM_Timer_B_clearTimerInterrupt
#define MAP_Timer_B_clearTimerInterrupt                                       \
        ROM_Timer_B_clearTimerInterrupt
#else
#define MAP_Timer_B_clearTimerInterrupt                                       \
        Timer_B_clearTimerInterrupt
#endif
#ifdef ROM_Timer_B_clearCaptureCompareInterrupt
#define MAP_Timer_B_clearCaptureCompareInterrupt                              \
        ROM_Timer_B_clearCaptureCompareInterrupt
#else
#define MAP_Timer_B_clearCaptureCompareInterrupt                              \
        Timer_B_clearCaptureCompareInterrupt
#endif
#ifdef ROM_Timer_B_selectCounterLength
#define MAP_Timer_B_selectCounterLength                                       \
        ROM_Timer_B_selectCounterLength
#else
#define MAP_Timer_B_selectCounterLength                                       \
        Timer_B_selectCounterLength
#endif
#ifdef ROM_Timer_B_selectLatchingGroup
#define MAP_Timer_B_selectLatchingGroup                                       \
        ROM_Timer_B_selectLatchingGroup
#else
#define MAP_Timer_B_selectLatchingGroup                                       \
        Timer_B_selectLatchingGroup
#endif
#ifdef ROM_Timer_B_initCompareLatchLoadEvent
#define MAP_Timer_B_initCompareLatchLoadEvent                                 \
        ROM_Timer_B_initCompareLatchLoadEvent
#else
#define MAP_Timer_B_initCompareLatchLoadEvent                                 \
        Timer_B_initCompareLatchLoadEvent
#endif
#ifdef ROM_Timer_B_getCounterValue
#define MAP_Timer_B_getCounterValue                                           \
        ROM_Timer_B_getCounterValue
#else
#define MAP_Timer_B_getCounterValue                                           \
        Timer_B_getCounterValue
#endif
#ifdef ROM_Timer_B_setOutputMode
#define MAP_Timer_B_setOutputMode                                             \
        ROM_Timer_B_setOutputMode
#else
#define MAP_Timer_B_setOutputMode                                             \
        Timer_B_setOutputMode
#endif
#ifdef ROM_Timer_B_selectOutputHighImpedanceTrigger
#define MAP_Timer_B_selectOutputHighImpedanceTrigger                          \
        ROM_Timer_B_selectOutputHighImpedanceTrigger
#else
#define MAP_Timer_B_selectOutputHighImpedanceTrigger                          \
        Timer_B_selectOutputHighImpedanceTrigger
#endif
#ifdef ROM_Timer_B_remapPins
#define MAP_Timer_B_remapPins                                                 \
        ROM_Timer_B_remapPins
#else
#define MAP_Timer_B_remapPins                                                 \
        Timer_B_remapPins
#endif

//*****************************************************************************
//
// Macros for the TLV API.
//
//*****************************************************************************
#ifdef ROM_TLV_getInfo
#define MAP_TLV_getInfo                                                       \
        ROM_TLV_getInfo
#else
#define MAP_TLV_getInfo                                                       \
        TLV_getInfo
#endif
#ifdef ROM_TLV_getDeviceType
#define MAP_TLV_getDeviceType                                                 \
        ROM_TLV_getDeviceType
#else
#define MAP_TLV_getDeviceType                                                 \
        TLV_getDeviceType
#endif
#ifdef ROM_TLV_getMemory
#define MAP_TLV_getMemory                                                     \
        ROM_TLV_getMemory
#else
#define MAP_TLV_getMemory                                                     \
        TLV_getMemory
#endif
#ifdef ROM_TLV_getPeripheral
#define MAP_TLV_getPeripheral                                                 \
        ROM_TLV_getPeripheral
#else
#define MAP_TLV_getPeripheral                                                 \
        TLV_getPeripheral
#endif
#ifdef ROM_TLV_getInterrupt
#define MAP_TLV_getInterrupt                                                  \
        ROM_TLV_getInterrupt
#else
#define MAP_TLV_getInterrupt                                                  \
        TLV_getInterrupt
#endif

//*****************************************************************************
//
// Macros for the WDT_A API.
//
//*****************************************************************************
#ifdef ROM_WDT_A_hold
#define MAP_WDT_A_hold                                                        \
        ROM_WDT_A_hold
#else
#define MAP_WDT_A_hold                                                        \
        WDT_A_hold
#endif
#ifdef ROM_WDT_A_start
#define MAP_WDT_A_start                                                       \
        ROM_WDT_A_start
#else
#define MAP_WDT_A_start                                                       \
        WDT_A_start
#endif
#ifdef ROM_WDT_A_resetTimer
#define MAP_WDT_A_resetTimer                                                  \
        ROM_WDT_A_resetTimer
#else
#define MAP_WDT_A_resetTimer                                                  \
        WDT_A_resetTimer
#endif
#ifdef ROM_WDT_A_initWatchdogTimer
#define MAP_WDT_A_initWatchdogTimer                                           \
        ROM_WDT_A_initWatchdogTimer
#else
#define MAP_WDT_A_initWatchdogTimer                                           \
        WDT_A_initWatchdogTimer
#endif
#ifdef ROM_WDT_A_initIntervalTimer
#define MAP_WDT_A_initIntervalTimer                                           \
        ROM_WDT_A_initIntervalTimer
#else
#define MAP_WDT_A_initIntervalTimer                                           \
        WDT_A_initIntervalTimer
#endif

#endif // __ROM_MAP_DRIVERLIB_H__
