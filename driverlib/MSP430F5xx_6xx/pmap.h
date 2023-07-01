//*****************************************************************************
//
// pmap.h - Driver for the PMAP Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_PMAP_H__
#define __MSP430WARE_PMAP_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_PORT_MAPPING__

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
//! \brief Used in the PMAP_initPorts() function as the param parameter.
//
//*****************************************************************************
typedef struct PMAP_initPortsParam {
    //! Is the pointer to init Data
    const uint8_t* portMapping;
    //! Is the pointer start of first PMAP to initialize
    uint8_t* PxMAPy;
    //! Is the number of Ports to initialize
    uint8_t numberOfPorts;
    //! Is used to enable/disable reconfiguration
    //! \n Valid values are:
    //! - \b PMAP_ENABLE_RECONFIGURATION
    //! - \b PMAP_DISABLE_RECONFIGURATION [Default]
    uint8_t portMapReconfigure;
} PMAP_initPortsParam;


//*****************************************************************************
//
// The following are values that can be passed to the param parameter for
// functions: PMAP_initPorts().
//
//*****************************************************************************
#define PMAP_ENABLE_RECONFIGURATION                                   PMAPRECFG
#define PMAP_DISABLE_RECONFIGURATION                                       0x00

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief This function configures the MSP430 Port Mapper
//!
//! This function port maps a set of pins to a new set.
//!
//!
//! Modified bits of \b PMAPKETID register and bits of \b PMAPCTL register.
//!
//! \return None
//
//*****************************************************************************
extern void PMAP_initPorts(uint16_t baseAddress,
                           PMAP_initPortsParam *param);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_PMAP_H__
