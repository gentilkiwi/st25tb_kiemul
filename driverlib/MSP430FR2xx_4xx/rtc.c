//*****************************************************************************
//
// rtc.c - Driver for the rtc Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup rtc_api rtc
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_RTC__
#include "rtc.h"

#include <assert.h>

void RTC_init(uint16_t baseAddress,
    uint16_t modulo,
    uint16_t clockPredivider)
{
    HWREG16(baseAddress + OFS_RTCCTL) &= ~(RTCSS_3 | RTCPS_7);
    
    HWREG16(baseAddress + OFS_RTCMOD) = modulo;
    HWREG16(baseAddress + OFS_RTCCTL) |= clockPredivider;
}

void RTC_start(uint16_t baseAddress, uint16_t clockSource)
{
    HWREG16(baseAddress + OFS_RTCCTL) &= ~RTCSS_3;

#ifdef RTCCKSEL
    HWREG16(SYS_BASE + OFS_SYSCFG2) &= ~RTCCKSEL;
    if (clockSource == RTC_CLOCKSOURCE_ACLK) {
        HWREG16(SYS_BASE + OFS_SYSCFG2) |= RTCCKSEL;
        HWREG16(baseAddress + OFS_RTCCTL) |= RTCSS_1;
    }
    else {
        HWREG16(baseAddress + OFS_RTCCTL) |= clockSource;
    }
#else
    HWREG16(baseAddress + OFS_RTCCTL) |= clockSource;
#endif

    HWREG16(baseAddress + OFS_RTCCTL) |= RTCSR;
}

void RTC_stop(uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_RTCCTL) &= ~RTCSS_3;
}

void RTC_setModulo(uint16_t baseAddress,
    uint16_t modulo)
{
    HWREG16(baseAddress + OFS_RTCMOD) = modulo;
}

void RTC_enableInterrupt(uint16_t baseAddress,
    uint8_t interruptMask)
{
    if (interruptMask & RTCIE) {
        HWREG16(baseAddress + OFS_RTCCTL) |= RTCIE;
    }
}

void RTC_disableInterrupt(uint16_t baseAddress,
    uint8_t interruptMask)
{
    if (interruptMask & RTCIE) {
        HWREG16(baseAddress + OFS_RTCCTL) &= ~RTCIE;
    }
}

uint8_t RTC_getInterruptStatus(uint16_t baseAddress,
    uint8_t interruptFlagMask) 
{
    uint8_t intStatus = 0;
    
    if (interruptFlagMask & RTCIF) {
        intStatus = (uint8_t)(HWREG16(baseAddress + OFS_RTCCTL) & RTCIF);
    }
    
    return intStatus;
}

void RTC_clearInterrupt(uint16_t baseAddress,
    int8_t interruptFlagMask)
{
    HWREG16(baseAddress + OFS_RTCCTL) &= ~RTCIF;
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for rtc_api
//! @}
//
//*****************************************************************************
