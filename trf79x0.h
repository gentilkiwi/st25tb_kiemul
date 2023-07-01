#pragma once
#include <mcu.h>
#include "nfc_spi.h"

#define SPI_MODULE_BASE_ADDR    USCI_B0_BASE
#define SPI_PORT                GPIO_PORT_P3
#define SPI_CLK                 GPIO_PIN2
#define SPI_MOSI                GPIO_PIN0
#define SPI_MISO                GPIO_PIN1
#define SPI_SS_PORT             GPIO_PORT_P4
#define SPI_SS_POUT             P4OUT
#define SPI_SS                  GPIO_PIN2
#define TRF_EN_PORT             GPIO_PORT_P4
#define TRF_EN                  GPIO_PIN1

#define TRF_IRQ_PORT            GPIO_PORT_P2
#define TRF_IRQ_PIN             P2IN
#define TRF_IRQ                 GPIO_PIN2


typedef enum _tTRF79x0_IRQFlag {
    IRQ_STATUS_IDLE = 0x00,
    IRQ_STATUS_COLLISION_ERROR = 0x01,
    IRQ_STATUS_COLLISION_AVOID_FINISHED = 0x02,
    IRQ_STATUS_RF_FIELD_CHANGE = 0x04,
    IRQ_STATUS_SDD_COMPLETE = 0x08,
    IRQ_STATUS_PROTOCOL_ERROR = 0x10,
    IRQ_STATUS_FIFO_HIGH_OR_LOW  = 0x20,
    IRQ_STATUS_RX_COMPLETE = 0x40,
    IRQ_STATUS_TX_COMPLETE = 0x80,
    IRQ_STATUS_OVERFLOW = 0xFC,
    IRQ_STATUS_NO_RESPONSE = 0xFE,
    IRQ_STATUS_TIME_OUT = 0xFF
} tTRF79x0_IRQFlag;

typedef enum _tTRF79x0_Mode {
    Initiator,
    Target,
} tTRF79x0_Mode;

extern volatile uint8_t g_ui8IrqFlag;
extern volatile uint8_t g_bBitclockFlag;

#define NFC_FIFO_SIZE       127//255

extern uint8_t g_ui8FifoBuffer[NFC_FIFO_SIZE];
extern uint8_t g_ui8cbFifoBuffer;


extern void TRF79x0_init();
extern void TRF79x0_directCommand(uint8_t ui8Command);
extern void TRF79x0_writeSingle(uint8_t ui8Value, uint8_t ui8Register);
extern void TRF79x0_writeCont(uint8_t * pui8Payload, uint8_t ui8Register, uint8_t ui8Length);
extern void TRF79x0_readSingle(uint8_t * pui8Value, uint8_t ui8Register);
extern void TRF79x0_readCont(uint8_t * pui8Payload, uint8_t ui8Register, uint8_t ui8Length);

extern bool TRF79x0_Send(tTRF79x0_Mode Mode, const uint8_t *pui8Payload, const uint8_t ui8Length);
extern bool TRF79x0_Initiator_Send_Recv(const uint8_t *pui8Payload, const uint8_t ui8Length, const uint16_t ui16TimeOut);
extern void TRF79x0_ignoreCmd();
extern tTRF79x0_IRQFlag TRF79x0_irqHandler(tTRF79x0_Mode Mode, uint16_t ui16TimeOut);

//*****************************************************************************
//
// TRF79X0 Register Definitions.
//
//*****************************************************************************
#define TRF79X0_CHIP_STATUS_CTRL_REG        0x00
#define TRF79X0_ISO_CONTROL_REG             0x01
#define TRF79X0_ISO14443B_OPTIONS_REG       0x02
#define TRF79X0_ISO14443A_OPTIONS_REG       0x03
#define TRF79X0_TX_TIMER_EPC_HIGH           0x04
#define TRF79X0_TX_TIMER_EPC_LOW            0x05
#define TRF79X0_TX_PULSE_LENGTH_CTRL_REG    0x06
#define TRF79X0_RX_NO_RESPONSE_WAIT_REG     0x07
#define TRF79X0_RX_WAIT_TIME_REG            0x08
#define TRF79X0_MODULATOR_CONTROL_REG       0x09
#define TRF79X0_RX_SPECIAL_SETTINGS_REG     0x0A
#define TRF79X0_REGULATOR_CONTROL_REG       0x0B
#define TRF79X0_IRQ_STATUS_REG              0x0C
#define TRF79X0_IRQ_MASK_REG                0x0D
#define TRF79X0_COLLISION_POSITION_REG      0x0E
#define TRF79X0_RSSI_LEVEL_REG              0x0F
#define TRF79X0_SPECIAL_FUNC_1_REG          0x10
#define TRF79X0_SPECIAL_FUNC_2_REG          0x11
#define TRF79X0_FIFO_IRQ_LEVEL              0x14
#define TRF79X0_NFC_LOW_DETECTION_LEVEL     0x16
#define TRF79X0_NFC_ID_REG                  0x17
#define TRF79X0_NFC_TARGET_LEVEL_REG        0x18
#define TRF79X0_NFC_TARGET_PROTOCOL_REG     0x19
#define TRF79X0_TEST_SETTING1_REG           0x1A
#define TRF79X0_TEST_SETTING2_REG           0x1B
#define TRF79X0_FIFO_STATUS_REG             0x1C
#define TRF79X0_TX_LENGTH_BYTE1_REG         0x1D
#define TRF79X0_TX_LENGTH_BYTE2_REG         0x1E
#define TRF79X0_FIFO_REG                    0x1F

//*****************************************************************************
//
// TRF79X0 TRF79X0_CHIP_STATUS_CTRL_REG Register Definitions.
//
//*****************************************************************************
#define TRF79X0_STATUS_CTRL_STANDBY_MODE    0x80
#define TRF79X0_STATUS_CTRL_ACTIVE_MODE     0x00
#define TRF79X0_STATUS_CTRL_DIRECT          0x40
#define TRF79X0_STATUS_CTRL_RF_ON           0x20
#define TRF79X0_STATUS_CTRL_RF_PWR_HALF     0x10
#define TRF79X0_STATUS_CTRL_RF_PWR_FULL     0x00
#define TRF79X0_STATUS_CTRL_AGC_ON          0x04
#define TRF79X0_STATUS_CTRL_RECEIVER_ON     0x02
#define TRF79X0_STATUS_CTRL_5V_SYSTEM       0x01
#define TRF79X0_STATUS_CTRL_3V_SYSTEM       0x00

//*****************************************************************************
//
// TRF79X0 TRF79X0_ISO_CONTROL Register Definitions.
//
//*****************************************************************************
#define TRF79X0_ISO_CONTROL_RX_CRC_N        0x80
#define TRF79X0_ISO_CONTROL_DIR_MODE        0x40
#define TRF79X0_ISO_NFC_TARGET              0x00
#define TRF79X0_ISO_NFC_INITIATOR           0x10
#define TRF79X0_NFC_PASSIVE_MODE            0x00
#define TRF79X0_NFC_ACTIVE_MODE             0x08
#define TRF79X0_NFC_NORMAL_MODE             0x00
#define TRF79X0_NFC_CARD_EMULATION_MODE     0x40
#define TRF79X0_ISO_CONTROL_14443A_106K     0x08

//*****************************************************************************
//
// TRF79X0 TRF79X0_MODULATOR_CONTROL_REG Register Definitions.
//
//*****************************************************************************
#define TRF79X0_MOD_CTRL_SYS_CLK_13_56MHZ   0x30
#define TRF79X0_MOD_CTRL_SYS_CLK_6_78MHZ    0x20
#define TRF79X0_MOD_CTRL_SYS_CLK_3_3MHZ     0x10
#define TRF79X0_MOD_CTRL_SYS_CLK_DISABLE    0x00
#define TRF79X0_MOD_CTRL_MOD_ASK_30         0x07
#define TRF79X0_MOD_CTRL_MOD_ASK_22         0x06
#define TRF79X0_MOD_CTRL_MOD_ASK_16         0x05
#define TRF79X0_MOD_CTRL_MOD_ASK_13         0x04
#define TRF79X0_MOD_CTRL_MOD_ASK_8_5        0x03
#define TRF79X0_MOD_CTRL_MOD_ASK_7          0x02
#define TRF79X0_MOD_CTRL_MOD_OOK_100        0x01
#define TRF79X0_MOD_CTRL_MOD_ASK_10         0x00

//*****************************************************************************
//
// TRF79X0 TRF79X0_REGULATOR_CONTROL_REG Register Definitions.
//
//*****************************************************************************
#define TRF79X0_REGULATOR_CTRL_AUTO_REG     0x80
#define TRF79X0_REGULATOR_CTRL_VRS_2_7V     0x00
#define TRF79X0_REGULATOR_CTRL_VRS_2_8V     0x01
#define TRF79X0_REGULATOR_CTRL_VRS_2_9V     0x02
#define TRF79X0_REGULATOR_CTRL_VRS_3_0V     0x03
#define TRF79X0_REGULATOR_CTRL_VRS_3_1V     0x04
#define TRF79X0_REGULATOR_CTRL_VRS_3_2V     0x05
#define TRF79X0_REGULATOR_CTRL_VRS_3_3V     0x06
#define TRF79X0_REGULATOR_CTRL_VRS_3_4V     0x07

//*****************************************************************************
//
// TRF79x0 Command Definitions.
//
//*****************************************************************************
#define TRF79X0_IDLE_CMD                                0x00
#define TRF79X0_SOFT_INIT_CMD                           0x03
#define TRF79X0_INITIAL_RF_COLLISION_AVOID_CMD          0x04
#define TRF79X0_PERFORM_RES_RF_COLLISION_AVOID_CMD      0x05
#define TRF79X0_PERFORM_RES_RF_COLLISION_AVOID_N0_CMD   0x06
#define TRF79X0_RESET_FIFO_CMD                          0x0F
#define TRF79X0_TRANSMIT_NO_CRC_CMD                     0x10
#define TRF79X0_TRANSMIT_CRC_CMD                        0x11
#define TRF79X0_DELAY_TRANSMIT_NO_CRC_CMD               0x12
#define TRF79X0_DELAY_TRANSMIT_CRC_CMD                  0x13
#define TRF79X0_TRANSMIT_NEXT_SLOT_CMD                  0x14
#define TRF79X0_CLOSE_SLOT_SEQUENCE_CMD                 0x15
#define TRF79X0_STOP_DECODERS_CMD                       0x16
#define TRF79X0_RUN_DECODERS_CMD                        0x17
#define TRF79X0_TEST_INTERNAL_RF_CMD                    0x18
#define TRF79X0_TEST_EXTERNAL_RF_CMD                    0x19
#define TRF79X0_RX_ADJUST_GAIN_CMD                      0x1A

//*****************************************************************************
//
// TRF79x0 Command/Address mode definitions.
//
//*****************************************************************************
#define TRF79X0_ADDRESS_MASK                            0x1F
#define TRF79X0_CONTROL_CMD                             0x80
#define TRF79X0_CONTROL_REG_READ                        0x40
#define TRF79X0_CONTROL_REG_WRITE                       0x00
#define TRF79X0_REG_MODE_SINGLE                         0x00
#define TRF79X0_REG_MODE_CONTINUOUS                     0x20

//*****************************************************************************
//
// TRF79X0 TRF79X0_RX_SPECIAL_SETTINGS_REG Register Definitions.
//
//*****************************************************************************
#define TRF79X0_RX_SP_SET_M848              0x20

//*****************************************************************************
//
// TRF79X0 TRF79X0_FIFO_STATUS_REG Register Definitions.
//
//*****************************************************************************
#define TRF79X0_FIFO_OVERFLOW                           0x80

//*****************************************************************************
//
// TRF79X0 TRF79X0_NFC_TARGET_PROTOCOL_REG Register Definitions.
//
//*****************************************************************************
#define TRF79X0_NFC_TARGET_PROTOCOL_RF_WAKE_UP          0x80
#define TRF79X0_NFC_TARGET_PROTOCOL_RF_COLLISION_LEVEL  0x40
#define TRF79X0_NFC_TARGET_PROTOCOL_FELICA              0x10
#define TRF79X0_NFC_TARGET_PROTOCOL_ISO14443A           0x00
#define TRF79X0_NFC_TARGET_PROTOCOL_ISO14443B           0x04 // fixed from 0x40
#define TRF79X0_NFC_TARGET_PROTOCOL_KBPS_MASK           0x03
#define TRF79X0_NFC_TARGET_PROTOCOL_106KBPS             0x01
#define TRF79X0_NFC_TARGET_PROTOCOL_212KBPS             0x02
#define TRF79X0_NFC_TARGET_PROTOCOL_424KBPS             0x03
