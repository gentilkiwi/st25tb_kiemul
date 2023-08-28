//*****************************************************************************
//
// icc.h - Driver for the ICC Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_ICC_H__
#define __MSP430WARE_ICC_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_ICC__

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
// The following are values that can be passed to the ILSRmask parameter for
// functions: ICC_setInterruptLevel(); the interruptSource parameter for
// functions: ICC_getInterruptLevel().
//
//*****************************************************************************
#define ICC_ILSR_P4                                                         0x1
#define ICC_ILSR_P3                                                         0x2
#define ICC_ILSR_P2                                                         0x4
#define ICC_ILSR_P1                                                         0x8
#define ICC_ILSR_SAC3DAC_SAC1DAC                                           0x10
#define ICC_ILSR_SAC2DAC_SAC0DAC                                           0x20
#define ICC_ILSR_ECOMP1_ECOMP0                                             0x40
#define ICC_ILSR_ADC                                                       0x80
#define ICC_ILSR_EUSCI_B1                                                 0x100
#define ICC_ILSR_EUSCI_B0                                                 0x200
#define ICC_ILSR_EUSCI_A1                                                 0x400
#define ICC_ILSR_EUSCI_A0                                                 0x800
#define ICC_ILSR_WDT_INT                                                 0x1000
#define ICC_ILSR_RTC_COUNTER                                             0x2000
#define ICC_ILSR_TIMER3_B1                                               0x4000
#define ICC_ILSR_TIMER3_B0                                               0x8000
#define ICC_ILSR_TIMER2_B1                                              0x10000
#define ICC_ILSR_TIMER2_B0                                              0x20000
#define ICC_ILSR_TIMER1_B1                                              0x40000
#define ICC_ILSR_TIMER1_B0                                              0x80000
#define ICC_ILSR_TIMER0_B1                                             0x100000
#define ICC_ILSR_TIMER0_B0                                             0x200000

//*****************************************************************************
//
// The following are values that can be passed to the interruptLevel parameter
// for functions: ICC_setInterruptLevel() as well as returned by the
// ICC_getInterruptLevel() function, the ICC_getCurrentICM() function, the
// ICC_getICM3() function, the ICC_getICM2() function, the ICC_getICM1()
// function and the ICC_getICM0() function.
//
//*****************************************************************************
#define ICC_LEVEL_0                                                         0x0
#define ICC_LEVEL_1                                                         0x1
#define ICC_LEVEL_2                                                         0x2
#define ICC_LEVEL_3                                                         0x3
#define ICC_LEVEL_ERROR                                                     0x4

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the ICC_getMVSStackPointer() function.
//
//*****************************************************************************
#define ICC_MVS_STACK_EMPTY                                                 0x0
#define ICC_MVS_STACK_ICM0                                                  0x1
#define ICC_MVS_STACK_ICM0_ICM1                                             0x2
#define ICC_MVS_STACK_ICM0_ICM1_ICM2                                        0x3
#define ICC_MVS_STACK_FULL                                                  0x4

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Enables ICC module
//!
//! This function enables ICC.
//!
//!
//! \return None
//
//*****************************************************************************
extern void ICC_enable(void);

//*****************************************************************************
//
//! \brief Disables ICC module
//!
//! This function disables ICC.
//!
//!
//! \return None
//
//*****************************************************************************
extern void ICC_disable(void);

//*****************************************************************************
//
//! \brief Sets ICC interrupt level for selected source
//!
//! This function sets ICC interrupt level given a maskable interrupt source.
//!
//! \param ILSRmask is a 32-bit unsigned integer in which bit position (31 to
//!        0) determines which interrupt source is set.
//!        Mask value is the logical OR of any of the following:
//!        - \b ICC_ILSR_P4
//!        - \b ICC_ILSR_P3
//!        - \b ICC_ILSR_P2
//!        - \b ICC_ILSR_P1
//!        - \b ICC_ILSR_SAC3DAC_SAC1DAC
//!        - \b ICC_ILSR_SAC2DAC_SAC0DAC
//!        - \b ICC_ILSR_ECOMP1_ECOMP0
//!        - \b ICC_ILSR_ADC
//!        - \b ICC_ILSR_EUSCI_B1
//!        - \b ICC_ILSR_EUSCI_B0
//!        - \b ICC_ILSR_EUSCI_A1
//!        - \b ICC_ILSR_EUSCI_A0
//!        - \b ICC_ILSR_WDT_INT
//!        - \b ICC_ILSR_RTC_COUNTER
//!        - \b ICC_ILSR_TIMER3_B1
//!        - \b ICC_ILSR_TIMER3_B0
//!        - \b ICC_ILSR_TIMER2_B1
//!        - \b ICC_ILSR_TIMER2_B0
//!        - \b ICC_ILSR_TIMER1_B1
//!        - \b ICC_ILSR_TIMER1_B0
//!        - \b ICC_ILSR_TIMER0_B1
//!        - \b ICC_ILSR_TIMER0_B0
//! \param interruptLevel determines what interrupt level to set to.
//!        Valid values are:
//!        - \b ICC_LEVEL_0
//!        - \b ICC_LEVEL_1
//!        - \b ICC_LEVEL_2
//!        - \b ICC_LEVEL_3
//!        - \b ICC_LEVEL_ERROR
//!
//! \return None
//
//*****************************************************************************
extern void ICC_setInterruptLevel(uint32_t ILSRmask,
                                  uint8_t interruptLevel);

//*****************************************************************************
//
//! \brief Gets ICC interrupt level for selected source
//!
//! This function gets ICC interrupt level given a maskable interrupt source.
//!
//! \param interruptSource is a 32-bit unsigned integer in which bit position
//!        (31 to 0) determines which interrupt source to read level from.
//!        Valid values are:
//!        - \b ICC_ILSR_P4
//!        - \b ICC_ILSR_P3
//!        - \b ICC_ILSR_P2
//!        - \b ICC_ILSR_P1
//!        - \b ICC_ILSR_SAC3DAC_SAC1DAC
//!        - \b ICC_ILSR_SAC2DAC_SAC0DAC
//!        - \b ICC_ILSR_ECOMP1_ECOMP0
//!        - \b ICC_ILSR_ADC
//!        - \b ICC_ILSR_EUSCI_B1
//!        - \b ICC_ILSR_EUSCI_B0
//!        - \b ICC_ILSR_EUSCI_A1
//!        - \b ICC_ILSR_EUSCI_A0
//!        - \b ICC_ILSR_WDT_INT
//!        - \b ICC_ILSR_RTC_COUNTER
//!        - \b ICC_ILSR_TIMER3_B1
//!        - \b ICC_ILSR_TIMER3_B0
//!        - \b ICC_ILSR_TIMER2_B1
//!        - \b ICC_ILSR_TIMER2_B0
//!        - \b ICC_ILSR_TIMER1_B1
//!        - \b ICC_ILSR_TIMER1_B0
//!        - \b ICC_ILSR_TIMER0_B1
//!        - \b ICC_ILSR_TIMER0_B0
//!
//! \return Interrupt level of a given maskable interrupt source.
//!         Return one of the following:
//!         - \b ICC_LEVEL_0
//!         - \b ICC_LEVEL_1
//!         - \b ICC_LEVEL_2
//!         - \b ICC_LEVEL_3
//!         - \b ICC_LEVEL_ERROR
//!         \n returns interrupt level of given interrupt source.
//
//*****************************************************************************
extern uint8_t ICC_getInterruptLevel(uint32_t interruptSource);

//*****************************************************************************
//
//! \brief Returns true if virtual stack is empty, false if not
//!
//! This function returns true(1) if virtual stack is empty, false(0) if not.
//!
//!
//! \return 1 if virtual stack is empty, 0 if not
//
//*****************************************************************************
extern bool ICC_isVirtualStackEmpty(void);

//*****************************************************************************
//
//! \brief Returns true if virtual stack is full, false if not
//!
//! This function returns true(1) if virtual stack is full, false(0) if not.
//!
//!
//! \return 1 if virtual stack is full, 0 if not
//
//*****************************************************************************
extern bool ICC_isVirtualStackFull(void);

//*****************************************************************************
//
//! \brief Gets the current interrupt compare mask
//!
//! Returns a 2-bit value that specifies the minimum interrupt priority level
//! that will be sent for service. If ICM[1:0] is less than the priority level
//! (ILSRx[1:0]) of the new interrupt, the corresponding source is sent to the
//! CPU. Note that the ICMC is the element stack that the stack pointer is
//! pointing to.
//!
//!
//! \return Minimum ICC interrupt priority level that will be serviced.
//!         Return one of the following:
//!         - \b ICC_LEVEL_0
//!         - \b ICC_LEVEL_1
//!         - \b ICC_LEVEL_2
//!         - \b ICC_LEVEL_3
//!         - \b ICC_LEVEL_ERROR
//!         \n returns minimum interrupt level.
//
//*****************************************************************************
extern uint8_t ICC_getCurrentICM(void);

//*****************************************************************************
//
//! \brief Gets the ICC Mask Virtual Stack stack pointer
//!
//! Returns the stack pointer of the ICC Mask Virtual Stack.
//!
//!
//! \return 0 if stack is empty, 1 if ICM0 occupied, 2 if ICM0/ICM1, 3 if
//!         ICM0/ICM1/ICM2, 4 if full.
//!         Return one of the following:
//!         - \b ICC_MVS_STACK_EMPTY
//!         - \b ICC_MVS_STACK_ICM0
//!         - \b ICC_MVS_STACK_ICM0_ICM1
//!         - \b ICC_MVS_STACK_ICM0_ICM1_ICM2
//!         - \b ICC_MVS_STACK_FULL
//!         \n Determines how full MVS stack is
//
//*****************************************************************************
extern uint8_t ICC_getMVSStackPointer(void);

//*****************************************************************************
//
//! \brief Gets the interrupt level at Interrupt compare mask virtual stack
//! position 3
//!
//! Returns interrupt level of ICM virtual stack position 3 as a ready-to-read
//! 8-bit integer value (automatically adjusted from original bit position.)
//!
//!
//! \return Interrupt level of ICM virtual stack position 3.
//!         Return one of the following:
//!         - \b ICC_LEVEL_0
//!         - \b ICC_LEVEL_1
//!         - \b ICC_LEVEL_2
//!         - \b ICC_LEVEL_3
//!         - \b ICC_LEVEL_ERROR
//!         \n returns interrupt level of ICM virtual stack position 3.
//
//*****************************************************************************
extern uint8_t ICC_getICM3(void);

//*****************************************************************************
//
//! \brief Gets the interrupt level at Interrupt compare mask virtual stack
//! position 2
//!
//! Returns interrupt level of ICM virtual stack position 2 as a ready-to-read
//! 8-bit integer value (automatically adjusted from original bit position.)
//!
//!
//! \return Interrupt level of ICM virtual stack position 2.
//!         Return one of the following:
//!         - \b ICC_LEVEL_0
//!         - \b ICC_LEVEL_1
//!         - \b ICC_LEVEL_2
//!         - \b ICC_LEVEL_3
//!         - \b ICC_LEVEL_ERROR
//!         \n returns interrupt level of ICM virtual stack position 2.
//
//*****************************************************************************
extern uint8_t ICC_getICM2(void);

//*****************************************************************************
//
//! \brief Gets the interrupt level at Interrupt compare mask virtual stack
//! position 1
//!
//! Returns interrupt level of ICM virtual stack position 1 as a ready-to-read
//! 8-bit integer value (automatically adjusted from original bit position.)
//!
//!
//! \return Interrupt level of ICM virtual stack position 1.
//!         Return one of the following:
//!         - \b ICC_LEVEL_0
//!         - \b ICC_LEVEL_1
//!         - \b ICC_LEVEL_2
//!         - \b ICC_LEVEL_3
//!         - \b ICC_LEVEL_ERROR
//!         \n returns interrupt level of ICM virtual stack position 1.
//
//*****************************************************************************
extern uint8_t ICC_getICM1(void);

//*****************************************************************************
//
//! \brief Gets the interrupt level at Interrupt compare mask virtual stack
//! position 0
//!
//! Returns interrupt level of ICM virtual stack position 0 as a ready-to-read
//! 8-bit integer value (automatically adjusted from original bit position.)
//!
//!
//! \return Interrupt level of ICM virtual stack position 0.
//!         Return one of the following:
//!         - \b ICC_LEVEL_0
//!         - \b ICC_LEVEL_1
//!         - \b ICC_LEVEL_2
//!         - \b ICC_LEVEL_3
//!         - \b ICC_LEVEL_ERROR
//!         \n returns interrupt level of ICM virtual stack position 0.
//
//*****************************************************************************
extern uint8_t ICC_getICM0(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_ICC_H__
