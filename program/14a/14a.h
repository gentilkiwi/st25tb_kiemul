/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../board.h"
#include "14a3_initiator.h"
#define K14A_ALL_REQ__WUPA  0x52
#define K14A_SENS_REQ__REQA 0x26
// SDD_REQ: SEL_CMD - SEL_PAR - data bit 1 ... data bit n
#define K14A_SDD_REQ_CL1    0x93
#define K14A_SDD_REQ_CL2    0x95
#define K14A_SDD_REQ_CL3    0x97

// SEL_REQ: SEL_CMD - 70h - NFCID1 CLn - BCC
#define K14A_HLTA    0x50 // 0x00
#define K14A_RATS    0xe0 // 0x..

#define K14A_CASCADE_TAG 0x88

extern uint8_t g_ui8_14a_Buffer[0x7f];
extern uint8_t g_ui8_cb14a_Buffer;

uint8_t K14A_Recv(uint8_t bIsinitiator, uint8_t irqProvided);
uint8_t K14A_Send(const uint8_t *pcbData, const uint8_t cbData, const uint8_t bIsCRC, const uint8_t brokenBits);
uint8_t K14_Initiator_SendRecv(const uint8_t *pui8Payload, const uint8_t ui8Length, const uint8_t bIsCRC, const uint8_t brokenBits, uint16_t timeout_ms);

extern const TRF7970A_MODE K14A_TRF7970A_Mode_Initiator;
