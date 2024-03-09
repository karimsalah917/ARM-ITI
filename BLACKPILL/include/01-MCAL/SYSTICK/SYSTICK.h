/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : SysTick                                                                  */
/* Version      : v1.0                                                                     */
/* Date         : 9/3/2024                                                                 */
/* File Details : Source file for SysTick Driver                                           */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
/********************************** Includes ***********************************************/
#include "../../00-LIB/STD.h"
/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/
typedef enum {
    SYSTICK_ERROR_OK,
    SYSTICK_ERROR_INVALID_ARGUMENT,
    SYSTICK_ERROR_NOK

}SysTick_Error_t;

typedef enum {
    SYSTICK_COUNTER_STATUS_DISABLED=0,
    SYSTICK_COUNTER_STATUS_ENABLED

}SysTick_CounterStatus_t;

//bahnasy

typedef enum {
    SysTick_INTERRUPT_STATUS_DISABLED=0,
    SysTick_INTERRUPT_STATUS_ENABLED
}SysTick_InterruptStatus_t;

typedef enum{
    SysTick_CLOCK_SOURCE_AHB_8,
    SysTick_CLOCK_SOURCE_AHB
}SysTick_ClockSource_t;

typedef void (*Handler_t) (void);
/**********************************   API's ************************************************/

/**
 * @brief Enable or disable the SysTick counter.
 * 
 * @param CounterStatus The status to set for the SysTick counter.
 * @return SysTick_Error_t Error code indicating success or failure of the operation.
 */
SysTick_Error_t SysTick_EnableCounter(SysTick_CounterStatus_t CounterStatus);

/**
 * @brief Enable or disable SysTick interrupts.
 * 
 * @param InterruptStatus The status to set for SysTick interrupts.
 * @return SysTick_Error_t Error code indicating success or failure of the operation.
 */
SysTick_Error_t SysTick_EnableInterrupt(SysTick_InterruptStatus_t InterruptStatus);

/**
 * @brief Set the clock source for the SysTick timer.
 * 
 * @param ClockSource The clock source to set for the SysTick timer.
 * @return SysTick_Error_t Error code indicating success or failure of the operation.
 */
SysTick_Error_t SysTick_SetClockSource(SysTick_ClockSource_t ClockSource);

/**
 * @brief Set the time interval in milliseconds for the SysTick timer.
 * 
 * @param Time The time interval in milliseconds.
 * @return SysTick_Error_t Error code indicating success or failure of the operation.
 */
SysTick_Error_t SysTick_SetTimeMS(uint32 Time);

/**
 * @brief Set the callback function to be called when SysTick interrupt occurs.
 * 
 * @param handler Pointer to the callback function.
 * @return SysTick_Error_t Error code indicating success or failure of the operation.
 */
SysTick_Error_t SysTick_SetCallBack(Handler_t handler);
