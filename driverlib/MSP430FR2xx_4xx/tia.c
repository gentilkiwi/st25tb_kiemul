//*****************************************************************************
//
// tia.c - Driver for the tia Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup tia_api tia
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_TRIx__
#include "tia.h"

#include <assert.h>

void TIA_selectPositiveInput(uint16_t baseAddress, uint16_t positiveInput)
{
	HWREG16(baseAddress + OFS_TRI0CTL) &= ~TRIPSEL_3;

	HWREG16(baseAddress + OFS_TRI0CTL) |= positiveInput;

}

void TIA_selectPowerMode(uint16_t baseAddress, uint16_t powerMode)
{
	HWREG16(baseAddress + OFS_TRI0CTL) &= ~TRIPM;
	HWREG16(baseAddress + OFS_TRI0CTL) |= powerMode;
}

void TIA_enable(uint16_t baseAddress)
{
	HWREG16(baseAddress + OFS_TRI0CTL) |= TRIEN;
}

void TIA_disable(uint16_t baseAddress)
{
	HWREG16(baseAddress + OFS_TRI0CTL) &= ~TRIEN;
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for tia_api
//! @}
//
//*****************************************************************************
