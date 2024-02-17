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

    GPIO_MODE_INPUT_FLOAT   = 0x00000000,
    GPIO_MODE_INPUT_PU      = 0x00000000,
    GPIO_MODE_INPUT_PD      = 0x00000000,

    

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
/**********************************   API's ************************************************/
GPIO_Error_t GPIO_INIT_PIN(GPIO_CONFIG_t * COPY_CONFIGURATION);

GPIO_Error_t GPIO_SetPinValue(uint32 GPIO_PORT,uint32 GPIO_PIN,uint32 PIN_STATE);

GPIO_Error_t GPIO_GetPinValue(uint32 GPIO_PORT,uint32 GPIO_PIN,uint8 * Copy_PinValue);