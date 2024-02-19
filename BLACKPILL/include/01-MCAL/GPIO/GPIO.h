/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : GPIO                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : 13/2/2024                                                                */
/* File Details : Header file for GPIO Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../00-LIB/STD.h"
/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/

/**
 * @brief Created Data type for the Return value of each funcion to state the success of the function 
*/
typedef enum 
{
    OK=1,
    NOK=0
}GPIO_Error_t;

/**
 *@brief Created Data type for the Port types the user will use it in the configuration structure 
*/
typedef enum 
{
    GPIO_PORTA = 0x0,
    GPIO_PORTB = 0x1,
    GPIO_PORTC = 0x2
}
GPIO_PORT_t;

/**
 * @brief Creatd Data Type for the pin values the user will use it in the configuration structure
*/
typedef enum 
{
    GPIO_PIN0  = 0x00000000,    
    GPIO_PIN1  = 0x00000001,    
    GPIO_PIN2  = 0x00000002,    
    GPIO_PIN3  = 0x00000003,    
    GPIO_PIN4  = 0x00000004,    
    GPIO_PIN5  = 0x00000005,    
    GPIO_PIN6  = 0x00000006,    
    GPIO_PIN7  = 0x00000007,    
    GPIO_PIN8  = 0x00000008,    
    GPIO_PIN9  = 0x00000009,    
    GPIO_PIN10 = 0x0000000A,    
    GPIO_PIN11 = 0x0000000B,    
    GPIO_PIN12 = 0x0000000C,    
    GPIO_PIN13 = 0x0000000D,    
    GPIO_PIN14 = 0x0000000E,    
    GPIO_PIN15 = 0x0000000F       
}GPIO_PIN_t;

/**
 *@brief Created Data Type for the mode of operation of each pin 
*/
typedef enum 
{
    GPIO_MODE_ANALOG        = 0x00000003,

    GPIO_MODE_INPUT_FL      = 0x00000000,
    GPIO_MODE_INPUT_PU      = 0x00000008,
    GPIO_MODE_INPUT_PD      = 0x00000010,

    GPIO_MODE_OUT_PP_FL     = 0x00000001,   
    GPIO_MODE_OUT_PP_PU     = 0x00000009,
    GPIO_MODE_OUT_PP_PD     = 0x00000011,
    GPIO_MODE_OUT_OD_FL     = 0x00000005,
    GPIO_MODE_OUT_OD_PU     = 0x0000000D,
    GPIO_MODE_OUT_OD_PD     = 0x00000015,

    GPIO_MODE_AF_PP_FL      = 0x00000002,   
    GPIO_MODE_AF_PP_PU      = 0x0000000A,
    GPIO_MODE_AF_PP_PD      = 0x00000012,
    GPIO_MODE_AF_OD_FL      = 0x00000006,
    GPIO_MODE_AF_OD_PU      = 0x0000000E,
    GPIO_MODE_AF_OD_PD      = 0x00000016

}GPIO_MODE_t;

/**
 *@brief Created Data Type for the Speed of each pin 
*/
typedef enum
{
    GPIO_SPEED_LOW   = 0x00000000,
    GPIO_SPEED_MED   = 0x00000001,
    GPIO_SPEED_HIGH  = 0x00000002,
    GPIO_SPEED_VHIGH = 0x00000003   
}GPIO_SPEED_t;
/**
 * @brief Created Data type for a Struct the user will use it to make a configuration for a 
 * single pin
*/
typedef struct 
{
    GPIO_PORT_t    PORT;
    GPIO_PIN_t     PIN ;
    GPIO_MODE_t    MODE;
    GPIO_SPEED_t   SPEED;
}
GPIO_CONFIG_t;

/**
 * @brief Created Data Type for Pin value at output mode of any pin
*/
typedef enum 
{
    PIN_STATE_LOW  =0xFFFFFFFE,
    PIN_STATE_HIGH =0x00000001
}
PIN_STATE_t;
/**********************************   API's ************************************************/

/**
 * @brief Initializes a GPIO pin with the specified configuration.
 *
 * @param COPY_CONFIGURATION Pointer to the GPIO configuration structure.
 * @return GPIO_Error_t Returns an error code indicating the success or failure of the operation.
 */
GPIO_Error_t GPIO_INIT_PIN(GPIO_CONFIG_t * ADD_CONFIGURATION);

/**
 * @brief Sets the value of a GPIO pin to the specified state.
 *
 * @param COPY_GPIO_PORT The GPIO port to which the pin belongs.
 * @param COPY_GPIO_PIN The GPIO pin number to set the value for.
 * @param COPT_PIN_STATE The state to set the GPIO pin to (e.g., HIGH or LOW).
 * @return GPIO_Error_t Returns an error code indicating the success or failure of the operation.
 */
GPIO_Error_t GPIO_SetPinValue(GPIO_PORT_t  COPY_GPIO_PORT, GPIO_PIN_t COPY_GPIO_PIN, PIN_STATE_t COPY_PIN_STATE);

/**
 * @brief Retrieves the current value of a GPIO pin.
 *
 * @param GPIO_PORT The GPIO port to which the pin belongs.
 * @param GPIO_PIN The GPIO pin number to get the value for.
 * @param Copy_PinValue Pointer to store the retrieved pin value.
 * @return GPIO_Error_t Returns an error code indicating the success or failure of the operation.
 */
GPIO_Error_t GPIO_GetPinValue(GPIO_PORT_t GPIO_PORT,GPIO_PIN_t GPIO_PIN,uint8 * Copy_PinValue);
