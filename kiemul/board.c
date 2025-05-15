/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "board.h"

volatile bool g_irq_TA0, g_irq_SW1, g_irq_SW2, g_irq_TRF;

void BOARD_init()
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    /*
     * MCU @ 16 MHz
     */
    __bis_SR_register(SCG0);
    CSCTL0 = ~DCO;
    CSCTL1 = DCOFTRIMEN_0 | DCORSEL_5 | DISMOD_1; // DCORSEL_5 for 16 MHz
    CSCTL2 = FLLD__1 | (16000000 / 32768);
    __bic_SR_register(SCG0);
    __delay_cycles((16000000 / 32768) * 32 * 30);
    while (CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1 | DCOFFG))
    {
        CSCTL7 &= ~DCOFFG;
        SFRIFG1 &= ~OFIFG;
    }

    /*
     * P1.0 LED_MOD_GREEN    output        |  P2.0                  output        |  P3.0                  output        |  P4.0 SW1              input/pullup  |  P5.0 n/a (LED2_G)     output        |  P6.0                  output        *
     * P1.1 (LP Temp Sensor) input         |  P2.1 TRF_IRQ          input/irq     |  P3.1                  output        |  P4.1                  output        |  P5.1 LED_MOD_RED      output        |  P6.1                  output        *
     * P1.2 TRF_EN           output        |  P2.2                  output        |  P3.2 SPI_MOSI         output/spi    |  P4.2 LED_STATUS_GREEN output        |  P5.2                  output        |  P6.2                  output        *
     * P1.3 SPI_CS           output        |  P2.3 SW2              input/pullup  |  P3.3                  output        |  P4.3                  output        |  P5.3                  output        *
     * P1.4 (LP UART TX)     output        |  P2.4 LED_STATUS_BLUE  output        |  P3.4                  output        |  P4.4                  output        |  P5.4 (DLP ""unused"") input         *
     * P1.5 (LP UART RX)     input         |  P2.5 (LP UART RX)     input         |  P3.5 SPI_CLK          output/spi    |  P4.5                  output        |  P5.5                  output        *
     * P1.6                  output        |  P2.6 (LP UART TX)     output        |  P3.6 SPI_MISO         input/spi     |  P4.6                  output        |  P5.6                  output        *
     * P1.7                  output        |  P2.7 LED_STATUS_RED   output        |  P3.7                  output        |  P4.7 n/a (LED2_BLUE)  output        |  P5.7                  output        *
     */
    P1DIR = BIT0 | /*BIT1 | */BIT2 | BIT3 | BIT4 | /*BIT5 | */BIT6 | BIT7;
    P2DIR = BIT0 | /*BIT1 | */BIT2 | /*BIT3 | */BIT4 | /*BIT5 | */BIT6 | BIT7;
    P3DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | /*BIT6 | */BIT7;
    P4DIR = /*BIT0 | */BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;
    P5DIR = BIT0 | BIT1 | BIT2 | BIT3 | /*BIT4 | */BIT5 | BIT6 | BIT7; // **unused DLP pin...**
    P6DIR = BIT0 | BIT1 | BIT2;

    /*
     * P4.0 & P2.3 pullup selected for SW1 & SW2
     * P1.3 high for SPI_CS
     * ... and all other to 0 (LEDs, etc.)
     * Pull-ups not strictly needed for SW1 & SW2:
     * - st25tb_kiemul board: resistors on board for that ;
     * - LP-MSP430FR2476: R9 and R10 are intended for that (per official schematics)
     *   - Unfortunately, they are not actually populated on the official board
     */
    P1OUT = BIT3;
    P2OUT = BIT3;
    P3OUT = 0;
    P4OUT = BIT0;
    P5OUT = 0;
    P6OUT = 0;

    /*
     * P4.0 & P2.3 pullup or pulldown enabled for SW1 & SW2
     * Pull-ups not strictly needed for SW1 & SW2:
     * - st25tb_kiemul board: resistors on board for that ;
     * - LP-MSP430FR2476: R9 and R10 are intended for that (per official schematics)
     *   - Unfortunately, they are not actually populated on the official board
     */
    P2REN = BIT3;
    P4REN = BIT0;

    /*
     * P4.0 & P2.3 IRQ high to low selected for SW1 & SW2
     * P2.1 low to high select for TRF_IRQ
     */
    P2IES = BIT3 | 0;
    P4IES = BIT0;

    /*
     * P4.0 & P2.3 IRQ clear for SW1 & SW2
     */
    P2IFG = 0;
    P4IFG = 0;

    /*
     * P4.0 & P2.3 IRQ enabled for SW1 & SW2
     */
    P2IE = BIT3;
    P4IE = BIT0;

    /*
     * SPI Primary function on P3.2, P3.5 & P3.6
     */
    P3SEL0 = /*BIT0 | BIT1 | */BIT2 | /*BIT3 | BIT4 | */BIT5 | BIT6 /*| BIT7*/;

    /*
     * SPI parameters
     */
    UCB1CTLW0 = UCCKPH_0 | UCCKPL__LOW | UCMSB_1 | UC7BIT__8BIT | UCMST__MASTER | UCMODE_0 | UCSYNC__SYNC | UCSSEL__SMCLK | UCSTEM_0 | UCSWRST;
    UCB1BRW = UCBR2; // UCBR2 = 4, 16000000 / 4 = 4000000
    UCB1CTLW0 &= ~UCSWRST;
}

uint16_t lfsr = 0xcafe, bit;
uint16_t RAND_Generate()
{
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}

void TIMER_delay_Milliseconds_internal(uint16_t n_unit_ms) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
{
    TA0CCR0 = n_unit_ms;
    g_irq_TA0 = false;
    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR | TAIE_1 | TAIFG_0;

    while(!g_irq_TA0)
    {
        __low_power_mode_0();
    }
    TIMER_stop();
}

void TIMER_start_Milliseconds_internal(uint16_t n_unit_ms) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
{
    TA0CCR0 = n_unit_ms;
    g_irq_TA0 = false;
    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR | TAIE_1 | TAIFG_0;
}

void TIMER_delay_Microseconds_internal(uint16_t n_unit_us) // max is UINT16_MAX ( 32767 us * 2 = ~ UINT16_MAX )
{
    TA0CCR0 = n_unit_us;
    g_irq_TA0 = false;
    TA0CTL = TASSEL__SMCLK | ID__8 | MC__UP | TACLR | TAIE_1 | TAIFG_0;

    while(!g_irq_TA0)
    {
        __low_power_mode_0();
    }
    TIMER_stop();
}

/*
 * TODO: Can be interesting to see a generic function with a bitmask of what is wanted instead of multiple functions
 */
uint8_t IRQ_Wait_for_SW1()
{
    g_irq_SW1 = false;
    while(!g_irq_SW1)
    {
       __low_power_mode_0();
    }
    g_irq_SW1 = false;

    return IRQ_SOURCE_SW1;
}

uint8_t IRQ_Wait_for_SW1_or_SW2()
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_SW2 = false;
    while(!g_irq_SW1 && !g_irq_SW2)
    {
       __low_power_mode_0();
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_SW2_or_TRF(uint8_t *pTRF7970A_irqStatus)
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_SW2 = false;

    while(!g_irq_TRF && !g_irq_SW1 && !g_irq_SW2)
    {
        __low_power_mode_0(); //__no_operation(); -- in case of problems to catch some IRQ :( hopefully routine is only used in emulation
    }

    if(g_irq_TRF)
    {
        g_irq_TRF = false;
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        ret |= IRQ_SOURCE_TRF7970A;
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_TRF(uint8_t *pTRF7970A_irqStatus)
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;

    while(!g_irq_TRF && !g_irq_SW1)
    {
        __low_power_mode_0();
    }

    if(g_irq_TRF)
    {
        g_irq_TRF = false;
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        ret |= IRQ_SOURCE_TRF7970A;
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_SW2_or_Timeout(uint16_t timeout_ms)
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_SW2 = false;
    TIMER_start_Milliseconds(timeout_ms);

    while(!g_irq_TA0 && !g_irq_SW1 && !g_irq_SW2)
    {
        __low_power_mode_0();
    }
    TIMER_stop();

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    if(g_irq_TA0)
    {
        ret |= IRQ_SOURCE_TIMER;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_SW2_or_TRF_or_Timeout(uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms)
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_SW2 = false;
    TIMER_start_Milliseconds(timeout_ms);

    while(!g_irq_TRF && !g_irq_TA0 && !g_irq_SW1 && !g_irq_SW2)
    {
        __low_power_mode_0();
    }
    TIMER_stop();

    if(g_irq_TRF)
    {
        g_irq_TRF = false;
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        ret |= IRQ_SOURCE_TRF7970A;
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    if(g_irq_TA0)
    {
        ret |= IRQ_SOURCE_TIMER;
    }

    return ret;
}

/*
 * Interrupt vector for SW2 (P2.3) & TRF_IRQ (P2.1)
 */
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    if(P2IV == P2IV_P2IFG1)
    {
        g_irq_TRF = true;
    }
    else
    {
        g_irq_SW2 = true;
    }
    __low_power_mode_off_on_exit();
}

/*
 * Interrupt vector for SW1 (P4.0)
 * Usually handled by switch(P4IV) and case P4IV__P4IFG0:, but as there is only one...
 */
#pragma vector=PORT4_VECTOR
__interrupt void Port4_ISR(void)
{
    P4IFG = 0; // P4IFG &= ~BIT2;
    g_irq_SW1 = true;
    __low_power_mode_off_on_exit();
}

/*
 * Interrupt vector for Timer TA0
 */
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMERA0_ISR (void)
{
    TA0CTL &= ~TAIFG;
    g_irq_TA0 = true;
    __low_power_mode_off_on_exit();
}
