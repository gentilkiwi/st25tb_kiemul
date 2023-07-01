//*****************************************************************************
//
// ldopwr.c - Driver for the ldopwr Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ldopwr_api ldopwr
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_PU__
#include "ldopwr.h"

#include <assert.h>

void LDOPWR_unLockConfiguration ( uint16_t baseAddress )
{
    HWREG16(baseAddress + OFS_LDOKEYPID) = 0x9628;
}

void LDOPWR_lockConfiguration ( uint16_t baseAddress )
{
    HWREG16(baseAddress + OFS_LDOKEYPID) = 0x0000;
}

void LDOPWR_enablePort_U_inputs (uint16_t baseAddress )
{
    HWREG8(baseAddress + OFS_PUCTL_H) |= PUIPE_H;
}

void LDOPWR_disablePort_U_inputs (uint16_t baseAddress )
{
    HWREG8(baseAddress + OFS_PUCTL_H) &= ~PUIPE_H;
}

void LDOPWR_enablePort_U_outputs (uint16_t baseAddress )
{
    HWREG8(baseAddress + OFS_PUCTL_L) |= PUOPE;
}

void LDOPWR_disablePort_U_outputs (uint16_t baseAddress )
{
    HWREG8(baseAddress + OFS_PUCTL_L) &= ~PUOPE;
}

uint8_t LDOPWR_getPort_U1_inputData (uint16_t baseAddress )
{
    return ((HWREG8(baseAddress + OFS_PUCTL_L) & PUIN1) >> 3 );
}

uint8_t LDOPWR_getPort_U0_inputData (uint16_t baseAddress )
{
    return ((HWREG8(baseAddress + OFS_PUCTL_L) & PUIN0) >> 2 );
}

uint8_t LDOPWR_getPort_U1_outputData (uint16_t baseAddress )
{
    return ((HWREG8(baseAddress + OFS_PUCTL_L) & PUOUT1) >> 1 );
}

uint8_t LDOPWR_getPort_U0_outputData (uint16_t baseAddress )
{
    return (HWREG8(baseAddress + OFS_PUCTL_L) & PUOUT0);
}

void LDOPWR_setPort_U1_outputData (uint16_t baseAddress,
    uint8_t value
    )
{
    if (LDOPWR_PORTU_PIN_HIGH == value){
        HWREG8(baseAddress + OFS_PUCTL_L) |= PUOUT1;
    } else   {
        HWREG8(baseAddress + OFS_PUCTL_L) &= ~PUOUT1;
    }
}

void LDOPWR_setPort_U0_outputData (uint16_t baseAddress,
    uint8_t value
    )
{
    if (LDOPWR_PORTU_PIN_HIGH == value){
        HWREG8(baseAddress + OFS_PUCTL_L) |= PUOUT0;
    } else   {
        HWREG8(baseAddress + OFS_PUCTL_L) &= ~PUOUT0;
    }
}

void LDOPWR_togglePort_U1_outputData (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_PUCTL_L) ^= PUOUT1;
}

void LDOPWR_togglePort_U0_outputData (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_PUCTL_L) ^= PUOUT0;
}

void LDOPWR_enableInterrupt (uint16_t baseAddress,
    uint16_t mask
    )
{
    HWREG8(baseAddress + OFS_LDOPWRCTL_H) |= mask;
}

void LDOPWR_disableInterrupt (uint16_t baseAddress,
    uint16_t mask
    )
{
    HWREG8(baseAddress + OFS_LDOPWRCTL_H) &= ~mask;
}

void LDOPWR_enable (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_LDOPWRCTL_H) |= LDOOEN_H;
}

void LDOPWR_disable (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_LDOPWRCTL_H) &= ~LDOOEN_H;
}

uint8_t LDOPWR_getInterruptStatus (uint16_t baseAddress,
    uint16_t mask
    )
{
    return (HWREG8(baseAddress + OFS_LDOPWRCTL_L) & mask);
}

void LDOPWR_clearInterrupt (uint16_t baseAddress,
    uint16_t mask
    )
{
    HWREG8(baseAddress + OFS_LDOPWRCTL_L) &=  ~mask;
}

uint8_t LDOPWR_isLDOInputValid (uint16_t baseAddress)
{
    return (HWREG8(baseAddress + OFS_LDOPWRCTL_L) & LDOBGVBV);
}

void LDOPWR_enableOverloadAutoOff (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_LDOPWRCTL_L) |= OVLAOFF_L;
}

void LDOPWR_disableOverloadAutoOff (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_LDOPWRCTL_L) &= ~OVLAOFF_L;
}

uint8_t LDOPWR_getOverloadAutoOffStatus (uint16_t baseAddress)
{
    return (HWREG8(baseAddress + OFS_LDOPWRCTL_L) & OVLAOFF_L);
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for ldopwr_api
//! @}
//
//*****************************************************************************
