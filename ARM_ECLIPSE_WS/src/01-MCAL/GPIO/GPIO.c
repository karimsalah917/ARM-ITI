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

/********************************** Static Functions ***************************************/

/********************************** Implementation *****************************************/
