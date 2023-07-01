//*****************************************************************************
//
// usci_b_spi.c - Driver for the usci_b_spi Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup usci_b_spi_api usci_b_spi
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_USCI_Bx__
#include "usci_b_spi.h"

#include <assert.h>

bool USCI_B_SPI_initMaster(uint16_t baseAddress, USCI_B_SPI_initMasterParam *param)
{
    //Disable the USCI Module
    HWREG8(baseAddress + OFS_UCBxCTL1) |= UCSWRST;

    //Reset OFS_UCBxCTL0 values
    HWREG8(baseAddress + OFS_UCBxCTL0) &= ~(UCCKPH + UCCKPL + UC7BIT + UCMSB +
        UCMST + UCMODE_3 + UCSYNC);

    //Reset OFS_UCBxCTL1 values
    HWREG8(baseAddress + OFS_UCBxCTL1) &= ~(UCSSEL_3);

    //Select Clock
    HWREG8(baseAddress + OFS_UCBxCTL1) |= param->selectClockSource;

    HWREG16(baseAddress + OFS_UCBxBRW) =
        (uint16_t)(param->clockSourceFrequency / param->desiredSpiClock);

    /*
     * Configure as SPI master mode.
     * Clock phase select, polarity, msb
     * UCMST = Master mode
     * UCSYNC = Synchronous mode
     * UCMODE_0 = 3-pin SPI
     */
    HWREG8(baseAddress + OFS_UCBxCTL0) |= (
        param->msbFirst +
        param->clockPhase +
        param->clockPolarity +
        UCMST +
        UCSYNC +
        UCMODE_0
        );

    return ( STATUS_SUCCESS) ;
}

void USCI_B_SPI_changeMasterClock(uint16_t baseAddress,
    USCI_B_SPI_changeMasterClockParam *param)
{
    //Disable the USCI Module
    HWREG8(baseAddress + OFS_UCBxCTL1) |= UCSWRST;

    HWREG8(baseAddress + OFS_UCBxBRW) =
        (uint16_t)(param->clockSourceFrequency / param->desiredSpiClock);

    //Reset the UCSWRST bit to enable the USCI Module
    HWREG8(baseAddress + OFS_UCBxCTL1) &= ~(UCSWRST);
}
bool USCI_B_SPI_initSlave (uint16_t baseAddress,
    uint8_t msbFirst,
    uint8_t clockPhase,
    uint8_t clockPolarity
    )
{
    //Disable USCI Module
    HWREG8(baseAddress + OFS_UCBxCTL1)  |= UCSWRST;

    //Reset OFS_UCBxCTL0 register
    HWREG8(baseAddress + OFS_UCBxCTL0) &= ~(UCMSB +
                                            UC7BIT +
                                            UCMST +
                                            UCCKPL +
                                            UCCKPH +
                                            UCMODE_3
                                            );

    //Clock polarity, phase select, msbFirst, SYNC, Mode0
    HWREG8(baseAddress + OFS_UCBxCTL0) |= ( clockPhase +
                                            clockPolarity +
                                            msbFirst +
                                            UCSYNC +
                                            UCMODE_0
                                            );

    return ( STATUS_SUCCESS) ;
}

void USCI_B_SPI_changeClockPhasePolarity (uint16_t baseAddress,
    uint8_t clockPhase,
    uint8_t clockPolarity
    )
{

  //Disable the USCI Module
  HWREG8(baseAddress + OFS_UCBxCTL1) |= UCSWRST;

  HWREG8(baseAddress + OFS_UCBxCTL0) &= ~(UCCKPH + UCCKPL);

  HWREG8(baseAddress + OFS_UCBxCTL0) |= (
        clockPhase +
        clockPolarity
          );

  //Reset the UCSWRST bit to enable the USCI Module
  HWREG8(baseAddress + OFS_UCBxCTL1) &= ~(UCSWRST);
}

void USCI_B_SPI_transmitData ( uint16_t baseAddress,
    uint8_t transmitData
    )
{
    HWREG8(baseAddress + OFS_UCBxTXBUF) = transmitData;
}

uint8_t USCI_B_SPI_receiveData (uint16_t baseAddress)
{
    return ( HWREG8(baseAddress + OFS_UCBxRXBUF)) ;
}

void USCI_B_SPI_enableInterrupt (uint16_t baseAddress,
    uint8_t mask
    )
{
    HWREG8(baseAddress + OFS_UCBxIE) |= mask;
}

void USCI_B_SPI_disableInterrupt (uint16_t baseAddress,
    uint8_t mask
    )
{
    HWREG8(baseAddress + OFS_UCBxIE) &= ~mask;
}

uint8_t USCI_B_SPI_getInterruptStatus (uint16_t baseAddress,
    uint8_t mask
    )
{
    return ( HWREG8(baseAddress + OFS_UCBxIFG) & mask );
}

void USCI_B_SPI_clearInterrupt (uint16_t baseAddress,
    uint8_t mask
    )
{
    HWREG8(baseAddress + OFS_UCBxIFG) &=  ~mask;
}

void USCI_B_SPI_enable (uint16_t baseAddress)
{
    //Reset the UCSWRST bit to enable the USCI Module
    HWREG8(baseAddress + OFS_UCBxCTL1) &= ~(UCSWRST);
}

void USCI_B_SPI_disable (uint16_t baseAddress)
{
    //Set the UCSWRST bit to disable the USCI Module
    HWREG8(baseAddress + OFS_UCBxCTL1) |= UCSWRST;
}

uint32_t USCI_B_SPI_getReceiveBufferAddressForDMA (uint16_t baseAddress)
{
    return ( baseAddress + OFS_UCBxRXBUF );
}

uint32_t USCI_B_SPI_getTransmitBufferAddressForDMA (uint16_t baseAddress)
{
    return ( baseAddress + OFS_UCBxTXBUF );
}

uint8_t USCI_B_SPI_isBusy (uint16_t baseAddress)
{
    //Return the bus busy status.
    return (HWREG8(baseAddress + OFS_UCBxSTAT) & UCBUSY);
}


#endif
//*****************************************************************************
//
//! Close the doxygen group for usci_b_spi_api
//! @}
//
//*****************************************************************************
