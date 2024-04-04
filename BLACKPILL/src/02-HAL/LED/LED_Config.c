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
/******************** Definitions ********************************************/
/*none*/
/**********************************   Types ************************************************/
/*none*/
/********************************** variables **********************************************/

/**
 * @brief Array containing user-defined LEDs and their configurations.
 * 
 * @warning Ensure you have appended your LED name to the enum called LEDS_t in the LED_Config.h file.
 * 
 * @example An example to enable and disable the built-in lamp:
 * 
 *          [BuiltInLED]=
 *          {
 *              .PORT=LED_PORTC,
 *              .PIN=LED_PIN13,
 *              .Connection=LED_Connection_ActiveLow
 *          }
*/
const LED_CONFG_t LEDARR[_LED_enum]=
{

    [TL_RED]=
    {
        .PORT=LED_PORTB,
        .PIN=LED_PIN0,
        .Connection=LED_Connection_ActiveHIGH
    },
    [TL_YELLOW]=
    {
        .PORT=LED_PORTB,
        .PIN=LED_PIN1,
        .Connection=LED_Connection_ActiveHIGH
    },
    [TL_GREEN]=
    {
        .PORT=LED_PORTB,
        .PIN=LED_PIN2,
        .Connection=LED_Connection_ActiveHIGH
    }
};
