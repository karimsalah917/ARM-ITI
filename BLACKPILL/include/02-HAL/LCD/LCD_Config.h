/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Header Configuration file for LCD  Driver                                */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#pragma once
/**********************************  Includes **********************************************/

/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/

/*
 *  DISPLAY_MODE  Options
 *  1-LCD_DISPLAY_ON 
 *  2-LCD_DISPLAY_OFF
 */

#define LCD_DISPLAY_MODE               LCD_DISPLAY_ON

/*
 *  CURSOR_MODE  Options
 *  1-LCD_CURSOR_ON,
 *  2-LCD_CURSOR_OFF
 * 
 */
#define LCD_CURSOR_MODE                LCD_CURSOR_OFF

/*
 *  CURSOR_BLINKING_MODE  Options
 *  1-LCD_CURSOR_BLINKING_ON
 *  2-LCD_CURSOR_BLINKING_OFF
 */
#define LCD_CURSOR_BLINKING_MODE       LCD_CURSOR_BLINKING_ON

/*
 *  BIT_MODE  Options
 *  1-LCD_4BIT_MODE
 *  2-LCD_8BIT_MODE
 */
#define LCD_BIT_MODE                    LCD_8BIT_MODE

/*
 *  FONT_MODE  Options
 *  1-LCD_5X8
 *  2-LCD_5X11
 */
#define LCD_FONT_MODE                   LCD_5X8

/*
 *  ROW_MODE  Options
 *  1-LCD_ONE_ROW  
 *  2-LCD_TWO_ROW  
 */
#define LCD_ROWS_MODE                  LCD_TWO_ROW  


#define   NUMBER_OF_LCD_PINS_8BIT             8
#define   NUMBER_OF_LCD_PINS_4BIT             4
#define   NUMBER_OF_LCD_COLUMNS              16
#define   USED_LCD_PIN_NUMS                  11
