/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "14a3_target.h"

#define UID_BCC(x)  *((x) + 4) = *((x) + 0) ^ *((x) + 1) ^ *((x) + 2) ^ *((x) + 3)
#define UID4(x, uid) \
        *((x) + 0) = *((uid) + 0); \
        *((x) + 1) = *((uid) + 1); \
        *((x) + 2) = *((uid) + 2); \
        *((x) + 3) = *((uid) + 3)
#define UID3(x, uid) \
        *((x) + 0) = (K14A_CASCADE_TAG); \
        *((x) + 1) = *((uid) + 0); \
        *((x) + 2) = *((uid) + 1); \
        *((x) + 3) = *((uid) + 2)

uint8_t K14A3_TG_AC_BUFFER[20];

void K14A3_TG_Prepare_AC_Buffer(const T3A_INFOS *pInfos)
{
    *(uint16_t *) (K14A3_TG_AC_BUFFER + 0) = pInfos->ATQA;
    K14A3_TG_AC_BUFFER[17] = pInfos->SAK;
    if(pInfos->cbUID > 4)
    {
        UID3(K14A3_TG_AC_BUFFER + 2, pInfos->UID + 0);
        K14A3_TG_AC_BUFFER[17] |= 0x04;
        K14A3_TG_AC_BUFFER[18] = pInfos->SAK;
        if(pInfos->cbUID > 7)
        {
            UID3(K14A3_TG_AC_BUFFER + 7, pInfos->UID + 3);
            K14A3_TG_AC_BUFFER[18] |= 0x04;
            K14A3_TG_AC_BUFFER[19] = pInfos->SAK;
            UID4(K14A3_TG_AC_BUFFER + 12, pInfos->UID + 6);
            UID_BCC(K14A3_TG_AC_BUFFER + 12);
        }
        else
        {
            UID4(K14A3_TG_AC_BUFFER + 7, pInfos->UID + 3);
        }
        UID_BCC(K14A3_TG_AC_BUFFER + 7);
    }
    else
    {
        UID4(K14A3_TG_AC_BUFFER + 2, pInfos->UID + 0);
    }
    UID_BCC(K14A3_TG_AC_BUFFER + 2);
}

uint8_t K14A3_TG_AC_AnswerTo(uint8_t *pbIsActivated)
{
    uint8_t ret = 0, firstByte, cbData, bIsCRC = 0;
    const uint8_t *pcbData = NULL;

    firstByte = g_ui8_14a_Buffer[0];
    if((g_ui8_cb14a_Buffer == 1) && ((firstByte == K14A_ALL_REQ__WUPA) || (firstByte == (K14A_ALL_REQ__WUPA >> 1)) || (firstByte == K14A_SENS_REQ__REQA))) // sometimes it shifts >>
    {
        TIMER_delay_Microseconds(8);
        pcbData = K14A3_TG_AC_BUFFER + 0;
        cbData = 2;
    }
    else if(g_ui8_cb14a_Buffer == 2)
    {
        if(firstByte == K14A_SDD_REQ_CL1)
        {
            pcbData = K14A3_TG_AC_BUFFER + 2;
        }
        else if(firstByte == K14A_SDD_REQ_CL2)
        {
            pcbData = K14A3_TG_AC_BUFFER + 7;
        }
        else if(firstByte == K14A_SDD_REQ_CL3)
        {
            pcbData = K14A3_TG_AC_BUFFER + 12;
        }
        cbData = 5;
    }
    else if(g_ui8_cb14a_Buffer == 9)
    {
        if(firstByte == K14A_SDD_REQ_CL1)
        {
            pcbData = K14A3_TG_AC_BUFFER + 17;
        }
        else if(firstByte == K14A_SDD_REQ_CL2)
        {
            pcbData = K14A3_TG_AC_BUFFER + 18;
        }
        else if(firstByte == K14A_SDD_REQ_CL3)
        {
            pcbData = K14A3_TG_AC_BUFFER + 19;
        }
        cbData = 1;
        bIsCRC = 1;
    }
    else if(g_ui8_cb14a_Buffer == 4)
    {
        if(firstByte == K14A_HLTA)
        {
            ret = 1;
        }
    }

    if(pcbData)
    {
        ret = K14A_Send(pcbData, cbData, bIsCRC, 0);
        if(bIsCRC && !(*pcbData & 0x04))
        {
            *pbIsActivated = 1;
        }
    }

    return ret;
}

const uint8_t K14A_TG_After_AC_Seq[] = {
    MK_WS(TRF79X0_ISO_CONTROL_REG), TRF79X0_ISO_NFC_OR_CARD_EMULATION_MODE | TRF79X0_NFC_CARD_EMULATION_MODE,
    MK_WS(TRF79X0_SPECIAL_FUNC_1_REG), 0x02,
};

void K14A3_TG_AC_BackToNormal()
{
    TRF7970A_SPI_Send_raw(K14A_TG_After_AC_Seq, sizeof(K14A_TG_After_AC_Seq));
}
