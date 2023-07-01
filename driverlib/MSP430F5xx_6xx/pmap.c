//*****************************************************************************
//
// pmap.c - Driver for the pmap Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup pmap_api pmap
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_PORT_MAPPING__
#include "pmap.h"

#include <assert.h>

void PMAP_initPorts ( uint16_t baseAddress,
    PMAP_initPortsParam *param)
{

    //Store current interrupt state, then disable all interrupts
    uint16_t globalInterruptState = __get_SR_register() & GIE;
    __disable_interrupt();

    //Get write-access to port mapping registers:
    HWREG16(baseAddress + OFS_PMAPKEYID) = PMAPPW;

    //Enable/Disable reconfiguration during runtime
    HWREG8(baseAddress + OFS_PMAPCTL) &= ~PMAPRECFG;
    HWREG8(baseAddress + OFS_PMAPCTL) |= param->portMapReconfigure;

    //Configure Port Mapping:
    uint16_t i;
    for (i = 0; i < param->numberOfPorts * 8; i++)
    {
        param->PxMAPy[i] = param->portMapping[i];
    }

    //Disable write-access to port mapping registers:
    HWREG8(baseAddress + OFS_PMAPKEYID) = 0;

    //Restore previous interrupt state
    __bis_SR_register(globalInterruptState);
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for pmap_api
//! @}
//
//*****************************************************************************
