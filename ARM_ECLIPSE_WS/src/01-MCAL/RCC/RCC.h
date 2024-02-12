/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : RCC                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 11/2/2024                                                                */
/* File Details : Header file for RCC Driver                                               */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#ifndef RCC_H
#define RCC_H
/********************************** Includes ***********************************************/

#include "../../00-LIB/STD.h"

/********************************** Definitions ********************************************/
#define PLLSRC_HSI 0xFFBFFFFF
#define PLLSRC_HSE 0x00400000
/**********************************   Types ************************************************/

/*
* @brief Created DataType Used for Return Error masseages from any API
*/
typedef enum
{
    RCC_Error_NOK=0,
    RCC_Error_OK=1
}RCC_Error_t;

/*
* @brief Created Data Type for Choosing Sys Clock
*/
typedef enum 
{
    SYSCLOCK_HSI =0xFFFFFFFC, //be carful dont ||
    SYSCLOCK_HSE =0x00000001,
    SYSCLOCK_PLL =0x00000002
}SYSCLOCK_t;
/*
* @brief Created DataType For Each Clock Source of the System
*/
typedef enum 
{
    CLOCK_HSE =0x00010000,
    CLOCK_HSI =0x00000001,
    CLOCK_PLL =0x01000000
}CLOCK_t;

/*
* @brief Created DataType for Each Peripheral on AHB1
*/
typedef enum 
{
    AHB1peripheral_GPIOA =0x00000001,
    AHB1peripheral_GPIOB =0x00000002,
    AHB1peripheral_GPIOC =0x00000004,
    AHB1peripheral_GPIOD =0x00000008,
    AHB1peripheral_GPIOE =0x00000010,
    AHB1peripheral_GPIOH =0x00000080,
    AHB1peripheral_CRC   =0x00001000,
    AHB1peripheral_DMA1  =0x00200000,
    AHB1peripheral_DMA2  =0x00400000
}AHB1peripheral_t;

/*
* @brief Created DataType for Each Peripheral on AHB2
*/
typedef enum 
{
    AHB2peripheral_OTGFS =0x00000080
}AHB2peripheral_t;

/*
* @brief Created DataType for Each Peripheral on APB1
*/
typedef enum 
{
    APB1peripheral_TIM2    =0x00000001,
    APB1peripheral_TIM3    =0x00000002,
    APB1peripheral_TIM4    =0x00000004,
    APB1peripheral_TIM5    =0x00000008,
    APB1peripheral_WWDG    =0x00000800,
    APB1peripheral_SPI2    =0x00004000,
    APB1peripheral_SPI3    =0x00008000,
    APB1peripheral_USART2  =0x00020000,
    APB1peripheral_I2C1    =0x00200000,
    APB1peripheral_I2C2    =0x00400000,
    APB1peripheral_I2C3    =0x00800000,
    APB1peripheral_PWR     =0x10000000
}APB1peripheral_t;

/*
* @brief Created DataType for Each Peripheral on APB2
*/
typedef enum 
{
    APB2peripheral_TIM1    =0x00000001,
    APB2peripheral_USART1  =0x00000010,
    APB2peripheral_USART6  =0x00000020,
    APB2peripheral_ADC1    =0x00000100,
    APB2peripheral_SDIO    =0x00000800,
    APB2peripheral_SPI1    =0x00001000,
    APB2peripheral_SPI4    =0x00002000,
    APB2peripheral_GYSCFG  =0x00004000,
    APB2peripheral_TIM9    =0x00010000,
    APB2peripheral_TIM10   =0x00020000,
    APB2peripheral_TIM11   =0x00040000
}APB2peripheral_t;

/*
* @brief Created DataType for Each Prescaling Value of AHB bus
*/
typedef enum 
{
    AHBprescaller_TWO =0x00000080
}AHBprescaller_t;

/*
* @brief Created DataType for Each Prescaling Value of APB1 Bus
*/
typedef enum 
{
    APB1prescaller_TWO      =0x00001000,
    APB1prescaller_FOUR     =0x00001400,
    APB1prescaller_EIGHT    =0x00001800,
    APB1prescaller_SIXTEEN  =0x00001C00
}APB1prescaller_t;


/*
* @brief Created DataType for Each Prescaling Value of APB2 Bus
*/
typedef enum 
{
    APB2prescaller_TWO      =0x00008000,
    APB2prescaller_FOUR     =0x0000A000,
    APB2prescaller_EIGHT    =0x0000C000,
    APB2prescaller_SIXTEEN  =0x0000E000
}APB2prescaller_t;
/**********************************   API's ************************************************/



/*
* @brief Function Used to Select System Clock from the Available Clocks
* @param uint8
*  (SYSCLOCK_HSE -    
*  SYSCLOCK_HSI -    
*  SYSCLOCK_PLL)   
* @warning Make sure that the chosen Clock is ON and Ready
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Select_SYSCLOCK(SYSCLOCK_t SYSCLOCK);

/*
* @brief Function Used to Get the current System Clock
* @param void
* @return uint8
*/
uint8 RCC_Get_SYSCLOCK(void);





/*
* @brief Function Used to Enable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Enable_CLOCK(CLOCK_t CLOCK);

/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Disable_CLOCK(CLOCK_t CLOCK);




/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Enable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral);
/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Disable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral);

/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Enable_AHB2Peripheral(AHB2peripheral_t AHB1peripheral);
/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Disable_AHB2Peripheral(AHB2peripheral_t AHB2peripheral);


RCC_Error_t RCC_Enable_APB1Peripheral(APB1peripheral_t APB1peripheral);
/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Disable_APB1Peripheral(APB1peripheral_t APB1peripheral);

/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Enable_APB2Peripheral(APB2peripheral_t APB2peripheral);
/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Disable_APB2Peripheral(APB2peripheral_t APB2peripheral);




/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Configure_AHBprescaller(AHBprescaller_t AHBprescaller);

/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Configure_APB1prescaller(APB1prescaller_t APB1prescaller);

/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Configure_APB2prescaller(APB2prescaller_t APB2prescaller);





/*
* @brief Function Used to Disable any Clock in the System
* @param CLOCK  
* @return Error status
* @example RCC_Select_SYSCLOCK(SYSCLOCK_PLL)
*/
RCC_Error_t RCC_Configure_PLL(uint8 PLLQ,uint8 PLLP, uint8 PLLN,uint8 PLLM,uint8 PLLSRC);
#endif