/******************************************************************************
*
* Copyright (C) 2012 - 2021 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*  Redistributions of source code must retain the above copyright
*  notice, this list of conditions and the following disclaimer.
*
*  Redistributions in binary form must reproduce the above copyright
*  notice, this list of conditions and the following disclaimer in the
*  documentation and/or other materials provided with the
*  distribution.
*
*  Neither the name of Texas Instruments Incorporated nor the names of
*  its contributors may be used to endorse or promote products derived
*  from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Default linker command file for Texas Instruments MSP430FR2475
*
*****************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   Usage:  lnk430 <obj files...>    -o <out file> -m <map file> lnk.cmd     */
/*           cl430  <src files...> -z -o <out file> -m <map file> lnk.cmd     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* These linker options are for command line linking only.  For IDE linking,  */
/* you should set your linker options in Project Properties                   */
/* -c                                               LINK USING C CONVENTIONS  */
/* -stack  0x0100                                   SOFTWARE STACK SIZE       */
/* -heap   0x0100                                   HEAP AREA SIZE            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 1.213 */
/*----------------------------------------------------------------------------*/

/****************************************************************************/
/* SPECIFY THE SYSTEM MEMORY MAP                                            */
/****************************************************************************/

MEMORY
{
    TINYRAM                 : origin = 0x6, length = 0x1A
    BSL0                    : origin = 0x1000, length = 0x800
    INFO                    : origin = 0x1800, length = 0x200
    TLVMEM                  : origin = 0x1A00, length = 0x200
    BOOTCODE                : origin = 0x1C00, length = 0x400
    RAM                     : origin = 0x2000, length = 0x1800
    FRAM                    : origin = 0x8000, length = 0x7F80
    ROMLIB                  : origin = 0xC0000, length = 0x4000
    BSL1                    : origin = 0xFFC00, length = 0x400
    JTAGSIGNATURE           : origin = 0xFF80, length = 0x0004, fill = 0xFFFF
    BSLSIGNATURE            : origin = 0xFF84, length = 0x0004, fill = 0xFFFF
    BSLCONFIGURATIONSIGNATURE: origin = 0xFF88, length = 0x0002, fill = 0xFFFF
    BSLCONFIGURATION        : origin = 0xFF8A, length = 0x0002, fill = 0xFFFF
    BSLI2CADDRESS           : origin = 0xFFA0, length = 0x0002, fill = 0xFFFF
    INT00                   : origin = 0xFFA2, length = 0x0002
    INT01                   : origin = 0xFFA4, length = 0x0002
    INT02                   : origin = 0xFFA6, length = 0x0002
    INT03                   : origin = 0xFFA8, length = 0x0002
    INT04                   : origin = 0xFFAA, length = 0x0002
    INT05                   : origin = 0xFFAC, length = 0x0002
    INT06                   : origin = 0xFFAE, length = 0x0002
    INT07                   : origin = 0xFFB0, length = 0x0002
    INT08                   : origin = 0xFFB2, length = 0x0002
    INT09                   : origin = 0xFFB4, length = 0x0002
    INT10                   : origin = 0xFFB6, length = 0x0002
    INT11                   : origin = 0xFFB8, length = 0x0002
    INT12                   : origin = 0xFFBA, length = 0x0002
    INT13                   : origin = 0xFFBC, length = 0x0002
    INT14                   : origin = 0xFFBE, length = 0x0002
    INT15                   : origin = 0xFFC0, length = 0x0002
    INT16                   : origin = 0xFFC2, length = 0x0002
    INT17                   : origin = 0xFFC4, length = 0x0002
    INT18                   : origin = 0xFFC6, length = 0x0002
    INT19                   : origin = 0xFFC8, length = 0x0002
    INT20                   : origin = 0xFFCA, length = 0x0002
    INT21                   : origin = 0xFFCC, length = 0x0002
    INT22                   : origin = 0xFFCE, length = 0x0002
    INT23                   : origin = 0xFFD0, length = 0x0002
    INT24                   : origin = 0xFFD2, length = 0x0002
    INT25                   : origin = 0xFFD4, length = 0x0002
    INT26                   : origin = 0xFFD6, length = 0x0002
    INT27                   : origin = 0xFFD8, length = 0x0002
    INT28                   : origin = 0xFFDA, length = 0x0002
    INT29                   : origin = 0xFFDC, length = 0x0002
    INT30                   : origin = 0xFFDE, length = 0x0002
    INT31                   : origin = 0xFFE0, length = 0x0002
    INT32                   : origin = 0xFFE2, length = 0x0002
    INT33                   : origin = 0xFFE4, length = 0x0002
    INT34                   : origin = 0xFFE6, length = 0x0002
    INT35                   : origin = 0xFFE8, length = 0x0002
    INT36                   : origin = 0xFFEA, length = 0x0002
    INT37                   : origin = 0xFFEC, length = 0x0002
    INT38                   : origin = 0xFFEE, length = 0x0002
    INT39                   : origin = 0xFFF0, length = 0x0002
    INT40                   : origin = 0xFFF2, length = 0x0002
    INT41                   : origin = 0xFFF4, length = 0x0002
    INT42                   : origin = 0xFFF6, length = 0x0002
    INT43                   : origin = 0xFFF8, length = 0x0002
    INT44                   : origin = 0xFFFA, length = 0x0002
    INT45                   : origin = 0xFFFC, length = 0x0002
    RESET                   : origin = 0xFFFE, length = 0x0002
}

/****************************************************************************/
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY                              */
/****************************************************************************/

SECTIONS
{
    GROUP(ALL_FRAM)
    {
        GROUP(READ_WRITE_MEMORY)
        {
            .TI.persistent : {}              /* For #pragma persistent            */
            .cio           : {}              /* C I/O Buffer                      */
            .sysmem        : {}              /* Dynamic memory allocation area    */
        } PALIGN(0x0400), RUN_START(fram_rw_start) RUN_END(fram_rx_start)

        GROUP(READ_ONLY_MEMORY)
        {
            .cinit      : {}                   /* Initialization tables             */
            .pinit      : {}                   /* C++ constructor tables            */
            .binit      : {}                   /* Boot-time Initialization tables   */
            .init_array : {}                   /* C++ constructor tables            */
            .mspabi.exidx : {}                 /* C++ constructor tables            */
            .mspabi.extab : {}                 /* C++ constructor tables            */
            .const      : {}                   /* Constant data                     */
        }

        GROUP(EXECUTABLE_MEMORY)
        {
            .text       : {}                   /* Code                              */
            .text:_isr  : {}                   /* Code ISRs                         */
        }
    } > FRAM

    #ifdef __TI_COMPILER_VERSION__
        #if __TI_COMPILER_VERSION__ >= 15009000
            .TI.ramfunc : {} load=FRAM, run=RAM, table(BINIT)
        #endif
    #endif

    .jtagsignature      : {} > JTAGSIGNATURE
    .bslsignature       : {} > BSLSIGNATURE
    .bslconfigsignature : {} > BSLCONFIGURATIONSIGNATURE
    .bslconfig          : {} > BSLCONFIGURATION
    .bsli2caddress      : {} > BSLI2CADDRESS

    .bss        : {} > RAM                  /* Global & static vars              */
    .data       : {} > RAM                  /* Global & static vars              */
    .TI.noinit  : {} > RAM                  /* For #pragma noinit                */
    .stack      : {} > RAM (HIGH)           /* Software system stack             */

    .tinyram    : {} > TINYRAM              /* Tiny RAM                          */

    /* MSP430 INFO memory segments */
    .info : type = NOINIT{} > INFO


    /* MSP430 interrupt vectors */

    .int00       : {}               > INT00
    .int01       : {}               > INT01
    .int02       : {}               > INT02
    .int03       : {}               > INT03
    .int04       : {}               > INT04
    .int05       : {}               > INT05
    .int06       : {}               > INT06
    .int07       : {}               > INT07
    .int08       : {}               > INT08
    .int09       : {}               > INT09
    .int10       : {}               > INT10
    .int11       : {}               > INT11
    .int12       : {}               > INT12
    .int13       : {}               > INT13
    .int14       : {}               > INT14
    .int15       : {}               > INT15
    .int16       : {}               > INT16
    .int17       : {}               > INT17
    .int18       : {}               > INT18
    .int19       : {}               > INT19
    ECOMP0       : { * ( .int20 ) } > INT20 type = VECT_INIT
    PORT6        : { * ( .int21 ) } > INT21 type = VECT_INIT
    PORT5        : { * ( .int22 ) } > INT22 type = VECT_INIT
    PORT4        : { * ( .int23 ) } > INT23 type = VECT_INIT
    PORT3        : { * ( .int24 ) } > INT24 type = VECT_INIT
    PORT2        : { * ( .int25 ) } > INT25 type = VECT_INIT
    PORT1        : { * ( .int26 ) } > INT26 type = VECT_INIT
    ADC          : { * ( .int27 ) } > INT27 type = VECT_INIT
    EUSCI_B1     : { * ( .int28 ) } > INT28 type = VECT_INIT
    EUSCI_B0     : { * ( .int29 ) } > INT29 type = VECT_INIT
    EUSCI_A1     : { * ( .int30 ) } > INT30 type = VECT_INIT
    EUSCI_A0     : { * ( .int31 ) } > INT31 type = VECT_INIT
    WDT          : { * ( .int32 ) } > INT32 type = VECT_INIT
    RTC          : { * ( .int33 ) } > INT33 type = VECT_INIT
    TIMER0_B1    : { * ( .int34 ) } > INT34 type = VECT_INIT
    TIMER0_B0    : { * ( .int35 ) } > INT35 type = VECT_INIT
    TIMER3_A1    : { * ( .int36 ) } > INT36 type = VECT_INIT
    TIMER3_A0    : { * ( .int37 ) } > INT37 type = VECT_INIT
    TIMER2_A1    : { * ( .int38 ) } > INT38 type = VECT_INIT
    TIMER2_A0    : { * ( .int39 ) } > INT39 type = VECT_INIT
    TIMER1_A1    : { * ( .int40 ) } > INT40 type = VECT_INIT
    TIMER1_A0    : { * ( .int41 ) } > INT41 type = VECT_INIT
    TIMER0_A1    : { * ( .int42 ) } > INT42 type = VECT_INIT
    TIMER0_A0    : { * ( .int43 ) } > INT43 type = VECT_INIT
    UNMI         : { * ( .int44 ) } > INT44 type = VECT_INIT
    SYSNMI       : { * ( .int45 ) } > INT45 type = VECT_INIT
    .reset       : {}               > RESET  /* MSP430 reset vector         */

}
/****************************************************************************/
/* FRAM WRITE PROTECTION SEGMENT DEFINITONS                                 */
/****************************************************************************/

#ifdef _FRWP_ENABLE
    __mpu_enable=1;
    start_protection_offset_address = (fram_rx_start - fram_rw_start) >> 10;
    program_fram_protection = 0x1;
    #ifdef _INFO_FRWP_ENABLE
        info_fram_protection = 0x1;
    #else
        info_fram_protection = 0x0;
    #endif
#endif

/****************************************************************************/
/* INCLUDE PERIPHERALS MEMORY MAP                                           */
/****************************************************************************/

-l msp430fr2475.cmd


