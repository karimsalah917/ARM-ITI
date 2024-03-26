/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Source Configuration file for LCD  Driver                                */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../../include/02-HAL/LCD/LCD.h"
#include "../../../include/02-HAL/LCD/LCD_Config.h"
/********************************** Definitions ********************************************/
#define LCD_D0_PIN                  0
#define LCD_D1_PIN                  1
#define LCD_D2_PIN                  2
#define LCD_D3_PIN                  3
#define LCD_D4_PIN                  4
#define LCD_D5_PIN                  5
#define LCD_D6_PIN                  6
#define LCD_D7_PIN                  7
#define LCD_ENABLE_PIN              8
#define LCD_RW_PIN                  9
#define LCD_RS_PIN                  10
/**********************************   Variables ********************************************/

/**
 *  CHOOSE THE CORESPONDING CONNECTION TO EACH LCD PIN
 * @warning be carful of the mode youre operating at 8bit/4bit
*/
const LCD_strLCDConfigration_t PIN_CONFIG[USED_LCD_PIN_NUMS]=
{
    [LCD_D0_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN0
    },
    [LCD_D1_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN1
    },
    [LCD_D2_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN2
    },
    [LCD_D3_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN3
    },
    [LCD_D4_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN4
    },
    [LCD_D5_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN5
    },
    [LCD_D6_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN6
    },
    [LCD_D7_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN7
    },
    [LCD_ENABLE_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN8
    },
    [LCD_RW_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN9
    },
    [LCD_RS_PIN]=
    {
       .LCD_PortNum = LCD_PORTA,
       .LCD_PinNum  = LCD_PIN10
    }
};
