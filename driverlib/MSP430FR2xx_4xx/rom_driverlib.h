/*******************************************************************
*                                                                  *
* This file is a generic ROM include file, that                    *
* helps find the appropriate ROM device header file                *
*                                                                  *
*******************************************************************/

#ifndef __MSP430_ROM_DRIVERLIB_H__
#define __MSP430_ROM_DRIVERLIB_H__

#if defined(__MSP430FR2532__) || defined (__MSP430FR2533__) \
    || defined (__MSP430FR2632__) || defined (__MSP430FR2633__) \
    || defined (__MSP430FR2433__) || defined (__MSP430FR2522__) \
    || defined (__MSP430FR2422__) || defined (__MSP430FR2512__)
#include "rom_headers/rom_driverlib_fr253x_fr263x.h"

#elif defined (__MSP430FR2355__) || defined (__MSP430FR2353__) \
    || defined (__MSP430FR2155__) || defined (__MSP430FR2153__)
#include "rom_headers/rom_driverlib_fr235x.h"

#elif defined (__MSP430FR2676__) || defined (__MSP430FR2675__) \
    || defined (__MSP430FR2673__) || defined (__MSP430FR2672__)
#include "rom_headers/rom_driverlib_fr2676.h"

#endif

#endif /* #ifndef __MSP430_ROM_DRIVERLIB_H__ */
