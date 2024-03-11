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
 * @brief Defines a data type to represent each LED in the system,
 * allowing easier handling of LED names in the application layer.
*/
typedef enum 
{
	TestLed,
	TestLed2,
    _LED_enum   /**< Enumeration boundary marker */
} LEDS_t;










#endif
