#include "bp-trf7970a.h"
#include "trf7970a.h"

void BP_LED_init()
{
    LED_OFF(BP_LED2);
    LED_OFF(BP_LED3);
    LED_OFF(BP_LED4);
    GPIO_setAsOutputPin(BP_LED2);
    GPIO_setAsOutputPin(BP_LED3);
    GPIO_setAsOutputPin(BP_LED4);
}

void BP_SPI_GPIO_init()
{
    LP_SPI_init(BP_TRF_SPI_FREQ);

    BP_TRF_SPI_CS_DISABLE();
    GPIO_setAsOutputPin(BP_TRF_SPI_CS);

    BP_TRF_EN_DISABLE();
    GPIO_setAsOutputPin(BP_TRF_EN);
    LP_delayMillisecond(10);
    BP_TRF_EN_ENABLE();

    GPIO_setAsInputPin(BP_TRF_IRQ);
    GPIO_selectInterruptEdge(BP_TRF_IRQ, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_clearInterrupt(BP_TRF_IRQ);
    GPIO_enableInterrupt(BP_TRF_IRQ);
}

void BP_init()
{
    BP_LED_init();
    BP_SPI_GPIO_init();
}

uint8_t BP_Wait_for_Buttons_or_TRF7970A(uint8_t *pTRF7970A_irqStatus)
{
    uint8_t ret = BP_IRQ_SOURCE_NONE;

    g_trf7970a_irq_flag = GPIO_getInputPinValue(BP_TRF_IRQ); // because sometimes it's already in IRQ
    while(!g_trf7970a_irq_flag && !g_button_LP_S1_pressed && !g_button_LP_S2_pressed)
    {
        __low_power_mode_0();
    }

    if(g_trf7970a_irq_flag)
    {
        g_trf7970a_irq_flag = false;
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        ret |= BP_IRQ_SOURCE_TRF7970A;
    }

    if(g_button_LP_S1_pressed)
    {
        g_button_LP_S1_pressed = false;
        ret |= BP_IRQ_SOURCE_LP_S1;
    }

    if(g_button_LP_S2_pressed)
    {
        g_button_LP_S2_pressed = false;
        ret |= BP_IRQ_SOURCE_LP_S2;
    }

    return ret;
}

uint8_t BP_Wait_for_Buttons_or_TRF7970A_or_Timeout(uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms)
{
    uint8_t ret = BP_IRQ_SOURCE_NONE;

    g_trf7970a_irq_flag = GPIO_getInputPinValue(BP_TRF_IRQ); // because sometimes it's already in IRQ

    LP_timerInit(timeout_ms);
    while(!g_trf7970a_irq_flag && !g_irq_Timer_TimeOut && !g_button_LP_S1_pressed && !g_button_LP_S2_pressed)
    {
        __low_power_mode_0();
    }

    if(g_trf7970a_irq_flag)
    {
        g_trf7970a_irq_flag = false;
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        ret |= BP_IRQ_SOURCE_TRF7970A;
    }

    if(g_button_LP_S1_pressed)
    {
        g_button_LP_S1_pressed = false;
        ret |= BP_IRQ_SOURCE_LP_S1;
    }

    if(g_button_LP_S2_pressed)
    {
        g_button_LP_S2_pressed = false;
        ret |= BP_IRQ_SOURCE_LP_S2;
    }

    if(g_irq_Timer_TimeOut)
    {
        ret |= BP_IRQ_SOURCE_TIMER;
    }
    LP_timerDisable(); // implicit false

    return ret;
}

uint8_t BP_Wait_for_Buttons()
{
    uint8_t ret = BP_IRQ_SOURCE_NONE;

    while(!g_button_LP_S1_pressed && !g_button_LP_S2_pressed)
    {
        __low_power_mode_0();
    }

    if(g_button_LP_S1_pressed)
    {
        g_button_LP_S1_pressed = false;
        ret |= BP_IRQ_SOURCE_LP_S1;
    }

    if(g_button_LP_S2_pressed)
    {
        g_button_LP_S2_pressed = false;
        ret |= BP_IRQ_SOURCE_LP_S2;
    }

    return ret;
}
