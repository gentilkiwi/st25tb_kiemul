//*****************************************************************************
//
// mcu.c - MCU Configuration and host interface APIs
//
// Copyright (c) 2015 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************
// Include Header Files
#include "mcu.h"
#include "gpio.h"

#include "inc/hw_memmap.h"
#include "wdt_a.h"
#include "timer_a.h"
#include "sfr.h"
#include "ucs.h"
#include "pmm.h"

volatile uint8_t * g_timeout_ptr;
uint32_t g_ui32RemainingTime;
volatile uint8_t g_ui8TimeoutFlag;
uint8_t g_ui8TimeoutF;

static void Init_FLL(unsigned int fsystem, unsigned int ratio) {
	unsigned int d, dco_div_bits;
	unsigned int mode = 0;

	// Save actual state of FLL loop control, then disable it. This is needed to
	// prevent the FLL from acting as we are making fundamental modifications to
	// the clock setup.
	unsigned int srRegisterState = __get_SR_register() & SCG0;
	__bic_SR_register(SCG0); d
	= ratio;
	dco_div_bits = FLLD__2;        // Have at least a divider of 2

	if (fsystem > 16000) {
		d >>= 1;
		mode = 1;
	} else {
		fsystem <<= 1;               // fsystem = fsystem * 2
	}

	while (d > 512) {
		dco_div_bits = dco_div_bits + FLLD0;  // Set next higher div level
		d >>= 1;
	}

	UCSCTL0 = 0x0000;              // Set DCO to lowest Tap

	UCSCTL2 &= ~(0x03FF);          // Reset FN bits
	UCSCTL2 = dco_div_bits | (d - 1);

	if (fsystem <= 630)            //           fsystem < 0.63MHz
		UCSCTL1 = DCORSEL_0;
	else if (fsystem < 1250)      // 0.63MHz < fsystem < 1.25MHz
		UCSCTL1 = DCORSEL_1;
	else if (fsystem < 2500)      // 1.25MHz < fsystem <  2.5MHz
		UCSCTL1 = DCORSEL_2;
	else if (fsystem < 5000)      // 2.5MHz  < fsystem <    5MHz
		UCSCTL1 = DCORSEL_3;
	else if (fsystem < 10000)     // 5MHz    < fsystem <   10MHz
		UCSCTL1 = DCORSEL_4;
	else if (fsystem < 20000)     // 10MHz   < fsystem <   20MHz
		UCSCTL1 = DCORSEL_5;
	else if (fsystem < 40000)     // 20MHz   < fsystem <   40MHz
		UCSCTL1 = DCORSEL_6;
	else
		UCSCTL1 = DCORSEL_7;

	while (SFRIFG1 & OFIFG) {                          // Check OFIFG fault flag
		UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT1HFOFFG + XT2OFFG); // Clear OSC flaut Flags
		SFRIFG1 &= ~OFIFG;                             // Clear OFIFG fault flag
	}

	if (mode == 1) {                              		  // fsystem > 16000
		SELECT_MCLK_SMCLK(SELM__DCOCLK + SELS__DCOCLK);
		// Select DCOCLK
	} else {
		SELECT_MCLK_SMCLK(SELM__DCOCLKDIV + SELS__DCOCLKDIV);
		// Select DCODIVCLK
	}

	__bis_SR_register(srRegisterState);	                // Restore previous SCG0
}


static void Init_FLL_Settle(unsigned int fsystem, unsigned int ratio) {
	volatile unsigned int x = ratio * 32;

	Init_FLL(fsystem, ratio);

	while (x--) {
		__delay_cycles(30);
	}
}

/*******************************************************************************
 * \brief   Increase Vcore by one level
 *
 * \param level     Level to which Vcore needs to be increased
 * \return status   Success/failure
 ******************************************************************************/
static unsigned int SetVCoreUp(unsigned int level) {
	unsigned int PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;

	// The code flow for increasing the Vcore has been altered to work around
	// the erratum FLASH37.
	// Please refer to the Errata sheet to know if a specific device is affected
	// DO NOT ALTER THIS FUNCTION

	// Open PMM registers for write access
	PMMCTL0_H = 0xA5;

	// Disable dedicated Interrupts
	// Backup all registers
	PMMRIE_backup = PMMRIE;
	PMMRIE &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE | SVSLPE | SVMHVLRIE | SVMHIE
			| SVSMHDLYIE | SVMLVLRIE | SVMLIE | SVSMLDLYIE);
	SVSMHCTL_backup = SVSMHCTL;
	SVSMLCTL_backup = SVSMLCTL;

	// Clear flags
	PMMIFG = 0;

	// Set SVM highside to new level and check if a VCore increase is possible
	SVSMHCTL = SVMHE | SVSHE | (SVSMHRRL0 * level);

	// Wait until SVM highside is settled
	while ((PMMIFG & SVSMHDLYIFG) == 0)
		;

	// Clear flag
	PMMIFG &= ~SVSMHDLYIFG;

	// Check if a VCore increase is possible
	if ((PMMIFG & SVMHIFG) == SVMHIFG) { // -> Vcc is too low for a Vcore increase
		// recover the previous settings
		PMMIFG &= ~SVSMHDLYIFG;
		SVSMHCTL = SVSMHCTL_backup;

		// Wait until SVM highside is settled
		while ((PMMIFG & SVSMHDLYIFG) == 0)
			;

		// Clear all Flags
		PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG
				| SVSMLDLYIFG);

		PMMRIE = PMMRIE_backup;         // Restore PMM interrupt enable register
		PMMCTL0_H = 0x00;                 // Lock PMM registers for write access
		return PMM_STATUS_ERROR;                // return: voltage not set
	}

	// Set also SVS highside to new level
	// Vcc is high enough for a Vcore increase
	SVSMHCTL |= (SVSHRVL0 * level);

	// Wait until SVM highside is settled
	while ((PMMIFG & SVSMHDLYIFG) == 0)
		;

	// Clear flag
	PMMIFG &= ~SVSMHDLYIFG;

	// Set VCore to new level
	PMMCTL0_L = PMMCOREV0 * level;

	// Set SVM, SVS low side to new level
	SVSMLCTL = SVMLE | (SVSMLRRL0 * level) | SVSLE | (SVSLRVL0 * level);

	// Wait until SVM, SVS low side is settled
	while ((PMMIFG & SVSMLDLYIFG) == 0)
		;

	// Clear flag
	PMMIFG &= ~SVSMLDLYIFG;
	// SVS, SVM core and high side are now set to protect for the new core level

	// Restore Low side settings
	// Clear all other bits _except_ level settings
	SVSMLCTL &= (SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

	// Clear level settings in the backup register,keep all other bits
	SVSMLCTL_backup &=
			~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

	// Restore low-side SVS monitor settings
	SVSMLCTL |= SVSMLCTL_backup;

	// Restore High side settings
	// Clear all other bits except level settings
	SVSMHCTL &= (SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

	// Clear level settings in the backup register,keep all other bits
	SVSMHCTL_backup &=
			~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

	// Restore backup
	SVSMHCTL |= SVSMHCTL_backup;

	// Wait until high side, low side settled
	while (((PMMIFG & SVSMLDLYIFG) == 0) && ((PMMIFG & SVSMHDLYIFG) == 0))
		;

	// Clear all Flags
	PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG
			| SVSMLDLYIFG);

	PMMRIE = PMMRIE_backup;             // Restore PMM interrupt enable register
	PMMCTL0_H = 0x00;                     // Lock PMM registers for write access

	return PMM_STATUS_OK;
}

/*******************************************************************************
 * \brief  Decrease Vcore by one level
 *
 * \param  level    Level to which Vcore needs to be decreased
 * \return status   Success/failure
 ******************************************************************************/
static unsigned int SetVCoreDown(unsigned int level) {
	unsigned int PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;

	// The code flow for decreasing the Vcore has been altered to work around
	// the erratum FLASH37.
	// Please refer to the Errata sheet to know if a specific device is affected
	// DO NOT ALTER THIS FUNCTION

	// Open PMM registers for write access
	PMMCTL0_H = 0xA5;

	// Disable dedicated Interrupts
	// Backup all registers
	PMMRIE_backup = PMMRIE;
	PMMRIE &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE | SVSLPE | SVMHVLRIE | SVMHIE
			| SVSMHDLYIE | SVMLVLRIE | SVMLIE | SVSMLDLYIE);
	SVSMHCTL_backup = SVSMHCTL;
	SVSMLCTL_backup = SVSMLCTL;

	// Clear flags
	PMMIFG &= ~(SVMHIFG | SVSMHDLYIFG | SVMLIFG | SVSMLDLYIFG);

	// Set SVM, SVS high & low side to new settings in normal mode
	SVSMHCTL = SVMHE | (SVSMHRRL0 * level) | SVSHE | (SVSHRVL0 * level);
	SVSMLCTL = SVMLE | (SVSMLRRL0 * level) | SVSLE | (SVSLRVL0 * level);

	// Wait until SVM high side and SVM low side is settled
	while ((PMMIFG & SVSMHDLYIFG) == 0 || (PMMIFG & SVSMLDLYIFG) == 0)
		;

	// Clear flags
	PMMIFG &= ~(SVSMHDLYIFG + SVSMLDLYIFG);
	// SVS, SVM core and high side are now set to protect for the new core level

	// Set VCore to new level
	PMMCTL0_L = PMMCOREV0 * level;

	// Restore Low side settings
	// Clear all other bits _except_ level settings
	SVSMLCTL &= (SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

	// Clear level settings in the backup register,keep all other bits
	SVSMLCTL_backup &=
			~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

	// Restore low-side SVS monitor settings
	SVSMLCTL |= SVSMLCTL_backup;

	// Restore High side settings
	// Clear all other bits except level settings
	SVSMHCTL &= (SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

	// Clear level settings in the backup register, keep all other bits
	SVSMHCTL_backup &=
			~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

	// Restore backup
	SVSMHCTL |= SVSMHCTL_backup;

	// Wait until high side, low side settled
	while (((PMMIFG & SVSMLDLYIFG) == 0) && ((PMMIFG & SVSMHDLYIFG) == 0))
		;

	// Clear all Flags
	PMMIFG &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG
			| SVSMLDLYIFG);

	PMMRIE = PMMRIE_backup;             // Restore PMM interrupt enable register
	PMMCTL0_H = 0x00;                     // Lock PMM registers for write access
	return PMM_STATUS_OK;		                // Return: OK
}
static unsigned int SetVCore(unsigned int level) {
	unsigned int actlevel;
	unsigned int status = 0;

	level &= PMMCOREV_3;                       // Set Mask for Max. level
	actlevel = (PMMCTL0 & PMMCOREV_3);         // Get actual VCore
											   // step by step increase or decrease
	while (((level != actlevel) && (status == 0)) || (level < actlevel)) {
		if (level > actlevel) {
			status = SetVCoreUp(++actlevel);
		} else {
			status = SetVCoreDown(--actlevel);
		}
	}

	return status;
}
static void LFXT_Start(unsigned int xtdrive) {
	// If the drive setting is not already set to maximum
	// Set it to max for LFXT startup
	if ((UCSCTL6 & XT1DRIVE_3) != XT1DRIVE_3) {
		UCSCTL6_L |= XT1DRIVE1_L + XT1DRIVE0_L; // Highest drive setting for XT1startup
	}

	while (SFRIFG1 & OFIFG) {   // Check OFIFG fault flag
		UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT1HFOFFG + XT2OFFG); // Clear OSC flaut Flags fault flags
		SFRIFG1 &= ~OFIFG;        // Clear OFIFG fault flag
	}

	UCSCTL6 = (UCSCTL6 & ~(XT1DRIVE_3)) | (xtdrive); // set requested Drive mode
}

/**
 * @brief <b>Function Name</b>: MCU_init
 * @brief <b>Description</b>: Initialize MSP430, such as Clock, Port, MPU and
 * System Time.
 * @param Input value: None
 * @return Return value:None
 **/
void MCU_init(void)
{
    WDT_A_hold(WDT_A_BASE);

	// Setup XT1 and XT2
	XT1_XT2_PORT_SEL |= XT1_ENABLE + XT2_ENABLE;

	// Set Vcore to accomodate for max. allowed system speed
	SetVCore(3);

	// Use 32.768kHz XTAL as reference
	LFXT_Start(XT1DRIVE_0);

	// MCU Frequency = 25MHz
	Init_FLL_Settle(MCLK_MS_COUNT, 762);
}

//===============================================================
// NAME: void McuDelayMillisecond (uint8_t n_ms)
//
// BRIEF: Is used to create delays.
//
// INPUTS:
//    Parameters:
//        uint8_t        n_ms        delay time in ms.
//
// OUTPUTS:
//
// PROCESS:    [1] do loop of 1 ms duration as often as required
//
// CHANGE:
// DATE          WHO    DETAIL
// 23Nov2010    RP    Original Code
//===============================================================

void MCU_delayMillisecond(uint32_t n_ms)
{
    Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_ACLK,
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1,
        .timerPeriod = 0,
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = true,
    };

	g_ui32RemainingTime = n_ms;

	g_timeout_ptr = (uint8_t *) &g_ui8TimeoutFlag;

	while(g_ui32RemainingTime > 0)
	{
		if(g_ui32RemainingTime > 1985)
		{
			g_ui32RemainingTime = n_ms - 1985;
			n_ms = 1985;
		}
		else
		{
			n_ms = g_ui32RemainingTime;
			g_ui32RemainingTime = 0x00;
		}

		// Clear Flag
		*g_timeout_ptr = 0x00;

		Timer_A_clearTimerInterrupt(TIMER_A0_BASE);

		//Start timer in up mode sourced by SMCLK
		param.timerPeriod = (n_ms*33);
		Timer_A_initUpMode(TIMER_A0_BASE, &param);

		// Wait until Flag is set
		while(*g_timeout_ptr != 0x01)
		{
			//
			// Enable Low Power Mode 0
			//
			__bis_SR_register(LPM0_bits);
		}
		MCU_timerDisable();
	}
}


void MCU_delayMicrosecond(uint32_t n_us)
{
    Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_24,
        .timerPeriod = 0,
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = true,
    };

	g_ui32RemainingTime = n_us;

	g_timeout_ptr = (uint8_t *) &g_ui8TimeoutFlag;

	while(g_ui32RemainingTime > 0)
	{
		if(g_ui32RemainingTime > 65535)
		{
			g_ui32RemainingTime = n_us - 65535;
			n_us = 65535;
		}
		else
		{
			n_us = g_ui32RemainingTime;
			g_ui32RemainingTime = 0x00;
		}

		// Clear Flag
		*g_timeout_ptr = 0x00;

		Timer_A_clearTimerInterrupt(TIMER_A0_BASE);

		//Start timer in up mode sourced by SMCLK
		param.timerPeriod = (n_us);
		Timer_A_initUpMode(TIMER_A0_BASE, &param);

		// Wait until Flag is set
		while(*g_timeout_ptr != 0x01)
		{
			//
			// Enable Low Power Mode 0
			//
			__bis_SR_register(LPM0_bits);
		}
		MCU_timerDisable();
	}
}

/**
 * @brief <b>Function Name</b>: Clock_init
 * @brief <b>Description</b>: This function to initialize MSP430 clock, to set
 * MCLK and SMCLK to 1MHz.For MSP430FR5969, set ACLK = LFXT1 = 32768Hz, so
 * External watch crystal installed on XIN XOUT is required for ACLK.
 * @param Input Parameters: None
 * @return Return Values: None
 * @note External watch crystal installed on XIN XOUT is required for ACLK,By
 * default, the MSP430 uses XT1 to source ACLK.
 **/
void MCU_clockInit()
{

}


/**
 * @brief <b>Function Name</b>: Port_init
 * @brief <b>Description</b>: This function to initialize MSP430 Port Pins to I/O.
 * Initializes the unused pins as outputs for low power consumption.
 * @param Input Parameters: None
 * @return Return Values: None
 **/
void MCU_portInit()
{

}

/**
 * @brief <b>Function Name</b>: Timer_init
 * @brief <b>Description</b>:
 * This function to initialize MSP430 Timer. Set SMCLK as Timer clock source,
 * and then set CCR0 as upmode, enable CCr0 interrupt and it will go to related
 * interrupt every 0.5s.
 * @param Input Parameters:
 * uint16_t timeout_ms has a maximum value of 8191 mS = 8.1 seconds
 * uint8_t * timeout_flag is the flag to set if the time is elapsed.
 * @return Return Values: None
 **/
void MCU_timerInit(uint16_t timeout_ms, uint8_t * timeout_flag)
{
    Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_ACLK,
        .clockSourceDivider = 0,
        .timerPeriod = 0,
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = false,
    };

	g_timeout_ptr = (uint8_t *) timeout_flag;

	// Clear Flag
	*g_timeout_ptr = 0x00;

	Timer_A_clearTimerInterrupt(TIMER_A0_BASE);

	if(timeout_ms == 0x00)
	{
		*timeout_flag = 0x01;
		return;
	}
	else if(timeout_ms > 8190)
	{
		// Error
		*timeout_flag = 0x01;
		return;
	}
	else if(timeout_ms < 1985)
	{
		//Start timer in up mode sourced by SMCLK
	    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	    param.timerPeriod = (timeout_ms*33);
	    Timer_A_initUpMode(TIMER_A0_BASE, &param);
	}
//	else if(timeout_ms < 4095)
//	{
//		//Start timer in up mode sourced by SMCLK
//		TIMER_A_configureUpMode(TIMER_A0_BASE,
//								TIMER_A_CLOCKSOURCE_ACLK,
//								TIMER_A_CLOCKSOURCE_DIVIDER_2,
//								(timeout_ms*16),
//								TIMER_A_TAIE_INTERRUPT_ENABLE,
//								TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
//								TIMER_A_DO_CLEAR);
//	}
	else if(timeout_ms < 5957)
	{
		//Start timer in up mode sourced by SMCLK
        param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_3;
        param.timerPeriod = (timeout_ms*11);
        Timer_A_initUpMode(TIMER_A0_BASE, &param);
	}
	else if(timeout_ms < 8191)
	{
		//Start timer in up mode sourced by SMCLK
        param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
        param.timerPeriod = (timeout_ms*8);
        Timer_A_initUpMode(TIMER_A0_BASE, &param);
	}

	Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

void MCU_timerDisable(void)
{
    Timer_A_disableInterrupt(TIMER_A0_BASE);
    Timer_A_stop(TIMER_A0_BASE);
}

#pragma vector= TIMER0_A1_VECTOR
__interrupt void TIMERA0_ISR (void)
{
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
	*g_timeout_ptr = 0x01;
//	MCU_timerDisable();
	__bic_SR_register_on_exit(LPM0_bits);
}
