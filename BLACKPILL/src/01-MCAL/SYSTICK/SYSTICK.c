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

#define STK_CTRL_ENABLE_BIT     (uint32)0x00000001
#define STK_CTRL_TICKINT_BIT    (uint32)0x00000002
#define STK_CTRL_CLKSOURCE_BIT  (uint32)0x00000004

#define SysTick_LOAD_RELOAD_Msk (uint32)0x00FFFFFF

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
static SysTick_ClockSource_t  SysTick_GetClockSource(void)
{
    return (SysTick->STK_CTRL&STK_CTRL_CLKSOURCE_BIT);
}
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
    SysTick_Error_t Local_ReturnValue=SYSTICK_ERROR_NOK;
        switch (ClockSource)
        {
        case SysTick_CLOCK_SOURCE_AHB_8:
            SysTick->STK_CTRL &=~STK_CTRL_CLKSOURCE_BIT;
            Local_ReturnValue=SYSTICK_ERROR_OK;
            break;
        case SysTick_CLOCK_SOURCE_AHB:
            SysTick->STK_CTRL |=STK_CTRL_CLKSOURCE_BIT;
            Local_ReturnValue=SYSTICK_ERROR_OK;
            break;
        default:
        Local_ReturnValue=SYSTICK_ERROR_INVALID_ARGUMENT;
            break;
        }
    return Local_ReturnValue;
}


SysTick_Error_t SysTick_SetTickMS(uint32 Time){
    SysTick_Error_t Local_returnVal=SYSTICK_ERROR_OK;
    // Calculate ticks for one millisecond
    uint32 ticksForMS = (CLOCK /(1000*(SysTick_GetClockSource()==0?8:1)));

    // Configure SysTick timer to generate an interrupt every 'Time' milliseconds
    uint32 loadValue = Time * ticksForMS;
    if (loadValue > SysTick_LOAD_RELOAD_Msk) {
        // Error: Time value too large
        Local_returnVal=SYSTICK_ERROR_NOK;
    }else
    {
    // Set reload value for SysTick timer
    SysTick->STK_LOAD = ((loadValue - 1));
    }

    // Success
    return Local_returnVal;
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

SysTick_Error_t SysTick_SetCurrentVal(uint32 CurrentVal)
{
    SysTick->STK_VAL=CurrentVal;
    return SYSTICK_ERROR_OK;
}

 void SysTick_Handler (void)
 {
    Handler_variable();
 }

