/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (LCD)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Header file for LCD  Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#pragma once
/**********************************  Includes **********************************************/
#include "../../00-LIB/STD.h"
/********************************** Definitions ********************************************/
#define LCD_SHIFTING_LEFT           0x18
#define LCD_SHIFTING_RIGHT          0x1C
#define LCD_CLEAR_DISPLAY           0x01
/**********************************   Types ************************************************/

/**
 * LCD INITIALISATION
*/

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
 * LCD CONNECTION INITIALISATION
*/
typedef struct
{
   uint32   LCD_PortNum;
   uint32   LCD_PinNum;
} LCD_strLCDConfigration_t;

typedef enum 
{
    LCD_PORTA = 0x0,
    LCD_PORTB = 0x1,
    LCD_PORTC = 0x2
}
LCD_PORT_t;

typedef enum 
{
    LCD_PIN0  = 0x00000000,    
    LCD_PIN1  = 0x00000001,    
    LCD_PIN2  = 0x00000002,    
    LCD_PIN3  = 0x00000003,    
    LCD_PIN4  = 0x00000004,    
    LCD_PIN5  = 0x00000005,    
    LCD_PIN6  = 0x00000006,    
    LCD_PIN7  = 0x00000007,    
    LCD_PIN8  = 0x00000008,    
    LCD_PIN9  = 0x00000009,    
    LCD_PIN10 = 0x0000000A,    
    LCD_PIN11 = 0x0000000B,    
    LCD_PIN12 = 0x0000000C,    
    LCD_PIN13 = 0x0000000D,    
    LCD_PIN14 = 0x0000000E,    
    LCD_PIN15 = 0x0000000F       
}LCD_PIN_t;

/**
 * LCD OPERATION 
*/

typedef enum
{
 LCD_Position0,
 LCD_Position1,
 LCD_Position2,
 LCD_Position3,
 LCD_Position4,
 LCD_Position5,
 LCD_Position6,
 LCD_Position7,
 LCD_Position8,
 LCD_Position9,
 LCD_Position10,
 LCD_Position11,
 LCD_Position12,
 LCD_Position13,
 LCD_Position14,
 LCD_Position15
}LCD_DDRAM_XPosition;

typedef enum
{
 LCD_FirstLine,
 LCD_SecondLine
}LCD_DDRAM_YPosition;

typedef enum
{
    LCD_Status_READY=0,
    LCD_Status_BUSY=1
}
LCD_Status_t;
/*********************************** API's *************************************************/
 
/**
 * @brief Initializes the pins required for LCD communication.
 * This function should be called before any other LCD operation.
 */
void LCD_PinInit(void);

/**
 * @brief Initializes the LCD display.
 * This function should be called after pin initialization.
 */
void LCD_InitAsync(void);

/**
 * @brief Writes a string asynchronously to the LCD display.
 * @param String Pointer to the string to be written.
 * @param Size Size of the string.
 * @param X_Postion X position where the string should start.
 * @param Y_Postion Y position where the string should start.
 * @return LCD_Error_t Error code indicating success or failure of the operation.
 */
LCD_Error_t LCD_WriteStringAsync(const char* String, uint8 Size, uint8 X_Postion, uint8 Y_Postion);

/**
 * @brief Clears the entire screen of the LCD display.
 * @return LCD_Error_t Error code indicating success or failure of the operation.
 */
LCD_Error_t LCD_ClearScreenAsync(void);

/**
 * @brief Retrieves the status of the LCD, indicating whether it is ready for further operations.
 * 
 * As the LCD functions are asynchronous, it's essential to check whether the LCD operation
 * has been completed before proceeding with another operation. This function provides
 * information on the readiness of the LCD.
 * 
 * @return LCD_Status_t Status indicating if the LCD is ready or not.
 */
LCD_Status_t LCD_GetStatus(void);


