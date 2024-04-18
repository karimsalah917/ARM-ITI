/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : SWITCH                                                                   */
/* Version      : v1.0                                                                     */
/* Date         : 22/02/2024                                                               */
/* File Details : Source Configuration file for xxxx Driver                                */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../../include/02-HAL/SWITCH/SWITCH.h"
#include "../../../include/02-HAL/SWITCH/SWITCH_Config.h"
/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/
const SWITCH_CONFG_t SWITCHARR[_SWITCH_enum]=
{
    [TEST_SWITCH]=
    {
        .Connection=SWITCH_Connection_InPU,
        .PORT=SWITCH_PORTB,
        .PIN=SWITCH_PIN7
    }
};
