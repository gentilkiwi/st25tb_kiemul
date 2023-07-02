#include <driverlib.h>
#include "led.h"
#include "trf79x0.h"
#include "st25tb.h"

void main(void)
{
    tTRF79x0_Mode Mode = Target, oldMode = Initiator;
    tTRF79x0_IRQFlag irqFlag;
    uint8_t ui8RxBuffer[2], ui8NFCTargetProtocol;
    bool bIsEqual;

    MCU_init();
    LED_init();
    ST25TB_Target_Init();

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

    __enable_interrupt();
    TRF79x0_init();

    while (true)
    {
        switch (Mode)
        {
        case Target:

            if (oldMode != Target)
            {
                oldMode = Target;
                LED_ON(LED1);
            }

            ST25TB_Target_ResetState();

            TRF79x0_directCommand(TRF79X0_SOFT_INIT_CMD);
            TRF79x0_directCommand(TRF79X0_IDLE_CMD);

            TRF79x0_writeSingle(0x25, TRF79X0_ISO_CONTROL_REG);
            TRF79x0_writeSingle(0xf0, TRF79X0_RX_SPECIAL_SETTINGS_REG); // test 0 ?
            TRF79x0_writeSingle(TRF79X0_STATUS_CTRL_RF_ON, TRF79X0_CHIP_STATUS_CTRL_REG);
            TRF79x0_writeSingle(TRF79X0_MOD_CTRL_MOD_ASK_10, TRF79X0_MODULATOR_CONTROL_REG);

            TRF79x0_writeSingle(0x00, TRF79X0_REGULATOR_CONTROL_REG);
            TRF79x0_writeSingle(0x0f, TRF79X0_FIFO_IRQ_LEVEL);
            TRF79x0_writeSingle(0x03, TRF79X0_NFC_LOW_DETECTION_LEVEL);
            TRF79x0_writeSingle(0x07, TRF79X0_NFC_TARGET_LEVEL_REG);

            TRF79x0_readCont(ui8RxBuffer, TRF79X0_IRQ_STATUS_REG, sizeof(ui8RxBuffer));
            TRF79x0_readSingle(&ui8NFCTargetProtocol, TRF79X0_NFC_TARGET_PROTOCOL_REG);

            TRF79x0_directCommand(TRF79X0_RUN_DECODERS_CMD);

            do
            {
                irqFlag = TRF79x0_irqHandler(Target, 250);
                if(irqFlag == IRQ_STATUS_RX_COMPLETE)
                {
                    if(ST25TB_Target_StateMachine(g_ui8FifoBuffer, g_ui8cbFifoBuffer) == Invalid)
                    {
                        irqFlag = IRQ_STATUS_PROTOCOL_ERROR;
                    }
                }

            } while(irqFlag == IRQ_STATUS_RX_COMPLETE);

            if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)
            {
                Mode = Initiator;
            }

            break;

        case Initiator:

            if (oldMode != Initiator)
            {
                oldMode = Initiator;
                LED_ON(LED2);
            }

            TRF79x0_directCommand(TRF79X0_SOFT_INIT_CMD);
            TRF79x0_directCommand(TRF79X0_IDLE_CMD);

            TRF79x0_writeSingle(0x0c, TRF79X0_ISO_CONTROL_REG);
            TRF79x0_writeSingle(0xf0, TRF79X0_RX_SPECIAL_SETTINGS_REG); // test 0 ?
            TRF79x0_writeSingle(TRF79X0_STATUS_CTRL_RF_ON, TRF79X0_CHIP_STATUS_CTRL_REG);
            TRF79x0_writeSingle(TRF79X0_MOD_CTRL_MOD_ASK_10, TRF79X0_MODULATOR_CONTROL_REG);

            TRF79x0_writeSingle(0x00, TRF79X0_REGULATOR_CONTROL_REG);
            TRF79x0_writeSingle(0x0f, TRF79X0_FIFO_IRQ_LEVEL);
            TRF79x0_writeSingle(0x03, TRF79X0_NFC_LOW_DETECTION_LEVEL);
            TRF79x0_writeSingle(0x07, TRF79X0_NFC_TARGET_LEVEL_REG);

            TRF79x0_readCont(ui8RxBuffer, TRF79X0_IRQ_STATUS_REG, sizeof(ui8RxBuffer));

            if(ST25TB_Initiator_Compare_UID_with_Ref(&bIsEqual))
            {
                if (bIsEqual)
                {
                    LED_ON(D2);
                    if(ST25TB_Initiator_Write_Then_Compare())
                    {
                        LED_ON(D4);
                    }
                    else
                    {
                        LED_ON(D3);
                    }
                }
                else
                {
                    LED_ON(D3);
                }

                while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1))
                {
                    MCU_delayMillisecond(25);
                }

                Mode = Target;
            }

            break;
        }

        if (Mode != oldMode)
        {
            LED_OFF(LED1);
            LED_OFF(LED2);
            LED_OFF(D2);
            LED_OFF(D3);
            LED_OFF(D4);
        }
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    if(P2IV == P2IV_P2IFG2)
    {
        g_ui8IrqFlag = 0x01;
        __bic_SR_register_on_exit(LPM0_bits);
    }
}

