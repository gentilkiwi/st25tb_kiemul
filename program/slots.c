/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "slots.h"

#if defined(STM32F405xx)
HAL_StatusTypeDef STM32_SPECIFIC_update_generic(const FLASH_STORED_DATA *newData);
#endif

uint8_t SLOTS_ST25TB_Current[SLOTS_ST25TB_SECTORS_INTERNAL][4];

uint8_t SLOTS_Change(uint8_t index)
{
    uint8_t ret;

    ret = SLOTS_Load(index);
    if(ret)
    {
        if(index != FlashStoredData.CurrentSlot)
        {
            SLOTS_Update_GenericConfig(&FlashStoredData.CurrentSlot, index);
			kprintf("|%s| - [%" PRIu8 "]" UART_NEWLINE, __FUNCTION__, index);
        }
#if SLOTS_ST25TB_COUNT > 8
        LEDS_SLOTS_Bitmask(index);
#else
        LED_Slot(index);
#endif
    }

    return ret;
}

uint8_t SLOTS_Load(uint8_t index)
{
    uint8_t ret;

    if(index < SLOTS_ST25TB_COUNT)
    {
        memcpy(SLOTS_ST25TB_Current, FlashStoredData.Slots[index], sizeof(FlashStoredData.Slots[index]));
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

uint8_t SLOTS_Save(uint8_t index)
{
    uint8_t ret;

    if(index < SLOTS_ST25TB_COUNT)
    {
#if defined(__MSP430_HAS_FRAM__)
        uint8_t state = SYSCFG0_L;
        SYSCFG0 = FWPW | (state & ~(DFWP | PFWP));
        memcpy(FlashStoredData.Slots[index], SLOTS_ST25TB_Current, sizeof(FlashStoredData.Slots[index]));
        SYSCFG0 = FWPW | state;
#elif defined(STM32F405xx)
    	FLASH_STORED_DATA tmp = FlashStoredData;
    	memcpy(tmp.Slots[index], SLOTS_ST25TB_Current, sizeof(tmp.Slots[index]));
    	STM32_SPECIFIC_update_generic(&tmp);
#else
#error Not supported
#endif
        kprintf("|%s| - [%" PRIu8 "] [UID: %016" PRIx64 "]" UART_NEWLINE, __FUNCTION__, index, *(uint64_t *) (SLOTS_ST25TB_Current + SLOTS_ST25TB_INDEX_UID));
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

uint8_t SLOTS_FindByUID(uint8_t pui8Data[8]) // ret == SLOTS_FIND_INVALID_INDEX -> not found
{
    uint8_t ret = SLOTS_FIND_INVALID_INDEX, i;
    for(i = 0; i < SLOTS_ST25TB_COUNT; i++)
    {
        if((*(uint64_t*) pui8Data) == (*(uint64_t*) FlashStoredData.Slots[i][SLOTS_ST25TB_INDEX_UID]))
        {
            ret = i;
            break;
        }
    }

    return ret;
}

uint8_t g_ui8_ST25TB_TraceBuffer[ST25TB_TRACE_BUFFER_SIZE];
uint16_t g_ui16_cbST25TB_TraceBuffer = 0;

void SLOTS_Trace_Save()
{
    if(g_ui16_cbST25TB_TraceBuffer)
    {
#if defined(__MSP430_HAS_FRAM__)
        uint8_t state = SYSCFG0_L;
        SYSCFG0 = FWPW | (state & ~(DFWP | PFWP));
        FlashStoredData.ST25TB_cbTrace = g_ui16_cbST25TB_TraceBuffer;
        memcpy(FlashStoredData.ST25TB_Trace, g_ui8_ST25TB_TraceBuffer, g_ui16_cbST25TB_TraceBuffer);
        SYSCFG0 = FWPW | state;
#elif defined(STM32F405xx)
		FLASH_STORED_DATA tmp = FlashStoredData;
		tmp.ST25TB_cbTrace = g_ui16_cbST25TB_TraceBuffer;
		memcpy(tmp.ST25TB_Trace, g_ui8_ST25TB_TraceBuffer, g_ui16_cbST25TB_TraceBuffer);
		STM32_SPECIFIC_update_generic(&tmp);
#else
#error Not supported
#endif
		kprintf("|%s| - Saved trace for %" PRIu16 " bytes" UART_NEWLINE, __FUNCTION__, g_ui16_cbST25TB_TraceBuffer);
        g_ui16_cbST25TB_TraceBuffer = 0;
    }
}

void SLOTS_Trace_Clear()
{
#if defined(__MSP430_HAS_FRAM__)
        uint8_t state = SYSCFG0_L;
        SYSCFG0 = FWPW | (state & ~(DFWP | PFWP));
        FlashStoredData.ST25TB_cbTrace = 0;
        memset(FlashStoredData.ST25TB_Trace, 0, ST25TB_TRACE_BUFFER_SIZE);
        SYSCFG0 = FWPW | state;
#elif defined(STM32F405xx)
	FLASH_STORED_DATA tmp = FlashStoredData;
	tmp.ST25TB_cbTrace = 0;
	memset(tmp.ST25TB_Trace, 0, ST25TB_TRACE_BUFFER_SIZE);
	STM32_SPECIFIC_update_generic(&tmp);
#else
#error Not supported
#endif
    g_ui16_cbST25TB_TraceBuffer = 0;
    kprintf("|%s| - Cleared trace" UART_NEWLINE, __FUNCTION__);
}

void SLOTS_Update_GenericConfig(uint8_t *configPtr, uint8_t value)
{
#if defined(__MSP430_HAS_FRAM__)
    uint8_t state = SYSCFG0_L;
    SYSCFG0 = FWPW | (state & ~(DFWP | PFWP));
    *configPtr = value;
    SYSCFG0 = FWPW | state;
#elif defined(STM32F405xx)
	FLASH_STORED_DATA tmp = FlashStoredData;
	size_t offset = configPtr - (uint8_t *)&FlashStoredData;
	((uint8_t *)&tmp)[offset] = value;
	STM32_SPECIFIC_update_generic(&tmp);
#else
#error Not supported
#endif
}

#if defined(__MSP430_HAS_FRAM__)
#pragma PERSISTENT(FlashStoredData)
#elif defined(STM32F405xx)
__attribute__((section(".flash_storage"), used))
#else
#error Not supported
#endif
/*const */FLASH_STORED_DATA FlashStoredData = {
	.CurrentSlot = 0,
	.bDoNotWriteSystem = 1,
	.bDoNotWriteCounters = 0,
	.bModeEmulateSW2Save = 1,
	.bUARTEnabled = 0,
    
    .Slots = {
        {   /* Slot 0 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x00
            #if defined(SLOT_0_CONTENT)
            #include SLOT_0_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #if SLOTS_ST25TB_COUNT > 1
        {   /* Slot 1 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x11
            #if defined(SLOT_1_CONTENT)
            #include SLOT_1_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #endif
    #if SLOTS_ST25TB_COUNT > 2
        {   /* Slot 2 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x22
            #if defined(SLOT_2_CONTENT)
            #include SLOT_2_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #endif
    #if SLOTS_ST25TB_COUNT > 3
        {   /* Slot 3 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x33
            #if defined(SLOT_3_CONTENT)
            #include SLOT_3_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #endif
    #if SLOTS_ST25TB_COUNT > 4
        {   /* Slot 4 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x44
            #if defined(SLOT_4_CONTENT)
            #include SLOT_4_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #endif
    #if SLOTS_ST25TB_COUNT > 5
        {   /* Slot 5 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x55
            #if defined(SLOT_5_CONTENT)
            #include SLOT_5_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #endif
    #if SLOTS_ST25TB_COUNT > 6
        {   /* Slot 6 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x66
            #if defined(SLOT_6_CONTENT)
            #include SLOT_6_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #endif
    #if SLOTS_ST25TB_COUNT > 7
        {   /* Slot 7 */
            #undef SLOT_UID_BYTE
            #define SLOT_UID_BYTE   0x77
            #if defined(SLOT_7_CONTENT)
            #include SLOT_7_CONTENT
            #else
            #include "slots_fixed_content.h"
            #endif
        },
    #endif
    },
    .ST25TB_cbTrace = 0,
    //.ST25TB_Trace
};

#if defined(STM32F405xx)
const FLASH_EraseInitTypeDef FLASH_STORAGE_ERASE = {
		.TypeErase = FLASH_TYPEERASE_SECTORS,
		.Banks = FLASH_BANK_1,
		.Sector = FLASH_SECTOR_1,
		.NbSectors = 1,
		.VoltageRange = FLASH_VOLTAGE_RANGE_3,
};
HAL_StatusTypeDef STM32_SPECIFIC_update_generic(const FLASH_STORED_DATA *newData)
{
  HAL_StatusTypeDef ret;
  uint32_t SectorError;

  ret = HAL_FLASH_Unlock();
  if (ret == HAL_OK)
  {
	  uint32_t primask = __get_PRIMASK();
	  __disable_irq();
	  ret = HAL_FLASHEx_Erase((FLASH_EraseInitTypeDef*) &FLASH_STORAGE_ERASE, &SectorError);
	  if (ret == HAL_OK)
	  {
		const uint32_t *src = (const uint32_t *)newData; // we know FLASH_STORED_DATA is multiple of 4 bytes by design
		uint32_t *dst = (uint32_t *)&FlashStoredData;
		size_t n_words = sizeof(FLASH_STORED_DATA) / sizeof(uint32_t);

		for (size_t i = 0; (i < n_words) && (ret == HAL_OK); i++)
		{
			ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)&dst[i], src[i]); // did you know FLASH_TYPEPROGRAM_DOUBLEWORD needs Vpp? now we both know
		}
	  }
	  __set_PRIMASK(primask); //__enable_irq();
	  HAL_FLASH_Lock();
  }
  return ret;
}
#endif
