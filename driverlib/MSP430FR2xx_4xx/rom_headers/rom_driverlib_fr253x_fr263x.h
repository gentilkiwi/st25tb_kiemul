//*****************************************************************************
//
// rom_driverlib_fr253x_fr263x.h - Macros to facilitate calling functions in 
// ROM for MSP430FR2532, FR2533, FR2632, FR2633
//
// Copyright (c) 2014-2017 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************
//

#ifndef __ROM_DRIVERLIB_H__
#define __ROM_DRIVERLIB_H__

#if (defined(__TI_COMPILER_VERSION__) && !defined(__LARGE_CODE_MODEL__)) || \
    (defined(__IAR_SYSTEMS_ICC__) && (__CODE_MODEL__==__CODE_MODEL_SMALL__))

//*****************************************************************************
//
// Pointers to the main API tables.
//
//*****************************************************************************
#define ROM_DRIVERLIB_APITABLE         ((uint16_t *)0x67E0)
#define ROM_DRIVERLIB_VERSIONL         (ROM_DRIVERLIB_APITABLE[0])
#define ROM_DRIVERLIB_VERSIONH         (ROM_DRIVERLIB_APITABLE[1])
#define ROM_EUSCIASPITABLE             ((uint16_t *)(ROM_DRIVERLIB_APITABLE[2]))
#define ROM_EUSCIAUARTTABLE            ((uint16_t *)(ROM_DRIVERLIB_APITABLE[3]))
#define ROM_EUSCIBI2CTABLE             ((uint16_t *)(ROM_DRIVERLIB_APITABLE[4]))
#define ROM_EUSCIBSPITABLE             ((uint16_t *)(ROM_DRIVERLIB_APITABLE[5]))

#define ROM_DRIVERLIB_getVersion()     ((uint32_t)ROM_DRIVERLIB_VERSIONH<<16|\
                                            ROM_DRIVERLIB_VERSIONL)

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIASPI API.
//
//*****************************************************************************
#define ROM_EUSCI_A_SPI_disableInterrupt                                      \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIASPITABLE[0])
#define ROM_EUSCI_A_SPI_disable                                               \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIASPITABLE[1])
#define ROM_EUSCI_A_SPI_isBusy                                                \
        ((uint16_t (*)(uint16_t baseAddress))ROM_EUSCIASPITABLE[2])
#define ROM_EUSCI_A_SPI_getReceiveBufferAddress                               \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIASPITABLE[3])
#define ROM_EUSCI_A_SPI_enableInterrupt                                       \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIASPITABLE[4])
#define ROM_EUSCI_A_SPI_transmitData                                          \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t transmitData))ROM_EUSCIASPITABLE[5])
#define ROM_EUSCI_A_SPI_changeMasterClock                                     \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_A_SPI_changeMasterClockParam *param))ROM_EUSCIASPITABLE[6])
#define ROM_EUSCI_A_SPI_initMaster                                            \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_A_SPI_initMasterParam *param))ROM_EUSCIASPITABLE[7])
#define ROM_EUSCI_A_SPI_changeClockPhasePolarity                              \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint16_t clockPhase,                                       \
                   uint16_t clockPolarity))ROM_EUSCIASPITABLE[8])
#define ROM_EUSCI_A_SPI_getInterruptStatus                                    \
        ((uint8_t (*)(uint16_t baseAddress,                                   \
                      uint8_t mask))ROM_EUSCIASPITABLE[9])
#define ROM_EUSCI_A_SPI_select4PinFunctionality                               \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t select4PinFunctionality))ROM_EUSCIASPITABLE[10])
#define ROM_EUSCI_A_SPI_initSlave                                             \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_A_SPI_initSlaveParam *param))ROM_EUSCIASPITABLE[11])
#define ROM_EUSCI_A_SPI_enable                                                \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIASPITABLE[12])
#define ROM_EUSCI_A_SPI_getTransmitBufferAddress                              \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIASPITABLE[13])
#define ROM_EUSCI_A_SPI_clearInterrupt                                        \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIASPITABLE[14])
#define ROM_EUSCI_A_SPI_receiveData                                           \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIASPITABLE[15])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIAUART API.
//
//*****************************************************************************
#define ROM_EUSCI_A_UART_setDormant                                           \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[0])
#define ROM_EUSCI_A_UART_getTransmitBufferAddress                             \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[1])
#define ROM_EUSCI_A_UART_disableInterrupt                                     \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIAUARTTABLE[2])
#define ROM_EUSCI_A_UART_enable                                               \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[3])
#define ROM_EUSCI_A_UART_transmitData                                         \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t transmitData))ROM_EUSCIAUARTTABLE[4])
#define ROM_EUSCI_A_UART_transmitBreak                                        \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[5])
#define ROM_EUSCI_A_UART_resetDormant                                         \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[6])
#define ROM_EUSCI_A_UART_init                                                 \
        ((bool (*)(uint16_t baseAddress,                                      \
                   EUSCI_A_UART_initParam *param))ROM_EUSCIAUARTTABLE[7])
#define ROM_EUSCI_A_UART_clearInterrupt                                       \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIAUARTTABLE[8])
#define ROM_EUSCI_A_UART_transmitAddress                                      \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t transmitAddress))ROM_EUSCIAUARTTABLE[9])
#define ROM_EUSCI_A_UART_receiveData                                          \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[10])
#define ROM_EUSCI_A_UART_enableInterrupt                                      \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIAUARTTABLE[11])
#define ROM_EUSCI_A_UART_queryStatusFlags                                     \
        ((uint8_t (*)(uint16_t baseAddress,                                   \
                      uint8_t mask))ROM_EUSCIAUARTTABLE[12])
#define ROM_EUSCI_A_UART_getReceiveBufferAddress                              \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[13])
#define ROM_EUSCI_A_UART_getInterruptStatus                                   \
        ((uint8_t (*)(uint16_t baseAddress,                                   \
                      uint8_t mask))ROM_EUSCIAUARTTABLE[14])
#define ROM_EUSCI_A_UART_selectDeglitchTime                                   \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint16_t deglitchTime))ROM_EUSCIAUARTTABLE[15])
#define ROM_EUSCI_A_UART_disable                                              \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIAUARTTABLE[16])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIBI2C API.
//
//*****************************************************************************
#define ROM_EUSCI_B_I2C_initSlave                                             \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_B_I2C_initSlaveParam *param))ROM_EUSCIBI2CTABLE[0])
#define ROM_EUSCI_B_I2C_masterSendMultiByteStop                               \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[1])
#define ROM_EUSCI_B_I2C_isBusBusy                                             \
        ((uint16_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[2])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteNext                            \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[3])
#define ROM_EUSCI_B_I2C_masterSendMultiByteStartWithTimeout                   \
        ((bool (*)(uint16_t baseAddress,                                      \
                   uint8_t txData,                                            \
                   uint32_t timeout))ROM_EUSCIBI2CTABLE[4])
#define ROM_EUSCI_B_I2C_masterSendStart                                       \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[5])
#define ROM_EUSCI_B_I2C_disableInterrupt                                      \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint16_t mask))ROM_EUSCIBI2CTABLE[6])
#define ROM_EUSCI_B_I2C_initMaster                                            \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_B_I2C_initMasterParam *param))ROM_EUSCIBI2CTABLE[7])
#define ROM_EUSCI_B_I2C_clearInterrupt                                        \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint16_t mask))ROM_EUSCIBI2CTABLE[8])
#define ROM_EUSCI_B_I2C_getTransmitBufferAddress                              \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[9])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteFinishWithTimeout               \
        ((bool (*)(uint16_t baseAddress,                                      \
                   uint8_t *txData,                                           \
                   uint32_t timeout))ROM_EUSCIBI2CTABLE[10])
#define ROM_EUSCI_B_I2C_masterReceiveSingleByte                               \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[11])
#define ROM_EUSCI_B_I2C_setSlaveAddress                                       \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t slaveAddress))ROM_EUSCIBI2CTABLE[12])
#define ROM_EUSCI_B_I2C_slaveGetData                                          \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[13])
#define ROM_EUSCI_B_I2C_masterSendSingleByte                                  \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t txData))ROM_EUSCIBI2CTABLE[14])
#define ROM_EUSCI_B_I2C_masterSendMultiByteFinish                             \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t txData))ROM_EUSCIBI2CTABLE[15])
#define ROM_EUSCI_B_I2C_setMode                                               \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mode))ROM_EUSCIBI2CTABLE[16])
#define ROM_EUSCI_B_I2C_enable                                                \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[17])
#define ROM_EUSCI_B_I2C_masterSendMultiByteNext                               \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t txData))ROM_EUSCIBI2CTABLE[18])
#define ROM_EUSCI_B_I2C_getMode                                               \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[19])
#define ROM_EUSCI_B_I2C_masterReceiveSingle                                   \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[20])
#define ROM_EUSCI_B_I2C_disable                                               \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[21])
#define ROM_EUSCI_B_I2C_enableInterrupt                                       \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint16_t mask))ROM_EUSCIBI2CTABLE[22])
#define ROM_EUSCI_B_I2C_masterSendMultiByteNextWithTimeout                    \
        ((bool (*)(uint16_t baseAddress,                                      \
                   uint8_t txData,                                            \
                   uint32_t timeout))ROM_EUSCIBI2CTABLE[23])
#define ROM_EUSCI_B_I2C_masterSendSingleByteWithTimeout                       \
        ((bool (*)(uint16_t baseAddress,                                      \
                   uint8_t txData,                                            \
                   uint32_t timeout))ROM_EUSCIBI2CTABLE[24])
#define ROM_EUSCI_B_I2C_slavePutData                                          \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t transmitData))ROM_EUSCIBI2CTABLE[25])
#define ROM_EUSCI_B_I2C_masterReceiveStart                                    \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[26])
#define ROM_EUSCI_B_I2C_getReceiveBufferAddress                               \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[27])
#define ROM_EUSCI_B_I2C_disableMultiMasterMode                                \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[28])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteFinish                          \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[29])
#define ROM_EUSCI_B_I2C_masterIsStartSent                                     \
        ((uint16_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[30])
#define ROM_EUSCI_B_I2C_enableMultiMasterMode                                 \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[31])
#define ROM_EUSCI_B_I2C_masterSendMultiByteStart                              \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t txData))ROM_EUSCIBI2CTABLE[32])
#define ROM_EUSCI_B_I2C_masterSendMultiByteStopWithTimeout                    \
        ((bool (*)(uint16_t baseAddress,                                      \
                   uint32_t timeout))ROM_EUSCIBI2CTABLE[33])
#define ROM_EUSCI_B_I2C_masterSendMultiByteFinishWithTimeout                  \
        ((bool (*)(uint16_t baseAddress,                                      \
                   uint8_t txData,                                            \
                   uint32_t timeout))ROM_EUSCIBI2CTABLE[34])
#define ROM_EUSCI_B_I2C_masterIsStopSent                                      \
        ((uint16_t (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[35])
#define ROM_EUSCI_B_I2C_masterReceiveMultiByteStop                            \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBI2CTABLE[36])
#define ROM_EUSCI_B_I2C_getInterruptStatus                                    \
        ((uint16_t (*)(uint16_t baseAddress,                                  \
                       uint16_t mask))ROM_EUSCIBI2CTABLE[37])

//*****************************************************************************
//
// Macros for calling ROM functions in the EUSCIBSPI API.
//
//*****************************************************************************
#define ROM_EUSCI_B_SPI_enableInterrupt                                       \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIBSPITABLE[0])
#define ROM_EUSCI_B_SPI_disable                                               \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[1])
#define ROM_EUSCI_B_SPI_clearInterrupt                                        \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIBSPITABLE[2])
#define ROM_EUSCI_B_SPI_isBusy                                                \
        ((uint16_t (*)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[3])
#define ROM_EUSCI_B_SPI_getReceiveBufferAddress                               \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[4])
#define ROM_EUSCI_B_SPI_changeMasterClock                                     \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_B_SPI_changeMasterClockParam *param))ROM_EUSCIBSPITABLE[5])
#define ROM_EUSCI_B_SPI_transmitData                                          \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t transmitData))ROM_EUSCIBSPITABLE[6])
#define ROM_EUSCI_B_SPI_select4PinFunctionality                               \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t select4PinFunctionality))ROM_EUSCIBSPITABLE[7])
#define ROM_EUSCI_B_SPI_initSlave                                             \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_B_SPI_initSlaveParam *param))ROM_EUSCIBSPITABLE[8])
#define ROM_EUSCI_B_SPI_disableInterrupt                                      \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint8_t mask))ROM_EUSCIBSPITABLE[9])
#define ROM_EUSCI_B_SPI_getTransmitBufferAddress                              \
        ((uint32_t (*)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[10])
#define ROM_EUSCI_B_SPI_changeClockPhasePolarity                              \
        ((void (*)(uint16_t baseAddress,                                      \
                   uint16_t clockPhase,                                       \
                   uint16_t clockPolarity))ROM_EUSCIBSPITABLE[11])
#define ROM_EUSCI_B_SPI_receiveData                                           \
        ((uint8_t (*)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[12])
#define ROM_EUSCI_B_SPI_getInterruptStatus                                    \
        ((uint8_t (*)(uint16_t baseAddress,                                   \
                      uint8_t mask))ROM_EUSCIBSPITABLE[13])
#define ROM_EUSCI_B_SPI_initMaster                                            \
        ((void (*)(uint16_t baseAddress,                                      \
                   EUSCI_B_SPI_initMasterParam *param))ROM_EUSCIBSPITABLE[14])
#define ROM_EUSCI_B_SPI_enable                                                \
        ((void (*)(uint16_t baseAddress))ROM_EUSCIBSPITABLE[15])

#else
#error "Large code model is not supported"
#endif

#endif // __ROM_DRIVERLIB_H__
