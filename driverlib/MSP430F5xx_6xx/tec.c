//*****************************************************************************
//
// tec.c - Driver for the tec Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup tec_api tec
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_TEV0__
#include "tec.h"

#include <assert.h>

void TEC_initExternalClearInput (uint16_t baseAddress,
                                        uint8_t signalType,
                                        uint8_t signalHold,
                                        uint8_t polarityBit
                                      )
{
    HWREG8(baseAddress + OFS_TEC0XCTL2_L)  &= ~(TEC_EXTERNAL_CLEAR_SIGNALTYPE_LEVEL_SENSITIVE +
                                                TEC_EXTERNAL_CLEAR_SIGNAL_HELD +
                                                TEC_EXTERNAL_CLEAR_POLARITY_RISING_EDGE_OR_HIGH_LEVEL
                                                );

    HWREG8(baseAddress + OFS_TEC0XCTL2_L)  |= (signalType +
                                                signalHold +
                                                polarityBit
                                                );
}

void TEC_initExternalFaultInput(uint16_t baseAddress,
    TEC_initExternalFaultInputParam *param)
{
    HWREG8(baseAddress + OFS_TEC0XCTL2_L)  &= ~((TEC_EXTERNAL_FAULT_SIGNALTYPE_LEVEL_SENSITIVE << param->selectedExternalFault)+
                                                (TEC_EXTERNAL_FAULT_POLARITY_RISING_EDGE_OR_HIGH_LEVEL << param->selectedExternalFault)+
                                                (TEC_EXTERNAL_FAULT_SIGNAL_HELD << param->selectedExternalFault )
                                                );

    HWREG8(baseAddress + OFS_TEC0XCTL2_L)  |= ((param->signalType << param->selectedExternalFault)+
                                               (param->polarityBit << param->selectedExternalFault) +
                                               (param->signalHold << param->selectedExternalFault )
                                               );
}

void TEC_enableExternalFaultInput (uint16_t baseAddress,
                                        uint8_t channelEventBlock
                                        )
{
    HWREG8(baseAddress + OFS_TEC0XCTL0_H)  |= (1 << channelEventBlock );
}

void TEC_disableExternalFaultInput (uint16_t baseAddress,
                                        uint8_t channelEventBlock
                                        )
{
    HWREG8(baseAddress + OFS_TEC0XCTL0_H)  &= ~(1 << channelEventBlock );
}

void TEC_enableExternalClearInput (uint16_t baseAddress )
{
   HWREG8(baseAddress + OFS_TEC0XCTL2_L)  |= TECEXCLREN;
}

void TEC_disableExternalClearInput (uint16_t baseAddress )
{
   HWREG8(baseAddress + OFS_TEC0XCTL2_L)  &= ~TECEXCLREN;
}

void TEC_enableAuxiliaryClearSignal (uint16_t baseAddress )
{
   HWREG8(baseAddress + OFS_TEC0XCTL2_L)  |= TECAXCLREN;
}

void TEC_disableAuxiliaryClearSignal (uint16_t baseAddress )
{
   HWREG8(baseAddress + OFS_TEC0XCTL2_L)  &= ~TECAXCLREN;
}

void TEC_clearInterrupt (uint16_t baseAddress,
    uint8_t mask
    )
{
    HWREG8(baseAddress + OFS_TEC0XINT_L)  &= ~mask;
}

uint8_t TEC_getInterruptStatus (uint16_t baseAddress,
    uint8_t mask
    )
{
    //Return the interrupt status of the request masked bit.
    return (HWREG8(baseAddress + OFS_TEC0XINT_L) & mask);
}

void TEC_enableInterrupt (uint16_t baseAddress,
    uint8_t mask
    )
{
    //Enable the interrupt masked bit
    HWREG8(baseAddress + OFS_TEC0XINT_H) |= mask;
}

void TEC_disableInterrupt (uint16_t baseAddress,
    uint8_t mask
    )
{
    //Disable the interrupt masked bit
    HWREG8(baseAddress + OFS_TEC0XINT_H) &= ~(mask);
}

uint8_t TEC_getExternalFaultStatus (uint16_t baseAddress,
    uint8_t mask
    )
{
    //Return the interrupt status of the request masked bit.
    return (HWREG8(baseAddress + OFS_TEC0STA_L) & mask);
}

void TEC_clearExternalFaultStatus (uint16_t baseAddress,
    uint8_t mask
    )
{
    HWREG8(baseAddress + OFS_TEC0STA_L)  &= ~mask;
}

uint8_t TEC_getExternalClearStatus (uint16_t baseAddress)

{
    //Return the interrupt status of the request masked bit.
    return (HWREG8(baseAddress + OFS_TEC0STA_L) & TECXCLRSTA);
}

void TEC_clearExternalClearStatus (uint16_t baseAddress)
{
   HWREG8(baseAddress + OFS_TEC0STA_L)  &= ~TECXCLRSTA;
}


#endif
//*****************************************************************************
//
//! Close the doxygen group for tec_api
//! @}
//
//*****************************************************************************
