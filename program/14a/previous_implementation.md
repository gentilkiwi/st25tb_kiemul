# NTAG210

## Header

```
#define NTAG_CMD_GET_VERSION            0x60
#define NTAG_CMD_READ                   0x30 // See rollover :')
#define NTAG_CMD_FAST_READ              0x3a
#define NTAG_CMD_WRITE                  0xa2
#define NTAG_CMD_COMPATIBILITY_WRITE    0xa0
#define NTAG_CMD_READ_CNT               0x39
#define NTAG_CMD_INCR_CNT               0xa5
#define NTAG_CMD_PWD_AUTH               0x1b
#define NTAG_CMD_READ_SIG               0x3c
#define NTAG_CMD_CHECK_TEARING_EVENT    0x3e
#define NTAG_CMD_VCSL                   0x4b
```

## Source

```
const T3A_INFOS t3a_infos_ntag210 = {
    .UID = {0x04, 0xa8, 0xc4, 0xaa, 0x28, 0x63, 0x80}, .tUID = T3A_UID_7BYTES,
    .ATQA = {0x44, 0x00}, .SAK = 0x00,
    .ATS = {0x00}, .cbATS = 0,
};

const uint8_t NTAG210_DATA[][4] = {
    /* 0x00 */ {0x04, 0xa8, 0xc4, 0xe0}, // UID0
    /* 0x01 */ {0xaa, 0x28, 0x63, 0x80}, // UID1
    /* 0x02 */ {0x61, 0x48, 0xff, 0xff}, // static lock bytes
    /* 0x03 */ {0xe1, 0x10, 0x06, 0x00}, // Capability Container (CC)
    /* 0x04 */ {0x03, 0x15, 0xd1, 0x01}, // User Memory | begin
    /* 0x05 */ {0x11, 0x54, 0x02, 0x66}, // .
    /* 0x06 */ {0x72, 0xf0, 0x9f, 0xa5}, // .
    /* 0x07 */ {0x9d, 0xe2, 0x9d, 0xa4}, // .
    /* 0x08 */ {0xef, 0xb8, 0x8f, 0xf0}, // .
    /* 0x09 */ {0x9f, 0xa6, 0x86, 0xfe}, // .
    /* 0x0A */ {0x00, 0x00, 0x00, 0x00}, // .
    /* 0x0B */ {0x00, 0x00, 0x00, 0x00}, // .
    /* 0x0C */ {0x00, 0x00, 0x00, 0x00}, // .
    /* 0x0D */ {0x00, 0x00, 0x00, 0x00}, // .
    /* 0x0E */ {0x00, 0x00, 0x00, 0x00}, // .
    /* 0x0F */ {0x00, 0x00, 0x00, 0x00}, // User memory | end
    /* 0x10 */ {0x04, 0x00, 0x00, 0xff}, // CFG0
    /* 0x11 */ {0x40, 0x05, 0x00, 0x00}, // CFG1 - CFGLCK: Write locking bit for the user configuration - user configuration permanently locked against write access
    /* 0x12 */ {0xff, 0xff, 0xff, 0xff}, // PWD
    /* 0x13 */ {0x00, 0x00, 0x00, 0x00}, // PACK, RFUI
};
const uint8_t NTAG210_VERSION[] = {0x00, 0x04, 0x04, 0x01, 0x01, 0x00, 0x0b, 0x03};
const uint8_t NTAG210_SIGNATURE[] = {0xd3, 0xae, 0x20, 0x27, 0x08, 0xb2, 0xcc, 0x51, 0x76, 0x4e, 0xa2, 0x89, 0x62, 0xae, 0xc9, 0xb8, 0xc8, 0xd0, 0x80, 0xbc, 0xad, 0xb1, 0x20, 0xd3, 0x84, 0xfa, 0xa3, 0xbc, 0xe5, 0xff, 0xa6, 0x1e};

void Dispatch_14a_NTAG210(const uint8_t **ppcbData, uint8_t *pcbData)
{
    uint8_t addr;
    uint32_t aligned;

    switch(g_ui8_14a_Buffer[0])
    {
    case NTAG_CMD_GET_VERSION:
        if(g_ui8_cb14a_Buffer == 1)
        {
            *ppcbData = NTAG210_VERSION;
            *pcbData = sizeof(NTAG210_VERSION);
        }

        break;

    case NTAG_CMD_READ:
        if(g_ui8_cb14a_Buffer == 2)
        {
            addr = g_ui8_14a_Buffer[1];
            if(addr < count_of(NTAG210_DATA))
            {
                *ppcbData = NTAG210_DATA[addr];
                *pcbData = 16; // ouch, TODO: FIX rollover, or not.... I pushed data after DATA
            }
        }

        break;

    case NTAG_CMD_PWD_AUTH:
        if(g_ui8_cb14a_Buffer == 1 + sizeof(NTAG210_DATA[0x12]))
        {
            /* Something something something... align! */
            aligned = ((uint32_t ) g_ui8_14a_Buffer[4] << 24) | ((uint32_t ) g_ui8_14a_Buffer[3] << 16) | ((uint32_t ) g_ui8_14a_Buffer[2] << 8) | (uint32_t ) g_ui8_14a_Buffer[1];
            if(*(uint32_t *)(NTAG210_DATA[0x12]) == aligned)
            {
                *ppcbData = NTAG210_DATA[0x13];
                *pcbData = 2;
            }
        }

        break;

    case NTAG_CMD_READ_SIG:
        if(g_ui8_cb14a_Buffer == 2)
        {
            *ppcbData = NTAG210_SIGNATURE;
            *pcbData = sizeof(NTAG210_SIGNATURE);
        }

        break;

    default:
        ;
    }
}
```

# ST25TA512

## Header

```
/*
 * Bit-number is different from ISO
 * we start at 0, like civilized people
 */
#define BLOCK_PCB_TYPE_I_MASK           0b11100010
#define BLOCK_PCB_TYPE_I_VALUE          0b00000010

#define BLOCK_PCB_TYPE_R_MASK           0b11100010
#define BLOCK_PCB_TYPE_R_VALUE          0b10100010

#define BLOCK_PCB_TYPE_S_MASK           0b11000111
#define BLOCK_PCB_TYPE_S_VALUE          0b11000010

/*
 * Coding of I-block PCB (BLOCK_PCB_TYPE_I)
 */
#define BLOCK_PCB_I_CHAINING_MASK       0b00010000 // B4
#define BLOCK_PCB_I_CHAINING_NO         0b00000000 // B4
#define BLOCK_PCB_I_CHAINING            0b00010000 // B4

#define BLOCK_PCB_I_CID_FOLLOWING_MASK  0b00001000 // B3
#define BLOCK_PCB_I_CID_FOLLOWING_NO    0b00000000 // B3
#define BLOCK_PCB_I_CID_FOLLOWING       0b00001000 // B3

#define BLOCK_PCB_I_NAD_FOLLOWING_MASK  0b00000100 // B2
#define BLOCK_PCB_I_NAD_FOLLOWING_NO    0b00000000 // B2
#define BLOCK_PCB_I_NAD_FOLLOWING       0b00000100 // B2

#define BLOCK_PCB_I_BLOCK_NUMBER_MASK   0b00000001 // B0

/*
 * Coding of R-block PCB (BLOCK_PCB_TYPE_R)
 */
#define BLOCK_PCB_R_ACK_NACK_MASK       0b00010000 // B4
#define BLOCK_PCB_R_ACK_NACK_VAL_NACK   0b00010000 // B4
#define BLOCK_PCB_R_ACK_NACK_VAL_ACK    0b00000000 // B4

#define BLOCK_PCB_R_CID_FOLLOWING_MASK  0b00001000 // B3
#define BLOCK_PCB_R_CID_FOLLOWING_NO    0b00000000 // B3
#define BLOCK_PCB_R_CID_FOLLOWING       0b00001000 // B3

#define BLOCK_PCB_R_BLOCK_NUMBER_MASK   0b00000001 // B0

/*
 * Coding of S-block PCB (BLOCK_PCB_TYPE_S)
 */
#define BLOCK_PCB_S_CMD_MASK            0b00110000 // B5-B4
#define BLOCK_PCB_S_CID_FOLLOWING_MASK  0b00001000 // B3
```

## Source

```
const T3A_INFOS t3a_infos_st25ta512 = {
    .UID = {0x02, 0xe5, 0x00, 0x11, 0x22, 0x33, 0x44}, .tUID = T3A_UID_7BYTES,
    .ATQA = {0x42, 0x00}, .SAK = 0x20,
    .ATS = {0x02, 0x05}, .cbATS = 2, // minimal one instead of .ATS = {0x05, 0x75, 0x80, 0x60, 0x02}, .cbATS = 5
};

const uint8_t NDEF_AID[] = {0xd2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01};
const uint8_t NDEF_FID[2] = {0x00, 0x01};
const uint8_t NDEF_FILE_DATA[] = {
    0x00, 0x2a,
    0xd1, 0x01, 0x26, 0x55, 0x04, 0x67, 0x69, 0x74, 0x68, 0x75, 0x62, 0x2E, 0x63, 0x6F, 0x6D, 0x2F,
    0x67, 0x65, 0x6E, 0x74, 0x69, 0x6C, 0x6B, 0x69, 0x77, 0x69, 0x2F, 0x73, 0x74, 0x32, 0x35, 0x74,
    0x62, 0x5F, 0x6B, 0x61, 0x6D, 0x65, 0x6C, 0x65, 0x6F, 0x6E
};
uint8_t NDEF_FID_SYSTEM[2] = {0xe1, 0x01};

const uint8_t NDEF_FID_CC[2] = {0xe1, 0x03};
const uint8_t NDEF_CC_FILE_DATA[] = {
    0x00, 0x0f, // CCLEN - Indicates the size of this CC (including this field)
    0x20,       // T4T_VNo - Mapping Version 2.0 (with the Standard Data Structure)
    0x00, 0xff, // MLe (bytes); Maximum R-APDU data size
    0x00, 0x36, // MLc (bytes); Maximum C-APDU data size
    /*
     * NDEF-File_Ctrl_TLV
     */
    0x04,       // Indicates the NDEF-File_Ctrl_TLV
    0x06,       // The length of the V-field is 6 bytes
    0x00, 0x01, // File identifier of the NDEF File - 0001h
    0x00, sizeof(NDEF_FILE_DATA), // We try to be a XX bytes tag
    0x00,       // READ access granted without any security
    0xff,       // No WRITE access granted at all (i.e., Read only)
};


/*
 * Ok, we mix a little bit generic 14443-4 / ISO-DEP / and NDEF here
 */
uint8_t ui8_14ASendBuffer[64];
uint8_t ui8_cb14ASendBuffer;
const uint8_t *pFile;
uint8_t cbFile;

/*
 * Dispatch_14a_ST25TA512 is more a generic NDEF T4 dispatcher
 * This function is not correct at all, not safe ISO DEP, etc.
 * This is just for the fun
 */
void Dispatch_14a_ST25TA512(const uint8_t **ppcbData, uint8_t *pcbData)
{
    uint8_t PCB, CLA, INS, P1, P2, LC;
    uint16_t offset;

    PCB = g_ui8_14a_Buffer[0];
    if((PCB & BLOCK_PCB_TYPE_I_MASK) == BLOCK_PCB_TYPE_I_VALUE)
    {
        ui8_14ASendBuffer[0] = BLOCK_PCB_TYPE_I_VALUE | BLOCK_PCB_I_CHAINING_NO | BLOCK_PCB_I_CID_FOLLOWING_NO | BLOCK_PCB_I_NAD_FOLLOWING_NO | (PCB & BLOCK_PCB_I_BLOCK_NUMBER_MASK);

        if(g_ui8_cb14a_Buffer >= (1 + 5))
        {
            CLA = g_ui8_14a_Buffer[1];
            INS = g_ui8_14a_Buffer[2];
            P1 = g_ui8_14a_Buffer[3];
            P2 = g_ui8_14a_Buffer[4];
            LC = g_ui8_14a_Buffer[5];

            ui8_cb14ASendBuffer = 3;

            switch(CLA)
            {
            case 0x00:

                switch(INS)
                {
                case 0xa4: // SELECT

                     pFile = 0;
                     cbFile = 0;

                     if((P1 == 0x04) && (P2 == 0x00))
                     {
                         if(LC == sizeof(NDEF_AID))
                         {
                             if(!memcmp(NDEF_AID, g_ui8_14a_Buffer + 6, sizeof(NDEF_AID)))
                             {
                                 ui8_14ASendBuffer[1] = 0x90;
                                 ui8_14ASendBuffer[2] = 0x00;
                             }
                             else
                             {
                                 ui8_14ASendBuffer[1] = 0x6A; // FILE_NOT_FOUND
                                 ui8_14ASendBuffer[2] = 0x82;
                             }
                         }
                         else
                         {
                             ui8_14ASendBuffer[1] = 0x67; // WRONG_LENGTH
                             ui8_14ASendBuffer[2] = 0x00;
                         }
                     }
                     else if((P1 == 0x00) && (P2 == 0x0c))
                     {
                         if(LC == 2)
                         {
                             if(!memcmp(NDEF_FID_CC, g_ui8_14a_Buffer + 6, 2)) // TODO: simplify
                             {
                                 pFile = NDEF_CC_FILE_DATA;
                                 cbFile = sizeof(NDEF_CC_FILE_DATA);

                                 ui8_14ASendBuffer[1] = 0x90;
                                 ui8_14ASendBuffer[2] = 0x00;
                             }
                             else if(!memcmp(NDEF_FID, g_ui8_14a_Buffer + 6, 2)) // TODO: simplify
                             {
                                 pFile = NDEF_FILE_DATA;
                                 cbFile = sizeof(NDEF_FILE_DATA);

                                 ui8_14ASendBuffer[1] = 0x90;
                                 ui8_14ASendBuffer[2] = 0x00;
                             }
                             else
                             {
                                 ui8_14ASendBuffer[1] = 0x6a; // FILE_NOT_FOUND
                                 ui8_14ASendBuffer[2] = 0x82;
                             }
                         }
                         else
                         {
                             ui8_14ASendBuffer[1] = 0x67; // WRONG_LENGTH
                             ui8_14ASendBuffer[2] = 0x00;
                         }
                     }
                     else
                     {
                         ui8_14ASendBuffer[1] = 0x6b; // WRONG_P1P2
                         ui8_14ASendBuffer[2] = 0x00;
                     }

                     break;

                 case 0xb0: // READ_BINARY
                     if(pFile && cbFile)
                     {
                         offset = (P1 << 8) | P2;
                         if((offset + LC) <= ((uint16_t) cbFile)) // we know LE = LC here
                         {
                             memcpy(ui8_14ASendBuffer + 1, pFile + offset, LC);
                             ui8_14ASendBuffer[1 + LC] = 0x90;
                             ui8_14ASendBuffer[1 + LC + 1] = 0x00;
                             ui8_cb14ASendBuffer += LC;
                         }
                         else
                         {
                             ui8_14ASendBuffer[1] = 0x67; // WRONG_LENGTH
                             ui8_14ASendBuffer[2] = 0x00;
                         }
                     }
                     else
                     {
                         ui8_14ASendBuffer[1] = 0x6a; // FILE_NOT_FOUND
                         ui8_14ASendBuffer[2] = 0x82;
                     }

                     break;

                 default:
                     ui8_14ASendBuffer[1] = 0x6d; // INS_NOT_SUPPORTED
                     ui8_14ASendBuffer[2] = 0x00;
                 }

                break;

            default:
                ui8_14ASendBuffer[1] = 0x6e; // CLA_NOT_SUPPORTED
                ui8_14ASendBuffer[2] = 0x00;
            }

            *ppcbData = ui8_14ASendBuffer;
            *pcbData = ui8_cb14ASendBuffer;
        }
    }
    else if((PCB & BLOCK_PCB_TYPE_R_MASK) == BLOCK_PCB_TYPE_R_VALUE)
    {
        if((PCB & BLOCK_PCB_R_ACK_NACK_MASK) == BLOCK_PCB_R_ACK_NACK_VAL_NACK)
        {
            ui8_14ASendBuffer[0] = BLOCK_PCB_TYPE_R_VALUE | BLOCK_PCB_R_ACK_NACK_VAL_ACK | BLOCK_PCB_R_CID_FOLLOWING_NO | (PCB & BLOCK_PCB_R_BLOCK_NUMBER_MASK);
            ui8_14ASendBuffer[0] ^= BLOCK_PCB_R_BLOCK_NUMBER_MASK;
            ui8_cb14ASendBuffer = 1;

            *ppcbData = ui8_14ASendBuffer;
            *pcbData = ui8_cb14ASendBuffer;
        }

    }
    else if((PCB & BLOCK_PCB_TYPE_S_MASK) == BLOCK_PCB_TYPE_S_VALUE)
    {
        ui8_14ASendBuffer[0] = PCB;
        ui8_cb14ASendBuffer = 1;

        *ppcbData = ui8_14ASendBuffer;
        *pcbData = ui8_cb14ASendBuffer;
    }
}
```