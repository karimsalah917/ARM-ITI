#include "../../include/01-MCAL/RCC/RCC.h"
#include "../../include/01-MCAL/SYSTICK/SYSTICK.h"
#include "../../include/4-Service/CLOCK_CONFIG.h"

void CLOCK_CONFIG(void)
{
    /**
     * RCC CONFIGURATION
    */
   RCC_Enable_CLOCK(CLOCK_HSE);
   RCC_Select_SYSCLOCK(SYSCLOCK_HSE);
   RCC_Enable_AHB1Peripheral(AHB1peripheral_GPIOA);
   RCC_Enable_AHB1Peripheral(AHB1peripheral_GPIOB);
   /**
    * SysTick Configuration
   */
   SysTick_SetClockSource(SysTick_CLOCK_SOURCE_AHB_8);
   SysTick_SetCurrentVal(0);
   SysTick_EnableInterrupt();
}
