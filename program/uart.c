/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "uart.h"
#if defined(ST25TB_HAVE_CLI)
#include "slots.h"

uint8_t UART_Enabled = 0x00;

#if defined(__msp430)
#include <file.h>
int UART_open(const char *path, unsigned flags, int llv_fd)
{
    return 0;
}

//int UART_close(int dev_fd)
//{
//    return 0;
//}
//
//int UART_read(int dev_fd, char *buf, unsigned count)
//{
//    return EOF;
//}

void UART_TX(const uint8_t transmitData)
{
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = transmitData;
}

int UART_write(int dev_fd, const char *buf, unsigned count)
{
    unsigned i;

    for(i = 0; i < count; i++)
    {
        UART_TX(buf[i]);
    }

    return count;
}

//off_t UART_lseek(int dev_fd, off_t offset, int origin)
//{
//    return (off_t) -1;
//}
//
//int UART_unlink(const char *path)
//{
//    return -1;
//}
//
//int UART_rename(const char *old_name, const char *new_name)
//{
//    return -1;
//}

void UART_Redirect_std()
{
    //add_device("uart", _SSA, UART_open, UART_close, UART_read, UART_write, UART_lseek, UART_unlink, UART_rename);
    add_device("uart", _SSA, UART_open, NULL, NULL, UART_write, NULL, NULL, NULL);
    freopen("uart:", "w", stdout);
    setvbuf(stdout, NULL, _IONBF, 0);

    UART_Enabled = FlashStoredData.bUARTEnabled;
}
#elif defined(STM32F405xx)

int _write(int file, char *ptr, int len)
{
	(void) file;
	uint8_t rc;

	if (UART_Enabled) //hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED)
	{
		do
		{
			rc = CDC_Transmit_FS((uint8_t*) ptr, len);
		} while (rc == USBD_BUSY);

		if (rc == USBD_FAIL)
		{
			len = 0;
		}

	}

	return len;
}

void UART_Redirect_std()
{
    //add_device("uart", _SSA, UART_open, UART_close, UART_read, UART_write, UART_lseek, UART_unlink, UART_rename);
    //add_device("uart", _SSA, UART_open, NULL, NULL, UART_write, NULL, NULL, NULL);
    //freopen("uart:", "w", stdout);
    setvbuf(stdout, NULL, _IONBF, 0);

    //UART_Enabled = FlashStoredData.bUARTEnabled;
}
#elif defined(PICO_BOARD)
#include <tusb.h>
void tud_cdc_line_state_cb(__unused uint8_t itf, bool dtr, __unused bool rts)
{
    UART_Enabled = dtr;
}

void tud_cdc_rx_cb(uint8_t itf)
{
    uint8_t echo[192];
    uint16_t echo_len = 0;
    uint8_t c;

    if (isUSBCDCWanted)
    {
        while (tud_cdc_n_available(itf))
        {
            if (tud_cdc_n_read(itf, &c, 1) != 1)
                break;

            if (c == 0x7f) // backspace
            {
                if (cbRxBuffer)
                {
                    echo[echo_len++] = '\b';
                    echo[echo_len++] = ' ';
                    echo[echo_len++] = '\b';
                    cbRxBuffer--;
                }
            }
            else if ((c >= ' ') && !(c & 0x80))
            {
                if (cbRxBuffer < (count_of(UART_RX_BUFFER) - 1))
                {
                    UART_RX_BUFFER[cbRxBuffer++] = c;
                    echo[echo_len++] = c;
                }
            }
            else if (c == '\r')
            {
                UART_RX_BUFFER[cbRxBuffer] = '\0';
                IRQ_Global |= IRQ_SOURCE_UART_RX;
            }
            else if (c == 0x1b || c == 0x03) // escape / ctrl+c
            {
                cbRxBuffer = 0;
                IRQ_Global |= IRQ_SOURCE_UART_RX;
            }


            if (echo_len > count_of(echo) - 4) // just in case...
            {
                tud_cdc_n_write(itf, echo, echo_len);
                tud_cdc_n_write_flush(itf);
                echo_len = 0;
            }
        }

        if (echo_len)
        {
            tud_cdc_n_write(itf, echo, echo_len);
            tud_cdc_n_write_flush(itf);
        }
    }
    else
    {
        tud_cdc_n_read_flush(itf);
    }
}
#endif

void kprinthex(const void *lpData, const uint16_t cbData)
{
    if(UART_Enabled)
    {
        uint16_t i;
        for(i = 0; i < cbData; i++)
        {
            printf("%02hx ", ((const uint8_t *)lpData)[i]);
        }
        printf(UART_NEWLINE);
    }
}
#endif
