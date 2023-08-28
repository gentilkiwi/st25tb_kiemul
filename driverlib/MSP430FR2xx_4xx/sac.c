//*****************************************************************************
//
// sac.c - Driver for the sac Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup sac_api sac
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_SACx__
#include "sac.h"

#include <assert.h>

#if defined(__MSP430_HAS_SACx_CONFIG_1__) ||    \
    defined(__MSP430_HAS_SACx_CONFIG_2__) ||    \
    defined(__MSP430_HAS_SACx_CONFIG_3__)

void SAC_OA_init(uint16_t baseAddress, uint16_t positiveInput, uint16_t negativeInput)
{
    HWREG16(baseAddress + OFS_SAC0OA) &= ~(PSEL1 | PSEL0 | NSEL1 | NSEL0);

    if (positiveInput == SAC_OA_POSITIVE_INPUT_SOURCE_DISCONNECTED) {
        HWREG16(baseAddress + OFS_SAC0OA) &= ~PMUXEN;
    }
    else {
        HWREG16(baseAddress + OFS_SAC0OA) |= PMUXEN | positiveInput;
    }

    if (negativeInput == SAC_OA_NEGATIVE_INPUT_SOURCE_DISCONNECTED) {
        HWREG16(baseAddress + OFS_SAC0OA) &= ~NMUXEN;
    }
    else {
        HWREG16(baseAddress + OFS_SAC0OA) |= NMUXEN | negativeInput;
    }
}

void SAC_OA_selectPowerMode(uint16_t baseAddress, uint16_t powerMode)
{
    HWREG16(baseAddress + OFS_SAC0OA) &= ~OAPM;
    HWREG16(baseAddress + OFS_SAC0OA) |= powerMode;
}

void SAC_OA_enable(uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_SAC0OA) |= OAEN;
}

void SAC_OA_disable(uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_SAC0OA) &= ~OAEN;
}

void SAC_enable(uint16_t baseAddress)
{
   HWREG16(baseAddress + OFS_SAC0OA) |= SACEN;
}

void SAC_disable(uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_SAC0OA) &= ~SACEN; 
}

#endif //if defined SAC-L1, SAC-L2, or SAC-L3
#if defined(__MSP430_HAS_SACx_CONFIG_2__) ||    \
    defined(__MSP430_HAS_SACx_CONFIG_3__)

void SAC_PGA_setMode(uint16_t baseAddress, uint16_t mode)
{
    HWREG16(baseAddress + OFS_SAC0PGA) &= ~MSEL;
    HWREG16(baseAddress + OFS_SAC0PGA) |= mode;
}

void SAC_PGA_setGain(uint16_t baseAddress, uint16_t gain)
{
    HWREG16(baseAddress + OFS_SAC0PGA) &= ~GAIN;
    HWREG16(baseAddress + OFS_SAC0PGA) |= gain;
}

#endif //if defined SAC-L2 or SAC-L3
#if defined(__MSP430_HAS_SACx_CONFIG_3__)

void SAC_DAC_enable(uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_SAC0DAC) |= DACEN;
}

void SAC_DAC_disable(uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_SAC0DAC) &= ~DACEN;
}

void SAC_DAC_interruptEnable(uint16_t baseAddress)
{
    assert(!(HWREG16(baseAddress + OFS_SAC0DAC) & DACEN));
    HWREG16(baseAddress + OFS_SAC0DAC) |= DACIE;
}

void SAC_DAC_interruptDisable(uint16_t baseAddress)
{
    assert(!(HWREG16(baseAddress + OFS_SAC0DAC) & DACEN));
    HWREG16(baseAddress + OFS_SAC0DAC) &= ~DACIE;
}

void SAC_DAC_DMARequestEnable(uint16_t baseAddress)
{
    assert(!(HWREG16(baseAddress + OFS_SAC0DAC) & DACEN));
    HWREG16(baseAddress + OFS_SAC0DAC) |= DACDMAE;
}

void SAC_DAC_DMARequestDisable(uint16_t baseAddress)
{
    assert(!(HWREG16(baseAddress + OFS_SAC0DAC) & DACEN));
    HWREG16(baseAddress + OFS_SAC0DAC) &= ~DACDMAE;
}

void SAC_DAC_selectLoad(uint16_t baseAddress, uint16_t load)
{
    assert(!(HWREG16(baseAddress + OFS_SAC0DAC) & DACEN));
    HWREG16(baseAddress + OFS_SAC0DAC) &= ~DACLSEL;
    HWREG16(baseAddress + OFS_SAC0DAC) |= load;
}

void SAC_DAC_selectRefVoltage(uint16_t baseAddress, uint16_t reference)
{
    assert(!(HWREG16(baseAddress + OFS_SAC0DAC) & DACEN));
    HWREG16(baseAddress + OFS_SAC0DAC) &= ~DACSREF;
    HWREG16(baseAddress + OFS_SAC0DAC) |= reference;
}

uint16_t SAC_DAC_getData(uint16_t baseAddress)
{
    return HWREG16(baseAddress + OFS_SAC0DAT);
}

void SAC_DAC_setData(uint16_t baseAddress, uint16_t data)
{
    HWREG16(baseAddress + OFS_SAC0DAT) = data;
}

bool SAC_DAC_getIFG(uint16_t baseAddress)
{
    return (HWREG16(baseAddress + OFS_SAC0DACSTS) & DACIFG);
}

void SAC_DAC_clearIFG(uint16_t baseAddress)
{
    assert(!(HWREG16(baseAddress + OFS_SAC0DACSTS) & DACEN));
    HWREG16(baseAddress + OFS_SAC0DACSTS) |= DACIFG;
}

uint16_t SAC_getInterruptVector(uint16_t baseAddress)
{
    return HWREG16(baseAddress + OFS_SAC0IV);
}

#endif //if defined SAC-L3

#endif
//*****************************************************************************
//
//! Close the doxygen group for sac_api
//! @}
//
//*****************************************************************************
