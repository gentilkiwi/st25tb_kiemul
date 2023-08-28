//*****************************************************************************
//
// cs.c - Driver for the cs Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup cs_api cs
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_CS__
#include "cs.h"

#include <assert.h>

//*****************************************************************************
//
// Internal very low power VLOCLK, low frequency oscillator with 10 kHz typical
// frequency
//
//*****************************************************************************
#define CS_VLOCLK_FREQUENCY                                               10000

//*****************************************************************************
//
// Internal, trimmed, low-frequency oscillator with 32768 Hz typical frequency
//
//*****************************************************************************
#define CS_REFOCLK_FREQUENCY                                              32768

//*****************************************************************************
//
// Internal DCO frequency range
//
//*****************************************************************************
#define CS_DCO_RANGE_1MHZ                                               1000000
#define CS_DCO_RANGE_2MHZ                                               2000000
#define CS_DCO_RANGE_4MHZ                                               4000000
#define CS_DCO_RANGE_8MHZ                                               8000000
#define CS_DCO_RANGE_12MHZ                                             12000000
#define CS_DCO_RANGE_16MHZ                                             16000000
#define CS_DCO_RANGE_20MHZ                                             20000000
#define CS_DCO_RANGE_24MHZ                                             24000000

//******************************************************************************
//
//The XT1 crystal frequency. Should be set with CS_externalClockSourceInit
//if XT1 is used and user intends to invoke CS_getSMCLK, CS_getMCLK or
//CS_getACLK
//
//******************************************************************************
static uint32_t privateXT1ClockFrequency = 0;

static uint32_t privateDCORange(void)
{
    uint32_t res = 0;
    switch ( (HWREG8(CS_BASE + OFS_CSCTL1)) & DCORSEL_7) {
    case DCORSEL_0:
        res = CS_DCO_RANGE_1MHZ;
        break;
    case DCORSEL_1:
        res = CS_DCO_RANGE_2MHZ;
        break;
    case DCORSEL_2:
        res = CS_DCO_RANGE_4MHZ;
        break;
    case DCORSEL_3:
        res = CS_DCO_RANGE_8MHZ;
        break;
    case DCORSEL_4:
        res = CS_DCO_RANGE_12MHZ;
        break;
    case DCORSEL_5:
        res = CS_DCO_RANGE_16MHZ;
        break;
    case DCORSEL_6:
        res = CS_DCO_RANGE_20MHZ;
        break;
    case DCORSEL_7:
        res = CS_DCO_RANGE_24MHZ;
        break;
    default:
        break;
    }

    return res;
}

static uint32_t privateCSSourceClockFromDCO(uint16_t FLLRefCLKSource)
{
    uint16_t N_value;
    uint16_t n_value = 1;
    uint32_t Fref_value = 1;

    N_value = (HWREG16(CS_BASE + OFS_CSCTL2)) & 0x03FF;
    uint16_t tempDivider = HWREG8(CS_BASE + OFS_CSCTL3) & FLLREFDIV_7;

    if (tempDivider > 1) {
        n_value = 32 << (tempDivider-1);
    }

    switch ( (HWREG8(CS_BASE + OFS_CSCTL3)) & SELREF_3 ) {
        case SELREF__XT1CLK:
            Fref_value = privateXT1ClockFrequency;

            if (HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG) {
                HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);
                //Clear OFIFG fault flag
                HWREG8(CS_BASE + OFS_SFRIFG1) &= ~OFIFG;

                if (HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG) {
                    if (HWREG16(CS_BASE + OFS_CSCTL6) & XTS) {
                        HWREG8(CS_BASE + OFS_CSCTL7) &= ~DCOFFG;
                        Fref_value = privateDCORange();
                    }   // XTS
                    else {
                        Fref_value = CS_REFOCLK_FREQUENCY;
                    }   // XTS
                }   // XT1OFFG #2
            }   // XT1OFFG #1
            break;
        case SELREF__REFOCLK:
            Fref_value = CS_REFOCLK_FREQUENCY;
            break;
        default: break;
    }

    return (Fref_value * (N_value + 1) / n_value);
}

static uint32_t privateCSComputeCLKFrequency(uint16_t CLKSource,
    uint16_t CLKSourceDivider,
    uint8_t CLKDest
    )
{
    uint32_t CLKFrequency = 0;
    uint8_t CLKSourceFrequencyDivider = 1;

    CLKSourceFrequencyDivider = 1<<CLKSourceDivider;

    switch (CLKSource) {
        case SELMS__XT1CLK:
            CLKFrequency = (privateXT1ClockFrequency /
                            CLKSourceFrequencyDivider);

              if (HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG) {
                HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);
                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
                //fail-safe operation
                if (HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG) {
                    //fail-safe for ACLK or XT1 mode is LF
                    if (CLKDest == CS_ACLK || (HWREG16(CS_BASE + OFS_CSCTL6) & XTS) == 0) {
                        CLKFrequency = CS_REFOCLK_FREQUENCY;
                    }
                    //XT1 mode is HF
                    else {
                        HWREG8(CS_BASE + OFS_CSCTL7) &= ~DCOFFG;
                        CLKFrequency = privateDCORange();
                    }
                }
            }
            break;

        case SELMS__VLOCLK:
            CLKFrequency =
                (CS_VLOCLK_FREQUENCY / CLKSourceFrequencyDivider);
            break;
        case SELMS__REFOCLK:
            CLKFrequency =
                (CS_REFOCLK_FREQUENCY / CLKSourceFrequencyDivider);
            break;
        case SELMS__DCOCLKDIV:
            CLKFrequency =
                    privateCSSourceClockFromDCO( CLKSource)
                    / CLKSourceFrequencyDivider;
            break;
    }
    return ( CLKFrequency) ;
}

static void privateCSComputeDCOFTrim(CS_initFLLParam *param)
{
    uint16_t oldDcoTap = 0xffff;
    uint16_t newDcoTap = 0xffff;
    uint16_t newDcoDelta = 0xffff;
    uint16_t bestDcoDelta = 0xffff;
    uint16_t csCtl0Copy = 0;
    uint16_t csCtl1Copy = 0;
    uint16_t csCtl0Read = 0;
    uint16_t csCtl1Read = 0;
    uint16_t dcoFreqTrim = 3;
    bool endLoop = false;
    
    do
    {
        HWREG16(CS_BASE + OFS_CSCTL0) = DCO8;   // DCO Tap = 256
        do
        {
            HWREG16(CS_BASE + OFS_CSCTL7) &= ~DCOFFG;   // Clear DCO fault flag
        } while(HWREG16(CS_BASE + OFS_CSCTL7) & DCOFFG);
        
        switch((HWREG16(CS_BASE + OFS_CSCTL1) & DCORSEL_7) >> 1)
        {
        // Wait FLL lock status (FLLUNLOCK) stable
        // Suggest to wait 24 cycles of divided FLL refclk
            case 0: // 1 MHz
                __delay_cycles((uint16_t)3000);
                break;
            case 1: // 2 MHz
                __delay_cycles((uint16_t)3000 * 2);
                break;
            case 2: // 4 MHz
                __delay_cycles((uint16_t)3000 * 4);
                break;
            case 3: // 8 MHz
                __delay_cycles((uint16_t)3000 * 8);
                break;
            case 4: // 12 MHz
                __delay_cycles((uint16_t)3000 * 12);
                break;
            case 5: // 16 MHz
                __delay_cycles((uint16_t)3000 * 16);
                break;
            case 6: // 20 MHz
                __delay_cycles((uint16_t)3000 * 20);
                break;
            case 7: // 24 MHz
                __delay_cycles((uint32_t)3000 * 24);
                break;
            default:    // reserved
                __delay_cycles((uint16_t)3000 * 16);
                break;
        }
        
        // Poll the FLLUNLOCK bits and DCOFFG bit until FLL is locked or DCO fault
        while((HWREG16(CS_BASE + OFS_CSCTL7) & (FLLUNLOCK0 | FLLUNLOCK1)) &&
            ((HWREG16(CS_BASE + OFS_CSCTL7) & DCOFFG) == 0));
            
        csCtl0Read = HWREG16(CS_BASE + OFS_CSCTL0); // Read CSCTL0
        csCtl1Read = HWREG16(CS_BASE + OFS_CSCTL1); // Read CSCTL1
        
        oldDcoTap = newDcoTap;  // Record DCOTAP value of last time
        newDcoTap = csCtl0Read & 0x01ff;    // Get DCOTAP value of this time
        dcoFreqTrim = (csCtl1Read & 0x0070) >> 4;   // Get DCOFTRIM value
        
        if(newDcoTap < 256) // DCOTAP < 256
        {
            newDcoDelta = 256 - newDcoTap;  // Delta value between DCOTAP and 256
            if((oldDcoTap != 0xffff) && (oldDcoTap >= 256)) // DCOTAP cross 256
            {
                endLoop = true; // Stop while loop
            }
            else
            {
                dcoFreqTrim--;
                HWREG16(CS_BASE + OFS_CSCTL1) = (csCtl1Read & (~0x0070)) | (dcoFreqTrim << 4);
            }
        }
        else   // DCOTAP >= 256
        {
            newDcoDelta = newDcoTap - 256;  // Delta value between DCOTAP and 256
            if(oldDcoTap < 256) // DCOTAP cross 256
            {
                endLoop = true; // Stop while loop
            }
            else
            {
                dcoFreqTrim++;
                HWREG16(CS_BASE + OFS_CSCTL1) = (csCtl1Read & (~0x0070)) | (dcoFreqTrim << 4);
            }
        }
    
        if(newDcoDelta < bestDcoDelta)  // Record DCOTAP closest to 256
        {
            csCtl0Copy = csCtl0Read;
            csCtl1Copy = csCtl1Read;
            bestDcoDelta = newDcoDelta;
        }
    
    } while(endLoop == false);  // Poll until endLoop == 1
    
    HWREG16(CS_BASE + OFS_CSCTL0) = csCtl0Copy; // Reload locked DCOTAP
    HWREG16(CS_BASE + OFS_CSCTL1) = csCtl1Copy; // Reload locked DCOFTRIM
    param->csCtl0 = csCtl0Copy;
    param->csCtl1 = csCtl1Copy;
    while(HWREG16(CS_BASE + OFS_CSCTL7) & (FLLUNLOCK0 | FLLUNLOCK1));   // Poll until FLL is locked
}

void CS_setExternalClockSource(uint32_t XT1CLK_frequency
    )
{
    privateXT1ClockFrequency = XT1CLK_frequency;
}

void CS_initClockSignal(uint8_t selectedClockSignal,
    uint16_t clockSource,
    uint16_t clockSourceDivider
    )
{
    uint16_t temp;
    switch (selectedClockSignal) {
        case CS_ACLK:

            HWREG16(CS_BASE + OFS_CSCTL4) &= ~(SELA);

            if (clockSource == CS_XT1CLK_SELECT) {
                clockSource = 0x0;
            }
            else if (clockSource == CS_REFOCLK_SELECT) {
                clockSource = 0x1;
            }
            else if (clockSource == CS_VLOCLK_SELECT) {
                clockSource = 0x2;
            }
            clockSource = clockSource << 8;

            HWREG16(CS_BASE + OFS_CSCTL4) |= (clockSource);
#ifdef DIVA0
            if (HWREG16(CS_BASE + OFS_CSCTL6) & XTS) {

                temp = HWREG16(CS_BASE + OFS_CSCTL6);
                if (clockSourceDivider != CS_CLOCK_DIVIDER_1) {
                    clockSourceDivider = (clockSourceDivider-3) << 8;
                    HWREG16(CS_BASE + OFS_CSCTL6) |= temp & ~(DIVA3|DIVA2|DIVA1|DIVA0)
                                                     | clockSourceDivider;
                }
            }
#endif
            break;
        case CS_SMCLK:

            HWREG16(CS_BASE + OFS_CSCTL4) &= ~(SELMS_7);
            HWREG16(CS_BASE + OFS_CSCTL4) |= (clockSource);

            temp = HWREG16(CS_BASE + OFS_CSCTL5);
            clockSourceDivider = clockSourceDivider << 4;
            HWREG16(CS_BASE + OFS_CSCTL5) = temp & ~(DIVS_3) | clockSourceDivider;
            break;
        case CS_MCLK:

            HWREG16(CS_BASE + OFS_CSCTL4) &= ~(SELMS_7);
            HWREG16(CS_BASE + OFS_CSCTL4) |= (clockSource);

            temp = HWREG16(CS_BASE + OFS_CSCTL5);
            HWREG16(CS_BASE + OFS_CSCTL5) = temp & ~(DIVM_7) | clockSourceDivider;
            break;
        case CS_FLLREF:

            HWREG8(CS_BASE + OFS_CSCTL3) &=  ~(SELREF_3);

            if (clockSource == CS_XT1CLK_SELECT) {
                clockSource = 0x0;
            }
            clockSource = clockSource << 4;
            HWREG8(CS_BASE + OFS_CSCTL3) |= (clockSource);

            temp = HWREG8(CS_BASE + OFS_CSCTL3);
            //Note that dividers for FLLREF are slightly different
            //Hence handled differently from other CLK signals
            if (clockSourceDivider != CS_CLOCK_DIVIDER_1) {
                if (clockSourceDivider == CS_CLOCK_DIVIDER_640) {
                    HWREG8(CS_BASE + OFS_CSCTL3) = temp & ~(FLLREFDIV_7) | (clockSourceDivider - 10);
                }
                else if (clockSourceDivider != CS_CLOCK_DIVIDER_512) {
                    HWREG8(CS_BASE + OFS_CSCTL3) = temp & ~(FLLREFDIV_7) | (clockSourceDivider - 4);
                }
                else {
                    HWREG8(CS_BASE + OFS_CSCTL3) = temp & ~(FLLREFDIV_7) | (clockSourceDivider - 5);
                }
            }
            break;
    }
}

void CS_turnOnXT1LF( uint16_t xt1Drive){
    //Switch ON XT1 oscillator
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1AUTOOFF;

    //Highest drive setting for turnOnXT1
    HWREG16(CS_BASE + OFS_CSCTL6_L) |= XT1DRIVE1_L | XT1DRIVE0_L;

    //Enable LF mode and clear bypass
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~(XTS | XT1BYPASS);
    
    while (HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG)
    {
        //Clear OSC fault flag
        HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    //set requested Drive mode
    HWREG16(CS_BASE + OFS_CSCTL6) = ( HWREG16(CS_BASE + OFS_CSCTL6) &
                                         ~(XT1DRIVE_3)
                                         ) |
                                       (xt1Drive);
}

void CS_bypassXT1(void)
{
    //Enable HF/LF mode
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XTS;

    //Switch OFF XT1 oscillator and enable BYPASS mode
    HWREG16(CS_BASE + OFS_CSCTL6) |= (XT1BYPASS | XT1AUTOOFF);

    while (HWREG8(CS_BASE + OFS_CSCTL7) & (XT1OFFG)) {
        //Clear OSC fault flags
        HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);

        // Clear the global fault flag. In case the XT1 caused the global fault
        // flag to get set this will clear the global error condition. If any
        // error condition persists, global flag will get again.
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }
}

bool CS_turnOnXT1LFWithTimeout(uint16_t xt1Drive,
    uint16_t timeout
    )
{
    //Switch ON XT1 oscillator
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1AUTOOFF;

    //Highest drive setting for turnOnXT1
    HWREG16(CS_BASE + OFS_CSCTL6_L) |= XT1DRIVE1_L | XT1DRIVE0_L;

       //Enable LF mode and clear bypass
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~(XTS | XT1BYPASS);
    
    do
    {
        HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    } while ((HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG) && --timeout);

    if (timeout) {
        //set requested Drive mode
        HWREG16(CS_BASE + OFS_CSCTL6) = ( HWREG16(CS_BASE + OFS_CSCTL6) &
                                             ~(XT1DRIVE_3)
                                             ) |
                                           (xt1Drive);
        return (STATUS_SUCCESS);
    }
    else {
        return (STATUS_FAIL);
    }
}

bool CS_bypassXT1WithTimeout(uint16_t timeout
    )
{
    //Enable HF/LF mode
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XTS;

    //Switch OFF XT1 oscillator  and enable bypass
    HWREG16(CS_BASE + OFS_CSCTL6) |= (XT1BYPASS | XT1AUTOOFF);

    do {
        //Clear OSC fault flags
        HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);

        // Clear the global fault flag. In case the XT1 caused the global fault
        // flag to get set this will clear the global error condition. If any
        // error condition persists, global flag will get again.
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }while ((HWREG8(CS_BASE + OFS_CSCTL7) & (XT1OFFG)) && --timeout);

    if (timeout) {
        return (STATUS_SUCCESS);
    }
    else {
        return (STATUS_FAIL);
    }
}

void CS_turnOffXT1(void)
{
    //Switch off XT1 oscillator
    HWREG16(CS_BASE + OFS_CSCTL6) |= XT1AUTOOFF;
}

void CS_turnOnXT1HF( uint16_t xt1Drive, uint16_t xt1HFFreq){
#ifdef XT1HFFREQ_3
    //Switch ON XT1 oscillator
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1AUTOOFF;

    //Enable HF and highest drive setting for XT1
    HWREG16(CS_BASE + OFS_CSCTL6_L) |= XTS | XT1DRIVE1_L | XT1DRIVE0_L;

    //Clear bypass
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1BYPASS;

    while (HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG)
    {
        //Clear OSC fault flag
        HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    //set requested Drive mode
    HWREG16(CS_BASE + OFS_CSCTL6) = (HWREG16(CS_BASE + OFS_CSCTL6) &
                                        ~(XT1DRIVE_3|XT1HFFREQ_3)) |
                                        xt1Drive | xt1HFFreq;
#endif
}

bool CS_turnOnXT1HFWithTimeout( uint16_t xt1Drive,uint16_t xt1HFFreq,
        uint16_t timeout)
{
#ifdef XT1HFFREQ_3
    //Switch ON XT1 oscillator
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1AUTOOFF;

    //Enable HF and highest drive setting for XT1
    HWREG16(CS_BASE + OFS_CSCTL6_L) |= XTS | XT1DRIVE1_L | XT1DRIVE0_L;

    //Clear bypass
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1BYPASS;

    do
    {
        HWREG8(CS_BASE + OFS_CSCTL7) &= ~(XT1OFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }while ((HWREG8(CS_BASE + OFS_CSCTL7) & XT1OFFG) && --timeout);

    if (timeout) {
        //set requested Drive mode
        HWREG16(CS_BASE + OFS_CSCTL6) = (HWREG16(CS_BASE + OFS_CSCTL6) &
                                            ~(XT1DRIVE_3|XT1HFFREQ_3)) |
                                            xt1Drive | xt1HFFreq;

        return (STATUS_SUCCESS);
    }
    else {
        return (STATUS_FAIL);
    }
#else
    return (STATUS_FAIL);
#endif
}

void CS_turnOnSMCLK (void)
{
    //Turn on SMCLK
    HWREG16(CS_BASE + OFS_CSCTL5) &= ~SMCLKOFF;
}

void CS_turnOffSMCLK (void)
{
    //Turn off SMCLK
    HWREG16(CS_BASE + OFS_CSCTL5) |= SMCLKOFF;
}

void CS_enableVLOAutoOff (void)
{
    //Enable VLO Auto Off
    HWREG16(CS_BASE + OFS_CSCTL5) |= VLOAUTOOFF;
}

void CS_disableVLOAutoOff (void)
{
    //Disable VLO Auto Off
    HWREG16(CS_BASE + OFS_CSCTL5) &= ~VLOAUTOOFF;
}

bool CS_initFLLSettle(uint16_t fsystem,
    uint16_t ratio
    )
{
    volatile uint16_t x = ratio * 32;

    bool status = CS_initFLL(fsystem, ratio);

    while (x--)
    {
        __delay_cycles(30);
    }
    
    return status;
}

bool CS_initFLL(uint16_t fsystem,
    uint16_t ratio
    )
{
    uint16_t dco_FLLN, dco_FLLD = FLLD__1;
    bool status = true;

    //Save actual state of FLL loop control, then disable it. This is needed to
    //prevent the FLL from acting as we are making fundamental modifications to
    //the clock setup.
    uint16_t srRegisterState = __get_SR_register() & SCG0;

    //Do not want the Oscillator Fault Flag to trigger during this routine.
    //So disable interrupt, save the state, and reapply later if necessary.
    uint8_t sfr_ofie_status = HWREG8(SFR_BASE + OFS_SFRIE1_L) & OFIE;
    HWREG8(SFR_BASE + OFS_SFRIE1_L) &= ~(OFIE);

    //Have at least a divider of 2
    dco_FLLN = ratio;

    // Disable FLL
    __bis_SR_register(SCG0);

    //Set DCO to lowest Tap
    HWREG16(CS_BASE + OFS_CSCTL0) &= ~( DCO8 |
                                            DCO7 |
                                            DCO6 |
                                            DCO5 |
                                            DCO4 |
                                            DCO3 |
                                            DCO2 |
                                            DCO1 |
                                            DCO0
                                        );

    //Reset FLLN bits
    HWREG16(CS_BASE + OFS_CSCTL2) &= ~( FLLN9 |
                                            FLLN8 |
                                            FLLN7 |
                                            FLLN6 |
                                            FLLN5 |
                                            FLLN4 |
                                            FLLN3 |
                                            FLLN2 |
                                            FLLN1 |
                                            FLLN0
                                        );
    HWREG16(CS_BASE + OFS_CSCTL2) = dco_FLLD | (dco_FLLN - 1);

    HWREG8(CS_BASE + OFS_CSCTL1) &= ~DCORSEL_7;
    if (fsystem <= 1500) {            //fsystem <= 1.5MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_0;
    }
    else if (fsystem <=  3000) {      //1.5MHz < fsystem <= 3MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_1;
    }
    else if (fsystem <=  6000) {      //3MHz < fsystem <= 6MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_2;
    }
    else if (fsystem <=  10000) {     //6MHz < fsystem <= 10MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_3;
    }
    else if (fsystem <=  14000) {     //10MHz < fsystem <= 14MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_4;
    }
    else if (fsystem <=  18000) {     //14MHz < fsystem <= 18MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_5;
    }
    else if (fsystem <=  22000) {     //18MHz < fsystem <= 22MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_6;
    }
    else if (fsystem <=  24000) {     //22MHz < fsystem <= 24MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_7;
    }
    else {
        //exceeds 24MHz, not supported
        status =  false;
    }

    // Re-enable FLL
    __bic_SR_register(SCG0);
    
    while ((HWREG16(CS_BASE + OFS_CSCTL7) & (FLLUNLOCK0 | FLLUNLOCK1)) ||
    (HWREG8(CS_BASE + OFS_CSCTL7_L) & DCOFFG))
    {
        //Clear OSC fault flags
        HWREG8(CS_BASE + OFS_CSCTL7_L) &= ~(DCOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    // Restore previous SCG0
    __bis_SR_register(srRegisterState);

    // Reapply Oscillator Fault Interrupt Enable if needed
    HWREG8(SFR_BASE + OFS_SFRIE1_L) |= sfr_ofie_status;

    return status;
}

bool CS_initFLLCalculateTrim(uint16_t fsystem,
    uint16_t ratio,
    CS_initFLLParam *param
    )
{
    uint16_t dco_FLLN, dco_FLLD = FLLD__1;
    bool status = true;
    volatile uint16_t x = ratio * 32;

    //Save actual state of FLL loop control, then disable it. This is needed to
    //prevent the FLL from acting as we are making fundamental modifications to
    //the clock setup.
    uint16_t srRegisterState = __get_SR_register() & SCG0;

    //Do not want the Oscillator Fault Flag to trigger during this routine.
    //So disable interrupt, save the state, and reapply later if necessary.
    uint8_t sfr_ofie_status = HWREG8(SFR_BASE + OFS_SFRIE1_L) & OFIE;
    HWREG8(SFR_BASE + OFS_SFRIE1_L) &= ~(OFIE);

    //Have at least a divider of 2
    dco_FLLN = ratio;

    // Disable FLL
    __bis_SR_register(SCG0);

    //Set DCO to lowest Tap
    HWREG16(CS_BASE + OFS_CSCTL0) &= ~( DCO8 |
                                            DCO7 |
                                            DCO6 |
                                            DCO5 |
                                            DCO4 |
                                            DCO3 |
                                            DCO2 |
                                            DCO1 |
                                            DCO0
                                        );
    //Reset FLLN bits
    HWREG16(CS_BASE + OFS_CSCTL2) &= ~( FLLN9 |
                                            FLLN8 |
                                            FLLN7 |
                                            FLLN6 |
                                            FLLN5 |
                                            FLLN4 |
                                            FLLN3 |
                                            FLLN2 |
                                            FLLN1 |
                                            FLLN0
                                        );
    HWREG16(CS_BASE + OFS_CSCTL2) = dco_FLLD | (dco_FLLN - 1);

    HWREG8(CS_BASE + OFS_CSCTL1) &= ~DCORSEL_7;
    if (fsystem <= 1500) {            //fsystem <= 1.5MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_0;
    }
    else if (fsystem <=  3000) {      //1.5MHz < fsystem <= 3MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_1;
    }
    else if (fsystem <=  6000) {      //3MHz < fsystem <= 6MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_2;
    }
    else if (fsystem <=  10000) {     //6MHz < fsystem <= 10MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_3;
    }
    else if (fsystem <=  14000) {     //10MHz < fsystem <= 14MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_4;
    }
    else if (fsystem <=  18000) {     //14MHz < fsystem <= 18MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_5;
    }
    else if (fsystem <=  22000) {     //18MHz < fsystem <= 22MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_6;
    }
    else if (fsystem <=  24000) {     //22MHz < fsystem <= 24MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_7;
    }
    else {
        //exceeds 24MHz, not supported
        status = false;
    }

    // Re-enable FLL
    __bic_SR_register(SCG0);
    
    // Enable DCO frequency trim
    HWREG16(CS_BASE + OFS_CSCTL1) |= DCOFTRIMEN;

    // Calculates DCO frequency trim values and stores them in struct pointer
    param->fsystem = fsystem;
    privateCSComputeDCOFTrim(param);
    
    while ((HWREG16(CS_BASE + OFS_CSCTL7) & (FLLUNLOCK0 | FLLUNLOCK1)) ||
        (HWREG8(CS_BASE + OFS_CSCTL7_L) & DCOFFG))
    {
        //Clear OSC fault flags
        HWREG8(CS_BASE + OFS_CSCTL7_L) &= ~(DCOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    // Restore previous SCG0
    __bis_SR_register(srRegisterState);
    
    while (x--)
    {
        __delay_cycles(30);
    }
    // Reapply Oscillator Fault Interrupt Enable if needed
    HWREG8(SFR_BASE + OFS_SFRIE1_L) |= sfr_ofie_status;
    
    return status;
}

bool CS_initFLLLoadTrim(uint16_t fsystem,
    uint16_t ratio,
    CS_initFLLParam *param
    )
{
    if(param->fsystem != fsystem)
    {
        // Protection against wrong clock frequency and trim combination
        return false;
    }
    
    uint16_t dco_FLLN, dco_FLLD = FLLD__1;
    bool status = true;
    volatile uint16_t x = ratio * 32;

    //Save actual state of FLL loop control, then disable it. This is needed to
    //prevent the FLL from acting as we are making fundamental modifications to
    //the clock setup.
    uint16_t srRegisterState = __get_SR_register() & SCG0;

    //Do not want the Oscillator Fault Flag to trigger during this routine.
    //So disable interrupt, save the state, and reapply later if necessary.
    uint8_t sfr_ofie_status = HWREG8(SFR_BASE + OFS_SFRIE1_L) & OFIE;
    HWREG8(SFR_BASE + OFS_SFRIE1_L) &= ~(OFIE);

    //Have at least a divider of 2
    dco_FLLN = ratio;
    
    // Disable FLL
    __bis_SR_register(SCG0);
    
    //Set DCO to proper tap
    HWREG16(CS_BASE + OFS_CSCTL0) &= ~( DCO8 |
                                            DCO7 |
                                            DCO6 |
                                            DCO5 |
                                            DCO4 |
                                            DCO3 |
                                            DCO2 |
                                            DCO1 |
                                            DCO0
                                            );
    HWREG16(CS_BASE + OFS_CSCTL0) |= (param->csCtl0 &
                                        (   DCO8 |
                                            DCO7 |
                                            DCO6 |
                                            DCO5 |
                                            DCO4 |
                                            DCO3 |
                                            DCO2 |
                                            DCO1 |
                                            DCO0
                                            ));

    //Reset FLLN bits
    HWREG16(CS_BASE + OFS_CSCTL2) &= ~( FLLN9 |
                                            FLLN8 |
                                            FLLN7 |
                                            FLLN6 |
                                            FLLN5 |
                                            FLLN4 |
                                            FLLN3 |
                                            FLLN2 |
                                            FLLN1 |
                                            FLLN0
                                        );
    HWREG16(CS_BASE + OFS_CSCTL2) = dco_FLLD | (dco_FLLN - 1);
    
    // Set proper DCORSEL value
    HWREG8(CS_BASE + OFS_CSCTL1) &= ~DCORSEL_7;
    if (fsystem <= 1500) {            //fsystem <= 1.5MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_0;
    }
    else if (fsystem <=  3000) {      //1.5MHz < fsystem <= 3MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_1;
    }
    else if (fsystem <=  6000) {      //3MHz < fsystem <= 6MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_2;
    }
    else if (fsystem <=  10000) {     //6MHz < fsystem <= 10MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_3;
    }
    else if (fsystem <=  14000) {     //10MHz < fsystem <= 14MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_4;
    }
    else if (fsystem <=  18000) {     //14MHz < fsystem <= 18MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_5;
    }
    else if (fsystem <=  22000) {     //18MHz < fsystem <= 22MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_6;
    }
    else if (fsystem <=  24000) {     //22MHz < fsystem <= 24MHz
        HWREG8(CS_BASE + OFS_CSCTL1) |= DCORSEL_7;
    }
    else {
        //exceeds 24MHz, not supported
        status = false;
    }
    
    // Enable DCO frequency trim
    HWREG16(CS_BASE + OFS_CSCTL1) |= DCOFTRIMEN;
    
    // Set proper DCOFTRIM value
    HWREG16(CS_BASE + OFS_CSCTL1) &= ~(DCOFTRIM0 | DCOFTRIM1 | DCOFTRIM2);
    HWREG16(CS_BASE + OFS_CSCTL1) |= (param->csCtl1 & (DCOFTRIM0 | DCOFTRIM1 | DCOFTRIM2));

    // Re-enable FLL
    __bic_SR_register(SCG0);
    
    while ((HWREG16(CS_BASE + OFS_CSCTL7) & (FLLUNLOCK0 | FLLUNLOCK1)) ||
        (HWREG8(CS_BASE + OFS_CSCTL7_L) & DCOFFG))
    {
        //Clear OSC fault flags
        HWREG8(CS_BASE + OFS_CSCTL7_L) &= ~(DCOFFG);

        //Clear OFIFG fault flag
        HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
    }

    // Restore previous SCG0
    __bis_SR_register(srRegisterState);
    
    while (x--)
    {
        __delay_cycles(30);
    }
    // Reapply Oscillator Fault Interrupt Enable if needed
    HWREG8(SFR_BASE + OFS_SFRIE1_L) |= sfr_ofie_status;
    
    return status;
}

void CS_enableClockRequest(uint8_t selectClock
    )
{
    HWREG8(CS_BASE + OFS_CSCTL8) |= selectClock;
}

void CS_disableClockRequest(uint8_t selectClock
    )
{
    HWREG8(CS_BASE + OFS_CSCTL8) &= ~selectClock;
}

uint8_t CS_getFaultFlagStatus(uint8_t mask
    )
{
    return (HWREG8(CS_BASE + OFS_CSCTL7) & mask);
}

void CS_clearFaultFlag(uint8_t mask
    )
{
    HWREG8(CS_BASE + OFS_CSCTL7) &= ~mask;
}

uint32_t CS_getACLK(void)
{
    //Find ACLK source
    uint16_t ACLKSource = (HWREG16(CS_BASE + OFS_CSCTL4) & SELA);

    ACLKSource = ACLKSource >> 8;

    if (ACLKSource == 0x0) {
        ACLKSource = SELMS__XT1CLK;
    }
    else if (ACLKSource == 0x1) {
        ACLKSource = SELMS__REFOCLK;
    }
    else {
        ACLKSource = SELMS__VLOCLK;
    }

    uint16_t ACLKSourceDivider = 0;
#ifdef DIVA0
    if (HWREG16(CS_BASE + OFS_CSCTL6) & XTS) {

        uint16_t div = (HWREG16(CS_BASE + OFS_CSCTL6) &
                (DIVA0|DIVA1|DIVA2|DIVA3)) >>8;
        switch(div) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            ACLKSourceDivider = 8*(1<<div);
            break;
        case 6:
            ACLKSourceDivider = 384;
            break;
        case 7:
            ACLKSourceDivider = 512;
            break;
        case 8:
            ACLKSourceDivider = 768;
            break;
        case 9:
            ACLKSourceDivider = 1024;
            break;
        case 10:
            ACLKSourceDivider = 108;
            break;
        case 11:
            ACLKSourceDivider = 338;
            break;
        case 12:
            ACLKSourceDivider = 414;
            break;
        case 13:
            ACLKSourceDivider = 640;
            break;
        default:
            break;
        }
    }
#endif
    return (privateCSComputeCLKFrequency(
            ACLKSource,
            ACLKSourceDivider,
            CS_ACLK)
            );
}

uint32_t CS_getSMCLK(void)
{
    uint16_t SMCLKSource = HWREG8(CS_BASE + OFS_CSCTL4_L) & SELMS_7;

    uint16_t SMCLKSourceDivider =
        HWREG16(CS_BASE + OFS_CSCTL5) & DIVS_3;
    SMCLKSourceDivider = SMCLKSourceDivider >> 4;

    return (privateCSComputeCLKFrequency(
                SMCLKSource,
                SMCLKSourceDivider,
                CS_SMCLK)
            );
}

uint32_t CS_getMCLK(void)
{
    //Find AMCLK source
    uint16_t MCLKSource = (HWREG16(CS_BASE + OFS_CSCTL4) & SELMS_7);

    uint16_t MCLKSourceDivider =  HWREG16(CS_BASE + OFS_CSCTL5) & DIVM_7;

    return (privateCSComputeCLKFrequency(
                MCLKSource,
                MCLKSourceDivider,
                CS_MCLK)
            );
}

uint16_t CS_clearAllOscFlagsWithTimeout( uint16_t timeout){
    do {
      // Clear all osc fault flags
      HWREG8(CS_BASE + OFS_CSCTL7) &= ~(DCOFFG | XT1OFFG);

      // Clear the global osc fault flag.
      HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
      
      // Check XT1 fault flags
    } while ((HWREG8(SFR_BASE + OFS_SFRIFG1) & OFIFG) && --timeout);

    return (HWREG8(CS_BASE + OFS_CSCTL7) & (DCOFFG | XT1OFFG));
}

void CS_enableXT1AutomaticGainControl(void)
{
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1AGCOFF;
}

void CS_disableXT1AutomaticGainControl(void)
{
    HWREG16(CS_BASE + OFS_CSCTL6) |= XT1AGCOFF;
}

void CS_enableFLLUnlock(void)
{
    HWREG16(CS_BASE + OFS_CSCTL7) |= FLLULPUC;
}

void CS_disableFLLUnlock(void)
{
    HWREG16(CS_BASE + OFS_CSCTL7) &= ~FLLULPUC;
}

void CS_enableREFOLP(void)
{
#ifdef REFOLP
    HWREG16(CS_BASE + OFS_CSCTL3) |= REFOLP;
#endif
}

void CS_disableREFOLP(void)
{
#ifdef REFOLP
    HWREG16(CS_BASE + OFS_CSCTL3) &= ~REFOLP;
#endif
}

bool CS_getREFOLP(void)
{
#ifdef REFOLP
    return ((HWREG16(CS_BASE + OFS_CSCTL3) & REFOLP) ? true : false);
#else
    return false;
#endif
}

void CS_enableXT1FaultOff(void)
{
#ifdef XT1FAULTOFF
    HWREG16(CS_BASE + OFS_CSCTL6) |= XT1FAULTOFF;
#endif
}

void CS_disableXT1FaultOff(void)
{
#ifdef XT1FAULTOFF
    HWREG16(CS_BASE + OFS_CSCTL6) &= ~XT1FAULTOFF;
#endif
}

bool CS_getXT1FaultOff(void)
{
#ifdef XT1FAULTOFF
    return ((HWREG16(CS_BASE + OFS_CSCTL6) & XT1FAULTOFF) ? true : false);
#else
    return false;
#endif
}

bool CS_getREFOReady(void)
{
#ifdef REFOREADY
    return ((HWREG16(CS_BASE + OFS_CSCTL7) & REFOREADY) ? true : false);
#else
    return false;
#endif
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for cs_api
//! @}
//
//*****************************************************************************
