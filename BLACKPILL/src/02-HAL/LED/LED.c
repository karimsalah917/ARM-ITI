/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LED                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 19/02/2024                                                               */
/* File Details : Source file for LED Driver                                               */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../../include/00-LIB/STD.h"
#include "../../../include/01-MCAL/GPIO/GPIO.h"
#include "../../../include/02-HAL/LED/LED.h"
/********************************** Definitions ********************************************/
/*none*/
/**********************************  Types  ************************************************/
/*none*/
/*********************************** variables *********************************************/
 extern const LED_CONFG_t LEDARR[_LED_enum];
/******************************** Implementation *******************************************/

LED_Error_t LED_INIT(void)
{
    GPIO_CONFIG_t LED; //creating instance of GPIO configuration struct
    LED.MODE=GPIO_MODE_OUT_PP_FL; //setting the mode as output pushpull
    LED.SPEED=GPIO_SPEED_HIGH; //setting speed high

    for(uint8 IDX=0;IDX<_LED_enum;IDX++) //looping to configure all leds
    {
        LED.PORT=LEDARR[IDX].PORT;
        LED.PIN=LEDARR[IDX].PIN;
        GPIO_INIT_PIN(&LED);
    }
    return LED_OK;
}


LED_Error_t LED_SetStatus(LEDS_t COPY_LED_NAME,LED_Status_t COPY_LED_STATUS)
{
    LED_Error_t retValue=LED_NOK;
    switch (COPY_LED_STATUS)
    {
    case LED_ON:
    GPIO_SetPinValue(LEDARR[COPY_LED_NAME].PORT,LEDARR[COPY_LED_NAME].PIN,LEDARR[COPY_LED_NAME].Connection);
    retValue=LED_OK;
        break;
     case LED_OFF:
    GPIO_SetPinValue(LEDARR[COPY_LED_NAME].PORT,LEDARR[COPY_LED_NAME].PIN,~LEDARR[COPY_LED_NAME].Connection);
    retValue=LED_OK;
        break;   
    default:
    retValue=LED_NOK;
        break;
    }
    return retValue;
}