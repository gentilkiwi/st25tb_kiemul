/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "board.h"
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

void main(void)
{
    uint8_t maxModes;
#if defined(ST25TB_HAVE_CLI)
    uint16_t calculatedCRC;
#endif
    const KAKI_MODE *pMode, *cMode;

    BOARD_init();
    TRF7970A_init();
    LEDS_Animation();
    SLOTS_Change(FlashStoredData.CurrentSlot);

#if defined(ST25TB_HAVE_CLI)
    UART_Redirect_std();

    puts(KIWI_BANNER);

#if defined(__msp430)
    calculatedCRC = CRC16_CCIT((const uint8_t *)(TLVMEM_START + 0x04), 0xf4);

    printf("CRC Value   : r:0x%04" PRIx16 " c:0x%04" PRIx16 " - %s" UART_NEWLINE
            "Device ID   : 0x%04" PRIx16 UART_NEWLINE
            "Lot wafer ID: 0x%08" PRIx32 " (x:%" PRIu16 "/y:%" PRIu16 ")" UART_NEWLINE
            "SYSRSTIV    : 0x%04" PRIx16 UART_NEWLINE
            , CRC_VALUE, calculatedCRC, (CRC_VALUE == calculatedCRC) ? "OK" : "KO"
            , DEVICE_ID
            , DIE_LOT_WAFER_ID, DIE_LOT_WAFER_X_POS, DIE_LOT_WAFER_Y_POS
            , SYSRSTIV
    );
#elif defined(STM32F405xx)
    printf("Device ID   : 0x%04" PRIx32 " rev: 0x%04" PRIx32 UART_NEWLINE
    		"Flash size  : %" PRIu16 " Kbytes" UART_NEWLINE
			"Device UID  : 0x%08" PRIx32 "%08" PRIx32 "%08" PRIx32 UART_NEWLINE
			"SysClockFreq: %" PRIu32 " kHz" UART_NEWLINE
			, HAL_GetDEVID(), HAL_GetREVID()
			, *(const uint16_t*)FLASHSIZE_BASE
			, HAL_GetUIDw0(), HAL_GetUIDw1(), HAL_GetUIDw2()
			, HAL_RCC_GetSysClockFreq() / 1000
	);
#endif
#endif

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
