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
#define NULL 0

#define STK_CTRL_ENABLE_BIT    0x00000001
#define STK_CTRL_TICKINT_BIT   0x00000002
#define STK_CTRL_CLKSOURCE_BIT 0x00000004


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

static Handler_t Handler_variable =NULL;
/********************************** Static Functions ***************************************/

/********************************** Implementation *****************************************/
SysTick_Error_t SysTick_EnableCounterPeriodic(void){
   
    SysTick->STK_CTRL|=STK_CTRL_ENABLE_BIT;
    return SYSTICK_ERROR_OK;
}
SysTick_Error_t SysTick_EnableCounterOneShot(void){
    SysTick->STK_CTRL|=STK_CTRL_ENABLE_BIT;
    SysTick->STK_LOAD=0; //clearing the reload value so counter will count just one time
    return SYSTICK_ERROR_OK;
}

SysTick_Error_t SysTick_DisableCounter(void){
    SysTick->STK_CTRL&=~(STK_CTRL_ENABLE_BIT);
    return SYSTICK_ERROR_OK;
}

SysTick_Error_t SysTick_EnableInterrupt(void){
    SysTick->STK_CTRL|=STK_CTRL_TICKINT_BIT;
    return SYSTICK_ERROR_OK;
}

SysTick_Error_t SysTick_DisableInterrupt(void){
    SysTick->STK_CTRL&=~STK_CTRL_TICKINT_BIT;
    return SYSTICK_ERROR_OK;
}

SysTick_Error_t SysTick_SetClockSource(SysTick_ClockSource_t ClockSource){
    SysTick_Error_t Local_ReturnValue=SYSTICK_ERROR_OK;
    if(ClockSource>SysTick_CLOCK_SOURCE_AHB||ClockSource<SysTick_CLOCK_SOURCE_AHB_8)
    {
        Local_ReturnValue=SYSTICK_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        switch (ClockSource)
        {
        case SysTick_CLOCK_SOURCE_AHB_8:
            SysTick->STK_CTRL &=~STK_CTRL_CLKSOURCE_BIT;
            break;
        case SysTick_CLOCK_SOURCE_AHB:
            SysTick->STK_CTRL |=STK_CTRL_CLKSOURCE_BIT;
            break;
        default:
        Local_ReturnValue=SYSTICK_ERROR_NOK;
            break;
        }
    }
    return Local_ReturnValue;
}

SysTick_Error_t SysTick_SetTimeMS(uint32 Time){
}

SysTick_Error_t SysTick_SetCallBack(Handler_t Handler){
    SysTick_Error_t Local_ReturnVariable=SYSTICK_ERROR_OK;
    if (Handler==NULL)
    {
        Local_ReturnVariable=SYSTICK_ERROR_NOK;
    }else{
        Handler_variable=Handler;
    }
    return Local_ReturnVariable;
}

SysTick_Handler()
{
    
}