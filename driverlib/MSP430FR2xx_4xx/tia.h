//*****************************************************************************
//
// tia.h - Driver for the TIA Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_TIA_H__
#define __MSP430WARE_TIA_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_TRIx__

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
// for functions: TIA_selectPositiveInput().
//
//*****************************************************************************
#define TIA_POSITIVE_INPUT_EXTERNAL_SOURCE                            TRIPSEL_0
#define TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_1                          TRIPSEL_1
#define TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_2                          TRIPSEL_2
#define TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_3                          TRIPSEL_3

//*****************************************************************************
//
// The following are values that can be passed to the powerMode parameter for
// functions: TIA_selectPowerMode().
//
//*****************************************************************************
#define TIA_HIGH_SPEED_HIGH_POWER                                           0x0
#define TIA_LOW_SPEED_LOW_POWER                                           TRIPM

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Selects TIA positive input
//!
//! This function selects TIA positive input.
//!
//! \param baseAddress is the base address of the TIA module.
//! \param positiveInput selects positive input.
//!        Valid values are:
//!        - \b TIA_POSITIVE_INPUT_EXTERNAL_SOURCE [Default]
//!        - \b TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_1
//!        - \b TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_2
//!        - \b TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_3
//!        \n Modified bits are \b TRIPSEL of \b TRICTL register.
//!
//! \return None
//
//*****************************************************************************
extern void TIA_selectPositiveInput(uint16_t baseAddress,
                                    uint16_t positiveInput);

//*****************************************************************************
//
//! \brief Selects TIA power mode
//!
//! This function selects TIA power mode.
//!
//! \param baseAddress is the base address of the TIA module.
//! \param powerMode selects TIA power mode.
//!        Valid values are:
//!        - \b TIA_HIGH_SPEED_HIGH_POWER [Default]
//!        - \b TIA_LOW_SPEED_LOW_POWER
//!        \n Modified bits are \b TRIPM of \b TRICTL register.
//!
//! \return None
//
//*****************************************************************************
extern void TIA_selectPowerMode(uint16_t baseAddress,
                                uint16_t powerMode);

//*****************************************************************************
//
//! \brief Enables TIA module
//!
//! This function enables TIA module.
//!
//! \param baseAddress is the base address of the TIA module.
//!
//! \return None
//
//*****************************************************************************
extern void TIA_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables TIA module
//!
//! This function disables TIA module.
//!
//! \param baseAddress is the base address of the TIA module.
//!
//! \return None
//
//*****************************************************************************
extern void TIA_disable(uint16_t baseAddress);

//*****************************************************************************
//
// The following are deprecated APIs.
//
//*****************************************************************************
#define TRI_selectPositiveInput                         TIA_selectPositiveInput
#define TRI_selectPowerMode                                 TIA_selectPowerMode
#define TRI_enable                                                   TIA_enable
#define TRI_disable                                                 TIA_disable
#define TRI_POSITIVE_INPUT_EXTERNAL_SOURCE   TIA_POSITIVE_INPUT_EXTERNAL_SOURCE
#define TRI_POSITIVE_INPUT_DEVICE_SPECIFIC_1                                  \
                                           TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_1
#define TRI_POSITIVE_INPUT_DEVICE_SPECIFIC_2                                  \
                                           TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_2
#define TRI_POSITIVE_INPUT_DEVICE_SPECIFIC_3                                  \
                                           TIA_POSITIVE_INPUT_DEVICE_SPECIFIC_3
#define TRI_HIGH_SPEED_HIGH_POWER                     TIA_HIGH_SPEED_HIGH_POWER
#define TRI_LOW_SPEED_LOW_POWER                         TIA_LOW_SPEED_LOW_POWER
#define TIA0_BASE                                                     TRI0_BASE

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_TIA_H__
