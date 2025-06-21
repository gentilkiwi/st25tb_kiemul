/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "uart.h"
#include "slots.h"
#include <file.h>

uint8_t UART_Enabled = 0x00;

int UART_open(const char *path, unsigned flags, int llv_fd)
{
    return 0;
}

int UART_close(int dev_fd)
{
    return 0;
}

int UART_read(int dev_fd, char *buf, unsigned count)
{
    return EOF;
}

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

off_t UART_lseek(int dev_fd, off_t offset, int origin)
{
    return (off_t) -1;
}

int UART_unlink(const char *path)
{
    return -1;
}

int UART_rename(const char *old_name, const char *new_name)
{
    return -1;
}

void UART_Redirect_std()
{
    //add_device("uart", _SSA, UART_open, UART_close, UART_read, UART_write, UART_lseek, UART_unlink, UART_rename);
    add_device("uart", _SSA, UART_open, NULL, NULL, UART_write, NULL, NULL, NULL);
    freopen("uart:", "w", stdout);
    setvbuf(stdout, NULL, _IONBF, 0);

    UART_Enabled = FlashStoredData.bUARTEnabled;
}

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
