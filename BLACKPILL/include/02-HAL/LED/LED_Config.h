/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LED                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 19/02/2024                                                               */
/* File Details : Header Configuration file for LED Driver                                 */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#ifndef LED_CONFIG_H
#define LED_CONFIG_H
/**********************************  Includes **********************************************/
/*none*/
/********************************** Definitions ********************************************/
/*none*/
/**********************************   Types ************************************************/

/**
 * @brief Created Data Type to define each led in your system so you can deal with
 * each led name in the application layer 
*/
typedef enum 
{
    BuiltInLED,
    _LED_enum
}LEDS_t;










#endif