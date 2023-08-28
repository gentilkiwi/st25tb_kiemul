//*****************************************************************************
//
// sac.h - Driver for the SAC Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_SAC_H__
#define __MSP430WARE_SAC_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_SACx__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The following are values that can be passed to the positiveInput parameter
// for functions: SAC_OA_init().
//
//*****************************************************************************
#define SAC_OA_POSITIVE_INPUT_SOURCE_EXTERNAL                               0x0
#define SAC_OA_POSITIVE_INPUT_SOURCE_DAC                                  PSEL0
#define SAC_OA_POSITIVE_INPUT_SOURCE_PAIR_OA                              PSEL1
#define SAC_OA_POSITIVE_INPUT_SOURCE_DISCONNECTED                           0xF

//*****************************************************************************
//
// The following are values that can be passed to the negativeInput parameter
// for functions: SAC_OA_init().
//
//*****************************************************************************
#define SAC_OA_NEGATIVE_INPUT_SOURCE_EXTERNAL                               0x0
#define SAC_OA_NEGATIVE_INPUT_SOURCE_PGA                                  NSEL0
#define SAC_OA_NEGATIVE_INPUT_SOURCE_DISCONNECTED                           0xF

//*****************************************************************************
//
// The following are values that can be passed to the powerMode parameter for
// functions: SAC_OA_selectPowerMode().
//
//*****************************************************************************
#define SAC_OA_POWER_MODE_HIGH_SPEED_HIGH_POWER                             0x0
#define SAC_OA_POWER_MODE_LOW_SPEED_LOW_POWER                              OAPM

//*****************************************************************************
//
// The following are values that can be passed to the mode parameter for
// functions: SAC_PGA_setMode().
//
//*****************************************************************************
#define SAC_PGA_MODE_INVERTING                                           MSEL_0
#define SAC_PGA_MODE_BUFFER                                              MSEL_1
#define SAC_PGA_MODE_NONINVERTING                                        MSEL_2
#define SAC_PGA_MODE_CASCADE_OA_INVERTING                                MSEL_3

//*****************************************************************************
//
// The following are values that can be passed to the gain parameter for
// functions: SAC_PGA_setGain().
//
//*****************************************************************************
#define SAC_PGA_GAIN_BIT0                                                 GAIN0
#define SAC_PGA_GAIN_BIT1                                                 GAIN1
#define SAC_PGA_GAIN_BIT2                                                 GAIN2

//*****************************************************************************
//
// The following are values that can be passed to the load parameter for
// functions: SAC_DAC_selectLoad().
//
//*****************************************************************************
#define SAC_DAC_LOAD_DACDAT_WRITTEN                                   DACLSEL_0
#define SAC_DAC_LOAD_DEVICE_SPECIFIC_0                                DACLSEL_2
#define SAC_DAC_LOAD_DEVICE_SPECIFIC_1                                DACLSEL_3

//*****************************************************************************
//
// The following are values that can be passed to the reference parameter for
// functions: SAC_DAC_selectRefVoltage().
//
//*****************************************************************************
#define SAC_DAC_PRIMARY_REFERENCE                                     DACSREF_0
#define SAC_DAC_SECONDARY_REFERENCE                                   DACSREF_1

//*****************************************************************************
//
// The following are values that can be passed to the data parameter for
// functions: SAC_DAC_setData().
//
//*****************************************************************************
#define SAC_DAC_DATA_BIT0                                              DACDATA0
#define SAC_DAC_DATA_BIT1                                              DACDATA1
#define SAC_DAC_DATA_BIT2                                              DACDATA2
#define SAC_DAC_DATA_BIT3                                              DACDATA3
#define SAC_DAC_DATA_BIT4                                              DACDATA4
#define SAC_DAC_DATA_BIT5                                              DACDATA5
#define SAC_DAC_DATA_BIT6                                              DACDATA6
#define SAC_DAC_DATA_BIT7                                              DACDATA7
#define SAC_DAC_DATA_BIT8                                              DACDATA8
#define SAC_DAC_DATA_BIT9                                              DACDATA9
#define SAC_DAC_DATA_BIT10                                            DACDATA10
#define SAC_DAC_DATA_BIT11                                            DACDATA11

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Initializes SAC OA with positive input and negative input. Available
//! to at least SAC-L1.
//!
//! This function initializes SAC OA with positive input and negative input.
//! Available to at least SAC-L1. Please consult your device-specific datasheet
//! to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param positiveInput selects the positive input source
//!        Valid values are:
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_EXTERNAL [Default]
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_DAC
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_PAIR_OA
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_DISCONNECTED
//!        \n Modified bits are \b PSEL and \b PMUXEN of \b SACxOA register.
//! \param negativeInput selects the negative input source
//!        Valid values are:
//!        - \b SAC_OA_NEGATIVE_INPUT_SOURCE_EXTERNAL [Default]
//!        - \b SAC_OA_NEGATIVE_INPUT_SOURCE_PGA
//!        - \b SAC_OA_NEGATIVE_INPUT_SOURCE_DISCONNECTED
//!        \n Modified bits are \b NSEL and \b NMUXEN of \b SACxOA register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_init(uint16_t baseAddress,
                        uint16_t positiveInput,
                        uint16_t negativeInput);

//*****************************************************************************
//
//! \brief Selects power mode for OA. Available to at least SAC-L1.
//!
//! This function selects power mode for OA. Available to at least SAC-L1.
//! Please consult your device-specific datasheet to see what SAC level is
//! available.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param powerMode selects OA power mode.
//!        Valid values are:
//!        - \b SAC_OA_POWER_MODE_HIGH_SPEED_HIGH_POWER [Default]
//!        - \b SAC_OA_POWER_MODE_LOW_SPEED_LOW_POWER
//!        \n Modified bits are \b OAPM of \b SACxOA register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_selectPowerMode(uint16_t baseAddress,
                                   uint16_t powerMode);

//*****************************************************************************
//
//! \brief Enables OA. Available to at least SAC-L1.
//!
//! This will enables OA for normal mode. Available to at least SAC-L1. Please
//! consult your device-specific datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables OA. Available to at least SAC-L1.
//!
//! This will disable OA and OA outputs high impedance. Available to at least
//! SAC-L1. Please consult your device-specific datasheet to see what SAC level
//! is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_disable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Enables the SAC all modules. Available to at least SAC-L1.
//!
//! This will enable SAC all modules. Available to at least SAC-L1. Please
//! consult your device-specific datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables the SAC all modules. Available to at least SAC-L1.
//!
//! This will disable SAC all modules. Available to at least SAC-L1. Please
//! consult your device-specific datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_disable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief SAC PGA mode selection. Only available to at least SAC-L2.
//!
//! Allows selection of different SAC PGA modes. Only available to at least
//! SAC-L2. Please consult your device-specific datasheet to see what SAC level
//! is available.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param mode selects PGA mode.
//!        Valid values are:
//!        - \b SAC_PGA_MODE_INVERTING
//!        - \b SAC_PGA_MODE_BUFFER [Default]
//!        - \b SAC_PGA_MODE_NONINVERTING
//!        - \b SAC_PGA_MODE_CASCADE_OA_INVERTING
//!        \n Modified bits are \b MSEL of \b SACxPGA register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_PGA_setMode(uint16_t baseAddress,
                            uint16_t mode);

//*****************************************************************************
//
//! \brief SAC PGA gain configuration. Only available to at least SAC-L2.
//!
//! Allows different SAC PGA gain configurations. Only available to at least
//! SAC-L2. Please consult your device-specific datasheet to see what SAC level
//! is available.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param gain selects PGA gain configuration.
//!        Mask value is the logical OR of any of the following:
//!        - \b SAC_PGA_GAIN_BIT0 [Default]
//!        - \b SAC_PGA_GAIN_BIT1
//!        - \b SAC_PGA_GAIN_BIT2
//!        \n Modified bits are \b GAIN of \b SACxPGA register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_PGA_setGain(uint16_t baseAddress,
                            uint16_t gain);

//*****************************************************************************
//
//! \brief SAC DAC enable. Only available to at least SAC-L3.
//!
//! Enables SAC DAC. Can be modified only when DACEN = 0. Only available to at
//! least SAC-L3. Please consult your device-specific datasheet to see what SAC
//! level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief SAC DAC disable. Only available to at least SAC-L3.
//!
//! Disables SAC DAC. Can be modified only when DACEN = 0. Only available to at
//! least SAC-L3. Please consult your device-specific datasheet to see what SAC
//! level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_disable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief SAC DAC interrupt enable. Only available to at least SAC-L3.
//!
//! Enables SAC DAC interrupt. Can be modified only when DACEN = 0.
//! Asynchronously enable the SAC and the SAC DAC interrupt to prevent
//! unexpected results. Only available to at least SAC-L3. Please consult your
//! device-specific datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_interruptEnable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief SAC DAC interrupt disable. Only available to at least SAC-L3.
//!
//! Disables SAC DAC interrupt. Can be modified only when DACEN = 0. Only
//! available to at least SAC-L3. Please consult your device-specific datasheet
//! to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_interruptDisable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief SAC DAC DMA request enable. Only available to at least SAC-L3.
//!
//! Enables SAC DAC DMA request. Can be modified only when DACEN = 0. Only
//! available to at least SAC-L3. Please consult your device-specific datasheet
//! to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_DMARequestEnable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief SAC DAC DMA request disable. Only available to at least SAC-L3.
//!
//! Disables SAC DAC DMA request. Can be modified only when DACEN = 0. Only
//! available to at least SAC-L3. Please consult your device-specific datasheet
//! to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_DMARequestDisable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief SAC DAC load select. Only available to at least SAC-L3.
//!
//! Selects the load trigger for the DAC latch. DACENC must be set for the DAC
//! to update, except when DACLSEL = 0. Can be modified only when DACEN = 0.
//! Only available to at least SAC-L3. Please consult your device-specific
//! datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param load selects DAC load.
//!        Valid values are:
//!        - \b SAC_DAC_LOAD_DACDAT_WRITTEN [Default]
//!        - \b SAC_DAC_LOAD_DEVICE_SPECIFIC_0
//!        - \b SAC_DAC_LOAD_DEVICE_SPECIFIC_1
//!        \n Modified bits are \b DACLSEL of \b SACxDAC register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_selectLoad(uint16_t baseAddress,
                               uint16_t load);

//*****************************************************************************
//
//! \brief SAC DAC select reference voltage. Only available to at least SAC-L3.
//!
//! Selects SAC DAC select reference voltage, primary or secondary. Can be
//! modified only when DACEN = 0. Only available to at least SAC-L3. Please
//! consult your device-specific datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param reference selects DAC reference voltage.
//!        Valid values are:
//!        - \b SAC_DAC_PRIMARY_REFERENCE [Default]
//!        - \b SAC_DAC_SECONDARY_REFERENCE
//!        \n Modified bits are \b DACSREF of \b SACxDAC register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_selectRefVoltage(uint16_t baseAddress,
                                     uint16_t reference);

//*****************************************************************************
//
//! \brief Get SAC DAC data. Only available to at least SAC-L3.
//!
//! Gets from SAC DAC data. Bit 11 represents the MSB. Only word access to
//! SACxDAT register is allowed. Byte operation may cause unexpected results.
//! Only available to at least SAC-L3. Please consult your device-specific
//! datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return 12-bit value from SAC DAC data.
//
//*****************************************************************************
extern uint16_t SAC_DAC_getData(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Set SAC DAC data. Only available to at least SAC-L3.
//!
//! Sets data to SAC DAC. Bit 11 represents the MSB. Only word access to
//! SACxDAT register is allowed. Byte operation may cause unexpected results.
//! Only available to at least SAC-L3. Please consult your device-specific
//! datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param data sends DAC data.
//!        Mask value is the logical OR of any of the following:
//!        - \b SAC_DAC_DATA_BIT0 [Default]
//!        - \b SAC_DAC_DATA_BIT1
//!        - \b SAC_DAC_DATA_BIT2
//!        - \b SAC_DAC_DATA_BIT3
//!        - \b SAC_DAC_DATA_BIT4
//!        - \b SAC_DAC_DATA_BIT5
//!        - \b SAC_DAC_DATA_BIT6
//!        - \b SAC_DAC_DATA_BIT7
//!        - \b SAC_DAC_DATA_BIT8
//!        - \b SAC_DAC_DATA_BIT9
//!        - \b SAC_DAC_DATA_BIT10
//!        - \b SAC_DAC_DATA_BIT11
//!        \n Modified bits are \b DACDATA of \b SACxDAT register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_setData(uint16_t baseAddress,
                            uint16_t data);

//*****************************************************************************
//
//! \brief Get SAC DAC data update flag. Only available to at least SAC-L3.
//!
//! Gets flag of SAC DAC update status. Only available to at least SAC-L3.
//! Please consult your device-specific datasheet to see what SAC level is
//! available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return True or false whether DAC latch data register updated
//
//*****************************************************************************
extern bool SAC_DAC_getIFG(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Clears SAC DAC data update flag. Only available to at least SAC-L3.
//!
//! Clears SAC DAC data update flag by writing 1. It could also be cleared by
//! reading SACxIV register. If DMA is enabled, this flag is automatically
//! cleared by DMA when a new data request is accepted. Can be modified only
//! when DACEN = 0. Only available to at least SAC-L3. Please consult your
//! device-specific datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_DAC_clearIFG(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Get SAC DAC interrupt vector value. Only available to at least
//! SAC-L3.
//!
//! Get SAC DAC interrupt vector value. Only word access to the SACIVx register
//! is recommended. Only available to at least SAC-L3. Please consult your
//! device-specific datasheet to see what SAC level is available.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return SAC DAC interrupt vector value
//
//*****************************************************************************
extern uint16_t SAC_getInterruptVector(uint16_t baseAddress);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_SAC_H__
