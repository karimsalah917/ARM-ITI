/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LED                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : 19/02/2024                                                               */
/* File Details : Header file for LED Driver                                               */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#ifndef LED_H
#define LED_H
/**********************************  Includes **********************************************/
#include "LED_Config.h"
/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/

/**
 * @brief Defines a data type for the return value of any function as an error status.
 */
typedef enum 
{
    LED_NOK = 0, /**< Indicates an error status */
    LED_OK  = 1  /**< Indicates a successful status */
} LED_Error_t;

/**
 * @brief Defines a data type for LED status.
 */
typedef enum 
{
    LED_OFF = 0, /**< LED is turned off */
    LED_ON  = 1  /**< LED is turned on */
} LED_Status_t;

/**
 * @brief Defines a data type for ports available to connect LEDs.
 */
typedef enum 
{
    LED_PORTA = 0x0, /**< Port A */
    LED_PORTB = 0x1, /**< Port B */
    LED_PORTC = 0x2  /**< Port C */
} LED_PORT_t;

/**
 * @brief Defines a data type for pins available to connect LEDs.
 */
typedef enum 
{
    LED_PIN0  = 0x00000000, /**< Pin 0 */
    LED_PIN1  = 0x00000001, /**< Pin 1 */
    LED_PIN2  = 0x00000002, /**< Pin 2 */
    LED_PIN3  = 0x00000003, /**< Pin 3 */
    LED_PIN4  = 0x00000004, /**< Pin 4 */
    LED_PIN5  = 0x00000005, /**< Pin 5 */
    LED_PIN6  = 0x00000006, /**< Pin 6 */
    LED_PIN7  = 0x00000007, /**< Pin 7 */
    LED_PIN8  = 0x00000008, /**< Pin 8 */
    LED_PIN9  = 0x00000009, /**< Pin 9 */
    LED_PIN10 = 0x0000000A, /**< Pin 10 */
    LED_PIN11 = 0x0000000B, /**< Pin 11 */
    LED_PIN12 = 0x0000000C, /**< Pin 12 */
    LED_PIN13 = 0x0000000D, /**< Pin 13 */
    LED_PIN14 = 0x0000000E, /**< Pin 14 */
    LED_PIN15 = 0x0000000F  /**< Pin 15 */
} LED_PIN_t;

/**
 * @brief Defines a data type for each LED connection type.
 */
typedef enum 
{
    LED_Connection_ActiveLow  = 0xFFFFFFFE, /**< Active low connection */
    LED_Connection_ActiveHIGH = 0x00000001  /**< Active high connection */
} LED_Connection_t;

/**
 * @brief Defines a data type for each LED configuration.
 */
typedef struct
{
    LED_PORT_t        PORT;       /**< Port of the LED */
    LED_PIN_t         PIN;        /**< Pin of the LED */
    LED_Connection_t  Connection; /**< Connection type of the LED */
} LED_CONFG_t;



/*********************************** API's *************************************************/
 
/**
 * @brief Initializes all selected components of this module.
 * 
 * @return Error message indicating the success or failure of the operation.
 * 
 * @warning This function must be called before using the other APIs.
 */
LED_Error_t LED_INIT(void);


/**
 *@brief Sets the status of a specified LED.
 *
 *@param COPY_LED_NAME The name or identifier of the LED.
 *@param COPY_LED_STATUS The status to set for the LED (ON, OFF, BLINK, etc.).
 *
 *@return LED_Error_t Indicates the success or failure of setting the LED status.
*/
LED_Error_t LED_SetStatus(LEDS_t COPY_LED_NAME,LED_Status_t COPY_LED_STATUS);



#endif