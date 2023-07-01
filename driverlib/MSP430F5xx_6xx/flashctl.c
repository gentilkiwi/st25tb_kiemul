//*****************************************************************************
//
// flashctl.c - Driver for the flashctl Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup flashctl_api flashctl
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_FLASH__
#include "flashctl.h"

#include <assert.h>

void FlashCtl_eraseSegment ( uint8_t *flash_ptr){
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Set Erase bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + ERASE;

    //Dummy write to erase Flash seg
    *flash_ptr = 0;

    //test busy
    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

    //Clear ERASE bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_eraseBank ( uint8_t *flash_ptr){
    uint16_t interruptState;

    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY);

    //FLASH34 errata: no concurrent access to flash bank while erasing
    interruptState = __get_interrupt_state();
    __disable_interrupt();
    __no_operation();

    //Set MERAS bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + MERAS;

    //Dummy write to erase Flash seg
    *flash_ptr = 0;

    //test busy
    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY);

    //FLASH34 errata
    //Re-enable interrupt state to whatever it was before
    if (interruptState & GIE)
    {
        __enable_interrupt();
    }

    //Clear MERAS bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_performMassErase ( uint8_t *flash_ptr){
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;
    
    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

    //Set MERAS bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + MERAS + ERASE;

    //Dummy write to erase Flash seg
    *flash_ptr = 0;

    //test busy
    while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

    //Clear MERAS bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

bool FlashCtl_performEraseCheck (uint8_t *flash_ptr,
    uint16_t numberOfBytes
    )
{
    uint16_t i;

    for (i = 0; i < numberOfBytes; i++)
    {
        //was erasing successfull?
        if ((*(flash_ptr + i)) != 0xFF){
            return ( STATUS_FAIL) ;
        }
    }
    return ( STATUS_SUCCESS) ;
}

void FlashCtl_write8 (uint8_t *data_ptr,
    uint8_t *flash_ptr,
    uint16_t count
    )
{
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + WRT;

    while (count > 0)
    {
        //test busy
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *data_ptr++;
        count--;
    }

    //Clear WRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_write16 (uint16_t *data_ptr,
    uint16_t *flash_ptr,
    uint16_t count
    )
{
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + WRT;

    while (count > 0)
    {
        //test busy
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *data_ptr++;
        count--;
    }

    //Clear WRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_write32 (uint32_t *data_ptr,
    uint32_t *flash_ptr,
    uint16_t count
    )
{
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable long-word write
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + BLKWRT;

    while (count > 0)
    {
        //test busy
        while (HWREG8(FLASH_BASE + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = *data_ptr++;

        count--;
    }

    //Clear BLKWRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

void FlashCtl_fillMemory32 (uint32_t value,
    uint32_t *flash_ptr,
    uint16_t count
    )
{
    //Clear Lock bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY;

    //Enable long-word write
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY + BLKWRT;

    //test busy
    while (count > 0)
    {
        while ((HWREG8(FLASH_BASE + OFS_FCTL3)) & BUSY) ;

        //Write to Flash
        *flash_ptr++ = value;

        count--;
    }

    //Clear BLKWRT bit
    HWREG16(FLASH_BASE + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY + LOCK;
}

uint8_t FlashCtl_getStatus (uint8_t mask
    )
{
    return ((HWREG8(FLASH_BASE + OFS_FCTL3) & mask ));
}

void FlashCtl_lockInfoA (void)
{
    //Disable global interrupts while doing RMW operation on LOCKA bit
    uint16_t gieStatus;
    gieStatus = __get_SR_register() & GIE;          //Store current SR register
    __disable_interrupt();                          //Disable global interrupt

    //Set the LOCKA bit in FCTL3.
    //Since LOCKA toggles when you write a 1 (and writing 0 has no effect),
    //read the register, XOR with LOCKA mask, mask the lower byte
    //and write it back.
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY
        + ((HWREG16(FLASH_BASE + OFS_FCTL3) ^ LOCKA) & 0xFF);

    //Reinstate SR register to restore global interrupt enable status
    __bis_SR_register(gieStatus);
}

void FlashCtl_unlockInfoA (void)
{
    //Disable global interrupts while doing RMW operation on LOCKA bit
    uint16_t gieStatus;
    gieStatus = __get_SR_register() & GIE;          //Store current SR register
    __disable_interrupt();                          //Disable global interrupt

    //Clear the LOCKA bit in FCTL3.
    //Since LOCKA toggles when you write a 1 (and writing 0 has no effect),
    //read the register, mask the lower byte, and write it back.
    HWREG16(FLASH_BASE + OFS_FCTL3) = FWKEY 
        + (HWREG16(FLASH_BASE + OFS_FCTL3) & 0xFF);

    //Reinstate SR register to restore global interrupt enable status
    __bis_SR_register(gieStatus);
}


#endif
//*****************************************************************************
//
//! Close the doxygen group for flashctl_api
//! @}
//
//*****************************************************************************
