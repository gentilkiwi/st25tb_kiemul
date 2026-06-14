#include "modes.h"
#include <pico/unique_id.h>
#include <pico/binary_info.h>

extern int __flash_binary_start, __flash_binary_end;

int main()
{
    pico_unique_board_id_t board_id;

    stdio_init_all();
    sleep_ms(1000);

    MODES_init();

#if defined(ST25TB_HAVE_CLI)
    pico_get_unique_board_id(&board_id);    
    printf(
        "PICO Unique Board Id: %016" PRIx64 UART_NEWLINE
        "SysFrequency        : %" PRIu32 " kHz" UART_NEWLINE
        "Flash size          : %" PRIu32 " bytes" UART_NEWLINE
        "Flash sector size   : %" PRIu16 " bytes" UART_NEWLINE
        "Flash page size     : %" PRIu16 " bytes" UART_NEWLINE
        "Flash binary_start  : 0x%p" UART_NEWLINE
        "Flash binary_end    : 0x%p" UART_NEWLINE,
        __builtin_bswap64(*(uint64_t *) &board_id), frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS), (uint32_t) PICO_FLASH_SIZE_BYTES, (uint16_t) FLASH_SECTOR_SIZE, (uint16_t) FLASH_PAGE_SIZE, &__flash_binary_start, &__flash_binary_end
    );
#endif

    MODES_main_loop();
}

bi_decl(bi_3pins_with_func(PIKO_GPIO_SPI_CLK, PIKO_GPIO_SPI_MOSI, PIKO_GPIO_SPI_MISO, GPIO_FUNC_SPI));
bi_decl(bi_3pins_with_names(PIKO_GPIO_SPI_CS, "TRF CS", PIKO_GPIO_TRF_EN, "TRF EN", PIKO_GPIO_TRF_IRQ, "TRF IRQ"));
bi_decl(bi_2pins_with_names(PIKO_GPIO_SW2_IRQ, "Switch 2 IRQ", PIKO_GPIO_SW1_IRQ, "Switch 1 IRQ"));
bi_decl(bi_3pins_with_names(PIKO_GPIO_LED_STATUS_BLUE, "LED Blue", PIKO_GPIO_LED_STATUS_GREEN, "LED Green", PIKO_GPIO_LED_STATUS_RED, "LED Red"));
bi_decl(bi_3pins_with_names(PIKO_GPIO_LED_MOD_EMULATE, "LED Mode Emulate", PIKO_GPIO_LED_MOD_REWRITE, "LED Mode Rewrite", PIKO_GPIO_LED_MOD_DETECT, "LED Mode Detect"));
bi_decl(bi_2pins_with_names(PIKO_GPIO_LED_MOD_LEARN, "LED Mode Learn", PIKO_GPIO_LED_MOD_UNK, "LED Mode Unk?"));
bi_decl(bi_4pins_with_names(PIKO_GPIO_LED_SLOT0, "LED #0", PIKO_GPIO_LED_SLOT1, "LED #1", PIKO_GPIO_LED_SLOT2, "LED #2", PIKO_GPIO_LED_SLOT3, "LED #3"));
bi_decl(bi_4pins_with_names(PIKO_GPIO_LED_SLOT4, "LED #4", PIKO_GPIO_LED_SLOT5, "LED #5", PIKO_GPIO_LED_SLOT6, "LED #6", PIKO_GPIO_LED_SLOT7, "LED #7"));