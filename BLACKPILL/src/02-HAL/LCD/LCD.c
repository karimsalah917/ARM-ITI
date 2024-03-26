/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Source file for LCD  Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/
#include "../../../include/02-HAL/LCD/LCD.h"
#include "../../../include/02-HAL/LCD/LCD_Config.h"
/********************************** Definitions ********************************************/

/**********************************  Types  ************************************************/
/**********************************  variables  ********************************************/

/******************************** Static functions *****************************************/
void LCD_Runnable(void)
{

}
/******************************** Interface functions **************************************/

void LCD_PinInit(void);

void LCD_InitAsync(void);

LCD_Error_t LCD_WriteStringAsync(const char* String, uint8 Size, uint8 X_Postion, uint8 Y_Postion);

LCD_Error_t LCD_ClearScreenAsync(void);

LCD_Status_t LCD_GetStatus(void);