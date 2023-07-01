#include "st25tb.h"

static tSt25TbState g_eCurrentTargetState;

const uint8_t ui8ChipId = 0x42;
const uint64_t MyRefStUID = 0xd0023375a24dfe07; //  UID: 07 fe 4d a2 75 33 02 d0
uint8_t MyRefSt[16 + 1][4] = {
        { 0x30, 0x00, 0x00, 0x00 }, // 0x00         [0x00] 30 00 00 00
        { 0x24, 0x78, 0x00, 0x25 }, // 0x01         [0x01] 24 78 00 25
        { 0x8a, 0x22, 0x03, 0x10 }, // 0x02         [0x02] 8a 22 03 10
        { 0x00, 0x00, 0x00, 0x00 }, // 0x03         [0x03] 00 00 00 00
        { 0x00, 0x00, 0x00, 0x00 }, // 0x04         [0x04] 00 00 00 00
        { 0x01, 0x00, 0x00, 0x04 }, // 0x05         [0x05] 01 00 00 04
        { 0xfe, 0xff, 0xff, 0xff }, // 0x06         [0x06] fe ff ff ff
        { 0x00, 0x00, 0x00, 0x00 }, // 0x07         [0x07] 00 00 00 00
        { 0x00, 0x00, 0x00, 0x00 }, // 0x08         [0x08] 00 00 00 00
        { 0xda, 0x2d, 0x00, 0x00 }, // 0x09         [0x09] da 2d 00 00
        { 0x00, 0x00, 0x00, 0x00 }, // 0x0a         [0x0a] 00 00 00 00
        { 0x00, 0x00, 0x00, 0x00 }, // 0x0b         [0x0b] 00 00 00 00
        { 0x00, 0x00, 0x00, 0x00 }, // 0x0c         [0x0c] 00 00 00 00
        { 0x00, 0x00, 0x00, 0x00 }, // 0x0d         [0x0d] 00 00 00 00
        { 0x00, 0x00, 0x00, 0x00 }, // 0x0e         [0x0e] 00 00 00 00
        { 0xd0, 0x5d, 0x0e, 0x46 }, // 0x0f         [0x0f] d0 5d 0e 46
        { 0xff, 0xff, 0xff, 0xff }, // 0xff (0x10)  [0xff] ff ff ff ff
};
uint8_t MySt[16 + 1][4];

void ST25TB_Target_Init()
{
    g_eCurrentTargetState = PowerOff;
}

tSt25TbState ST25TB_Target_StateMachine(uint8_t *pui8Payload, uint8_t ui8Length)
{
    uint8_t cbData = 0;
    const uint8_t *pcbData = NULL;

    switch (g_eCurrentTargetState)
    {
    case PowerOff:
    case Ready:

        if ((ui8Length == 2) && (pui8Payload[0] == ST25TB_INITIATE))
        {
            g_eCurrentTargetState = Inventory;
            pcbData = &ui8ChipId;
            cbData = sizeof(ui8ChipId);
        }
        else
        {
            g_eCurrentTargetState = Invalid;
        }

        break;

    case Inventory:

        if ((ui8Length == 2) && (pui8Payload[0] == ST25TB_SELECT))
        {
            if (pui8Payload[1] == ui8ChipId)
            {
                g_eCurrentTargetState = Selected;
            }
            pcbData = &ui8ChipId;
            cbData = sizeof(ui8ChipId);
        }
        else if ((ui8Length >= 1)
                && ((pui8Payload[0] & 0x0f) == ST25TB_SLOT_MARKER_MASK)) // Slot_marker() mask includes Initiate() and Pcall16()
        {
            pcbData = &ui8ChipId;
            cbData = sizeof(ui8ChipId);
        }
        else
        {
            g_eCurrentTargetState = PowerOff;
        }

        break;

    case Selected:

        if (ui8Length == 1)
        {
            if (pui8Payload[0] == ST25TB_RESET_TO_INVENTORY)
            {
                g_eCurrentTargetState = Inventory;
            }
            else if (pui8Payload[0] == ST25TB_COMPLETION)
            {
                g_eCurrentTargetState = Deactivated;
            }
            else if (pui8Payload[0] == ST25TB_GET_UID)
            {
                pcbData = (const uint8_t *) &MyRefStUID; //MyRefSt[0x11]; //ui8UID;
                cbData = sizeof(MyRefStUID);//2 * sizeof(MyRefSt[0]); //sizeof(ui8UID);
            }
        }
        else if (ui8Length == 2)
        {
            if (pui8Payload[0] == ST25TB_READ_BLOCK)
            {
                pcbData = MyRefSt[min(pui8Payload[1], 0x10)];
                cbData = sizeof(MyRefSt[0]);
            }
        }
        else if ((ui8Length == 6) && (pui8Payload[0] == ST25TB_WRITE_BLOCK))
        {
            memcpy(MyRefSt[min(pui8Payload[1], 0x10)], &pui8Payload[2],
                   sizeof(MyRefSt[0]));
        }

        break;

    case Deselected:

        if ((ui8Length == 2) && (pui8Payload[0] == ST25TB_SELECT))
        {
            if (pui8Payload[1] == ui8ChipId)
            {
                g_eCurrentTargetState = Selected;
            }
            pcbData = &ui8ChipId;
            cbData = sizeof(ui8ChipId);
        }
        else
        {
            g_eCurrentTargetState = PowerOff;
        }

        break;

    case Deactivated:
    default:

        g_eCurrentTargetState = PowerOff;

        break;

    }

    if (pcbData && cbData)
    {
        TRF79x0_Send(Target, pcbData, cbData);
    }
    else if(g_eCurrentTargetState != Invalid)
    {
        TRF79x0_ignoreCmd();
    }

    return g_eCurrentTargetState;
}

const uint8_t St25_Initiate_Command[] = { ST25TB_INITIATE, 0x00 };
bool ST25TB_Initiator_Initiate(uint8_t *pui8ChipId)
{
    bool bStatus = false;

    if(TRF79x0_Initiator_Send_Recv(St25_Initiate_Command, sizeof(St25_Initiate_Command), 2))
    {
        if(g_ui8cbFifoBuffer == 1)
        {
            *pui8ChipId = *g_ui8FifoBuffer;
            bStatus = true;
        }
    }

    return bStatus;
}

bool ST25TB_Initiator_Select(const uint8_t ui8ChipId)
{
    bool bStatus = false;
    uint8_t St25_Select_Command[] = { ST25TB_SELECT, ui8ChipId };

    if(TRF79x0_Initiator_Send_Recv(St25_Select_Command, sizeof(St25_Select_Command), 2))
    {
        if((g_ui8cbFifoBuffer == 1) && (ui8ChipId == *g_ui8FifoBuffer))
        {
            bStatus = true;
        }
    }

    return bStatus;
}

const uint8_t St25_Get_Uid_Command[] = { ST25TB_GET_UID };
bool ST25TB_Initiator_Get_Uid(uint64_t *pui64UID)
{
    bool bStatus = false;

    if(TRF79x0_Initiator_Send_Recv(St25_Get_Uid_Command, sizeof(St25_Get_Uid_Command), 5))
    {
        if(g_ui8cbFifoBuffer == 8)
        {
            *pui64UID = *(uint64_t *) g_ui8FifoBuffer;
            bStatus = true;
        }
    }

    return bStatus;
}

bool ST25TB_Initiator_Read_Block(const uint8_t block, uint8_t pui8Data[4])
{
    bool bStatus = false;
    uint8_t St25_Read_Block_Command[] = { ST25TB_READ_BLOCK, block };

    if(TRF79x0_Initiator_Send_Recv(St25_Read_Block_Command, sizeof(St25_Read_Block_Command), 5))
    {
        if(g_ui8cbFifoBuffer == 4)
        {
            *((uint32_t *) pui8Data) = *(uint32_t *) g_ui8FifoBuffer;
            bStatus = true;
        }
    }

    return bStatus;
}

bool ST25TB_Initiator_Write_Block(const uint8_t block, const uint8_t pui8Data[4])
{
    bool bStatus = false;

    uint8_t St25_Write_Block_Command[2 + 4] = { ST25TB_WRITE_BLOCK, block };
    *(uint32_t *) (St25_Write_Block_Command + 2) = *((uint32_t *) pui8Data);

    bStatus = TRF79x0_Send(Initiator, St25_Write_Block_Command, sizeof(St25_Write_Block_Command));

    if(bStatus)
    {
        MCU_delayMillisecond(5);
    }

    return bStatus;
}

const uint8_t St25_Completion_Command[] = { ST25TB_COMPLETION };
bool ST25TB_Initiator_Completion()
{
    return TRF79x0_Send(Initiator, St25_Completion_Command, sizeof(St25_Completion_Command));
}

bool ST25TB_Initiator_Compare_UID_with_Ref(bool *pbIsEqual)
{
    bool bStatus = false;

    uint8_t ui8ChipId;
    uint64_t ui64UID;

    *pbIsEqual = false;

    if(ST25TB_Initiator_Initiate(&ui8ChipId))
    {
        if(ST25TB_Initiator_Select(ui8ChipId))
        {
            if(ST25TB_Initiator_Get_Uid(&ui64UID))
            {
                bStatus = true;
#if defined(ST25TB_TEST_CARD)
                *pbIsEqual = true;
#else
                *pbIsEqual = (ui64UID == MyRefStUID);// *(uint64_t *) (MyRefSt + 0x11));
#endif
            }

            if(!*pbIsEqual)
            {
                ST25TB_Initiator_Completion();
            }
        }
    }

    return bStatus;
}

bool ST25TB_Initiator_Write_Then_Compare()
{
    uint8_t i;

    for (i = 0; i < 0x10; i++)
    {
#if defined(ST25TB_TEST_CARD)
        if ((i == 5) || (i == 6))
        {
            continue;
        }
#endif
        ST25TB_Initiator_Write_Block(i, MyRefSt[i]);
    }
    ST25TB_Initiator_Write_Block(0xff, MyRefSt[0x10]);

    memset(MySt, 0x00, sizeof(MySt));
    for(i = 0; i < 0x10; i++)
    {
#if defined(ST25TB_TEST_CARD)
        if ((i == 5) || (i == 6))
        {
            memcpy(MySt[i], MyRefSt[i], sizeof(MySt[0])) ;
            continue;
        }
#endif
        ST25TB_Initiator_Read_Block(i, MySt[i]);

    }
    ST25TB_Initiator_Read_Block(0xff, MySt[0x10]);

    return (memcmp(MySt, MyRefSt, min(sizeof(MySt), sizeof(MyRefSt))) == 0);
}