//*****************************************************************************
//
// usci_a_uart.h - Driver for the USCI_A_UART Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_A_UART_H__
#define __MSP430WARE_USCI_A_UART_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_USCI_Ax__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "inc/hw_memmap.h"
//*****************************************************************************
//
// The following values are the sync characters possible
//
//*****************************************************************************
#define DEFAULT_SYNC                                                       0x00
#define USCI_A_UART_AUTOMATICBAUDRATE_SYNC                                 0x55

//*****************************************************************************
//
//! \brief Used in the USCI_A_UART_init() function as the param parameter.
//
//*****************************************************************************
typedef struct USCI_A_UART_initParam {
    //! Selects Clock source.
    //! \n Valid values are:
    //! - \b USCI_A_UART_CLOCKSOURCE_SMCLK
    //! - \b USCI_A_UART_CLOCKSOURCE_ACLK
    uint8_t selectClockSource;
    //! Is the value to be written into UCBRx bits
    uint16_t clockPrescalar;
    //! Is First modulation stage register setting. This value is a pre-
    //! calculated value which can be obtained from the Device Users Guide.
    //! This value is written into UCBRFx bits of UCAxMCTLW.
    uint8_t firstModReg;
    //! Is Second modulation stage register setting. This value is a pre-
    //! calculated value which can be obtained from the Device Users Guide.
    //! This value is written into UCBRSx bits of UCAxMCTLW.
    uint8_t secondModReg;
    //! Is the desired parity.
    //! \n Valid values are:
    //! - \b USCI_A_UART_NO_PARITY [Default]
    //! - \b USCI_A_UART_ODD_PARITY
    //! - \b USCI_A_UART_EVEN_PARITY
    uint8_t parity;
    //! Controls direction of receive and transmit shift register.
    //! \n Valid values are:
    //! - \b USCI_A_UART_MSB_FIRST
    //! - \b USCI_A_UART_LSB_FIRST [Default]
    uint8_t msborLsbFirst;
    //! Indicates one/two STOP bits
    //! \n Valid values are:
    //! - \b USCI_A_UART_ONE_STOP_BIT [Default]
    //! - \b USCI_A_UART_TWO_STOP_BITS
    uint8_t numberofStopBits;
    //! Selects the mode of operation
    //! \n Valid values are:
    //! - \b USCI_A_UART_MODE [Default]
    //! - \b USCI_A_UART_IDLE_LINE_MULTI_PROCESSOR_MODE
    //! - \b USCI_A_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE
    //! - \b USCI_A_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE
    uint8_t uartMode;
    //! Indicates low frequency or oversampling baud generation
    //! \n Valid values are:
    //! - \b USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
    //! - \b USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION
    uint8_t overSampling;
} USCI_A_UART_initParam;


//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: USCI_A_UART_init().
//
//*****************************************************************************
#define USCI_A_UART_NO_PARITY                                              0x00
#define USCI_A_UART_ODD_PARITY                                             0x01
#define USCI_A_UART_EVEN_PARITY                                            0x02

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: USCI_A_UART_init().
//
//*****************************************************************************
#define USCI_A_UART_MSB_FIRST                                             UCMSB
#define USCI_A_UART_LSB_FIRST                                              0x00

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: USCI_A_UART_init().
//
//*****************************************************************************
#define USCI_A_UART_MODE                                               UCMODE_0
#define USCI_A_UART_IDLE_LINE_MULTI_PROCESSOR_MODE                     UCMODE_1
#define USCI_A_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE                   UCMODE_2
#define USCI_A_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE                  UCMODE_3

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: USCI_A_UART_init().
//
//*****************************************************************************
#define USCI_A_UART_CLOCKSOURCE_SMCLK                             UCSSEL__SMCLK
#define USCI_A_UART_CLOCKSOURCE_ACLK                               UCSSEL__ACLK

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: USCI_A_UART_init().
//
//*****************************************************************************
#define USCI_A_UART_ONE_STOP_BIT                                           0x00
#define USCI_A_UART_TWO_STOP_BITS                                         UCSPB

//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: USCI_A_UART_init().
//
//*****************************************************************************
#define USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION                       0x01
#define USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION                      0x00

//*****************************************************************************
//
// The following are values that can be passed to the mask parameter for
// functions: USCI_A_UART_enableInterrupt(), and
// USCI_A_UART_disableInterrupt().
//
//*****************************************************************************
#define USCI_A_UART_RECEIVE_INTERRUPT                                    UCRXIE
#define USCI_A_UART_TRANSMIT_INTERRUPT                                   UCTXIE
#define USCI_A_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT                     UCRXEIE
#define USCI_A_UART_BREAKCHAR_INTERRUPT                                 UCBRKIE

//*****************************************************************************
//
// The following are values that can be passed to the mask parameter for
// functions: USCI_A_UART_getInterruptStatus(), and
// USCI_A_UART_clearInterrupt() as well as returned by the
// USCI_A_UART_getInterruptStatus() function.
//
//*****************************************************************************
#define USCI_A_UART_RECEIVE_INTERRUPT_FLAG                              UCRXIFG
#define USCI_A_UART_TRANSMIT_INTERRUPT_FLAG                             UCTXIFG

//*****************************************************************************
//
// The following are values that can be passed to the mask parameter for
// functions: USCI_A_UART_queryStatusFlags() as well as returned by the
// USCI_A_UART_queryStatusFlags() function.
//
//*****************************************************************************
#define USCI_A_UART_LISTEN_ENABLE                                      UCLISTEN
#define USCI_A_UART_FRAMING_ERROR                                          UCFE
#define USCI_A_UART_OVERRUN_ERROR                                          UCOE
#define USCI_A_UART_PARITY_ERROR                                           UCPE
#define USCI_A_UART_BREAK_DETECT                                          UCBRK
#define USCI_A_UART_RECEIVE_ERROR                                       UCRXERR
#define USCI_A_UART_ADDRESS_RECEIVED                                     UCADDR
#define USCI_A_UART_IDLELINE                                             UCIDLE
#define USCI_A_UART_BUSY                                                 UCBUSY

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Advanced initialization routine for the UART block. The values to be
//! written into the clockPrescalar, firstModReg, secondModReg and overSampling
//! parameters should be pre-computed and passed into the initialization
//! function.
//!
//! Upon successful initialization of the UART block, this function will have
//! initialized the module, but the UART block still remains disabled and must
//! be enabled with USCI_A_UART_enable(). To calculate values for
//! clockPrescalar, firstModReg, secondModReg and overSampling please use the
//! link below.
//!
//! http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param param is the pointer to struct for initialization.
//!
//! Modified bits are \b UCPEN, \b UCPAR, \b UCMSB, \b UC7BIT, \b UCSPB, \b
//! UCMODEx and \b UCSYNC of \b UCAxCTL0 register; bits \b UCSSELx and \b
//! UCSWRST of \b UCAxCTL1 register.
//!
//! \return STATUS_SUCCESS or STATUS_FAIL of the initialization process
//
//*****************************************************************************
extern bool USCI_A_UART_init(uint16_t baseAddress,
                             USCI_A_UART_initParam *param);

//*****************************************************************************
//
//! \brief Transmits a byte from the UART Module.
//!
//! This function will place the supplied data into UART transmit data register
//! to start transmission
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param transmitData data to be transmitted from the UART module
//!
//! Modified bits of \b UCAxTXBUF register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_transmitData(uint16_t baseAddress,
                                     uint8_t transmitData);

//*****************************************************************************
//
//! \brief Receives a byte that has been sent to the UART Module.
//!
//! This function reads a byte of data from the UART receive data Register.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! Modified bits of \b UCAxRXBUF register.
//!
//! \return Returns the byte received from by the UART module, cast as an
//!         uint8_t.
//
//*****************************************************************************
extern uint8_t USCI_A_UART_receiveData(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Enables individual UART interrupt sources.
//!
//! Enables the indicated UART interrupt sources.  The interrupt flag is first
//! and then the corresponding interrupt is enabled. Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor. Does not clear interrupt flags.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param mask is the bit mask of the interrupt sources to be enabled.
//!        Mask value is the logical OR of any of the following:
//!        - \b USCI_A_UART_RECEIVE_INTERRUPT - Receive interrupt
//!        - \b USCI_A_UART_TRANSMIT_INTERRUPT - Transmit interrupt
//!        - \b USCI_A_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT - Receive
//!           erroneous-character interrupt enable
//!        - \b USCI_A_UART_BREAKCHAR_INTERRUPT - Receive break character
//!           interrupt enable
//!
//! Modified bits of \b UCAxCTL1 register and bits of \b UCAxIE register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_enableInterrupt(uint16_t baseAddress,
                                        uint8_t mask);

//*****************************************************************************
//
//! \brief Disables individual UART interrupt sources.
//!
//! Disables the indicated UART interrupt sources. Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param mask is the bit mask of the interrupt sources to be disabled.
//!        Mask value is the logical OR of any of the following:
//!        - \b USCI_A_UART_RECEIVE_INTERRUPT - Receive interrupt
//!        - \b USCI_A_UART_TRANSMIT_INTERRUPT - Transmit interrupt
//!        - \b USCI_A_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT - Receive
//!           erroneous-character interrupt enable
//!        - \b USCI_A_UART_BREAKCHAR_INTERRUPT - Receive break character
//!           interrupt enable
//!
//! Modified bits of \b UCAxCTL1 register and bits of \b UCAxIE register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_disableInterrupt(uint16_t baseAddress,
                                         uint8_t mask);

//*****************************************************************************
//
//! \brief Gets the current UART interrupt status.
//!
//! This returns the interrupt status for the UART module based on which flag
//! is passed.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param mask is the masked interrupt flag status to be returned.
//!        Mask value is the logical OR of any of the following:
//!        - \b USCI_A_UART_RECEIVE_INTERRUPT_FLAG - Receive interrupt flag
//!        - \b USCI_A_UART_TRANSMIT_INTERRUPT_FLAG - Transmit interrupt flag
//!
//! Modified bits of \b UCAxIFG register.
//!
//! \return Logical OR of any of the following:
//!         - \b USCI_A_UART_RECEIVE_INTERRUPT_FLAG Receive interrupt flag
//!         - \b USCI_A_UART_TRANSMIT_INTERRUPT_FLAG Transmit interrupt flag
//!         \n indicating the status of the masked flags
//
//*****************************************************************************
extern uint8_t USCI_A_UART_getInterruptStatus(uint16_t baseAddress,
                                              uint8_t mask);

//*****************************************************************************
//
//! \brief Clears UART interrupt sources.
//!
//! The UART interrupt source is cleared, so that it no longer asserts. The
//! highest interrupt flag is automatically cleared when an interrupt vector
//! generator is used.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param mask is a bit mask of the interrupt sources to be cleared.
//!        Mask value is the logical OR of any of the following:
//!        - \b USCI_A_UART_RECEIVE_INTERRUPT_FLAG - Receive interrupt flag
//!        - \b USCI_A_UART_TRANSMIT_INTERRUPT_FLAG - Transmit interrupt flag
//!
//! Modified bits of \b UCAxIFG register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_clearInterrupt(uint16_t baseAddress,
                                       uint8_t mask);

//*****************************************************************************
//
//! \brief Enables the UART block.
//!
//! This will enable operation of the UART block.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! Modified bits are \b UCSWRST of \b UCAxCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables the UART block.
//!
//! This will disable operation of the UART block.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! Modified bits are \b UCSWRST of \b UCAxCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_disable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Gets the current UART status flags.
//!
//! This returns the status for the UART module based on which flag is passed.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param mask is the masked interrupt flag status to be returned.
//!        Mask value is the logical OR of any of the following:
//!        - \b USCI_A_UART_LISTEN_ENABLE
//!        - \b USCI_A_UART_FRAMING_ERROR
//!        - \b USCI_A_UART_OVERRUN_ERROR
//!        - \b USCI_A_UART_PARITY_ERROR
//!        - \b USCI_A_UART_BREAK_DETECT
//!        - \b USCI_A_UART_RECEIVE_ERROR
//!        - \b USCI_A_UART_ADDRESS_RECEIVED
//!        - \b USCI_A_UART_IDLELINE
//!        - \b USCI_A_UART_BUSY
//!
//! Modified bits of \b UCAxSTAT register.
//!
//! \return Logical OR of any of the following:
//!         - \b USCI_A_UART_LISTEN_ENABLE
//!         - \b USCI_A_UART_FRAMING_ERROR
//!         - \b USCI_A_UART_OVERRUN_ERROR
//!         - \b USCI_A_UART_PARITY_ERROR
//!         - \b USCI_A_UART_BREAK_DETECT
//!         - \b USCI_A_UART_RECEIVE_ERROR
//!         - \b USCI_A_UART_ADDRESS_RECEIVED
//!         - \b USCI_A_UART_IDLELINE
//!         - \b USCI_A_UART_BUSY
//!         \n indicating the status of the masked interrupt flags
//
//*****************************************************************************
extern uint8_t USCI_A_UART_queryStatusFlags(uint16_t baseAddress,
                                            uint8_t mask);

//*****************************************************************************
//
//! \brief Sets the UART module in dormant mode
//!
//! Puts USCI in sleep mode. Only characters that are preceded by an idle-line
//! or with address bit set UCRXIFG. In UART mode with automatic baud-rate
//! detection, only the combination of a break and sync field sets UCRXIFG.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! Modified bits of \b UCAxCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_setDormant(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Re-enables UART module from dormant mode
//!
//! Not dormant. All received characters set UCRXIFG.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! Modified bits are \b UCDORM of \b UCAxCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_resetDormant(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Transmits the next byte to be transmitted marked as address
//! depending on selected multiprocessor mode
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//! \param transmitAddress is the next byte to be transmitted
//!
//! Modified bits of \b UCAxTXBUF register and bits of \b UCAxCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_transmitAddress(uint16_t baseAddress,
                                        uint8_t transmitAddress);

//*****************************************************************************
//
//! \brief Transmit break.
//!
//! Transmits a break with the next write to the transmit buffer. In UART mode
//! with automatic baud-rate detection,
//! USCI_A_UART_AUTOMATICBAUDRATE_SYNC(0x55) must be written into UCAxTXBUF to
//! generate the required break/sync fields. Otherwise, DEFAULT_SYNC(0x00) must
//! be written into the transmit buffer. Also ensures module is ready for
//! transmitting the next data.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! Modified bits of \b UCAxTXBUF register and bits of \b UCAxCTL1 register.
//!
//! \return None
//
//*****************************************************************************
extern void USCI_A_UART_transmitBreak(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Returns the address of the RX Buffer of the UART for the DMA module.
//!
//! Returns the address of the UART RX Buffer. This can be used in conjunction
//! with the DMA to store the received data directly to memory.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! \return Address of RX Buffer
//
//*****************************************************************************
extern uint32_t USCI_A_UART_getReceiveBufferAddressForDMA(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Returns the address of the TX Buffer of the UART for the DMA module.
//!
//! Returns the address of the UART TX Buffer. This can be used in conjunction
//! with the DMA to obtain transmitted data directly from memory.
//!
//! \param baseAddress is the base address of the USCI_A_UART module.
//!
//! \return Address of TX Buffer
//
//*****************************************************************************
extern uint32_t USCI_A_UART_getTransmitBufferAddressForDMA(uint16_t baseAddress);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_USCI_A_UART_H__
