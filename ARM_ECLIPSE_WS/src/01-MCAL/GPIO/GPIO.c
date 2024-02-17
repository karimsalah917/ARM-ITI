/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : GPIO                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : 13/2/2024                                                                */
/* File Details : Source file for GPIO Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../../include/01-MCAL/GPIO/GPIO.h"
/********************************** Definitions ********************************************/
#define GPIOA_BASE_ADDRESS                      0x40020000                     
#define GPIOB_BASE_ADDRESS                      0x40020400
#define GPIOC_BASE_ADDRESS                      0x40020800
/**********************************   Types ************************************************/

typedef struct
{
    volatile uint32 MODER;
    volatile uint32 OTYPER;
    volatile uint32 OSPEEDR;
    volatile uint32 PUPDR;
    volatile uint32 IDR;
    volatile uint32 ODR;
    volatile uint32 BSRR;
    volatile uint32 LCKR;
    volatile uint32 AFRL;
    volatile uint32 AFRH;
}GPIO_t;
/**********************************  Variables *********************************************/
static GPIO_t * const GPIO[3] =
{
    (GPIO_t*)GPIOA_BASE_ADDRESS,
    (GPIO_t*)GPIOB_BASE_ADDRESS,
    (GPIO_t*)GPIOC_BASE_ADDRESS
};
/********************************** Static Functions ***************************************/

/********************************** Implementation *****************************************/

/**
 * @brief Initializes a GPIO pin with the specified configuration.
 *
 * @param COPY_CONFIGURATION Pointer to the GPIO configuration structure.
 * @return GPIO_Error_t Returns an error code indicating the success or failure of the operation.
 */
GPIO_Error_t GPIO_INIT_PIN(GPIO_CONFIG_t * ADD_CONFIGURATION)
{
    uint32 LocalTempMODER =
    GPIO[ADD_CONFIGURATION->PORT]-> MODER &=;
    GPIO[ADD_CONFIGURATION->PORT]-> OSPEEDR=;
    GPIO[ADD_CONFIGURATION->PORT]->OTYPER;
    GPIO[ADD_CONFIGURATION->PORT]->PUPDR;
}

GPIO_Error_t GPIO_SetPinValue(GPIO_PORT_t  COPY_GPIO_PORT, GPIO_PIN_t COPY_GPIO_PIN, PIN_STATE_t COPT_PIN_STATE);

GPIO_Error_t GPIO_GetPinValue(GPIO_PORT_t GPIO_PORT,GPIO_PIN_t GPIO_PIN,uint8 * Copy_PinValue);