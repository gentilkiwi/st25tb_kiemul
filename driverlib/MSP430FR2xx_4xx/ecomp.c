//*****************************************************************************
//
// ecomp.c - Driver for the ecomp Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ecomp_api ecomp
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_ECOMPx__
#include "ecomp.h"

#include <assert.h>

void EComp_init(uint16_t baseAddress, EComp_initParam *param)
{
	HWREG16(baseAddress + OFS_CPCTL0) &= ~(CPNEN | CPNSEL_7 | CPPEN | CPPSEL_7);
	HWREG16(baseAddress + OFS_CPCTL1) &= ~(CPFLT | CPFLTDLY_3 | CPINV);

	if (param->positiveTerminalInput != ECOMP_INPUT_DISABLED) {
		HWREG16(baseAddress + OFS_CPCTL0) |= CPPEN | param->positiveTerminalInput;
	}

	if (param->negativeTerminalInput != ECOMP_INPUT_DISABLED) {
		HWREG16(baseAddress + OFS_CPCTL0) |= CPNEN | (param->negativeTerminalInput<<8);
	}

	HWREG16(baseAddress + OFS_CPCTL1) |= param->outputFilterEnableAndDelayLevel |
			param->invertedOutputPolarity;
}

void EComp_selectHysteresisMode(uint16_t baseAddress,
		uint16_t hysteresisMode)
{
	HWREG16(baseAddress + OFS_CPCTL1) &= ~CPHSEL_3;
	HWREG16(baseAddress + OFS_CPCTL1) |= hysteresisMode;
}

void EComp_selectPowerMode(uint16_t baseAddress, uint16_t powerMode)
{
	HWREG16(baseAddress + OFS_CPCTL1) &= ~CPMSEL;
	HWREG16(baseAddress + OFS_CPCTL1) |= powerMode;
}

void EComp_enable(uint16_t baseAddress)
{
	HWREG16(baseAddress + OFS_CPCTL1) |= CPEN;
}

void EComp_disable(uint16_t baseAddress)
{
	HWREG16(baseAddress + OFS_CPCTL1) &= ~CPEN;
}

void EComp_enableInterrupt(uint16_t baseAddress, uint16_t interruptMask)
{
	HWREG16(baseAddress + OFS_CPCTL1) |= interruptMask;
}

void EComp_disableInterrupt(uint16_t baseAddress, uint16_t interruptMask)
{
	HWREG16(baseAddress + OFS_CPCTL1) &= ~(interruptMask);
}

void EComp_clearInterrupt(uint16_t baseAddress, uint16_t interruptFlagMask)
{
	HWREG16(baseAddress + OFS_CPINT) |= interruptFlagMask;
}

uint8_t EComp_getInterruptStatus(uint16_t baseAddress,
		uint16_t interruptFlagMask)
{
    return (HWREG8(baseAddress + OFS_CPINT) & interruptFlagMask);
}

void EComp_setInterruptEdgeDirection(uint16_t baseAddress,
		uint16_t edgeDirection)
{
	HWREG16(baseAddress + OFS_CPCTL1) &= ~CPIES;
	HWREG16(baseAddress + OFS_CPCTL1) |= edgeDirection;
}

void EComp_toggleInterruptEdgeDirection(uint16_t baseAddress)
{
	HWREG16(baseAddress + OFS_CPCTL1) ^= CPIES;
}

uint8_t EComp_outputValue(uint16_t baseAddress)
{
	return (HWREG8(baseAddress + OFS_CPCTL1) & CPOUT);
}

void EComp_configureDAC(uint16_t baseAddress, EComp_configureDACParam *param)
{
	HWREG16(baseAddress + OFS_CPDACCTL) &= ~(CPDACREFS | CPDACBUFS | CPDACSW);
	HWREG16(baseAddress + OFS_CPDACDATA) &= 0xC0C0;

	HWREG16(baseAddress + OFS_CPDACCTL) |= param->referenceVoltage |
			param->bufferSource;

	HWREG16(baseAddress + OFS_CPDACDATA) |= param->firstBufferData;
	HWREG16(baseAddress + OFS_CPDACDATA) |= param->secondBufferData<<8;
}

void EComp_enableDAC(uint16_t baseAddress)
{
	HWREG16(baseAddress + OFS_CPDACCTL) |= CPDACEN;
}

void EComp_disableDAC(uint16_t baseAddress)
{
	HWREG16(baseAddress + OFS_CPDACCTL) &= ~CPDACEN;
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for ecomp_api
//! @}
//
//*****************************************************************************
