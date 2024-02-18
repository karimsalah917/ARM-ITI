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

#define GPIO_MODER_RESETMASK                    0xFFFFFFFC
#define MODER_OFFSET                            0x00000003

#define OTYPER_OFFSET                           0x00000004

#define GPIO_PUPDR_RESETMASK                    0xFFFFFFFC
#define PUPDR_OFFSET                            0x00000018
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
    uint32 LocalTempMODER =GPIO[ADD_CONFIGURATION->PORT]-> MODER;
    LocalTempMODER &=GPIO_MODER_RESETMASK<<( ADD_CONFIGURATION->PIN );
    LocalTempMODER |=( (ADD_CONFIGURATION->MODE) & MODER_OFFSET ) << ( 2*(ADD_CONFIGURATION->PIN) );
    GPIO[ADD_CONFIGURATION->PORT]-> MODER =LocalTempMODER;

    GPIO[ADD_CONFIGURATION->PORT]-> OSPEEDR |=(ADD_CONFIGURATION->SPEED) << ( 2*(ADD_CONFIGURATION->PIN) );

    uint32 LocalTempOTYPER = GPIO[ADD_CONFIGURATION->PORT]->OTYPER;
    LocalTempOTYPER |=(((ADD_CONFIGURATION->MODE)&OTYPER_OFFSET)>>2)<<( ADD_CONFIGURATION->PIN );
    GPIO[ADD_CONFIGURATION->PORT]->OTYPER =LocalTempOTYPER;

    uint32 LocalTempPUPDR = GPIO[ADD_CONFIGURATION->PORT]->PUPDR;
    LocalTempPUPDR &= GPIO_PUPDR_RESETMASK << ( ADD_CONFIGURATION->PIN );
    LocalTempPUPDR |=( ((ADD_CONFIGURATION->MODE) & PUPDR_OFFSET)>>3 ) << ( 2*(ADD_CONFIGURATION->PIN) );
    GPIO[ADD_CONFIGURATION->PORT]->PUPDR=LocalTempPUPDR;

    return 1;
}

GPIO_Error_t GPIO_SetPinValue(GPIO_PORT_t  COPY_GPIO_PORT, GPIO_PIN_t COPY_GPIO_PIN, PIN_STATE_t COPY_PIN_STATE)
{
    GPIO[COPY_GPIO_PORT]->ODR |= (COPY_PIN_STATE<<COPY_GPIO_PIN);
    return OK;
}

GPIO_Error_t GPIO_GetPinValue(GPIO_PORT_t GPIO_PORT,GPIO_PIN_t GPIO_PIN,uint8 * Copy_PinValue);
