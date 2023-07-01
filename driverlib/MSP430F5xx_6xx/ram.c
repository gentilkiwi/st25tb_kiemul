//*****************************************************************************
//
// ram.c - Driver for the ram Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ram_api ram
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_RC__
#include "ram.h"

#include <assert.h>

void RAM_setSectorOff (uint8_t sector
    )
{
    //Write key to start write to RCCTL0 and sector
    HWREG16(RAM_BASE + OFS_RCCTL0) = (RCKEY + sector);
}

uint8_t RAM_getSectorState (uint8_t sector
    )
{
    return (HWREG8(RAM_BASE + OFS_RCCTL0_L) & sector);
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for ram_api
//! @}
//
//*****************************************************************************
