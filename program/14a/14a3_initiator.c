/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "14a3_initiator.h"

const uint8_t K14A_ALL_REQ__WUPA_DATA[] = {K14A_ALL_REQ__WUPA};
const uint8_t K14A_SENS_REQ__REQA_DATA[] = {K14A_SENS_REQ__REQA};

uint8_t K14A3_Anticoll_CL(uint8_t cl, uint8_t UID[10], uint8_t *pSAK, uint8_t *pUIDIdx)
{
    uint8_t ret, buffer[7], recIdx;

    buffer[0] = cl;
    buffer[1] = 0x02 << 4;

    TRF7970A_SPI_Write_SingleRegister(TRF79X0_ISO_CONTROL_REG, TRF79X0_ISO_CONTROL_RX_CRC_N | TRF79X0_ISO_CONTROL_14443A_106K);
    ret = K14_Initiator_SendRecv(buffer, 2, 0, 0, 5);
    if(ret == IRQ_SOURCE_NONE)
    {
        if(g_ui8_cb14a_Buffer == 5)
        {
            if(g_ui8_14a_Buffer[0] ^ g_ui8_14a_Buffer[1] ^ g_ui8_14a_Buffer[2] ^ g_ui8_14a_Buffer[3] ==  g_ui8_14a_Buffer[4])
            {
                recIdx = (g_ui8_14a_Buffer[0] == K14A_CASCADE_TAG);
                memcpy(UID + *pUIDIdx, g_ui8_14a_Buffer + recIdx, 4 - recIdx);
                *pUIDIdx += 4 - recIdx;

                buffer[1] = 0x07 << 4;
                memcpy(buffer + 2, g_ui8_14a_Buffer, 5);

                TRF7970A_SPI_Write_SingleRegister(TRF79X0_ISO_CONTROL_REG, 0 | TRF79X0_ISO_CONTROL_14443A_106K);
                ret = K14_Initiator_SendRecv(buffer, 7, 1, 0, 5);
                if(ret == IRQ_SOURCE_NONE)
                {
                    if(g_ui8_cb14a_Buffer == 1)
                    {
                        *pSAK = g_ui8_14a_Buffer[0];
                        if(((*pSAK >> 2) & 1) ^ recIdx)
                        {
                            ret = IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
                        }
                    }
                    else
                    {
                        ret = IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
                    }
                }
            }
            else
            {
                ret = IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
            }
        }
        else
        {
            ret = IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
        }
    }

    return ret;
}

uint8_t K14A3_Anticoll(uint16_t *pATQA, uint8_t *pUID, uint8_t *pcbUID, uint8_t *pSAK)
{
    uint8_t ret;

    *pcbUID = 0;
    ret = K14_Initiator_SendRecv(K14A_ALL_REQ__WUPA_DATA, sizeof(K14A_ALL_REQ__WUPA_DATA), 0, 7, 5);
    if(ret == IRQ_SOURCE_NONE)
    {
        if(g_ui8_cb14a_Buffer == sizeof(*pATQA))
        {
            *pATQA = *(uint16_t *) g_ui8_14a_Buffer;
            if(*pATQA & 0x1f) // anticoll
            {
                ret = K14A3_Anticoll_CL(K14A_SDD_REQ_CL1, pUID, pSAK, pcbUID);
                if ((ret == IRQ_SOURCE_NONE) && (*pSAK & 0x04))
                {
                    ret = K14A3_Anticoll_CL(K14A_SDD_REQ_CL2, pUID, pSAK, pcbUID);
                    if ((ret == IRQ_SOURCE_NONE) && (*pSAK & 0x04))
                    {
                        ret = K14A3_Anticoll_CL(K14A_SDD_REQ_CL3, pUID, pSAK, pcbUID);
                        if ((ret == IRQ_SOURCE_NONE) && (*pSAK & 0x04))
                        {
                            ret = IRQ_SOURCE_ST25TB_PROTOCOL_ERR; // not valid at this point
                        }
                    }
                }
            }
            else
            {
                ret = IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
            }
        }
        else
        {
            ret = IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
        }
    }

    return ret;
}
