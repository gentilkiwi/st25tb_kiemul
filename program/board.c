/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "board.h"

volatile uint8_t IRQ_Global = IRQ_SOURCE_NONE;
char UART_RX_BUFFER[0x300];
uint16_t cbRxBuffer = 0;

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

#if defined(__MSP430FR2476__)
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
     * P4.0 & P2.3 pullup or pulldown enabled for SW1 & SW2
     * Pull-ups not strictly needed for SW1 & SW2:
     * - st25tb_kiemul board: resistors on board for that ;
     * - LP-MSP430FR2476: R9 and R10 are intended for that (per official schematics)
     *   - Unfortunately, they are not actually populated on the official board
     */
    P2REN = BIT3;
    P4REN = BIT0;

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
#elif defined(__MSP430FR2676__)
    /*
     * P1.0 LED_MOD_REWRITE     output      |   P2.0 SPI_CS             output  |   P3.0 LED_SLOT1              output      |   P4.0 LED_STATUS_GREEN   output      *
     * P1.1 LED_MOD_DETECT      output      |   P2.1 TRF_IRQ            input   |   P3.1 LED_SLOT5              output      |   P4.1 LED_STATUS_RED     output      *
     * P1.2 LED_MOD_LEARN       output      |   P2.2 LED_SLOT0          output  |   P3.2 SPI_MOSI               output/spi  |   P4.2 SW2                input/pu    *
     * P1.3 LED_MOD_UNK         output      |   P2.3 LED_SLOT3          output  |   P3.3 LED_SLOT2              output      |   P4.3 n/a                output      *
     * P1.4 UART_TX             output      |   P2.4 LED_SLOT6          output  |   P3.4 LED_SLOT4              output      |   P4.3 n/a                output      *
     * P1.5 UART_RX             input       |   P2.5 LED_SLOT7          output  |   P3.5 SPI_CLK                output/spi  |   P4.3 n/a                output      *
     * P1.6 SW1                 input/pu    |   P2.6 BonusPin           output  |   P3.6 SPI_MISO               input/spi   |   P4.3 n/a                output      *
     * P1.7 LED_MOD_EMULATE     output      |   P2.7 TRF_EN             output  |   P3.7 LED_STATUS_BLUE        output      |   P4.3 n/a                output      *
     */
    P1DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | /*BIT5 | BIT6 |*/ BIT7;
    P2DIR = BIT0 | /*BIT1 |*/ BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;
    P3DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | /*BIT6 |*/ BIT7;
    P4DIR = BIT0 | BIT1 | /*BIT2 |*/ BIT3 | BIT4 | BIT5 | BIT6 | BIT7;

    /*
     * P1.6 & P4.2 pullup or pulldown enabled for SW1 & SW2
     */
    P1REN = BIT6;
    P4REN = BIT2;

    /*
     * P1.6 & P4.2 pullup selected for SW1 & SW2
     * P2.0 high for SPI_CS
     * ... and all other to 0 (LEDs, etc.)
     */
    P1OUT = BIT6;
    P2OUT = BIT0;
    P3OUT = 0;
    P4OUT = BIT2;

    /*
     * P1.6 & P4.2 IRQ high to low selected for SW1 & SW2
     * P2.1 low to high select for TRF_IRQ
     */
    P1IES = BIT6;
    P2IES = 0;
    P4IES = BIT2;

    /*
     * P1.6 & P4.2 IRQ clear for SW1 & SW2
     */
    P1IFG = 0;
    P4IFG = 0;

    /*
     * P1.6 & P4.2 IRQ enabled for SW1 & SW2
     */
    P1IE = BIT6;
    P4IE = BIT2;
#endif
    /*
     * UART Primary function on P1.4 & P1.5
     */
    P1SEL0 = /*BIT0 | BIT1 | BIT2 | BIT3 | */BIT4 | BIT5 /*| BIT6 | BIT7*/;

    /*
     * SPI Primary function on P3.2, P3.5 & P3.6
     */
    P3SEL0 = /*BIT0 | BIT1 | */BIT2 | /*BIT3 | BIT4 | */BIT5 | BIT6 /*| BIT7*/;

    /*
     * UART parameters (115200 bauds/second, 8 bits, LSB first, 1 stop bit, no parity)
     * https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/
     */
    UCA0CTLW0 = UCSWRST_1 | UCSSEL__SMCLK | UCMSB_0 | UCSPB_0 | UCPEN_0 | UCMODE_0 | UCSYNC__ASYNC | UC7BIT__8BIT;
    UCA0BRW = 8; // Clock prescaler setting of the Baud rate generator
    UCA0MCTLW = (247 << 8) | (10 << 4) | UCOS16_1; // Second modulation stage select, First modulation stage select, Oversampling mode enabled
    UCA0CTLW0 &= ~UCSWRST;

    /*
     * SPI parameters
     */
    UCB1CTLW0 = UCCKPH_0 | UCCKPL__LOW | UCMSB_1 | UC7BIT__8BIT | UCMST__MASTER | UCMODE_0 | UCSYNC__SYNC | UCSSEL__SMCLK | UCSTEM_0 | UCSWRST;
    UCB1BRW = 4; // 16000000 / 4 = 4000000
    UCB1CTLW0 &= ~UCSWRST;
}

void ADC_TEMP_Enable()
{
    PMMCTL0_H = PMMPW_H;
    PMMCTL2 |= TSENSOREN_1 | INTREFEN_1;
    PMMCTL0_H = 0x00;
    while(!(PMMCTL2 & REFGENRDY));
    __delay_cycles(1600);

    ADCCTL0 = ADCMSC_0 | ADCSHT_2 | ADCON_1;
    ADCCTL1 = ADCSHP_1 | ADCCONSEQ_0 | ADCSHS_0 | ADCDIV_0 | ADCSSEL_0;
    ADCCTL2 = ADCPDIV_0 | ADCRES_2;
    ADCMCTL0 = ADCINCH_12 | ADCSREF_1;
}

void ADC_TEMP_Disable()
{
    ADCCTL0 &= ~ADCON_1;
    PMMCTL0_H = PMMPW_H;
    PMMCTL2 &= ~(TSENSOREN_1 | INTREFEN_1);
    PMMCTL0_H = 0x00;
}

uint16_t ADC_TEMP_Get_RAW()
{
    ADCCTL0 |= ADCENC_1 | ADCSC_1;
    while(ADCCTL1 & ADCBUSY_1);
    return ADCMEM0;
}

int16_t ADC_TEMP_Get()
{
    uint16_t ADC_Result = ADC_TEMP_Get_RAW();
    return (int16_t) (((int32_t)((int16_t)(ADC_Result - CALADC_15V_30C)) * (105 - 30) * 10) / (CALADC_15V_105C - CALADC_15V_30C) + (30 * 10));
}

uint16_t lfsr = 0xcafe, bit;
uint16_t RAND_Generate()
{
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}

uint16_t CRC16_CCIT(const uint8_t *data, uint16_t cbData)
{
    uint16_t i;

    CRCINIRES = 0xffff;
    for(i = 0; i < cbData; i++)
    {
        CRCDIRB_L = data[i];
    }

    return CRCINIRES;
}

void TIMER_delay_Milliseconds_internal(uint16_t n_unit_ms) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
{
    TA0CCR0 = n_unit_ms;
    IRQ_Global &= ~IRQ_SOURCE_TIMER;
    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR | TAIE_1 | TAIFG_0;

    while(!(IRQ_Global & IRQ_SOURCE_TIMER))
    {
        __low_power_mode_0();
    }
    TIMER_stop();
}

void TIMER_start_Milliseconds_internal(uint16_t n_unit_ms) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
{
    TA0CCR0 = n_unit_ms;
    IRQ_Global &= ~IRQ_SOURCE_TIMER;
    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR | TAIE_1 | TAIFG_0;
}

void TIMER_delay_Microseconds_internal(uint16_t n_unit_us) // max is UINT16_MAX ( 32767 us * 2 = ~ UINT16_MAX )
{
    TA0CCR0 = n_unit_us;
    IRQ_Global &= ~IRQ_SOURCE_TIMER;
    TA0CTL = TASSEL__SMCLK | ID__8 | MC__UP | TACLR | TAIE_1 | TAIFG_0;

    while(!(IRQ_Global & IRQ_SOURCE_TIMER))
    {
        __low_power_mode_0();
    }
    TIMER_stop();
}

uint8_t IRQ_Wait_for(uint8_t IRQWanted, uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms)
{
    uint8_t ret;

    if(IRQWanted & IRQ_SOURCE_SW1)
    {
        IRQ_Global &= ~IRQ_SOURCE_SW1;
    }

    if(IRQWanted & IRQ_SOURCE_SW2)
    {
        IRQ_Global &= ~IRQ_SOURCE_SW2;
    }

    if(IRQWanted & IRQ_SOURCE_TIMER)
    {
        TIMER_start_Milliseconds(timeout_ms);
    }

    if(IRQWanted & IRQ_SOURCE_UART_RX)
    {
        IRQ_Global &= ~IRQ_SOURCE_UART_RX;
        cbRxBuffer = 0;
        UART_ENABLE_RX_IRQ();
    }

    while(!(IRQWanted & IRQ_Global))
    {
        __low_power_mode_0();
    }
    ret = IRQWanted & IRQ_Global;

    if(IRQWanted & IRQ_SOURCE_TRF7970A)
    {
        IRQ_Global &= ~IRQ_SOURCE_TRF7970A;
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
    }

    if(IRQWanted & IRQ_SOURCE_TIMER)
    {
        TIMER_stop();
    }

    if(IRQWanted & IRQ_SOURCE_UART_RX)
    {
        UART_DISABLE_RX_IRQ();
    }

    return ret;
}

#if defined(__MSP430FR2476__)
/*
 * Interrupt vector for SW2 (P2.3) & TRF_IRQ (P2.1)
 */
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    if(P2IV == P2IV_P2IFG1)
    {
        IRQ_Global |= IRQ_SOURCE_TRF7970A;
    }
    else
    {
        IRQ_Global |= IRQ_SOURCE_SW2;
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
    IRQ_Global |= IRQ_SOURCE_SW1;
    __low_power_mode_off_on_exit();
}

#elif defined(__MSP430FR2676__)
/*
 * Interrupt vector for SW1 (P1.6)
 * Usually handled by switch(P1IV) and case P1IV__P1IFG6:, but as there is only one...
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
    P1IFG = 0; // P1IFG &= ~BIT6;
    IRQ_Global |= IRQ_SOURCE_SW1;
    __low_power_mode_off_on_exit();
}

/*
 * Interrupt vector for SW2 (P4.2)
 * Usually handled by switch(P4IV) and case P4IV__P4IFG2:, but as there is only one...
 */
#pragma vector=PORT4_VECTOR
__interrupt void Port4_ISR(void)
{
    P4IFG = 0; // P4IFG &= ~BIT2;
    IRQ_Global |= IRQ_SOURCE_SW2;
    __low_power_mode_off_on_exit();
}

/*
 * Interrupt vector for TRF_IRQ (P2.1)
 * Usually handled by switch(P2IV) and case P2IV__P2IFG1:, but as there is only one...
 */
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    P2IFG = 0; // P2IFG &= ~BIT1;
    IRQ_Global |= IRQ_SOURCE_TRF7970A;
    __low_power_mode_off_on_exit();
}
#endif

/*
 * Interrupt vector for Timer TA0
 */
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMERA0_ISR (void)
{
    TA0CTL &= ~TAIFG;
    IRQ_Global |= IRQ_SOURCE_TIMER;
    __low_power_mode_off_on_exit();
}

/*
 * Interrupt vector for EUSCI AO (UART RX)
 */
#pragma vector=EUSCI_A0_VECTOR
__interrupt void EUSCI_A0_ISR (void)
{
    uint8_t c;

    (void) UCA0IV;
    c = UCA0RXBUF;

    if(c == 0x7f) // backspace
    {
        if(cbRxBuffer)
        {
            UART_TX('\b');
            UART_TX(' ');
            UART_TX('\b');
            cbRxBuffer--;
        }
    }
    else if((c >= ' ') && !(c & 0x80))
    {
        if(cbRxBuffer < (count_of(UART_RX_BUFFER) - 1))
        {
            UART_RX_BUFFER[cbRxBuffer] = c;
            UART_TX(c);
            cbRxBuffer++;
        }
    }
    else if(c == '\r')
    {
        if(cbRxBuffer < count_of(UART_RX_BUFFER))
        {
            UART_RX_BUFFER[cbRxBuffer] = '\0';
            IRQ_Global |= IRQ_SOURCE_UART_RX;
        }
    }
    else if((c == 0x1b) || (c == 0x03)) // escape / ctrl+c
    {
        cbRxBuffer = 0;
        IRQ_Global |= IRQ_SOURCE_UART_RX;
    }

    __low_power_mode_off_on_exit();
}
