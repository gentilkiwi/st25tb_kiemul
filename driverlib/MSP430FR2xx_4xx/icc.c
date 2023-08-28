//*****************************************************************************
//
// icc.c - Driver for the icc Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup icc_api icc
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_ICC__
#include "icc.h"

#include <assert.h>

void ICC_enable(void)
{
	HWREG16(ICC_BASE + OFS_ICCSC) |= ICCEN;
}

void ICC_disable(void)
{
	HWREG16(ICC_BASE + OFS_ICCSC) &= ~ICCEN;
}

void ICC_setInterruptLevel( uint32_t ILSRmask, uint8_t interruptLevel){
	uint32_t mask = 0x1;
	uint8_t i;

	for(i = 0; i < 8; i++)
	{
		if(ILSRmask & mask)
		{
			HWREG16(ICC_BASE + OFS_ICCILSR0) &= ~(0x3 << (i << 1));
			HWREG16(ICC_BASE + OFS_ICCILSR0) |= (interruptLevel << (i << 1));
		}
		mask <<= 1;
	}
	for(i = 0; i < 8; i++)
	{
		if(ILSRmask & mask)
		{
			HWREG16(ICC_BASE + OFS_ICCILSR1) &= ~(0x3 << (i << 1));
			HWREG16(ICC_BASE + OFS_ICCILSR1) |= (interruptLevel << (i << 1));
		}
		mask <<= 1;
	}
	for(i = 0; i < 8; i++)
	{
		if(ILSRmask & mask)
		{
			HWREG16(ICC_BASE + OFS_ICCILSR2) &= ~(0x3 << (i << 1));
			HWREG16(ICC_BASE + OFS_ICCILSR2) |= (interruptLevel << (i << 1));
		}
		mask <<= 1;
	}
	for(i = 0; i < 8; i++)
	{
		if(ILSRmask & mask)
		{
			HWREG16(ICC_BASE + OFS_ICCILSR3) &= ~(0x3 << (i << 1));
			HWREG16(ICC_BASE + OFS_ICCILSR3) |= (interruptLevel << (i << 1));
		}
		mask <<= 1;
	}
}

uint8_t ICC_getInterruptLevel( uint32_t interruptSource){
    uint32_t mask = 0x1;
	uint8_t i;

	for(i = 0; i < 8; i++)
	{
		if(interruptSource & mask)
		{
			return (HWREG16(ICC_BASE + OFS_ICCILSR0) & (0x3 << (i << 1))) >> (i << 1);
		}
		mask <<= 1;
	}
	for(i = 0; i < 8; i++)
	{
		if(interruptSource & mask)
		{
			return (HWREG16(ICC_BASE + OFS_ICCILSR1) & (0x3 << (i << 1))) >> (i << 1);
		}
		mask <<= 1;
	}
	for(i = 0; i < 8; i++)
	{
		if(interruptSource & mask)
		{
			return (HWREG16(ICC_BASE + OFS_ICCILSR2) & (0x3 << (i << 1))) >> (i << 1);
		}
		mask <<= 1;
	}
	for(i = 0; i < 8; i++)
	{
		if(interruptSource & mask)
		{
			return (HWREG16(ICC_BASE + OFS_ICCILSR3) & (0x3 << (i << 1))) >> (i << 1);
		}
		mask <<= 1;
	}
	
	//Error code
	return 4;
}

bool ICC_isVirtualStackEmpty(void)
{
	return (HWREG16(ICC_BASE + OFS_ICCSC) & VSEFLG) ? true : false;
}

bool ICC_isVirtualStackFull(void)
{
	return (HWREG16(ICC_BASE + OFS_ICCSC) & VSFFLG) ? true : false;
}

uint8_t ICC_getCurrentICM(void)
{
	return (HWREG16(ICC_BASE + OFS_ICCSC) & ICMC);
}

uint8_t ICC_getMVSStackPointer(void)
{
	return ((HWREG16(ICC_BASE + OFS_ICCMVS) & MVSSP) >> 8);
}

uint8_t ICC_getICM3(void)
{
	return ((HWREG16(ICC_BASE + OFS_ICCMVS) & ICM3) >> 6);
}

uint8_t ICC_getICM2(void)
{
	return ((HWREG16(ICC_BASE + OFS_ICCMVS) & ICM2) >> 4);
}

uint8_t ICC_getICM1(void)
{
	return ((HWREG16(ICC_BASE + OFS_ICCMVS) & ICM1) >> 2);
}

uint8_t ICC_getICM0(void)
{
	return (HWREG16(ICC_BASE + OFS_ICCMVS) & ICM0);
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for icc_api
//! @}
//
//*****************************************************************************
