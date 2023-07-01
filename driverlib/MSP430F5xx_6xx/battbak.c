//*****************************************************************************
//
// battbak.c - Driver for the battbak Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup battbak_api battbak
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_BATTERY_CHARGER__
#include "battbak.h"

#include <assert.h>

uint16_t BattBak_unlockBackupSubSystem (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_BAKCTL) &= ~(LOCKBAK);
    return (HWREG8(baseAddress + OFS_BAKCTL) & LOCKBAK);
}

void BattBak_enableBackupSupplyToADC (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_BAKCTL) |= BAKADC;
}

void BattBak_disableBackupSupplyToADC (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_BAKCTL) &= ~(BAKADC);
}

void BattBak_switchToBackupSupplyManually (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_BAKCTL) |= BAKSW;
}

void BattBak_disable (uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_BAKCTL) |= BAKDIS;
}

void BattBak_initAndEnableCharger (uint16_t baseAddress,
    uint8_t chargerEndVoltage,
    uint8_t chargeCurrent)
{
    HWREG16(baseAddress +
        OFS_BAKCHCTL) = CHPWD + chargerEndVoltage + chargeCurrent + CHEN;
}

void BattBak_disableCharger (uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_BAKCHCTL) = CHPWD;
}

void BattBak_setBackupRAMData (uint16_t baseAddress,
    uint8_t backupRAMSelect,
    uint16_t data)
{
    HWREG16(baseAddress + backupRAMSelect) = data;
}

uint16_t BattBak_getBackupRAMData (uint16_t baseAddress,
    uint8_t backupRAMSelect)
{
    return ( HWREG16(baseAddress + backupRAMSelect) );
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for battbak_api
//! @}
//
//*****************************************************************************
