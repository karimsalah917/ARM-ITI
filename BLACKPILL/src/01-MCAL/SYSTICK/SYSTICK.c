/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : RCC                                                                      */
/* Version      : v1.1                                                                     */
/* Date         : 11/2/2024                                                                */
/* File Details : Source file for RCC Driver                                               */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
/********************************** Includes ***********************************************/
#include "../../../include/01-MCAL/SYSTICK/SYSTICK.h"
/********************************** Definitions ********************************************/
#define SysTick_BaseAddress 0xE000E010
/**********************************  Types  ************************************************/
typedef struct 
{
    uint32 STK_CTRL;
    uint32 STK_LOAD;
    uint32 STK_VAL;
    uint32 STK_CALIB;
}SysTick_t;

/**********************************  Variables *********************************************/
volatile SysTick_t* const SysTick =(volatile SysTick_t*)SysTick_BaseAddress;
/********************************** Static Functions ***************************************/

/********************************** Implementation *****************************************/
SysTick_Error_t SysTick_EnableCounter(SysTick_CounterStatus_t CounterStatus){
    
}

SysTick_Error_t SysTick_EnableInterrupt(SysTick_InterruptStatus_t InterruptStatus){}

SysTick_Error_t SysTick_SetClockSource(SysTick_ClockSource_t){}

SysTick_Error_t SysTick_SetTimeMS(uint32 Time){}

SysTick_Error_t SysTick_SetCallBack(Handler_t handler){}