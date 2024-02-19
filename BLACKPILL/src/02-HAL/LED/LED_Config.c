/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LED                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 19/02/2024                                                               */
/* File Details : Source Configuration file for LED Driver                                 */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../../include/02-HAL/LED/LED.h"
/********************************** Definitions ********************************************/
/*none*/
/**********************************   Types ************************************************/
/*none*/
/********************************** variables **********************************************/

/**
 * @brief Array filled with user defined leds to set it's configuration
*/
const LED_CONFG_t LEDARR[_LED_enum]=
{
    [BuiltInLED]=
    {
        .PORT=LED_PORTC,
        .PIN=LED_PIN13,
        .Connection=LED_Connection_ActiveHIGH
    }
};