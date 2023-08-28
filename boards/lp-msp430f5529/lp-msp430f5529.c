#include "lp-msp430f5529.h"

volatile bool g_irq_Timer_TimeOut;

void LP_CLOCK_init()
{
    //UCS_setExternalClockSource(XT1_FREQ, XT2_FREQ);
    GPIO_setAsPeripheralModuleFunctionOutputPin(LP_XT1_OUT);
    GPIO_setAsPeripheralModuleFunctionInputPin(LP_XT1_IN);
    UCS_turnOnLFXT1(XT1DRIVE_0, UCS_XCAP_3);
    //GPIO_setAsPeripheralModuleFunctionOutputPin(XT2_OUT);
    //GPIO_setAsPeripheralModuleFunctionInputPin(XT2_IN);
    //UCS_turnOnXT2(UCS_XT2_DRIVE_4MHZ_8MHZ);
    UCS_initFLLSettle(LP_MCU_FREQ / 1000, LP_MCU_FREQ / LP_XT1_FREQ);
}

void LP_LED_init()
{
    LED_OFF(LP_LED1);
    LED_OFF(LP_LED2);


    GPIO_setAsOutputPin(LP_LED1);
    GPIO_setAsOutputPin(LP_LED2);


}

void LP_BUTTON_init(bool bIsInterrupt)
{
    GPIO_setAsInputPinWithPullUpResistor(LP_S1);
    GPIO_setAsInputPinWithPullUpResistor(LP_S2);

    if(bIsInterrupt)
    {
        GPIO_selectInterruptEdge(LP_S1, GPIO_HIGH_TO_LOW_TRANSITION);
        GPIO_clearInterrupt(LP_S1);
        GPIO_selectInterruptEdge(LP_S2, GPIO_HIGH_TO_LOW_TRANSITION);
        GPIO_clearInterrupt(LP_S2);
    }
}

void LP_init()
{
    WDT_A_hold(WDT_A_BASE);
    PMM_setVCore(PMM_CORE_LEVEL_3);

    LP_CLOCK_init();
    LP_LED_init();
    LP_BUTTON_init(true);
}

void LP_timerInit(uint16_t timeout_ms) // Max ~ 8s
{
    Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_ACLK,
        .clockSourceDivider = 0,
        .timerPeriod = timeout_ms,
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = false,
    };

    if((!timeout_ms) || (timeout_ms > 8190))
    {
        g_irq_Timer_TimeOut = true;
        return;
    }
    else if(timeout_ms < 1985)
    {
        param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
        param.timerPeriod *= 33;
    }
    else if(timeout_ms < 5957)
    {
        param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_3;
        param.timerPeriod *= 11;
    }
    else if(timeout_ms < 8191)
    {
        param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
        param.timerPeriod *= 8;
    }

    g_irq_Timer_TimeOut = false;
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
    Timer_A_initUpMode(TIMER_A0_BASE, &param);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

void LP_timerDisable()
{
    Timer_A_disableInterrupt(TIMER_A0_BASE);
    Timer_A_stop(TIMER_A0_BASE);
}

void LP_delayMillisecond(uint32_t n_ms)
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
    uint32_t remainingTime = n_ms;

    while(remainingTime)
    {
        if(remainingTime > 1985) // 1985 * 33 = ~ MAX 16 bits
        {
            remainingTime -= 1985;
            n_ms = 1985;
        }
        else
        {
            n_ms = remainingTime;
            remainingTime = 0;
        }

        param.timerPeriod = n_ms * 33; // ~(XT1_FREQ * 0.001) at DIVIDER_1

        g_irq_Timer_TimeOut = false;
        Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
        Timer_A_initUpMode(TIMER_A0_BASE, &param);
        while(!g_irq_Timer_TimeOut)
        {
            __low_power_mode_0();
        }
        LP_timerDisable();
    }
}

void LP_delayMicrosecond(uint32_t n_us)
{
    Timer_A_initUpModeParam param = {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK, // ACLK is not good enough
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_5, // at 25 Mhz -> 5
        .timerPeriod = 0,
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = true,
    };
    uint32_t g_ui32RemainingTime = n_us;

    while(g_ui32RemainingTime)
    {
        if(g_ui32RemainingTime > 13107) // 13107 * 5 = ~ MAX 16 bits
        {
            g_ui32RemainingTime -= 13107;
            n_us = 13107;
        }
        else
        {
            n_us = g_ui32RemainingTime;
            g_ui32RemainingTime = 0;
        }

        param.timerPeriod = n_us * 5;

        g_irq_Timer_TimeOut = false;
        Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
        Timer_A_initUpMode(TIMER_A0_BASE, &param);

        while(!g_irq_Timer_TimeOut)
        {
            __low_power_mode_0();
        }
        LP_timerDisable();
    }
}

void LP_SPI_init(uint32_t desiredSpiClock)
{
    USCI_B_SPI_initMasterParam param = {
        .selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK,
        .clockSourceFrequency = LP_MCU_FREQ,
        .desiredSpiClock = desiredSpiClock,
        .msbFirst = USCI_B_SPI_MSB_FIRST,
        .clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
        .clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW

    };

    GPIO_setAsPeripheralModuleFunctionOutputPin(LP_BP_HEADER_SPI_CLK);
    GPIO_setAsPeripheralModuleFunctionOutputPin(LP_BP_HEADER_SPI_MOSI);
    GPIO_setAsPeripheralModuleFunctionInputPin(LP_BP_HEADER_SPI_MISO);

    USCI_B_SPI_initMaster(USCI_B0_BASE, &param);
    USCI_B_SPI_enable(USCI_B0_BASE);
}

void LP_SPI_sendByte(uint8_t data)
{
    USCI_B_SPI_transmitData(USCI_B0_BASE, data);
    while (USCI_B_SPI_isBusy(USCI_B0_BASE));
}

uint8_t LP_SPI_receiveByte()
{
    LP_SPI_sendByte(0x00);
    return USCI_B_SPI_receiveData(USCI_B0_BASE);
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMERA0_ISR (void)
{
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
    g_irq_Timer_TimeOut = true;
    __low_power_mode_off_on_exit();
}

#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    switch(P2IV)
    {
        case P2IV_P2IFG1:
            g_button_LP_S1_pressed = true;
            __low_power_mode_off_on_exit();

            break;

        case P2IV_P2IFG2:
            g_trf7970a_irq_flag = true;
            __low_power_mode_off_on_exit();

            break;

        default:

            break;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
    switch(P1IV)
    {
        case P1IV_P1IFG1:
            g_button_LP_S2_pressed = true;
            __low_power_mode_off_on_exit();

            break;

        default:

            break;
    }
}
