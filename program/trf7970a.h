/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "board.h"

#define TRF_ENABLE()        TRF_EN_PORT |= TRF_EN_BIT
#define TRF_DISABLE()       TRF_EN_PORT &= ~TRF_EN_BIT

#define TRF_CS_ENABLE()     TRF_CS_PORT &= ~TRF_CS_BIT
#define TRF_CS_DISABLE()    do{TRF_SPI_WAIT_BUSY(); TRF_CS_PORT |= TRF_CS_BIT;} while(0)

#define TRF_IRQ_READ()      (TRF_IRQ_PORT & TRF_IRQ_BIT)
#define TRF_IRQ_ENABLE()    do{TRF_IRQ_IFG &= ~TRF_IRQ_BIT; TRF_IRQ_READ() ? (IRQ_Global |= IRQ_SOURCE_TRF7970A) : (IRQ_Global &= ~IRQ_SOURCE_TRF7970A); TRF_IRQ_IE |= TRF_IRQ_BIT;} while(0)
#define TRF_IRQ_DISABLE()   TRF_IRQ_IE &= ~TRF_IRQ_BIT
#define TRF_IRQ_CLEAR()     TRF_IRQ_IFG &= ~TRF_IRQ_BIT

#define TRF_SPI_WAIT_BUSY() while(UCB1STATW & UCBUSY__BUSY)
#define TRF_SPI_WAIT_TX()   while(!(UCB1IFG & UCTXIFG))
#define TRF_SPI_WAIT_RX()   while(!(UCB1IFG & UCRXIFG))

#define TRF_SPI_SEND(s)     do{UCB1TXBUF = s; TRF_SPI_WAIT_TX(); } while(0) // Usually, WAIT_TX before sending, but 1/ we're sure 1st one will be ok, 2/ more efficient for direct reading after
#define TRF_SPI_RECV(r)     do{UCB1TXBUF = 0x00; TRF_SPI_WAIT_BUSY(); r = UCB1RXBUF;} while(0)   // More efficient than playing with RX/TX or IRQ...

void TRF7970A_init();
void TRF7970A_SPI_Send_raw(const uint8_t *pcbData, uint8_t cbData);
void TRF7970A_SPI_DirectCommand_internal(uint8_t CommandCode_Preparred);
uint8_t TRF7970A_SPI_Read_SingleRegister_internal(uint8_t Register_Prepared);
void TRF7970A_SPI_Write_SingleRegister_internal(uint8_t Register_Prepared, const uint8_t Value);
void TRF7970A_SPI_Read_ContinuousRegister_internal(uint8_t Register_Prepared, uint8_t *pbData, uint8_t cbData);

#define TRF7970A_SPI_Write_Packet(pcbData, cbData)  TRF7970A_SPI_Write_Packet_TYPED(pcbData, cbData, MK_DC(TRF79X0_TRANSMIT_CRC_CMD))
#define TRF7970A_SPI_Write_Packet_NOCRC(pcbData, cbData)  TRF7970A_SPI_Write_Packet_TYPED(pcbData, cbData, MK_DC(TRF79X0_TRANSMIT_NO_CRC_CMD))
void TRF7970A_SPI_Write_Packet_TYPED(const uint8_t *pcbData, uint8_t cbData, const uint8_t type);

uint8_t TRF7970A_SPI_waitIrq();

#define MK_DC(x) ((x & TRF79X0_ADDRESS_MASK) | TRF79X0_CONTROL_CMD)
#define MK_RS(x) ((x & TRF79X0_ADDRESS_MASK) | TRF79X0_CONTROL_REG_READ  | TRF79X0_REG_MODE_SINGLE)
#define MK_WS(x) ((x & TRF79X0_ADDRESS_MASK) | TRF79X0_CONTROL_REG_WRITE | TRF79X0_REG_MODE_SINGLE)
#define MK_RC(x) ((x & TRF79X0_ADDRESS_MASK) | TRF79X0_CONTROL_REG_READ  | TRF79X0_REG_MODE_CONTINUOUS)
#define MK_WC(x) ((x & TRF79X0_ADDRESS_MASK) | TRF79X0_CONTROL_REG_WRITE | TRF79X0_REG_MODE_CONTINUOUS)

#define TRF7970A_SPI_DirectCommand(CommandCode)                         TRF7970A_SPI_DirectCommand_internal(MK_DC(CommandCode))
#define TRF7970A_SPI_Read_SingleRegister(Register)                      TRF7970A_SPI_Read_SingleRegister_internal(MK_RS(Register))
#define TRF7970A_SPI_Write_SingleRegister(Register, Value)              TRF7970A_SPI_Write_SingleRegister_internal(MK_WS(Register), Value)
#define TRF7970A_SPI_Read_ContinuousRegister(Register, pbData, cbData)  TRF7970A_SPI_Read_ContinuousRegister_internal(MK_RC(Register), pbData, cbData)

#define TRF7970A_getIrqStatus()     TRF7970A_SPI_Read_SingleRegister(TRF79X0_IRQ_STATUS_REG)
#define TRF7970A_clearIrqStatus()   TRF7970A_getIrqStatus()


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
#define TRF79X0_ISO_NFC_OR_CARD_EMULATION_MODE  0x20 // 6.15.3.1.2
#define TRF79X0_ISO_NFC_TARGET              0x00
#define TRF79X0_ISO_NFC_INITIATOR           0x10
#define TRF79X0_NFC_PASSIVE_MODE            0x00
#define TRF79X0_NFC_ACTIVE_MODE             0x08
#define TRF79X0_NFC_NORMAL_MODE             0x00
#define TRF79X0_NFC_CARD_EMULATION_MODE     0x04 // Fixed from 6.15.3.1.2
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
#define TRF79X0_NFC_TARGET_PROTOCOL_PT_OR_CE            0x08 // from 6.17
#define TRF79X0_NFC_TARGET_PROTOCOL_ISO14443A           0x00
#define TRF79X0_NFC_TARGET_PROTOCOL_ISO14443B           0x04 // fixed from 0x40
#define TRF79X0_NFC_TARGET_PROTOCOL_KBPS_MASK           0x03
#define TRF79X0_NFC_TARGET_PROTOCOL_106KBPS             0x01
#define TRF79X0_NFC_TARGET_PROTOCOL_212KBPS             0x02
#define TRF79X0_NFC_TARGET_PROTOCOL_424KBPS             0x03

// 6.15.3.3.10
#define TRF79X0_NFC_TARGET_PROTOCOL_14B_COMMAND         (TRF79X0_NFC_TARGET_PROTOCOL_RF_COLLISION_LEVEL | TRF79X0_NFC_TARGET_PROTOCOL_ISO14443B | TRF79X0_NFC_TARGET_PROTOCOL_106KBPS) // TRF79X0_NFC_TARGET_PROTOCOL_RF_WAKE_UP -- to deal with RF field ON/OFF
#define TRF79X0_NFC_TARGET_PROTOCOL_14A_COMMAND         (TRF79X0_NFC_TARGET_PROTOCOL_RF_WAKE_UP | TRF79X0_NFC_TARGET_PROTOCOL_RF_COLLISION_LEVEL | TRF79X0_NFC_TARGET_PROTOCOL_ISO14443A)

#define TRF79X0_IRQ_STATUS_COL_ERR                      0x01 // The external RF field was present so the collision avoidance could not be carried out.
#define TRF79X0_IRQ_STATUS_COL                          0x02 // The system has finished collision avoidance and the minimum wait time is elapsed.
#define TRF79X0_IRQ_STATUS_RF                           0x04 // Sufficient RF signal level for operation was reached or lost
#define TRF79X0_IRQ_STATUS_SDD                          0x08 // SDD (passive target at 106 kbps) successfully finished
#define TRF79X0_IRQ_STATUS_ERR1                         0x10 // Any protocol error
#define TRF79X0_IRQ_STATUS_FIFO                         0x20 // Signals FIFO high or low as set in the Adjustable FIFO IRQ Levels (0x14) register
#define TRF79X0_IRQ_STATUS_SRX                          0x40 // Signals that RX SOF was received and RX is in progress. The flag is set at the start of RX but the interrupt request (IRQ = 1) is sent when RX is finished.
#define TRF79X0_IRQ_STATUS_TX                           0x80 // Signals that TX is in progress. The flag is set at the start of TX but the interrupt request (IRQ = 1) is sent when TX is finished.
