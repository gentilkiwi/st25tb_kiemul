/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "modes.h"

#if !defined(ST25TB_HAVE_FULL_LEDS)
const KAKI_MODE Modes[] = {
    {.function = MODE_emulate,  .ledsModesBitmask = 0b01,       .Name = "Emulate"},
    {.function = MODE_rewrite,  .ledsModesBitmask = 0b10,       .Name = "Rewrite"},
    {.function = MODE_field,    .ledsModesBitmask = 0b00,       .Name = "Field"},
};
const KAKI_MODE Modes_2[] = {
    {.function = MODE_detect,   .ledsModesBitmask = 0b01,       .Name = "Detect"},
    {.function = MODE_select,   .ledsModesBitmask = 0b10,       .Name = "Select"},
    {.function = MODE_learn,    .ledsModesBitmask = 0b11,       .Name = "Learn"},
    {.function = MODE_tear,     .ledsModesBitmask = 0b00,       .Name = "Tear!"},
    {.function = MODE_cli,      .ledsModesBitmask = 0b00,       .Name = "CLI"},
};
#else
const KAKI_MODE Modes[] = {
    {.function = MODE_emulate,  .ledsModesBitmask = 1 << 0,     .Name = "Emulate"},
    {.function = MODE_rewrite,  .ledsModesBitmask = 1 << 1,     .Name = "Rewrite"},
    {.function = MODE_detect,   .ledsModesBitmask = 1 << 2,     .Name = "Detect"},
    {.function = MODE_select,   .ledsModesBitmask = 1 << 3,     .Name = "Select"},
    {.function = MODE_field,    .ledsModesBitmask = 1 << 4,     .Name = "Field"},
    {.function = MODE_unk,      .ledsModesBitmask = 0,          .Name = "Counter5"},
};
const KAKI_MODE Modes_2[] = {
    {.function = MODE_learn,    .ledsModesBitmask = 1 << 3,     .Name = "Learn"},
    {.function = MODE_tear,     .ledsModesBitmask = 1 << 4,     .Name = "Tear!"},
#if defined(ST25TB_HAVE_CLI)
    {.function = MODE_cli,      .ledsModesBitmask = 0b10101,    .Name = "CLI"},
#endif
};
#endif

#if defined(ST25TB_HAVE_CLI)
const char KIWI_BANNER[] =  "\x1b[2J\x1b[3J\x1b[H" UART_NEWLINE
    "  .#####.         " ST25TB_BOARD_NAME " (fw " ST25TB_FW_VERSION ")" UART_NEWLINE
    " .## ^ ##.__ _    " ST25TB_MCU_NAME " & TRF7970A" UART_NEWLINE
    " ## / \\ /   ('>-  /***" UART_NEWLINE
    " ## \\ / | K  |     Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )" UART_NEWLINE
    " '## v #\\____/" UART_NEWLINE
    "  '#####' L\\_      ***/" UART_NEWLINE UART_NEWLINE;
#endif

void MODES_init()
{
    BOARD_init();
    TRF7970A_init();
    LEDS_Animation();
    SLOTS_Change(FlashStoredData.CurrentSlot);

#if defined(ST25TB_HAVE_CLI)
    UART_Redirect_std();
    puts(KIWI_BANNER);
#endif
}

void MODES_main_loop()
{
    uint8_t maxModes;
    const KAKI_MODE *pMode, *cMode;

    if(!SW1_IS_PRESSED()) // LEARN & TEAR only available if pushing MODE at startup
    {
        pMode = cMode = Modes;
        maxModes = count_of(Modes);
    }
    else
    {
        pMode = cMode = Modes_2;
        maxModes = count_of(Modes_2);
    }

#if defined(ST25TB_HAVE_CLI)
    if(SW2_IS_PRESSED()) // override stored config
    {
        UART_Enabled = 1;
    }

    printf(
            UART_NEWLINE "ST25TB board mode      : %s" UART_NEWLINE
            "ST25TB board UART      : %s" UART_NEWLINE
            "ST25TB Current Slot    : %" PRIu8 UART_NEWLINE
            "ST25TB Total slots     : %u" UART_NEWLINE
            "ST25TB support for     : "
#if defined(SLOTS_ST25TB_SUPPORT_4K)
            "4Kb"
#elif defined(SLOTS_ST25TB_SUPPORT_2K)
            "2Kb"
#elif defined(SLOTS_ST25TB_SUPPORT_512)
            "512b"
#endif
            UART_NEWLINE
            , (pMode == Modes) ? "normal" : "special"
            , UART_Enabled ? "enabled" : "disabled"
            , FlashStoredData.CurrentSlot
            , SLOTS_ST25TB_COUNT
    );
#endif

    while(1)
    {
        IRQ_Global &= ~(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2);
        LEDS_MODES_Bitmask(cMode->ledsModesBitmask);
        LEDS_STATUS_Bitmask(0);

        kprintf(UART_NEWLINE "--- Mode: %s ---" UART_NEWLINE, cMode->Name);

        cMode->function();

        __no_operation();
        TRF7970A_SPI_DirectCommand(TRF79X0_STOP_DECODERS_CMD);
        __no_operation();
        __no_operation();
        TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00);
        cMode++;
        if(cMode >= (pMode + maxModes))
        {
            cMode = pMode + 0;
        }
        TIMER_delay_Milliseconds(150);
    }
}
