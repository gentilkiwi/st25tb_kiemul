#ifndef __HW_MEMMAP__
#define __HW_MEMMAP__

#define __DRIVERLIB_MSP430F5XX_6XX_FAMILY__
//*****************************************************************************
//
// Include device specific header file
//
//*****************************************************************************
#include <msp430.h>

#include "msp430f5xx_6xxgeneric.h"

#include "stdint.h"
#include "stdbool.h"

//*****************************************************************************
//
// SUCCESS and FAILURE for API return value
//
//*****************************************************************************
#define STATUS_SUCCESS  0x01
#define STATUS_FAIL     0x00

//*****************************************************************************
//
// Macro for enabling assert statements for debugging
//
//*****************************************************************************
#define NDEBUG

//*****************************************************************************
//
// Macros for hardware access
//
//*****************************************************************************
#define HWREG32(x)                                                              \
        (*((volatile uint32_t *)((uint16_t)x)))
#define HWREG16(x)                                                             \
        (*((volatile uint16_t *)((uint16_t)x)))
#define HWREG8(x)                                                             \
        (*((volatile uint8_t *)((uint16_t)x)))


#endif // #ifndef __HW_MEMMAP__
