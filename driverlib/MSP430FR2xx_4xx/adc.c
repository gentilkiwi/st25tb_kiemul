//*****************************************************************************
//
// adc.c - Driver for the adc Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup adc_api adc
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_ADC__
#include "adc.h"

#include <assert.h>

void ADC_init(uint16_t baseAddress,
    uint16_t sampleHoldSignalSourceSelect,
    uint8_t clockSourceSelect,
    uint16_t clockSourceDivider)
{
    //Turn OFF ADC Module & Clear Interrupt Registers
    HWREG16(baseAddress + OFS_ADCCTL0) &= ~(ADCON + ADCENC + ADCSC);
    HWREG16(baseAddress + OFS_ADCIE)  &= 0x0000; //Reset ALL interrupt enables
    HWREG16(baseAddress + OFS_ADCIFG) &= 0x0000; //Reset ALL interrupt flags

    //Set ADC Control 1
    HWREG16(baseAddress + OFS_ADCCTL1) = sampleHoldSignalSourceSelect //Setup the Sample-and-Hold Source
        + (clockSourceDivider & ADCDIV_7)  //Set Clock Divider
        + clockSourceSelect; //Setup Clock Source

    //Set ADC Control 2
    HWREG16(baseAddress + OFS_ADCCTL2) = (clockSourceDivider & ADCPDIV_3) //Set Clock Pre-Divider
        + ADCRES_1; //Default resolution to 10-bits
}

void ADC_enable(uint16_t baseAddress)
{
    //Reset the ADCON bit to enable the ADC Module
    HWREG16(baseAddress + OFS_ADCCTL0) |= ADCON;
}

void ADC_disable(uint16_t baseAddress)
{
    //Set the ADCON bit to disable the ADC Module
    HWREG16(baseAddress + OFS_ADCCTL0) &= ~ADCON;
}

void ADC_setupSamplingTimer(uint16_t baseAddress,
    uint16_t clockCycleHoldCount,
    uint16_t multipleSamplesEnabled)
{
    HWREG16(baseAddress + OFS_ADCCTL1) |= ADCSHP;

    //Reset and Set CB Control 0 Bits
    HWREG16(baseAddress + OFS_ADCCTL0) &= ~(ADCSHT_15 + ADCMSC);
    HWREG16(baseAddress + OFS_ADCCTL0) |= clockCycleHoldCount + multipleSamplesEnabled;
}

void ADC_disableSamplingTimer(uint16_t baseAddress)
{
    HWREG16(baseAddress + OFS_ADCCTL1) &= ~(ADCSHP);
}

void ADC_configureMemory(uint16_t baseAddress,
    uint8_t inputSourceSelect,
    uint8_t positiveRefVoltageSourceSelect,
    uint8_t negativeRefVoltageSourceSelect)
{

    //Make sure the ENC bit is cleared before configuring a Memory Buffer Control
    assert( !(HWREG16(baseAddress + OFS_ADCCTL0) & ADCENC) );

    if(!(HWREG16(baseAddress + OFS_ADCCTL0) & ADCENC))
    {
#ifdef ADCPCTL9
        //Enable ADC input pin
        if(inputSourceSelect < ADCINCH_10)
        {
            HWREG16(SYS_BASE + OFS_SYSCFG2) |= (1 << inputSourceSelect);
        }
#elif ADCPCTL7
        if(inputSourceSelect < ADCINCH_8)
        {
            HWREG16(SYS_BASE + OFS_SYSCFG2) |= (1 << inputSourceSelect);
        }
#endif

        //Reset and Set the Memory Buffer Control Bits
        HWREG16(baseAddress + OFS_ADCMCTL0) = inputSourceSelect + positiveRefVoltageSourceSelect
            + negativeRefVoltageSourceSelect;
    }
}

void ADC_enableInterrupt(uint16_t baseAddress,
    uint16_t interruptMask)
{
    HWREG16(baseAddress + OFS_ADCIE) |= interruptMask;
}

void ADC_disableInterrupt(uint16_t baseAddress,
    uint16_t interruptMask)
{
    HWREG16(baseAddress + OFS_ADCIE) &= ~(interruptMask);
}

void ADC_clearInterrupt(uint16_t baseAddress,
    uint16_t interruptFlagMask)
{
    HWREG16(baseAddress + OFS_ADCIFG) &= ~(interruptFlagMask);
}

uint8_t ADC_getInterruptStatus(uint16_t baseAddress,
    uint8_t interruptFlagMask)
{
    return (HWREG16(baseAddress + OFS_ADCIFG) & interruptFlagMask);
}

void ADC_startConversion(uint16_t baseAddress,
    uint16_t conversionSequenceModeSelect)
{
    //Reset the ENC bit to set the conversion mode sequence
    HWREG16(baseAddress + OFS_ADCCTL0) &= ~(ADCENC);

    HWREG16(baseAddress + OFS_ADCCTL1) &= ~ADCCONSEQ;
    HWREG16(baseAddress + OFS_ADCCTL1) |= conversionSequenceModeSelect;
    HWREG16(baseAddress + OFS_ADCCTL0) |= ADCENC | ADCSC;
}

void ADC_disableConversions(uint16_t baseAddress,
    bool preempt)
{
    if (!preempt) {
        if (!(HWREG16(baseAddress + OFS_ADCCTL1) & ADCCONSEQ_3)) {
            //To prevent preemption of a single-channel, single-conversion we must
            //wait for the ADC core to finish the conversion.
            while (HWREG16(baseAddress + OFS_ADCCTL1) & ADCBUSY);
        }
    }

    HWREG16(baseAddress + OFS_ADCCTL0) &= ~(ADCENC);
    HWREG16(baseAddress + OFS_ADCCTL1) &= ~(ADCCONSEQ_3);
}

int16_t ADC_getResults(uint16_t baseAddress)
{
    return (int16_t)(HWREG16(baseAddress + OFS_ADCMEM0));
}

void ADC_setResolution(uint16_t baseAddress,
    uint16_t resolutionSelect)
{
    HWREG16(baseAddress + OFS_ADCCTL2) &= ~(ADCRES);
    HWREG16(baseAddress + OFS_ADCCTL2) |= resolutionSelect;
}

void ADC_setSampleHoldSignalInversion(uint16_t baseAddress,
    uint16_t invertedSignal)
{
    HWREG16(baseAddress + OFS_ADCCTL1) &= ~(ADCISSH);
    HWREG16(baseAddress + OFS_ADCCTL1) |= invertedSignal;
}

void ADC_setDataReadBackFormat(uint16_t baseAddress,
    uint16_t readBackFormat)
{
    HWREG16(baseAddress + OFS_ADCCTL2) &= ~(ADCDF);
    HWREG16(baseAddress + OFS_ADCCTL2) |= readBackFormat;
}

void ADC_setReferenceBufferSamplingRate(uint16_t baseAddress,
    uint16_t samplingRateSelect)
{
    HWREG16(baseAddress + OFS_ADCCTL2) &= ~(ADCSR);
    HWREG16(baseAddress + OFS_ADCCTL2) |= samplingRateSelect;
}

void ADC_setWindowComp(uint16_t baseAddress,
    uint16_t highThreshold,
    uint16_t lowThreshold)
{
    HWREG16(baseAddress + OFS_ADCHI) = highThreshold;
    HWREG16(baseAddress + OFS_ADCLO) = lowThreshold;
}

uint32_t ADC_getMemoryAddressForDMA(uint16_t baseAddress)
{
    return (baseAddress + OFS_ADCMEM0);
}

uint8_t ADC_isBusy(uint16_t baseAddress)
{
    return (HWREG16(baseAddress + OFS_ADCCTL1) & ADCBUSY);
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for adc_api
//! @}
//
//*****************************************************************************
