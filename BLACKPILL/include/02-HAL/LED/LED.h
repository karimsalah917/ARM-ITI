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
* @brief Created Data Type for the Return value of any function as 
* an error status 
*/
typedef enum 
{
    HAL_NOK=0,
    HAL_OK=1
}LED_Error_t;

/**
 * @brief Created Data Type for LED status
*/
typedef enum 
{
    LED_OFF=0,
    LED_ON =1,
}LED_Status_t;

/**
 * @brief Created Data Type for Ports that available to connect leds at
*/
typedef enum 
{
    LED_PORTA = 0x0,
    LED_PORTB = 0x1,
    LED_PORTC = 0x2
}
LED_PORT_t;

/**
 * @brief Created Data Typef for pins avaailable to connect leds at
*/
typedef enum 
{
    LED_PIN0  = 0x00000000,    
    LED_PIN1  = 0x00000001,    
    LED_PIN2  = 0x00000002,    
    LED_PIN3  = 0x00000003,    
    LED_PIN4  = 0x00000004,    
    LED_PIN5  = 0x00000005,    
    LED_PIN6  = 0x00000006,    
    LED_PIN7  = 0x00000007,    
    LED_PIN8  = 0x00000008,    
    LED_PIN9  = 0x00000009,    
    LED_PIN10 = 0x0000000A,    
    LED_PIN11 = 0x0000000B,    
    LED_PIN12 = 0x0000000C,    
    LED_PIN13 = 0x0000000D,    
    LED_PIN14 = 0x0000000E,    
    LED_PIN15 = 0x0000000F       
}LED_PIN_t;

/**
 *@brief Created Data Type for Each LED Connection 
*/
typedef enum 
{
    LED_Connection_ActiveLow  = 0,
    LED_Connection_ActiveHIGH = 1
}LED_Connection_t;

/**
 * @brief Created Data Type for each pin configuration
*/
typedef struct
{
    LED_PORT_t        PORT      ;
    LED_PIN_t         PIN       ;
    LED_Connection_t  Connection;
}LED_CONFG_t;


/*********************************** API's *************************************************/
 
 /**
  * @brief Initialise all selected components of this module
  *  
  * @return Error message indicating the success or failure of the operation.
  * 
  * @warning this function must be called before using the other API's
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