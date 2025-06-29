/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "14a4_initiator.h"

uint8_t K14A4_Rats()
{
    uint8_t buffer[2] = {K14A_RATS, 0x80};
    return K14_Initiator_SendRecv(buffer, sizeof(buffer), 1, 0, 5);
}
