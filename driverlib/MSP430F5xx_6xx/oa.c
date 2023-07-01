//*****************************************************************************
//
// oa.c - Driver for the oa Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup oa_api oa
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_OA_0__
#include "oa.h"

#include <assert.h>

void OA_openSwitch( uint16_t baseAddress,
                    uint8_t positiveInputMask,
                    uint8_t negativeInputMask,
                    uint8_t groundMask
                  )
{
    HWREG16(baseAddress + OFS_OA0PSW) &= ~positiveInputMask;
    HWREG16(baseAddress + OFS_OA0NSW) &= ~negativeInputMask;
    HWREG16(baseAddress + OFS_OA0GSW) &= ~groundMask;
}

void OA_closeSwitch(uint16_t baseAddress,
                    uint8_t positiveInputMask,
                    uint8_t negativeInputMask,
                    uint8_t groundMask
                  )
{

    HWREG16(baseAddress + OFS_OA0PSW) |= positiveInputMask;
    HWREG16(baseAddress + OFS_OA0NSW) |= negativeInputMask;
    HWREG16(baseAddress + OFS_OA0GSW) |= groundMask;
}

uint8_t OA_getSwitchStatus(uint16_t baseAddress,
                        uint8_t inputTerminal
                        )
{
    uint8_t returnValue = 0;

    switch(inputTerminal)
    {
        case OA_POSITIVE_INPUT_TERMINAL_SWITCHES:
            returnValue = (HWREG16(baseAddress + OFS_OA0PSW) & (PSW3 |
                                                            PSW2 |
                                                            PSW1 |
                                                            PSW0)
                                                            );
            break;
        case OA_NEGATIVE_INPUT_TERMINAL_SWITCHES:
            returnValue = (HWREG16(baseAddress + OFS_OA0NSW) & (NSW4 |
                                                            NSW3 |
                                                            NSW2 |
                                                            NSW1 |
                                                            NSW0)
                                                            );
            break;
        case OA_GROUND_SWITCHES:
            returnValue = (HWREG16(baseAddress + OFS_OA0GSW) & (GSW1 |
                                                            GSW0)
                                                            );
            break;
    }

    return returnValue;

}

uint8_t OA_getRailToRailInputReadyStatus(uint16_t baseAddress)
{
    return ((HWREG8(baseAddress + OFS_OA0CTL0) & OARRIRDY));
}

uint8_t OA_getRailToRailInputStatus(uint16_t baseAddress)
{
    return ((HWREG8(baseAddress + OFS_OA0CTL0) & OARRI));
}

void OA_enableRailToRailInput(uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_OA0CTL0) |= OARRI;
}

void OA_disableRailToRailInput(uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_OA0CTL0) &= ~OARRI;
}

void OA_disableAmplifierMode(uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_OA0CTL0) &= ~OAM;
}

void OA_enableAmplifierMode(uint16_t baseAddress)
{
    HWREG8(baseAddress + OFS_OA0CTL0) |= OAM;
}

uint8_t OA_getAmplifierModeStatus(uint16_t baseAddress)
{
    return ((HWREG8(baseAddress + OFS_OA0CTL0) & OAM));
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for oa_api
//! @}
//
//*****************************************************************************
