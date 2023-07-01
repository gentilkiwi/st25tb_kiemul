//*****************************************************************************
//
// ucs.c - Driver for the ucs Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ucs_api ucs
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#if defined(__MSP430_HAS_UCS__) || defined(__MSP430_HAS_UCS_RF__)
#include "ucs.h"

#include <assert.h>

#ifdef __GNUC__
#define __extension__(x)
__extension__(#define __delay_cycles(x) \
({ \
	volatile unsigned int j; \
	for (j=0;j<x;j++) \
	{ \
	  __no_operation(); \
	} \
})
);

#endif

#define CC430_DEVICE (defined (__CC430F5133__) || defined(__CC430F5135__) || defined(__CC430F5137__) || \
        defined(__CC430F6125__) || defined(__CC430F6126__) || defined(__CC430F6127__) || \
        defined(__CC430F6135__) || defined(__CC430F6137__) || defined(__CC430F5123__) || \
        defined(__CC430F5125__) || defined(__CC430F5143__) || defined(__CC430F5145__) || \
        defined(__CC430F5147__) || defined(__CC430F6143__) || defined(__CC430F6145__) || \
        defined(__CC430F6147__))

#define NOT_CC430_DEVICE (!defined (__CC430F5133__) && !defined(__CC430F5135__) && !defined(__CC430F5137__) && \
        !defined(__CC430F6125__) && !defined(__CC430F6126__) &&  !defined(__CC430F6127__) && \
         !defined(__CC430F6135__) &&  !defined(__CC430F6137__) &&  !defined(__CC430F5123__) && \
         !defined(__CC430F5125__) &&  !defined(__CC430F5143__) &&  !defined(__CC430F5145__) && \
         !defined(__CC430F5147__) &&  !defined(__CC430F6143__) &&  !defined(__CC430F6145__) && \
         !defined(__CC430F6147__))
//******************************************************************************
//
// The XT1 crystal frequency. Should be set with
// UCS_setExternalClockSource if XT1 is used and user intends to
// invoke UCS_getSMCLK, UCS_getMCLK or UCS_getACLK
//
//******************************************************************************
static uint32_t privateXT1ClockFrequency = 0;

//******************************************************************************
//
// The XT2 crystal frequency. Should be set with
// UCS_setExternalClockSource if XT1 is used and user intends to invoke
// UCS_getSMCLK, UCS_getMCLK or UCS_getACLK
//
//******************************************************************************
static uint32_t privateXT2ClockFrequency = 0;

static uint32_t privateUCSSourceClockFromDCO (uint16_t FLLRefCLKSource
    )
{
    assert((SELM__DCOCLKDIV == FLLRefCLKSource) ||
        (SELM__DCOCLK == FLLRefCLKSource)
        );
    uint16_t D_value = 1;
    uint16_t N_value;
    uint16_t n_value = 1;
    uint32_t Fref_value;
    uint8_t i;

    N_value = (HWREG16(UCS_BASE + OFS_UCSCTL2)) & 0x03FF;
    uint16_t tempDivider = HWREG8(UCS_BASE + OFS_UCSCTL3) & FLLREFDIV_7;

    if (tempDivider < 4) {
        n_value <<= tempDivider;
    }
    else if (tempDivider == 4) {
        n_value = 12;
    }
    else if (tempDivider == 5) {
        n_value = 16;
    }

    switch ( (HWREG8(UCS_BASE + OFS_UCSCTL3)) & SELREF_7){
        case SELREF__XT1CLK:
            Fref_value = privateXT1ClockFrequency;

            if(XTS != (HWREG16(UCS_BASE + OFS_UCSCTL6) & XTS)) {
              if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1LFOFFG){
                HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1LFOFFG);
                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;

                if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1LFOFFG){
                    Fref_value = UCS_REFOCLK_FREQUENCY;
                }
              }
            }
            else {
              if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1HFOFFG){
                HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1HFOFFG);
                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;

                if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1HFOFFG){
                    Fref_value = UCS_REFOCLK_FREQUENCY;
                }
              }
            }

            break;
        case SELREF__REFOCLK:
            Fref_value = UCS_REFOCLK_FREQUENCY;
            break;
        case SELREF__XT2CLK:
            Fref_value = privateXT2ClockFrequency;

            if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG){
                HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT2OFFG);

                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;

                if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG){
                    Fref_value = UCS_REFOCLK_FREQUENCY;
                }
            }

            break;
        default: assert(0);
    }

    uint32_t CLKFrequency = Fref_value * ( N_value + 1) / n_value;

    if (SELM__DCOCLK == FLLRefCLKSource){
        tempDivider = (HWREG16(UCS_BASE + OFS_UCSCTL2)) & FLLD_7;
        tempDivider = tempDivider >> 12;

        for (i = 0; i < tempDivider; i++){
            D_value =  D_value * 2;
        }

        CLKFrequency *= D_value;
    }
    return ( CLKFrequency) ;
}

static uint32_t privateUCSComputeCLKFrequency (uint16_t CLKSource,
    uint16_t CLKSourceDivider
    )
{
    uint32_t CLKFrequency;
    uint8_t CLKSourceFrequencyDivider = 1;
    uint8_t i = 0;

    for ( i = 0; i < CLKSourceDivider; i++){
        CLKSourceFrequencyDivider *= 2;
    }

    switch (CLKSource){
        case SELM__XT1CLK:
            CLKFrequency = (privateXT1ClockFrequency /
                            CLKSourceFrequencyDivider);

            if(XTS != (HWREG16(UCS_BASE + OFS_UCSCTL6) & XTS))  {
              if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1LFOFFG){
                HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1LFOFFG);
                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;

                if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1LFOFFG){
                    CLKFrequency = UCS_REFOCLK_FREQUENCY;
                }
              }
            }
            else {
              if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1HFOFFG){
                HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1HFOFFG);
                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;

                if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1HFOFFG){
                    CLKFrequency = UCS_REFOCLK_FREQUENCY;
                }
              }
            }
            break;

        case SELM__VLOCLK:
            CLKFrequency =
                (UCS_VLOCLK_FREQUENCY / CLKSourceFrequencyDivider);
            break;
        case SELM__REFOCLK:
            CLKFrequency =
                (UCS_REFOCLK_FREQUENCY / CLKSourceFrequencyDivider);
            break;
        case SELM__XT2CLK:
            CLKFrequency =
                (privateXT2ClockFrequency / CLKSourceFrequencyDivider);

            if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG){

              HWREG8(UCS_BASE + OFS_UCSCTL7) &=  ~XT2OFFG;
              //Clear OFIFG fault flag
              HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
            }

            if (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG){
                CLKFrequency =
                    privateUCSSourceClockFromDCO( SELM__DCOCLKDIV);
            }
            break;
        case SELM__DCOCLK:
        case SELM__DCOCLKDIV:
            CLKFrequency = privateUCSSourceClockFromDCO(
                CLKSource) / CLKSourceFrequencyDivider;
            break;
    }

    return ( CLKFrequency) ;
}

void UCS_setExternalClockSource (uint32_t XT1CLK_frequency,
    uint32_t XT2CLK_frequency
    )
{
    privateXT1ClockFrequency = XT1CLK_frequency;
    privateXT2ClockFrequency = XT2CLK_frequency;
}

void UCS_initClockSignal (uint8_t selectedClockSignal,
    uint16_t clockSource,
    uint16_t clockSourceDivider
    )
{
    assert(
        (UCS_XT1CLK_SELECT == clockSource) ||
        (UCS_VLOCLK_SELECT == clockSource) ||
        (UCS_REFOCLK_SELECT == clockSource) ||
        (UCS_DCOCLK_SELECT == clockSource) ||
        (UCS_DCOCLKDIV_SELECT == clockSource) ||
        (UCS_XT2CLK_SELECT == clockSource)
        );

    assert(
        (UCS_CLOCK_DIVIDER_1 == clockSourceDivider) ||
        (UCS_CLOCK_DIVIDER_2 == clockSourceDivider) ||
        (UCS_CLOCK_DIVIDER_4 == clockSourceDivider) ||
        (UCS_CLOCK_DIVIDER_8 == clockSourceDivider) ||
        (UCS_CLOCK_DIVIDER_16 == clockSourceDivider) ||
        (UCS_CLOCK_DIVIDER_32 == clockSourceDivider)
        );

    uint16_t temp = HWREG16(UCS_BASE + OFS_UCSCTL5);
    switch (selectedClockSignal){
        case UCS_ACLK:
            HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELA_7);
            clockSource = clockSource << 8;
            HWREG16(UCS_BASE + OFS_UCSCTL4) |= (clockSource);

            clockSourceDivider = clockSourceDivider << 8;
            HWREG16(UCS_BASE + OFS_UCSCTL5) = temp & ~(DIVA_7) | clockSourceDivider;
            break;
        case UCS_SMCLK:
            HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELS_7);
            clockSource = clockSource << 4;
            HWREG16(UCS_BASE + OFS_UCSCTL4) |= (clockSource);

            clockSourceDivider = clockSourceDivider << 4;
            HWREG16(UCS_BASE + OFS_UCSCTL5) = temp & ~(DIVS_7) | clockSourceDivider;
            break;
        case UCS_MCLK:
            HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELM_7);
            HWREG16(UCS_BASE + OFS_UCSCTL4) |= (clockSource);

            HWREG16(UCS_BASE + OFS_UCSCTL5) = temp & ~(DIVM_7) | clockSourceDivider;
            break;
        case UCS_FLLREF:
            assert(clockSource <= SELA_5);
            HWREG8(UCS_BASE + OFS_UCSCTL3) &=  ~(SELREF_7);

            clockSource = clockSource << 4;
            HWREG8(UCS_BASE + OFS_UCSCTL3) |= (clockSource);

            temp = HWREG8(UCS_BASE + OFS_UCSCTL3) & 0x00FF;
            //Note that dividers for FLLREF are slightly different
            //Hence handled differently from other CLK signals
            switch(clockSourceDivider)
            {
              case UCS_CLOCK_DIVIDER_12:
                HWREG8(UCS_BASE + OFS_UCSCTL3) = temp & ~(FLLREFDIV_7) | FLLREFDIV__12;
                break;
              case UCS_CLOCK_DIVIDER_16:
                HWREG8(UCS_BASE + OFS_UCSCTL3) = temp & ~(FLLREFDIV_7) | FLLREFDIV__16;
                break;
              default:
                HWREG8(UCS_BASE + OFS_UCSCTL3) = temp & ~(FLLREFDIV_7) | clockSourceDivider;
                break;
            }

            break;
    }
}

void UCS_turnOnLFXT1 (uint16_t xt1drive,
    uint8_t xcap
    )
{
    assert((xcap == UCS_XCAP_0) ||
        (xcap == UCS_XCAP_1) ||
        (xcap == UCS_XCAP_2) ||
        (xcap == UCS_XCAP_3) );

    assert((xt1drive == UCS_XT1_DRIVE_0 ) ||
        (xt1drive == UCS_XT1_DRIVE_1 ) ||
        (xt1drive == UCS_XT1_DRIVE_2 ) ||
        (xt1drive == UCS_XT1_DRIVE_3 ));

    //Switch ON XT1 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1OFF;

    //Highest drive setting for XT1startup
    HWREG16(UCS_BASE + OFS_UCSCTL6_L) |= XT1DRIVE1_L + XT1DRIVE0_L;

    //Enable LF mode and clear xcap and bypass
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~(XTS + XCAP_3 + XT1BYPASS);
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= xcap;

    while (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1LFOFFG)
    {
        //Clear OSC flaut Flags fault flags
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1LFOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    //set requested Drive mode
    HWREG16(UCS_BASE + OFS_UCSCTL6) = ( HWREG16(UCS_BASE + OFS_UCSCTL6) &
                                         ~(XT1DRIVE_3)
                                         ) |
                                       (xt1drive);

}

void UCS_turnOnHFXT1(uint16_t xt1drive
    )
{
    //Switch ON XT1 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1OFF;

    //Check if drive value is the expected one
    if ((HWREG16(UCS_BASE + OFS_UCSCTL6) & XT1DRIVE_3) != xt1drive){
        //Clear XT1drive field
        HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1DRIVE_3;

        //Set requested value
        HWREG16(UCS_BASE + OFS_UCSCTL6) |= xt1drive;
    }

    //Enable HF mode
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XTS;

    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1BYPASS;

    // Check XT1 fault flags
    while((HWREG8(UCS_BASE + OFS_UCSCTL7) & (XT1HFOFFG))){
        //Clear OSC flaut Flags fault flags
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1HFOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }
}

void UCS_bypassXT1 (uint8_t highOrLowFrequency
    )
{
    assert((UCS_XT1_LOW_FREQUENCY == highOrLowFrequency) ||
        (UCS_XT1_HIGH_FREQUENCY == highOrLowFrequency )
        );

    //Enable HF/LF mode
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XTS;
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= highOrLowFrequency;

    //Switch OFF XT1 oscillator and enable BYPASS mode
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= (XT1BYPASS + XT1OFF);

    if (UCS_XT1_LOW_FREQUENCY == highOrLowFrequency){
      while (HWREG8(UCS_BASE + OFS_UCSCTL7) & (XT1LFOFFG)) {
        //Clear OSC flaut Flags fault flags
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1LFOFFG);

        // Clear the global fault flag. In case the XT1 caused the global fault
        // flag to get set this will clear the global error condition. If any
        // error condition persists, global flag will get again.
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
      }
    } else   {
        while (HWREG8(UCS_BASE + OFS_UCSCTL7) & (XT1HFOFFG)) {
          //Clear OSC flaut Flags fault flags
          HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1HFOFFG);

          //Clear the global fault flag. In case the XT1 caused the global fault
          //flag to get set this will clear the global error condition. If any
          //error condition persists, global flag will get again.
          HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
        }
      }

}

bool UCS_turnOnLFXT1WithTimeout(uint16_t xt1drive,
    uint8_t xcap,
    uint16_t timeout
    )
{
    assert((xcap == UCS_XCAP_0) ||
        (xcap == UCS_XCAP_1) ||
        (xcap == UCS_XCAP_2) ||
        (xcap == UCS_XCAP_3) );

    assert((xt1drive == UCS_XT1_DRIVE_0 ) ||
        (xt1drive == UCS_XT1_DRIVE_1 ) ||
        (xt1drive == UCS_XT1_DRIVE_2 ) ||
        (xt1drive == UCS_XT1_DRIVE_3 ));

    assert(timeout > 0);

    //Switch ON XT1 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1OFF;

    //Highest drive setting for XT1startup
    HWREG16(UCS_BASE + OFS_UCSCTL6_L) |= XT1DRIVE1_L + XT1DRIVE0_L;

   	//Enable LF mode and clear xcap and bypass
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~(XTS + XCAP_3 + XT1BYPASS);
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= xcap;

    do
    {
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1LFOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & XT1LFOFFG) && --timeout);

    if (timeout){
        //set requested Drive mode
        HWREG16(UCS_BASE + OFS_UCSCTL6) = ( HWREG16(UCS_BASE + OFS_UCSCTL6) &
                                             ~(XT1DRIVE_3)
                                             ) |
                                           (xt1drive);

        return (STATUS_SUCCESS);
    } else   {
        return (STATUS_FAIL);
    }
}

bool UCS_turnOnHFXT1WithTimeout (uint16_t xt1drive,
    uint16_t timeout
    )
{
    assert((xt1drive == UCS_XT1_DRIVE_0 ) ||
        (xt1drive == UCS_XT1_DRIVE_1 ) ||
        (xt1drive == UCS_XT1_DRIVE_2 ) ||
        (xt1drive == UCS_XT1_DRIVE_3 ));

    assert(timeout > 0);

    //Switch ON XT1 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1OFF;

    //Check if drive value is the expected one
    if ((HWREG16(UCS_BASE + OFS_UCSCTL6) & XT1DRIVE_3) != xt1drive){
        //Clear XT1drive field
        HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1DRIVE_3;

        //Set requested value
        HWREG16(UCS_BASE + OFS_UCSCTL6) |= xt1drive;
    }

    //Enable HF mode
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XTS;

    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT1BYPASS;

    // Check XT1 fault flags
    do
    {
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1HFOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & ( XT1HFOFFG))
            && --timeout);

    if (timeout){
        return (STATUS_SUCCESS);
    } else   {
        return (STATUS_FAIL);
    }
}

bool UCS_bypassXT1WithTimeout (uint8_t highOrLowFrequency,
    uint16_t timeout
    )
{
    assert((UCS_XT1_LOW_FREQUENCY == highOrLowFrequency) ||
        (UCS_XT1_HIGH_FREQUENCY == highOrLowFrequency )
        );

    assert(timeout > 0);

    //Enable HF/LF mode
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XTS;
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= highOrLowFrequency;

    //Switch OFF XT1 oscillator  and enable bypass
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= (XT1BYPASS + XT1OFF);

    if (UCS_XT1_LOW_FREQUENCY == highOrLowFrequency){
      do {
        //Clear OSC flaut Flags fault flags
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1LFOFFG);

        // Clear the global fault flag. In case the XT1 caused the global fault
        // flag to get set this will clear the global error condition. If any
        // error condition persists, global flag will get again.
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
      }while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & (XT1LFOFFG)) && --timeout);

    } else   {
        do {
          //Clear OSC flaut Flags fault flags
          HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT1HFOFFG);

          //Clear the global fault flag. In case the XT1 caused the global fault
          //flag to get set this will clear the global error condition. If any
          //error condition persists, global flag will get again.
          HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
        }while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & (XT1HFOFFG))&& --timeout);
    }

    if (timeout){
        return (STATUS_SUCCESS);
    } else {
        return (STATUS_FAIL);
    }
}

void UCS_turnOffXT1 (void)
{
    //Switch off XT1 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT1OFF;
}

void UCS_turnOnXT2 (uint16_t xt2drive
    )
{
#if NOT_CC430_DEVICE

    //Check if drive value is the expected one
    if ((HWREG16(UCS_BASE + OFS_UCSCTL6) & XT2DRIVE_3) != xt2drive){
        //Clear XT2drive field
        HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2DRIVE_3;

        //Set requested value
        HWREG16(UCS_BASE + OFS_UCSCTL6) |= xt2drive;
    }

    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2BYPASS;
#endif

    //Enable XT2 and Switch on XT2 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2OFF;

    while (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG){
     //Clear OSC flaut Flags
     HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT2OFFG);

#if CC430_DEVICE
        // CC430 uses a different fault mechanism. It requires 3 VLO clock
        // cycles delay.If 20MHz CPU, 5000 clock cycles are required in worst
        // case.
        __delay_cycles(5000);
#endif

     //Clear OFIFG fault flag
     HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }
}

void UCS_bypassXT2 (void)
{
    //Switch on XT2 oscillator
#if NOT_CC430_DEVICE
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT2BYPASS;
#endif
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT2OFF;

    while (HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG){
     //Clear OSC flaut Flags
     HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT2OFFG);

#if CC430_DEVICE
        // CC430 uses a different fault mechanism. It requires 3 VLO clock
        // cycles delay.If 20MHz CPU, 5000 clock cycles are required in worst
        // case.
        __delay_cycles(5000);
#endif

     //Clear OFIFG fault flag
     HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }
}

bool UCS_turnOnXT2WithTimeout (uint16_t xt2drive,
    uint16_t timeout
    )
{
    assert(timeout > 0);

#if NOT_CC430_DEVICE
    //Check if drive value is the expected one
    if ((HWREG16(UCS_BASE + OFS_UCSCTL6) & XT2DRIVE_3) != xt2drive){
        //Clear XT2drive field
        HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2DRIVE_3;

        //Set requested value
        HWREG16(UCS_BASE + OFS_UCSCTL6) |= xt2drive;
    }

    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2BYPASS;
#endif

    //Switch on XT2 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~XT2OFF;

    do{
     //Clear OSC flaut Flags
     HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT2OFFG);

#if CC430_DEVICE
        // CC430 uses a different fault mechanism. It requires 3 VLO clock
        // cycles delay.If 20MHz CPU, 5000 clock cycles are required in worst
        // case.
        __delay_cycles(5000);
#endif

     //Clear OFIFG fault flag
     HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG) && --timeout);

    if (timeout){
        return (STATUS_SUCCESS);
    } else   {
        return (STATUS_FAIL);
    }
}

bool UCS_bypassXT2WithTimeout (uint16_t timeout
    )
{
    assert(timeout > 0);

    //Switch off XT2 oscillator and enable BYPASS mode
#if NOT_CC430_DEVICE
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT2BYPASS;
#endif
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT2OFF;

    do{
     //Clear OSC flaut Flags
     HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT2OFFG);

#if CC430_DEVICE
        // CC430 uses a different fault mechanism. It requires 3 VLO clock
        // cycles delay.If 20MHz CPU, 5000 clock cycles are required in worst
        // case.
        __delay_cycles(5000);
#endif

     //Clear OFIFG fault flag
     HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG) && --timeout);

    if (timeout){
        return (STATUS_SUCCESS);
    } else   {
        return (STATUS_FAIL);
    }
}

void UCS_turnOffXT2 (void)
{
    //Switch off XT2 oscillator
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT2OFF;
}

void UCS_initFLLSettle (uint16_t fsystem,
    uint16_t ratio
    )
{
    volatile uint16_t x = ratio * 32;

    UCS_initFLL(fsystem, ratio);

    while (x--)
    {
        __delay_cycles(30);
    }
}

void UCS_initFLL (uint16_t fsystem,
    uint16_t ratio
    )
{
    uint16_t d, dco_div_bits;
    uint16_t mode = 0;

    //Save actual state of FLL loop control, then disable it. This is needed to
    //prevent the FLL from acting as we are making fundamental modifications to
    //the clock setup.
    uint16_t srRegisterState = __get_SR_register() & SCG0;

    d = ratio;
    //Have at least a divider of 2
    dco_div_bits = FLLD__2;

    if (fsystem > 16000){
        d >>= 1 ;
        mode = 1;
    } else   {
        //fsystem = fsystem * 2
        fsystem <<= 1;
    }

    while (d > 512)
    {
        //Set next higher div level
        dco_div_bits = dco_div_bits + FLLD0;
        d >>= 1;
    }

    // Disable FLL
    __bis_SR_register(SCG0);

    //Set DCO to lowest Tap
    HWREG8(UCS_BASE + OFS_UCSCTL0_H) = 0x0000;

    //Reset FN bits
    HWREG16(UCS_BASE + OFS_UCSCTL2) &= ~(0x03FF);
    HWREG16(UCS_BASE + OFS_UCSCTL2) = dco_div_bits | (d - 1);

    if (fsystem <= 630){           //fsystem < 0.63MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_0;
    } else if (fsystem <  1250){      //0.63MHz < fsystem < 1.25MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_1;
    } else if (fsystem <  2500){      //1.25MHz < fsystem <  2.5MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_2;
    } else if (fsystem <  5000){      //2.5MHz  < fsystem <    5MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_3;
    } else if (fsystem <  10000){     //5MHz    < fsystem <   10MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_4;
    } else if (fsystem <  20000){     //10MHz   < fsystem <   20MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_5;
    } else if (fsystem <  40000){     //20MHz   < fsystem <   40MHz
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_6;
    } else {
        HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_7;
    }

    // Re-enable FLL
     __bic_SR_register(SCG0);

    while (HWREG8(UCS_BASE + OFS_UCSCTL7_L) & DCOFFG)
    {
        //Clear OSC flaut Flags
        HWREG8(UCS_BASE + OFS_UCSCTL7_L) &= ~(DCOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    // Restore previous SCG0
    __bis_SR_register(srRegisterState);

    if (mode == 1){
        //fsystem > 16000
        //Select DCOCLK
        HWREG16(UCS_BASE + OFS_UCSCTL4) &=  ~(SELM_7 + SELS_7);
        HWREG16(UCS_BASE + OFS_UCSCTL4) |= SELM__DCOCLK + SELS__DCOCLK;
    } else   {
        //Select DCODIVCLK
        HWREG16(UCS_BASE + OFS_UCSCTL4) &=  ~(SELM_7 + SELS_7);
        HWREG16(UCS_BASE + OFS_UCSCTL4) |= SELM__DCOCLKDIV + SELS__DCOCLKDIV;
    }

}

void UCS_enableClockRequest (uint8_t selectClock
    )
{
    HWREG8(UCS_BASE + OFS_UCSCTL8) |= selectClock;
}

void UCS_disableClockRequest (uint8_t selectClock
    )
{
    HWREG8(UCS_BASE + OFS_UCSCTL8) &= ~selectClock;
}

uint8_t UCS_getFaultFlagStatus (uint8_t mask
    )
{
    assert(mask <= UCS_XT2OFFG );
    return (HWREG8(UCS_BASE + OFS_UCSCTL7) & mask);
}

void UCS_clearFaultFlag (uint8_t mask
    )
{
    assert(mask <= UCS_XT2OFFG );
    HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~mask;
}

void UCS_turnOffSMCLK (void)
{
    HWREG16(UCS_BASE + OFS_UCSCTL6) |= SMCLKOFF;
}

void UCS_turnOnSMCLK (void)
{
    HWREG16(UCS_BASE + OFS_UCSCTL6) &= ~SMCLKOFF;
}

uint32_t UCS_getACLK (void)
{
    //Find ACLK source
    uint16_t ACLKSource = (HWREG16(UCS_BASE + OFS_UCSCTL4) & SELA_7);

    ACLKSource = ACLKSource >> 8;

    uint16_t ACLKSourceDivider =  HWREG16(UCS_BASE + OFS_UCSCTL5) & DIVA_7;
    ACLKSourceDivider = ACLKSourceDivider >> 8;

    return (privateUCSComputeCLKFrequency(
                ACLKSource,
                ACLKSourceDivider
                ));
}

uint32_t UCS_getSMCLK (void)
{
    uint16_t SMCLKSource = HWREG8(UCS_BASE + OFS_UCSCTL4_L) & SELS_7;

    SMCLKSource = SMCLKSource >> 4;

    uint16_t SMCLKSourceDivider =
        HWREG16(UCS_BASE + OFS_UCSCTL5) & DIVS_7;
    SMCLKSourceDivider = SMCLKSourceDivider >> 4;

    return (privateUCSComputeCLKFrequency(
                SMCLKSource,
                SMCLKSourceDivider )
            );
}

uint32_t UCS_getMCLK (void)
{
    //Find AMCLK source
    uint16_t MCLKSource = (HWREG16(UCS_BASE + OFS_UCSCTL4) & SELM_7);

    uint16_t MCLKSourceDivider =  HWREG16(UCS_BASE + OFS_UCSCTL5) & DIVM_7;

    return (privateUCSComputeCLKFrequency(
                MCLKSource,
                MCLKSourceDivider )
            );
}

uint16_t UCS_clearAllOscFlagsWithTimeout(uint16_t timeout
                                             )
{
    assert(timeout > 0);

    do {
      // Clear all osc fault flags
      HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(DCOFFG +
                                             XT1LFOFFG +
                                             XT1HFOFFG +
                                             XT2OFFG
                                             );

#if CC430_DEVICE
        // CC430 uses a different fault mechanism. It requires 3 VLO clock
        // cycles delay.If 20MHz CPU, 5000 clock cycles are required in worst
        // case.
        __delay_cycles(5000);
#endif

      // Clear the global osc fault flag.
      HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;

      // Check XT1 fault flags
    } while ((HWREG8(SFR_BASE + OFS_SFRIFG1) & OFIFG) && --timeout);

    return (HWREG8(UCS_BASE + OFS_UCSCTL7) & (DCOFFG +
                                                 XT1LFOFFG +
                                                 XT1HFOFFG +
                                                 XT2OFFG)
                                                );
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for ucs_api
//! @}
//
//*****************************************************************************
