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

#define GPIO_MODER_RESETMASK                    0x00000003
#define MODER_OFFSET                            0x00000003

#define OTYPER_OFFSET                           0x00000004

#define GPIO_PUPDR_RESETMASK                    0x00000003
#define PUPDR_OFFSET                            0x00000018

#define GPIO_OSPEEDR_RESETMASK                  0x00000003

#define GPIO_IDR_MASK                           0x00000001
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
    uint32 LocalTempREG=0x00000000;

    /**
     * Configuring MODER Register
    */
    LocalTempREG =GPIO[ADD_CONFIGURATION->PORT]-> MODER;//Reading the Corresponding OSPEEDR Register to the chosen Port
    LocalTempREG &=~(GPIO_MODER_RESETMASK<<( 2*(ADD_CONFIGURATION->PIN) ));//Reseting the needed bits before modifing it
    LocalTempREG |=( (ADD_CONFIGURATION->MODE) & MODER_OFFSET ) << ( 2*(ADD_CONFIGURATION->PIN) );//modifing the needed bits 
    GPIO[ADD_CONFIGURATION->PORT]-> MODER =LocalTempREG;//Applying the modification to the physical Register

    /**
     * Configuring OSPEEDR Register
    */
    LocalTempREG =GPIO[ADD_CONFIGURATION->PORT]->OSPEEDR;//Reading the Corresponding OSPEEDR Register to the chosen Port
    LocalTempREG &=~(GPIO_OSPEEDR_RESETMASK<<( 2*(ADD_CONFIGURATION->PIN) ));//Reseting the needed bits before modifing it
    LocalTempREG |=(ADD_CONFIGURATION->SPEED) << ( 2*(ADD_CONFIGURATION->PIN) );//modifing the needed bits 
    GPIO[ADD_CONFIGURATION->PORT]-> OSPEEDR=LocalTempREG;//Applying the modification to the physical Register
    /**
     * Configuring OTYPER Register
    */
    LocalTempREG = GPIO[ADD_CONFIGURATION->PORT]->OTYPER;//Reading the Corresponding OTYPER Register to the chosen Port
    LocalTempREG |=(((ADD_CONFIGURATION->MODE)&OTYPER_OFFSET)>>2)<<( ADD_CONFIGURATION->PIN );//modifing the needed bits 
    GPIO[ADD_CONFIGURATION->PORT]->OTYPER =LocalTempREG;//Applying the modification to the physical Register


    /**
     * Configuring PUPDR Register
    */
    LocalTempREG = GPIO[ADD_CONFIGURATION->PORT]->PUPDR; //Reading the Corresponding PUPDR Register to the chosen Port
    LocalTempREG &= ~(GPIO_PUPDR_RESETMASK << ( 2*(ADD_CONFIGURATION->PIN ))); //Reseting the needed bits before modifing it
    LocalTempREG |=( ((ADD_CONFIGURATION->MODE) & PUPDR_OFFSET)>>3 ) << ( 2*(ADD_CONFIGURATION->PIN) ); //modifing the needed bits 
    GPIO[ADD_CONFIGURATION->PORT]->PUPDR=LocalTempREG; //Applying the modification to the physical Register

    return OK;
}

GPIO_Error_t GPIO_SetPinValue(GPIO_PORT_t  COPY_GPIO_PORT, GPIO_PIN_t COPY_GPIO_PIN, PIN_STATE_t COPY_PIN_STATE)
{
    GPIO_Error_t RetValue=NOK;
    if(COPY_PIN_STATE==PIN_STATE_HIGH)
    {
        GPIO[COPY_GPIO_PORT]->ODR |= (COPY_PIN_STATE<<COPY_GPIO_PIN);
        RetValue=OK;
    }else if (COPY_PIN_STATE==PIN_STATE_LOW)
    {
        GPIO[COPY_GPIO_PORT]->ODR &= (COPY_PIN_STATE<<COPY_GPIO_PIN);
        RetValue=OK;
    }
    
    return RetValue;
}

GPIO_Error_t GPIO_GetPinValue(GPIO_PORT_t GPIO_PORT,GPIO_PIN_t GPIO_PIN,uint8 * Copy_PinValue)
{
    * Copy_PinValue= (((GPIO[GPIO_PORT]->IDR) & (GPIO_IDR_MASK<<GPIO_PIN)) >> GPIO_PIN) ;
    return OK;
}