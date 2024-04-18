/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : xxxx                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : xx/xx/2024                                                               */
/* File Details : Source file for xxxx Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../../include/02-HAL/SWITCH/SWITCH.h"
#include "../../../include/00-LIB/STD.h"
#include "../../../include/01-MCAL/GPIO/GPIO.h"
/********************************** Definitions ********************************************/

/**********************************  Variables  ********************************************/
extern const SWITCH_CONFG_t SWITCHARR[_SWITCH_enum];
/******************************** Implementation *******************************************/
SWITCH_Error_t SWITCH_INIT()
{
    GPIO_CONFIG_t SWITCH;
    SWITCH.SPEED=GPIO_SPEED_HIGH;
    for(uint8 IDX=0;IDX<_SWITCH_enum;IDX++)
    {
        SWITCH.MODE=SWITCHARR[IDX].Connection;
        SWITCH.PORT=SWITCHARR[IDX].PORT;
        SWITCH.PIN=SWITCHARR[IDX].PIN;
        GPIO_INIT_PIN(&SWITCH);
    }
    return SWITCH_OK;
}

SWITCH_Error_t SWITCH_GetStatus(SWITCHS_t COPY_SWITCH_NAME, uint8* COPY_SWITCH_STATUS)
{
    uint8 ret=SWITCH_NOK;
    ret=GPIO_GetPinValue(SWITCHARR[COPY_SWITCH_NAME].PORT,SWITCHARR[COPY_SWITCH_NAME].PIN, &COPY_SWITCH_STATUS);
    return ret;
}