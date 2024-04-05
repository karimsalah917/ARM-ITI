/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (LCD)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Header file for LCD Driver                                                */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#pragma once

/**********************************  Includes **********************************************/
#include "../../00-LIB/STD.h"  // Include for standard definitions

/********************************** Definitions ********************************************/
#define LCD_SHIFTING_LEFT           0x18 // Command for shifting display to the left
#define LCD_SHIFTING_RIGHT          0x1C // Command for shifting display to the right
#define LCD_CLEAR_SCREEN            0x01 // Command for clearing display

/**********************************   Types ************************************************/

/**
 * @brief Enumeration for LCD error codes.
 * Provides status indicators for LCD operation success or failure.
 */
typedef enum 
{
    LCD_NOK = 0, /**< LCD operation unsuccessful */
    LCD_OK = 1   /**< LCD operation successful */
} LCD_Error_t;

/**
 * @brief Enumeration for LCD display modes.
 * Specifies whether the LCD display is turned on or off.
 */
typedef enum
{
    LCD_DISPLAY_OFF = 0, /**< LCD display off */
    LCD_DISPLAY_ON = 1   /**< LCD display on */
} LCD_DISPLAY_MODE_t;

/**
 * @brief Enumeration for LCD cursor modes.
 * Specifies whether the cursor on the LCD is displayed or hidden.
 */
typedef enum 
{
    LCD_CURSOR_OFF = 0, /**< Cursor off */
    LCD_CURSOR_ON = 1   /**< Cursor on */
} LCD_CURSOR_MODE_t;

/**
 * @brief Enumeration for LCD cursor blinking modes.
 * Specifies whether the blinking cursor on the LCD is enabled or disabled.
 */
typedef enum
{
    LCD_CURSOR_BLINKING_OFF = 0, /**< Cursor blinking off */
    LCD_CURSOR_BLINKING_ON = 1   /**< Cursor blinking on */
} LCD_CURSOR_BLINKING_MODE_t;

/**
 * @brief Enumeration for LCD font modes.
 * Specifies the font size used on the LCD.
 */
typedef enum 
{
    LCD_5X8 = 0,  /**< 5x8 pixel font mode */
    LCD_5X11 = 1  /**< 5x11 pixel font mode */
} LCD_FONT_MODE_t;

/**
 * @brief Enumeration for LCD rows modes.
 * Specifies the number of rows displayed on the LCD.
 */
typedef enum 
{
    LCD_ONE_ROW = 0,  /**< Single row display mode */
    LCD_TWO_ROW = 1   /**< Dual row display mode */
} LCD_ROWS_MODE_t;

/**
 * @brief Enumeration for LCD bit modes.
 * Specifies the data transfer mode used for communication with the LCD.
 */
typedef enum 
{
    LCD_4BIT_MODE = 0,  /**< 4-bit data transfer mode */
    LCD_8BIT_MODE = 1   /**< 8-bit data transfer mode */
} LCD_BIT_MODE_t;

/**
 * @brief Structure for LCD pin configuration.
 * Contains port and pin number for each LCD pin.
 */
typedef struct
{
   uint32   LCD_PortNum; /**< Port number for the LCD pin */
   uint32   LCD_PinNum;  /**< Pin number for the LCD pin */
} LCD_strLCDConfigration_t;

/**
 * @brief Enumeration for LCD port numbers.
 * Specifies the port number for LCD pin configuration.
 */
typedef enum 
{
    LCD_PORTA = 0x0, /**< Port A */
    LCD_PORTB = 0x1, /**< Port B */
    LCD_PORTC = 0x2  /**< Port C */
} LCD_PORT_t;

/**
 * @brief Enumeration for LCD pin numbers.
 * Specifies the pin number for LCD pin configuration.
 */
typedef enum 
{
    LCD_PIN0  = 0x00000000, /**< Pin 0 */
    LCD_PIN1  = 0x00000001, /**< Pin 1 */
    LCD_PIN2  = 0x00000002, /**< Pin 2 */
    LCD_PIN3  = 0x00000003, /**< Pin 3 */
    LCD_PIN4  = 0x00000004, /**< Pin 4 */
    LCD_PIN5  = 0x00000005, /**< Pin 5 */
    LCD_PIN6  = 0x00000006, /**< Pin 6 */
    LCD_PIN7  = 0x00000007, /**< Pin 7 */
    LCD_PIN8  = 0x00000008, /**< Pin 8 */
    LCD_PIN9  = 0x00000009, /**< Pin 9 */
    LCD_PIN10 = 0x0000000A, /**< Pin 10 */
    LCD_PIN11 = 0x0000000B, /**< Pin 11 */
    LCD_PIN12 = 0x0000000C, /**< Pin 12 */
    LCD_PIN13 = 0x0000000D, /**< Pin 13 */
    LCD_PIN14 = 0x0000000E, /**< Pin 14 */
    LCD_PIN15 = 0x0000000F  /**< Pin 15 */
} LCD_PIN_t;

/**
 * @brief Enumeration for LCD operation status.
 * Specifies whether the LCD is ready or busy.
 */
typedef enum
{
    LCD_Status_READY = 0, /**< LCD is ready */
    LCD_Status_BUSY       /**< LCD is busy */
} LCD_Status_t;

/*********************************** API's *************************************************/
 
/**
 * @brief Initializes the LCD display asynchronously.
 * This function should be called after pin initialization.
 */
void lcd_init_async(void);

/**
 * @brief Writes a string asynchronously to the LCD display.
 * 
 * @param string Pointer to the string to be written.
 * @param size Size of the string to be written.
 * @return LCD_Error_t Returns an error code indicating the success or failure of the operation.
 *                    Possible error codes include:
 *                        - LCD_OK: Operation completed successfully.
 *                        - LCD_NOK: Operation failed.
 * 
 * This function writes a string to the LCD display asynchronously. The size parameter allows specifying the length
 * of the string to be written. The function returns an error code indicating the success or failure of the operation.
 */
LCD_Error_t lcd_write_string_async(const char* string, uint8 size);

/**
 * @brief Sets the position asynchronously on the LCD display.
 * 
 * @param x_pos The x-coordinate position on the display.
 * @param y_pos The y-coordinate position on the display.
 * @return LCD_Error_t Returns an error code indicating the success or failure of the operation.
 *                    Possible error codes include:
 *                        - LCD_OK: Operation completed successfully.
 *                        - LCD_NOK: Operation failed.
 * 
 * This function sets the position on the LCD display asynchronously. The x_pos parameter specifies
 * the horizontal position, and y_pos specifies the vertical position. The function returns an error
 * code indicating the success or failure of the operation.
 */
LCD_Error_t lcd_set_position_async(uint8 x_pos, uint8 y_pos);

/**
 * @brief Sends a command asynchronously to the LCD display.
 * 
 * @param CMD The command to be sent.
 * @return LCD_Error_t Returns an error code indicating the success or failure of the operation.
 *                    Possible error codes include:
 *                        - LCD_OK: Operation completed successfully.
 *                        - LCD_NOK: Operation failed.
 * 
 * This function sends a command to the LCD display asynchronously. The CMD parameter specifies
 * the command to be sent. The function returns an error code indicating the success or failure
 * of the operation.
 */
LCD_Error_t lcd_send_command_async(uint8 CMD);

