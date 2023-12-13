/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "lp-msp430fr2476.h"

void LP_CLOCK_init()
{
    //UCS_setExternalClockSource(XT1_FREQ, XT2_FREQ); ??
    //GPIO_setAsPeripheralModuleFunctionOutputPin(LP_XT1_OUT, GPIO_PRIMARY_MODULE_FUNCTION);
    //GPIO_setAsPeripheralModuleFunctionInputPin(LP_XT1_IN, GPIO_PRIMARY_MODULE_FUNCTION);
    //CS_turnOnXT1LF(XT1DRIVE_0);



    CS_initFLLSettle(LP_MCU_FREQ / 1000, LP_MCU_FREQ / LP_XT1_FREQ);
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
    PMM_unlockLPM5();

    LP_CLOCK_init();
    LP_LED_init();
    LP_BUTTON_init(true);
}

void LP_SPI_init(uint32_t desiredSpiClock)
{
    EUSCI_B_SPI_initMasterParam param = {
        .selectClockSource = EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
        .clockSourceFrequency = LP_MCU_FREQ,
        .desiredSpiClock = desiredSpiClock,
        .msbFirst = EUSCI_B_SPI_MSB_FIRST,
        .clockPhase = EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
        .clockPolarity = EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
        .spiMode = EUSCI_B_SPI_3PIN
    };

    GPIO_setAsPeripheralModuleFunctionOutputPin(LP_BP_HEADER_SPI_CLK, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(LP_BP_HEADER_SPI_MOSI, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(LP_BP_HEADER_SPI_MISO, GPIO_PRIMARY_MODULE_FUNCTION);

    EUSCI_B_SPI_initMaster(EUSCI_B1_BASE, &param);
    EUSCI_B_SPI_enable(EUSCI_B1_BASE);
}

void LP_SPI_sendByte(uint8_t data)
{
    EUSCI_B_SPI_transmitData(EUSCI_B1_BASE, data);
    while (EUSCI_B_SPI_isBusy(EUSCI_B1_BASE));
}

uint8_t LP_SPI_receiveByte()
{
    LP_SPI_sendByte(0x00);
    return EUSCI_B_SPI_receiveData(EUSCI_B1_BASE);
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
            g_trf7970a_irq_flag = true;
            __low_power_mode_off_on_exit();

            break;

        case P2IV_P2IFG3:
            g_button_LP_S2_pressed = true;
            __low_power_mode_off_on_exit();

            break;

        default:

            break;
    }
}

#pragma vector=PORT4_VECTOR
__interrupt void Port4_ISR(void)
{
    switch(P4IV)
    {
        case P4IV_P4IFG0:
            g_button_LP_S1_pressed = true;
            __low_power_mode_off_on_exit();

            break;

        default:

            break;
    }
}
