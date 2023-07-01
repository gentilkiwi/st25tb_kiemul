//*****************************************************************************
//
// ref.c - Driver for the ref Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ref_api ref
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_REF__
#include "ref.h"

#include <assert.h>

void Ref_setReferenceVoltage (uint16_t baseAddress,
    uint8_t referenceVoltageSelect)
{
    HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFVSEL_3);
    HWREG8(baseAddress + OFS_REFCTL0_L) |= referenceVoltageSelect;
}

void Ref_disableTempSensor (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_REFCTL0_L) |= REFTCOFF;
}

void Ref_enableTempSensor (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFTCOFF);
}

void Ref_enableReferenceVoltageOutput (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_REFCTL0_L) |= REFOUT;
}

void Ref_disableReferenceVoltageOutput (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFOUT);
}

void Ref_enableReferenceVoltage (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_REFCTL0_L) |= REFON;
}

void Ref_disableReferenceVoltage (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFON);
}

uint16_t Ref_getBandgapMode (uint16_t baseAddress)
{
    return (HWREG16((baseAddress) + OFS_REFCTL0) & BGMODE);
}

bool Ref_isBandgapActive (uint16_t baseAddress)
{
    if (HWREG16((baseAddress) + OFS_REFCTL0) & REFBGACT){
        return (REF_ACTIVE) ;
    } else   {
        return (REF_INACTIVE) ;
    }
}

uint16_t Ref_isRefGenBusy (uint16_t baseAddress)
{
    return (HWREG16((baseAddress) + OFS_REFCTL0) & REFGENBUSY);
}

bool Ref_isRefGenActive (uint16_t baseAddress)
{
    if (HWREG16((baseAddress) + OFS_REFCTL0) & REFGENACT){
        return (REF_ACTIVE) ;
    } else   {
        return (REF_INACTIVE) ;
    }
}


#endif
//*****************************************************************************
//
//! Close the doxygen group for ref_api
//! @}
//
//*****************************************************************************
