/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "lp-msp430.h"

volatile bool g_button_LP_S1_pressed = false, g_button_LP_S2_pressed = false;

void LP_BUTTON_WaitFor_LP_S1()
{
    g_button_LP_S1_pressed = false;
    GPIO_clearInterrupt(LP_S1);
    GPIO_enableInterrupt(LP_S1);

    while(!g_button_LP_S1_pressed)
    {
        __low_power_mode_0();
    }

    GPIO_disableInterrupt(LP_S1);
}

void LP_BUTTON_WaitFor_LP_S2()
{
    g_button_LP_S2_pressed = false;
    GPIO_clearInterrupt(LP_S2);
    GPIO_enableInterrupt(LP_S2);

    while(!g_button_LP_S2_pressed)
    {
        __low_power_mode_0();
    }

    GPIO_disableInterrupt(LP_S2);
}

bool LP_BUTTON_WaitFor_LP_S1_or_LP_S2() // LP_S1, true, LP_S2, false
{
    g_button_LP_S1_pressed = false;
    g_button_LP_S2_pressed = false;
    GPIO_clearInterrupt(LP_S1);
    GPIO_clearInterrupt(LP_S2);
    GPIO_enableInterrupt(LP_S1);
    GPIO_enableInterrupt(LP_S2);

   while(!g_button_LP_S1_pressed && !g_button_LP_S2_pressed)
   {
       __low_power_mode_0();
   }

   GPIO_disableInterrupt(LP_S1);
   GPIO_disableInterrupt(LP_S2);

   return g_button_LP_S1_pressed; // false if S2
}
