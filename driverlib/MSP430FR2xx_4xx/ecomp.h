//*****************************************************************************
//
// ecomp.h - Driver for the ECOMP Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_ECOMP_H__
#define __MSP430WARE_ECOMP_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_ECOMPx__

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

#include "inc/hw_memmap.h"
//*****************************************************************************
//
//! \brief Used in the EComp_init() function as the param parameter.
//
//*****************************************************************************
typedef struct EComp_initParam {
    //! Selects the input to the positive terminal
    //! \n Valid values are:
    //! - \b ECOMP_INPUT_0
    //! - \b ECOMP_INPUT_1
    //! - \b ECOMP_INPUT_2
    //! - \b ECOMP_INPUT_3
    //! - \b ECOMP_INPUT_DEVICE_SPECIFIC_0
    //! - \b ECOMP_INPUT_DEVICE_SPECIFIC_1
    //! - \b ECOMP_INPUT_DAC
    //! - \b ECOMP_INPUT_DISABLED
    uint8_t positiveTerminalInput;
    //! Selects the input to the negative terminal
    //! \n Valid values are:
    //! - \b ECOMP_INPUT_0
    //! - \b ECOMP_INPUT_1
    //! - \b ECOMP_INPUT_2
    //! - \b ECOMP_INPUT_3
    //! - \b ECOMP_INPUT_DEVICE_SPECIFIC_0
    //! - \b ECOMP_INPUT_DEVICE_SPECIFIC_1
    //! - \b ECOMP_INPUT_DAC
    //! - \b ECOMP_INPUT_DISABLED
    uint8_t negativeTerminalInput;
    //! Controls the output filter delay state, which is either off or enabled
    //! with a specified delay level. This parameter is device specific and
    //! delay levels should be found in the device's datasheet.
    //! \n Valid values are:
    //! - \b ECOMP_FILTER_DELAY_OFF [Default]
    //! - \b ECOMP_FILTER_DELAY_450NS
    //! - \b ECOMP_FILTER_DELAY_900NS
    //! - \b ECOMP_FILTER_DELAY_1800NS
    //! - \b ECOMP_FILTER_DELAY_3600NS
    uint16_t outputFilterEnableAndDelayLevel;
    //! Controls if the output will be inverted or not
    //! \n Valid values are:
    //! - \b ECOMP_NORMAL_OUTPUT_POLARITY [Default]
    //! - \b ECOMP_INVERTED_OUTPUT_POLARITY
    uint16_t invertedOutputPolarity;
} EComp_initParam;

//*****************************************************************************
//
//! \brief Used in the EComp_configureDAC() function as the param parameter.
//
//*****************************************************************************
typedef struct EComp_configureDACParam {
    //! Selects the built-in DAC reference voltage.
    //! \n Valid values are:
    //! - \b ECOMP_DAC_REFERENCE_VOLTAGE_VDD [Default]
    //! - \b ECOMP_DAC_REFERENCE_VOLTAGE_VREF
    uint8_t referenceVoltage;
    //! Selects the built-in DAC buffer controlled source.
    //! \n Valid values are:
    //! - \b ECOMP_DAC_BUFFER_SOURCE_COMP_OUTPUT
    //! - \b ECOMP_DAC_BUFFER_SOURCE_DUAL_BUFFER_1 [Default]
    //! - \b ECOMP_DAC_BUFFER_SOURCE_DUAL_BUFFER_2
    uint8_t bufferSource;
    //! Sets the first DAC buffer data (0~63).
    uint16_t firstBufferData;
    //! Sets the second DAC buffer data (0~63). The reset value for the second
    //! DAC buffer is 0x1.
    uint16_t secondBufferData;
} EComp_configureDACParam;



//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: EComp_init(), and EComp_init().
//
//*****************************************************************************
#define ECOMP_INPUT_0                                                       0x0
#define ECOMP_INPUT_1                                                       0x1
#define ECOMP_INPUT_2                                                       0x2
#define ECOMP_INPUT_3                                                       0x3
#define ECOMP_INPUT_DEVICE_SPECIFIC_0                                       0x4
#define ECOMP_INPUT_DEVICE_SPECIFIC_1                                       0x5
#define ECOMP_INPUT_DAC                                                     0x6
#define ECOMP_INPUT_DISABLED                                                0x7

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: EComp_init().
//
//*****************************************************************************
#define ECOMP_FILTER_DELAY_OFF                                              0x0
#define ECOMP_FILTER_DELAY_450NS                             (CPFLT|CPFLTDLY_0)
#define ECOMP_FILTER_DELAY_900NS                             (CPFLT|CPFLTDLY_1)
#define ECOMP_FILTER_DELAY_1800NS                            (CPFLT|CPFLTDLY_2)
#define ECOMP_FILTER_DELAY_3600NS                            (CPFLT|CPFLTDLY_3)

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: EComp_init().
//
//*****************************************************************************
#define ECOMP_NORMAL_OUTPUT_POLARITY                                        0x0
#define ECOMP_INVERTED_OUTPUT_POLARITY                                    CPINV

//*****************************************************************************
//
// The following are values that can be passed to the hysteresisMode parameter
// for functions: EComp_selectHysteresisMode().
//
//*****************************************************************************
#define ECOMP_HYSTERESIS_MODE_DISABLE                                  CPHSEL_0
#define ECOMP_HYSTERESIS_MODE_10MV                                     CPHSEL_1
#define ECOMP_HYSTERESIS_MODE_20MV                                     CPHSEL_2
#define ECOMP_HYSTERESIS_MODE_30MV                                     CPHSEL_3

//*****************************************************************************
//
// The following are values that can be passed to the powerMode parameter for
// functions: EComp_selectPowerMode().
//
//*****************************************************************************
#define ECOMP_POWER_MODE_HIGH_POWER_HIGH_SPEED                              0x0
#define ECOMP_POWER_MODE_LOW_POWER_LOW_SPEED                             CPMSEL

//*****************************************************************************
//
// The following are values that can be passed to the interruptMask parameter
// for functions: EComp_enableInterrupt(), and EComp_disableInterrupt().
//
//*****************************************************************************
#define ECOMP_OUTPUT_INTERRUPT                                             CPIE
#define ECOMP_INVERTED_POLARITY_INTERRUPT                                 CPIIE

//*****************************************************************************
//
// The following are values that can be passed to the interruptFlagMask
// parameter for functions: EComp_clearInterrupt(), and
// EComp_getInterruptStatus() as well as returned by the
// EComp_getInterruptStatus() function.
//
//*****************************************************************************
#define ECOMP_OUTPUT_INTERRUPT_FLAG                                       CPIFG
#define ECOMP_INVERTED_POLARITY_INTERRUPT_FLAG                           CPIIFG

//*****************************************************************************
//
// The following are values that can be passed to the edgeDirection parameter
// for functions: EComp_setInterruptEdgeDirection().
//
//*****************************************************************************
#define ECOMP_OUTPUT_INTERRUPT_RISING_EDGE                                  0x0
#define ECOMP_OUTPUT_INTERRUPT_FALLING_EDGE                               CPIES

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the EComp_outputValue() function.
//
//*****************************************************************************
#define ECOMP_LOW                                                           0x0
#define ECOMP_HIGH                                                        CPOUT

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: EComp_configureDAC().
//
//*****************************************************************************
#define ECOMP_DAC_REFERENCE_VOLTAGE_VDD                                     0x0
#define ECOMP_DAC_REFERENCE_VOLTAGE_VREF                              CPDACREFS

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: EComp_configureDAC().
//
//*****************************************************************************
#define ECOMP_DAC_BUFFER_SOURCE_COMP_OUTPUT                                 0x0
#define ECOMP_DAC_BUFFER_SOURCE_DUAL_BUFFER_1                       (CPDACBUFS)
#define ECOMP_DAC_BUFFER_SOURCE_DUAL_BUFFER_2               (CPDACBUFS|CPDACSW)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Initializes the EComp
//!
//! Upon successful initialization of the EComp module, this function will have
//! reset all necessary register bits and set the given options in the
//! registers. To actually use the EComp_E module, the EComp_enable() function
//! must be explicitly called before use. (If a Reference Voltage is set to a
//! terminal, the Voltage should be set using the EComp_configureDAC()
//! function.)
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_init(uint16_t baseAddress,
                       EComp_initParam *param);

//*****************************************************************************
//
//! \brief Sets the hysteresis mode
//!
//! This function sets the hysteresis mode.
//!
//! \param baseAddress is the base address of the ECOMP module.
//! \param hysteresisMode decides the hysteresis mode
//!        Valid values are:
//!        - \b ECOMP_HYSTERESIS_MODE_DISABLE [Default]
//!        - \b ECOMP_HYSTERESIS_MODE_10MV
//!        - \b ECOMP_HYSTERESIS_MODE_20MV
//!        - \b ECOMP_HYSTERESIS_MODE_30MV
//!
//! Modified bits are \b CPHSEL of \b CPCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_selectHysteresisMode(uint16_t baseAddress,
                                       uint16_t hysteresisMode);

//*****************************************************************************
//
//! \brief Sets the power mode
//!
//! This function sets the power mode.
//!
//! \param baseAddress is the base address of the ECOMP module.
//! \param powerMode decides the power mode
//!        Valid values are:
//!        - \b ECOMP_POWER_MODE_HIGH_POWER_HIGH_SPEED [Default]
//!        - \b ECOMP_POWER_MODE_LOW_POWER_LOW_SPEED
//!
//! \return None
//
//*****************************************************************************
extern void EComp_selectPowerMode(uint16_t baseAddress,
                                  uint16_t powerMode);

//*****************************************************************************
//
//! \brief Turns on the EComp module
//!
//! This function sets the bit that enables the operation of the EComp module.
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! Modified bits are \b CPEN of \b CPCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Turns off the EComp module
//!
//! This function clears the CPEN bit disabling the operation of the EComp
//! module, saving from excess power consumption.
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! Modified bits are \b CPEN of \b CPCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_disable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Enables selected EComp interrupt sources
//!
//! Enables the indicated EComp interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor. <b>Does not clear interrupt flags.</b>
//!
//! \param baseAddress is the base address of the ECOMP module.
//! \param interruptMask
//!        Mask value is the logical OR of any of the following:
//!        - \b ECOMP_OUTPUT_INTERRUPT - Output interrupt
//!        - \b ECOMP_INVERTED_POLARITY_INTERRUPT - Output interrupt inverted
//!           polarity
//!
//! \return None
//
//*****************************************************************************
extern void EComp_enableInterrupt(uint16_t baseAddress,
                                  uint16_t interruptMask);

//*****************************************************************************
//
//! \brief Disables selected EComp interrupt sources
//!
//! Disables the indicated EComp interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor. <b>Does not clear interrupt flags.</b>
//!
//! \param baseAddress is the base address of the ECOMP module.
//! \param interruptMask
//!        Mask value is the logical OR of any of the following:
//!        - \b ECOMP_OUTPUT_INTERRUPT - Output interrupt
//!        - \b ECOMP_INVERTED_POLARITY_INTERRUPT - Output interrupt inverted
//!           polarity
//!
//! \return None
//
//*****************************************************************************
extern void EComp_disableInterrupt(uint16_t baseAddress,
                                   uint16_t interruptMask);

//*****************************************************************************
//
//! \brief Clears EComp interrupt flags
//!
//! The EComp interrupt source is cleared, so that it no longer asserts. The
//! highest interrupt flag is automatically cleared when an interrupt vector
//! generator is used.
//!
//! \param baseAddress is the base address of the ECOMP module.
//! \param interruptFlagMask
//!        Mask value is the logical OR of any of the following:
//!        - \b ECOMP_OUTPUT_INTERRUPT_FLAG - Output interrupt flag
//!        - \b ECOMP_INVERTED_POLARITY_INTERRUPT_FLAG - Output interrupt flag
//!           inverted polarity
//!
//! \return None
//
//*****************************************************************************
extern void EComp_clearInterrupt(uint16_t baseAddress,
                                 uint16_t interruptFlagMask);

//*****************************************************************************
//
//! \brief Gets the current EComp interrupt status
//!
//! This returns the interrupt status for the EComp_E module based on which
//! flag is passed.
//!
//! \param baseAddress is the base address of the ECOMP module.
//! \param interruptFlagMask
//!        Mask value is the logical OR of any of the following:
//!        - \b ECOMP_OUTPUT_INTERRUPT_FLAG - Output interrupt flag
//!        - \b ECOMP_INVERTED_POLARITY_INTERRUPT_FLAG - Output interrupt flag
//!           inverted polarity
//!
//! \return Logical OR of any of the following:
//!         - \b ECOMP_OUTPUT_INTERRUPT_FLAG Output interrupt flag
//!         - \b ECOMP_INVERTED_POLARITY_INTERRUPT_FLAG Output interrupt flag
//!         inverted polarity
//!         \n indicating the status of the masked flags
//
//*****************************************************************************
extern uint8_t EComp_getInterruptStatus(uint16_t baseAddress,
                                        uint16_t interruptFlagMask);

//*****************************************************************************
//
//! \brief Explicitly sets the edge direction that would trigger an interrupt
//!
//! This function will set which direction the output will have to go, whether
//! rising or falling, to generate an interrupt based on a non-inverted
//! interrupt.
//!
//! \param baseAddress is the base address of the ECOMP module.
//! \param edgeDirection determines which direction the edge would have to go
//!        to generate an interrupt based on the non-inverted interrupt flag.
//!        Valid values are:
//!        - \b ECOMP_OUTPUT_INTERRUPT_RISING_EDGE [Default] - sets the bit to
//!           generate an interrupt when the output of the EComp rises from LOW
//!           to HIGH if the normal interrupt bit is set(and HIGH to LOW if the
//!           inverted interrupt enable bit is set).
//!        - \b ECOMP_OUTPUT_INTERRUPT_FALLING_EDGE - sets the bit to generate
//!           an interrupt when the output of the EComp falls from HIGH to LOW
//!           if the normal interrupt bit is set(and LOW to HIGH if the
//!           inverted interrupt enable bit is set).
//!        \n Modified bits are \b CPIES of \b CPCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_setInterruptEdgeDirection(uint16_t baseAddress,
                                            uint16_t edgeDirection);

//*****************************************************************************
//
//! \brief Toggles the edge direction that would trigger an interrupt
//!
//! This function will toggle which direction the output will have to go,
//! whether rising or falling, to generate an interrupt based on a non-inverted
//! interrupt. If the direction was rising, it is now falling, if it was
//! falling, it is now rising.
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! Modified bits are \b CPIES of \b CPCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_toggleInterruptEdgeDirection(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Returns the output value of the EComp module
//!
//! Returns the output value of the EComp  module.
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! \return indicating the output value of the EComp module
//!         Return one of the following:
//!         - \b ECOMP_LOW
//!         - \b ECOMP_HIGH
//!         \n indicating the output value of the EComp module
//
//*****************************************************************************
extern uint8_t EComp_outputValue(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Configures the built-in DAC for internal reference
//!
//! This function will configure the built-in DAC register bits including
//! reference voltage and DAC buffer source.
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_configureDAC(uint16_t baseAddress,
                               EComp_configureDACParam *param);

//*****************************************************************************
//
//! \brief Enables DAC output
//!
//! This function will enable DAC output.
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_enableDAC(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables DAC output
//!
//! This function will disable DAC output. When it is disabled, the DAC always
//! output low.
//!
//! \param baseAddress is the base address of the ECOMP module.
//!
//! \return None
//
//*****************************************************************************
extern void EComp_disableDAC(uint16_t baseAddress);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_ECOMP_H__
