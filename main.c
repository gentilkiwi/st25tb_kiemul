#include "boards/bp-trf7970a/trf7970a.h"
#include "st25tb/st25tb_target.h"
//#define ST25TB_DO_NOT_WRITE_DANGEROUS_SECTOR
#include "st25tb/st25tb_initiator.h"

#define LED_ACTION_DELAY   15 // DO NOT TOUCH !

bool MOD_Emulate_VirtualCard();
bool MOD_Write_VirtualToCard();
bool MOD_Read_CardToFlash();

void LED_Startup();
void LED_ChangeMode();

typedef bool (* PMODE_FUNCTION) ();
typedef struct _KIEMUL_MODE {
    const PMODE_FUNCTION current;
    const struct _KIEMUL_MODE *prev;
    const struct _KIEMUL_MODE *next;
    const bool bLedGreen;
    const bool bLedRed;
} KIEMUL_MODE, PKIEMUL_MODE;

const KIEMUL_MODE Modes[] = {
    /*index  Function                  Previous   Next       GreenL RedL */
    /*[0]*/ {MOD_Emulate_VirtualCard,  &Modes[2], &Modes[1], true,  false},
    /*[1]*/ {MOD_Write_VirtualToCard,  &Modes[0], &Modes[2], false, true },
    /*[2]*/ {MOD_Read_CardToFlash,     &Modes[1], &Modes[0], true,  true },
};

void main()
{
    const KIEMUL_MODE *pMode = &Modes[0];

    LP_init();
    BP_init();

    GPIO_enableInterrupt(LP_S1);
    GPIO_enableInterrupt(LP_S2);

    TRF7970A_init();
    ST25TB_Target_Init();

    LED_Startup();
    while(true)
    {
        LED_SET(LP_LED_GREEN, pMode->bLedGreen);
        LED_SET(LP_LED_RED, pMode->bLedRed);
        pMode = pMode->current() ? pMode->next : pMode->prev;
        LED_ChangeMode(); // at this time, timing of this animation is __mandatory__
    }
}

bool MOD_Emulate_VirtualCard()
{
    bool bContinueStateMachine, bExitMode = false, bNextOrPrev = true;
    uint8_t BP_IrqSource, TRF7970A_irqStatus;

    do
    {
        ST25TB_Target_ResetState();
        ST25TB_TRF7970A_Mode(false);

        do
        {
            bContinueStateMachine = false;

            BP_IrqSource = BP_Wait_for_Buttons_or_TRF7970A(&TRF7970A_irqStatus);
            if(BP_IrqSource & BP_IRQ_SOURCE_LP_S1)
            {
                bExitMode = true;
                bNextOrPrev = false;
            }
            else if(BP_IrqSource & BP_IRQ_SOURCE_LP_S2)
            {
                bExitMode = true;
                bNextOrPrev = true;
            }
            else if(BP_IrqSource & BP_IRQ_SOURCE_TRF7970A)
            {
                if (ST25TB_Recv(false, TRF7970A_irqStatus))
                {
                    if (ST25TB_Target_StateMachine() != Invalid)
                    {
                        bContinueStateMachine = true;
                    }
                }
            }

        }
        while (bContinueStateMachine);
    }
    while (!bExitMode);

    return bNextOrPrev;
}

bool MOD_Write_VirtualToCard()
{
    bool bExitMode = false, bNextOrPrev = true;
    uint8_t BP_IrqSource;

    do
    {
        ST25TB_TRF7970A_Mode(true);
        BP_IrqSource = ST25TB_Initiator_Write_Card(); // avoid dangerous area with ST25TB_DO_NOT_WRITE_DANGEROUS_SECTOR
        TRF7970A_writeSingle(0, TRF79X0_CHIP_STATUS_CTRL_REG);

        if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
        {
            LED_ON(BP_LED_BLUE);
            LED_OFF(BP_LED_RED);
            LED_ON(BP_LED_GREEN);
            BP_IrqSource = BP_Wait_for_Buttons();
        }
        else if(BP_IrqSource & (BP_IRQ_SOURCE_TRF7970A | BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR))
        {
            LED_ON(BP_LED_RED);
        }

        if(BP_IrqSource & BP_IRQ_SOURCE_LP_S1)
        {
            bExitMode = true;
            bNextOrPrev = false;
        }
        else if(BP_IrqSource & BP_IRQ_SOURCE_LP_S2)
        {
            bExitMode = true;
            bNextOrPrev = true;
        }
        // other is timer or trf / protocol error, no exit
    }
    while (!bExitMode);

    return bNextOrPrev;
}

bool MOD_Read_CardToFlash()
{
    bool bExitMode = false, bNextOrPrev = true;
    uint8_t BP_IrqSource;

    do
    {
        ST25TB_TRF7970A_Mode(true);
        BP_IrqSource = ST25TB_Initiator_Read_Card();
        TRF7970A_writeSingle(0, TRF79X0_CHIP_STATUS_CTRL_REG);

        if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
        {
            LED_ON(BP_LED_BLUE);
            LED_OFF(BP_LED_RED);
            ST25TB_CARDS_toSlot(0);
            LED_ON(BP_LED_GREEN);
            BP_IrqSource = BP_Wait_for_Buttons();
        }
        else if(BP_IrqSource & (BP_IRQ_SOURCE_TRF7970A | BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR))
        {
            LED_ON(BP_LED_RED);
        }

        if(BP_IrqSource & BP_IRQ_SOURCE_LP_S1)
        {
            bExitMode = true;
            bNextOrPrev = false;
        }
        else if(BP_IrqSource & BP_IRQ_SOURCE_LP_S2)
        {
            bExitMode = true;
            bNextOrPrev = true;
        }
        // other is timer or trf / protocol error, no exit
    }
    while(!bExitMode);

    return bNextOrPrev;
}

void LED_Startup()
{
    uint8_t i;

    for(i = 0; i < 2; i++)
    {
        LED_ON(LP_LED1);
        LP_delayMillisecond(LED_ACTION_DELAY * 8);
        LED_OFF(LP_LED1);
        LP_delayMillisecond(LED_ACTION_DELAY);

        LED_ON(LP_LED2);
        LP_delayMillisecond(LED_ACTION_DELAY);
        LED_OFF(LP_LED2);
        LP_delayMillisecond(LED_ACTION_DELAY);

        LED_ON(BP_LED4);
        LP_delayMillisecond(LED_ACTION_DELAY);
        LED_OFF(BP_LED4);
        LP_delayMillisecond(LED_ACTION_DELAY);

        LED_ON(BP_LED3);
        LP_delayMillisecond(LED_ACTION_DELAY);
        LED_OFF(BP_LED3);
        LP_delayMillisecond(LED_ACTION_DELAY);

        LED_ON(BP_LED2);
        LP_delayMillisecond(LED_ACTION_DELAY * 8);
        LED_OFF(BP_LED2);
        LP_delayMillisecond(LED_ACTION_DELAY);

        LED_ON(BP_LED3);
        LP_delayMillisecond(LED_ACTION_DELAY);
        LED_OFF(BP_LED3);
        LP_delayMillisecond(LED_ACTION_DELAY);

        LED_ON(BP_LED4);
        LP_delayMillisecond(LED_ACTION_DELAY);
        LED_OFF(BP_LED4);
        LP_delayMillisecond(LED_ACTION_DELAY);

        LED_ON(LP_LED2);
        LP_delayMillisecond(LED_ACTION_DELAY);
        LED_OFF(LP_LED2);
        LP_delayMillisecond(LED_ACTION_DELAY);
    }
}

void LED_ChangeMode()
{
    LED_ON(BP_LED4);
    LP_delayMillisecond(LED_ACTION_DELAY);
    LED_OFF(BP_LED4);
    LP_delayMillisecond(LED_ACTION_DELAY);

    LED_ON(BP_LED3);
    LP_delayMillisecond(LED_ACTION_DELAY);
    LED_OFF(BP_LED3);
    LP_delayMillisecond(LED_ACTION_DELAY);

    LED_ON(BP_LED2);
    LP_delayMillisecond(LED_ACTION_DELAY);
    LED_OFF(BP_LED2);
}
