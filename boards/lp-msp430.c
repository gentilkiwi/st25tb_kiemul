/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "lp-msp430.h"

volatile bool g_button_LP_S1_pressed = false, g_button_LP_S2_pressed = false, g_irq_Timer_TimeOut;

void LP_LED_init()
{
    LED_OFF(LP_LED1);
    LED_OFF(LP_LED2);
    GPIO_setAsOutputPin(LP_LED1);
    GPIO_setAsOutputPin(LP_LED2);
}

void LP_BUTTON_WaitFor_LP_S1()
{
    g_button_LP_S1_pressed = false;
    GPIO_clearInterrupt(LP_S1);
    GPIO_enableInterrupt(LP_S1);

    while(!g_button_LP_S1_pressed)
    {
        __low_power_mode_0();
    }

    GPIO_disableInterrupt(LP_S1);
}

void LP_BUTTON_WaitFor_LP_S2()
{
    g_button_LP_S2_pressed = false;
    GPIO_clearInterrupt(LP_S2);
    GPIO_enableInterrupt(LP_S2);

    while(!g_button_LP_S2_pressed)
    {
        __low_power_mode_0();
    }

    GPIO_disableInterrupt(LP_S2);
}

bool LP_BUTTON_WaitFor_LP_S1_or_LP_S2() // LP_S1, true, LP_S2, false
{
    g_button_LP_S1_pressed = false;
    g_button_LP_S2_pressed = false;
    GPIO_clearInterrupt(LP_S1);
    GPIO_clearInterrupt(LP_S2);
    GPIO_enableInterrupt(LP_S1);
    GPIO_enableInterrupt(LP_S2);

   while(!g_button_LP_S1_pressed && !g_button_LP_S2_pressed)
   {
       __low_power_mode_0();
   }

   GPIO_disableInterrupt(LP_S1);
   GPIO_disableInterrupt(LP_S2);

   return g_button_LP_S1_pressed; // false if S2
}

void LP_TIMER_Disable()
{
    Timer_A_disableInterrupt(TIMER_A0_BASE);
    Timer_A_stop(TIMER_A0_BASE);
}

void LP_TIMER_StartTimer_internal(uint16_t n_unit_ms) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
{
    static Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_ACLK,
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1,
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = true,
    };
    param.timerPeriod = n_unit_ms,
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
    g_irq_Timer_TimeOut = false;
    Timer_A_initUpMode(TIMER_A0_BASE, &param);
}

void LP_TIMER_delay_Millisecond_internal(uint16_t n_unit_ms) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
{
    static Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_ACLK,
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1,
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = true,
    };
    param.timerPeriod = n_unit_ms;
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
    g_irq_Timer_TimeOut = false;
    Timer_A_initUpMode(TIMER_A0_BASE, &param);
    while(!g_irq_Timer_TimeOut)
    {
        __low_power_mode_0();
    }
    LP_TIMER_Disable();
}

void LP_TIMER_delay_Microsecond_internal(uint16_t n_unit_us) // max is UINT16_MAX
{
    static Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK, // ACLK is not good enough
        .clockSourceDivider = LP_TIMER_A_MICRO_DIVISOR, // see implementations
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = true,
    };
    param.timerPeriod = n_unit_us;
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
    g_irq_Timer_TimeOut = false;
    Timer_A_initUpMode(TIMER_A0_BASE, &param);
    while(!g_irq_Timer_TimeOut)
    {
        __low_power_mode_0();
    }
    LP_TIMER_Disable();
}
