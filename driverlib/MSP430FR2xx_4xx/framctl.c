//*****************************************************************************
//
// framctl.c - Driver for the framctl Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup framctl_api framctl
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_FRAM__
#include "framctl.h"

#include <assert.h>

void FRAMCtl_write8(uint8_t *dataPtr,
    uint8_t *framPtr,
    uint16_t numberOfBytes
    )
{
    //Get previous write protection setting
    uint8_t state = HWREG8(SYS_BASE + OFS_SYSCFG0_L);
#ifdef DFWP
    uint8_t wp = DFWP | PFWP;
#else
    uint8_t wp = PFWP;
#endif

#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | (state & ~wp);
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) &= ~wp;
#endif

    while (numberOfBytes > 0)
    {
        //Write to Fram
        *framPtr++ = *dataPtr++;
        numberOfBytes--;
    }

    //Restore previous write protection setting
#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | state;
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) = state;
#endif
}

void FRAMCtl_write16(uint16_t *dataPtr,uint16_t *framPtr,
		uint16_t numberOfWords)
{
    //Get previous write protection setting
    uint8_t state = HWREG8(SYS_BASE + OFS_SYSCFG0_L);
#ifdef DFWP
    uint8_t wp = DFWP | PFWP;
#else
    uint8_t wp = PFWP;
#endif

#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | (state & ~wp);
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) &= ~wp;
#endif

    while (numberOfWords > 0)
    {
        //Write to Fram
        *framPtr++ = *dataPtr++;
        numberOfWords--;
    }

    //Restore previous write protection setting
#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | state;
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) = state;
#endif
}

void FRAMCtl_write32(uint32_t *dataPtr,uint32_t *framPtr,
		uint16_t count)
{
    //Get previous write protection setting
    uint8_t state = HWREG8(SYS_BASE + OFS_SYSCFG0_L);
#ifdef DFWP
    uint8_t wp = DFWP | PFWP;
#else
    uint8_t wp = PFWP;
#endif

#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | (state & ~wp);
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) &= ~wp;
#endif

    while (count > 0)
    {
        //Write to Fram
        *framPtr++ = *dataPtr++;
        count--;
    }

    //Restore previous write protection setting
#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | state;
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) = state;
#endif
}

void FRAMCtl_fillMemory32 (uint32_t value,
    uint32_t *framPtr,
    uint16_t count
    )
{
    //Get previous write protection setting
    uint8_t state = HWREG8(SYS_BASE + OFS_SYSCFG0_L);
#ifdef DFWP
    uint8_t wp = DFWP | PFWP;
#else
    uint8_t wp = PFWP;
#endif

#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | (state & ~wp);
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) &= ~wp;
#endif

    while (count> 0)
    {
        //Write to Fram
        *framPtr++ = value;
        count--;
    }
    
    //Restore previous write protection setting
#ifdef FRWPPW
    HWREG16(SYS_BASE + OFS_SYSCFG0) = FWPW | state;
#else
    HWREG8(SYS_BASE + OFS_SYSCFG0_L) = state;
#endif
}

void FRAMCtl_enableInterrupt (uint16_t interruptMask)
{
    uint8_t waitSelection;

    waitSelection=(HWREG8(FRAM_BASE + OFS_FRCTL0) & 0xFF);
    // Clear lock in FRAM control registers
    HWREG16(FRAM_BASE + OFS_FRCTL0) = FWPW | waitSelection;

    // Enable user selected interrupt sources
    HWREG16(FRAM_BASE + OFS_GCCTL0) |= interruptMask;
}

uint8_t FRAMCtl_getInterruptStatus(uint16_t interruptFlagMask)
{
	return ( HWREG16(FRAM_BASE + OFS_GCCTL1) & interruptFlagMask );
}

void FRAMCtl_disableInterrupt(uint16_t interruptMask)
{
	uint8_t waitSelection;

	waitSelection=(HWREG8(FRAM_BASE + OFS_FRCTL0) & 0xFF);
	//Clear lock in FRAM control registers
	HWREG16(FRAM_BASE + OFS_FRCTL0) = FWPW | waitSelection;

    HWREG16(FRAM_BASE + OFS_GCCTL0) &= ~(interruptMask);
}

void FRAMCtl_configureWaitStateControl(uint8_t waitState )
{    
	uint8_t tempVariable = HWREG8(FRAM_BASE + OFS_FRCTL0_L);
	tempVariable &= ~NWAITS_7;
	tempVariable |= waitState;
	HWREG16(FRAM_BASE + OFS_FRCTL0) = ( FWPW | tempVariable );
}

void FRAMCtl_delayPowerUpFromLPM(uint8_t delayStatus)
{
#ifdef FRLPMPWR
    uint8_t waitSelection;

    waitSelection = (HWREG8(FRAM_BASE + OFS_FRCTL0) & 0xFF);

    // Clear lock in FRAM control registers
    HWREG16(FRAM_BASE + OFS_FRCTL0) = FWPW | waitSelection;

	HWREG8(FRAM_BASE + OFS_GCCTL0_L) &= ~FRLPMPWR;
	HWREG8(FRAM_BASE + OFS_GCCTL0_L) |= delayStatus;
#endif
}


#endif
//*****************************************************************************
//
//! Close the doxygen group for framctl_api
//! @}
//
//*****************************************************************************
