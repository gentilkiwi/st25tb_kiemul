//*****************************************************************************
//
// ram.h - Driver for the RAM Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_RAM_H__
#define __MSP430WARE_RAM_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_RC__

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

//*****************************************************************************
//
// The following are values that can be passed to the sector parameter for
// functions: RAM_setSectorOff(), and RAM_getSectorState() as well as returned
// by the RAM_getSectorState() function.
//
//*****************************************************************************
#define RAM_SECTOR0                                                    RCRS0OFF
#define RAM_SECTOR1                                                    RCRS1OFF
#define RAM_SECTOR2                                                    RCRS2OFF
#define RAM_SECTOR3                                                    RCRS3OFF
#define RAM_SECTOR4                                                    RCRS4OFF
#define RAM_SECTOR5                                                    RCRS5OFF
#define RAM_SECTOR6                                                    RCRS6OFF
#define RAM_SECTOR7                                                    RCRS7OFF

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Set specified RAM sector off
//!
//! \param sector is specified sector to be set off.
//!        Mask value is the logical OR of any of the following:
//!        - \b RAM_SECTOR0
//!        - \b RAM_SECTOR1
//!        - \b RAM_SECTOR2
//!        - \b RAM_SECTOR3
//!        - \b RAM_SECTOR4
//!        - \b RAM_SECTOR5
//!        - \b RAM_SECTOR6
//!        - \b RAM_SECTOR7
//!
//! Modified bits of \b RCCTL0 register.
//!
//! \return None
//
//*****************************************************************************
extern void RAM_setSectorOff(uint8_t sector);

//*****************************************************************************
//
//! \brief Get RAM sector ON/OFF status
//!
//! \param sector is specified sector
//!        Mask value is the logical OR of any of the following:
//!        - \b RAM_SECTOR0
//!        - \b RAM_SECTOR1
//!        - \b RAM_SECTOR2
//!        - \b RAM_SECTOR3
//!        - \b RAM_SECTOR4
//!        - \b RAM_SECTOR5
//!        - \b RAM_SECTOR6
//!        - \b RAM_SECTOR7
//!
//! Modified bits of \b RCCTL0 register.
//!
//! \return Logical OR of any of the following:
//!         - \b RAM_SECTOR0
//!         - \b RAM_SECTOR1
//!         - \b RAM_SECTOR2
//!         - \b RAM_SECTOR3
//!         - \b RAM_SECTOR4
//!         - \b RAM_SECTOR5
//!         - \b RAM_SECTOR6
//!         - \b RAM_SECTOR7
//!         \n indicating the status of the masked sectors
//
//*****************************************************************************
extern uint8_t RAM_getSectorState(uint8_t sector);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_RAM_H__
