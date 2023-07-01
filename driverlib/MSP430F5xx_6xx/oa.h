//*****************************************************************************
//
// oa.h - Driver for the OA Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_OA_H__
#define __MSP430WARE_OA_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_OA_0__

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
// The following are values that can be passed to the positiveInputMask
// parameter for functions: OA_openSwitch(), and OA_closeSwitch().
//
//*****************************************************************************
#define OA_POSITIVE_INPUT_TERMINAL_SWITCH0                                 PSW0
#define OA_POSITIVE_INPUT_TERMINAL_SWITCH1                                 PSW1
#define OA_POSITIVE_INPUT_TERMINAL_SWITCH2                                 PSW2
#define OA_POSITIVE_INPUT_TERMINAL_SWITCH3                                 PSW3
#define OA_POSITIVE_INPUT_TERMINAL_NONE                                    0x00

//*****************************************************************************
//
// The following are values that can be passed to the negativeInputMask
// parameter for functions: OA_openSwitch(), and OA_closeSwitch().
//
//*****************************************************************************
#define OA_NEGATIVE_INPUT_TERMINAL_SWITCH0                                 NSW0
#define OA_NEGATIVE_INPUT_TERMINAL_SWITCH1                                 NSW1
#define OA_NEGATIVE_INPUT_TERMINAL_SWITCH2                                 NSW2
#define OA_NEGATIVE_INPUT_TERMINAL_SWITCH3                                 NSW3
#define OA_NEGATIVE_INPUT_TERMINAL_SWITCH4                                 NSW4
#define OA_NEGATIVE_INPUT_TERMINAL_NONE                                    0x00

//*****************************************************************************
//
// The following are values that can be passed to the groundMask parameter for
// functions: OA_openSwitch(), and OA_closeSwitch().
//
//*****************************************************************************
#define OA_GROUND_SWITCH0                                                  GSW0
#define OA_GROUND_SWITCH1                                                  GSW1
#define OA_GROUND_NONE                                                     0x00

//*****************************************************************************
//
// The following are values that can be passed to the inputTerminal parameter
// for functions: OA_getSwitchStatus().
//
//*****************************************************************************
#define OA_POSITIVE_INPUT_TERMINAL_SWITCHES                                0x00
#define OA_NEGATIVE_INPUT_TERMINAL_SWITCHES                                0x01
#define OA_GROUND_SWITCHES                                                 0x02

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the OA_getRailToRailInputReadyStatus() function.
//
//*****************************************************************************
#define OA_INPUT_READY                                                 OARRIRDY
#define OA_INPUT_NOT_READY                                                 0x00

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the OA_getRailToRailInputStatus() function.
//
//*****************************************************************************
#define OA_INPUT_ENABLED                                                  OARRI
#define OA_INPUT_DISABLED                                                (0x00)

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the OA_getAmplifierModeStatus() function.
//
//*****************************************************************************
#define OA_AMPLIFIER_MODE_ENABLED                                           OAM
#define OA_AMPLIFIER_MODE_DISABLED                                       (0x00)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Opens the positive input terminal, negative input terminal and
//! ground switch of the OA Module per user selection
//!
//! \param baseAddress is the base address of the OA module.
//! \param positiveInputMask
//!        Mask value is the logical OR of any of the following:
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH0
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH1
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH2
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH3
//!        - \b OA_POSITIVE_INPUT_TERMINAL_NONE
//! \param negativeInputMask
//!        Mask value is the logical OR of any of the following:
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH0
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH1
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH2
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH3
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH4
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_NONE
//! \param groundMask
//!        Mask value is the logical OR of any of the following:
//!        - \b OA_GROUND_SWITCH0
//!        - \b OA_GROUND_SWITCH1
//!        - \b OA_GROUND_NONE
//!
//! \return None
//
//*****************************************************************************
extern void OA_openSwitch(uint16_t baseAddress,
                          uint8_t positiveInputMask,
                          uint8_t negativeInputMask,
                          uint8_t groundMask);

//*****************************************************************************
//
//! \brief Closes the positive input terminal, negative input terminal and
//! ground switch of the OA Module per user selection.
//!
//! \param baseAddress is the base address of the OA module.
//! \param positiveInputMask
//!        Mask value is the logical OR of any of the following:
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH0
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH1
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH2
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCH3
//!        - \b OA_POSITIVE_INPUT_TERMINAL_NONE
//! \param negativeInputMask
//!        Mask value is the logical OR of any of the following:
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH0
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH1
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH2
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH3
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCH4
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_NONE
//! \param groundMask
//!        Mask value is the logical OR of any of the following:
//!        - \b OA_GROUND_SWITCH0
//!        - \b OA_GROUND_SWITCH1
//!        - \b OA_GROUND_NONE
//!
//! \return None
//
//*****************************************************************************
extern void OA_closeSwitch(uint16_t baseAddress,
                           uint8_t positiveInputMask,
                           uint8_t negativeInputMask,
                           uint8_t groundMask);

//*****************************************************************************
//
//! \brief Gets the positive input terminal, negative input terminal and ground
//! switch status of the OA Module per user selection.
//!
//! \param baseAddress is the base address of the OA module.
//! \param inputTerminal
//!        Valid values are:
//!        - \b OA_POSITIVE_INPUT_TERMINAL_SWITCHES
//!        - \b OA_NEGATIVE_INPUT_TERMINAL_SWITCHES
//!        - \b OA_GROUND_SWITCHES
//!
//! \return Logical OR of the switches that are closed in the selected
//!         inputTerminal
//
//*****************************************************************************
extern uint8_t OA_getSwitchStatus(uint16_t baseAddress,
                                  uint8_t inputTerminal);

//*****************************************************************************
//
//! \brief Gets the rail to rail input ready status
//!
//! \param baseAddress is the base address of the OA module.
//!
//! \return One of the following:
//!         - \b OA_INPUT_READY
//!         - \b OA_INPUT_NOT_READY
//
//*****************************************************************************
extern uint8_t OA_getRailToRailInputReadyStatus(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Gets the rail to rail input status
//!
//! \param baseAddress is the base address of the OA module.
//!
//! \return One of the following:
//!         - \b OA_INPUT_ENABLED
//!         - \b OA_INPUT_DISABLED
//
//*****************************************************************************
extern uint8_t OA_getRailToRailInputStatus(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Enables the rail to rail input
//!
//! \param baseAddress is the base address of the OA module.
//!
//! \return None
//
//*****************************************************************************
extern void OA_enableRailToRailInput(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables the rail to rail input
//!
//! \param baseAddress is the base address of the OA module.
//!
//! \return None
//
//*****************************************************************************
extern void OA_disableRailToRailInput(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables the amplifier mode
//!
//! \param baseAddress is the base address of the OA module.
//!
//! \return None
//
//*****************************************************************************
extern void OA_disableAmplifierMode(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Enables the amplifier mode
//!
//! \param baseAddress is the base address of the OA module.
//!
//! \return None
//
//*****************************************************************************
extern void OA_enableAmplifierMode(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Gets the amplifier mode status
//!
//! \param baseAddress is the base address of the OA module.
//!
//! \return One of the following:
//!         - \b OA_AMPLIFIER_MODE_ENABLED
//!         - \b OA_AMPLIFIER_MODE_DISABLED
//
//*****************************************************************************
extern uint8_t OA_getAmplifierModeStatus(uint16_t baseAddress);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_OA_H__
