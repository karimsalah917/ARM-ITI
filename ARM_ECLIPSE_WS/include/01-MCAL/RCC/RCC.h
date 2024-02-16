/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : RCC                                                                      */
/* Version      : v1.1                                                                     */
/* Date         : 11/2/2024                                                                */
/* File Details : Header file for RCC Driver                                               */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#ifndef RCC_H
#define RCC_H
/********************************** Includes ***********************************************/

#include "../../00-LIB/STD.h"

/********************************** Definitions ********************************************/
#define SWS 0x0000000C
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
    SYSCLOCK_HSI =0x00000000,
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

/*
* @brief Created DataType for Each PLLSRC Values
*/
typedef enum 
{
    PLLSRC_HSI =0xFFBFFFFF,
    PLLSRC_HSE =0x00400000
}PLLSRC_t;
/**********************************   API's ************************************************/



/**
 * @brief Selects the system clock from the available options.
 *
 * @param SYSCLOCK The selected system clock source, defined by the enumeration SYSCLOCK_t.
 *
 * @warning Ensure that the chosen clock source is activated and ready for use.
 *
 * @return Error status RCC_Error_OK if the system clock selection is successful.
 *
 * @note Once the system clock is set to PLL, it cannot be reconfigured.
 */
RCC_Error_t RCC_Select_SYSCLOCK(SYSCLOCK_t SYSCLOCK);


/**
 * @brief Retrieves the current system clock status.
 *
 * This function retrieves the current status of the system clock and stores it in the provided status variable.
 *
 * @param COPY_Status_variable Pointer to the variable where the system clock status will be stored.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Get_SYSCLOCK(uint8 *COPY_Status_variable);



/**
 * @brief Enables the specified clock source.
 *
 * This function is used to enable the specified clock source, identified by the parameter CLOCK.
 * It ensures that the designated clock is activated and ready for use by the system.
 *
 * @param CLOCK The clock source to be enabled, specified by the enumeration CLOCK_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Enable_CLOCK(CLOCK_t CLOCK);

/**
 * @brief Disables the specified clock source.
 *
 * This function is used to disable the specified clock source, identified by the parameter CLOCK.
 * It ensures that the designated clock is deactivated and no longer used by the system.
 *
 * @param CLOCK The clock source to be disabled, specified by the enumeration CLOCK_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Disable_CLOCK(CLOCK_t CLOCK);




/**
 * @brief Enables the specified AHB1 peripheral.
 *
 * This function enables the clock for the specified AHB1 peripheral, identified by the parameter AHB1peripheral.
 * Enabling the clock allows the peripheral to operate and communicate with other parts of the system.
 *
 * @param AHB1peripheral The AHB1 peripheral to be enabled, specified by the enumeration AHB1peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Enable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral);

/**
 * @brief Disables the specified AHB1 peripheral.
 *
 * This function disables the clock for the specified AHB1 peripheral, identified by the parameter AHB1peripheral.
 * Disabling the clock prevents the peripheral from operating and communicating with other parts of the system.
 *
 * @param AHB1peripheral The AHB1 peripheral to be disabled, specified by the enumeration AHB1peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Disable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral);



/**
 * @brief Enables the specified AHB2 peripheral.
 *
 * This function enables the clock for the specified AHB2 peripheral, identified by the parameter AHB2peripheral.
 * Enabling the clock allows the peripheral to operate and communicate with other parts of the system.
 *
 * @param AHB2peripheral The AHB2 peripheral to be enabled, specified by the enumeration AHB2peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Enable_AHB2Peripheral(AHB2peripheral_t AHB2peripheral);

/**
 * @brief Disables the specified AHB2 peripheral.
 *
 * This function disables the clock for the specified AHB2 peripheral, identified by the parameter AHB2peripheral.
 * Disabling the clock prevents the peripheral from operating and communicating with other parts of the system.
 *
 * @param AHB2peripheral The AHB2 peripheral to be disabled, specified by the enumeration AHB2peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Disable_AHB2Peripheral(AHB2peripheral_t AHB2peripheral);


/**
 * @brief Enables the specified APB1 peripheral.
 *
 * This function enables the clock for the specified APB1 peripheral, identified by the parameter APB1peripheral.
 * Enabling the clock allows the peripheral to operate and communicate with other parts of the system.
 *
 * @param APB1peripheral The APB1 peripheral to be enabled, specified by the enumeration APB1peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Enable_APB1Peripheral(APB1peripheral_t APB1peripheral);

/**
 * @brief Disables the specified APB1 peripheral.
 *
 * This function disables the clock for the specified APB1 peripheral, identified by the parameter APB1peripheral.
 * Disabling the clock prevents the peripheral from operating and communicating with other parts of the system.
 *
 * @param APB1peripheral The APB1 peripheral to be disabled, specified by the enumeration APB1peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Disable_APB1Peripheral(APB1peripheral_t APB1peripheral);


/**
 * @brief Enables the specified APB2 peripheral.
 *
 * This function enables the clock for the specified APB2 peripheral, identified by the parameter APB2peripheral.
 * Enabling the clock allows the peripheral to operate and communicate with other parts of the system.
 *
 * @param APB2peripheral The APB2 peripheral to be enabled, specified by the enumeration APB2peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Enable_APB2Peripheral(APB2peripheral_t APB2peripheral);

/**
 * @brief Disables the specified APB2 peripheral.
 *
 * This function disables the clock for the specified APB2 peripheral, identified by the parameter APB2peripheral.
 * Disabling the clock prevents the peripheral from operating and communicating with other parts of the system.
 *
 * @param APB2peripheral The APB2 peripheral to be disabled, specified by the enumeration APB2peripheral_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Disable_APB2Peripheral(APB2peripheral_t APB2peripheral);




/**
 * @brief Configures the prescaler for the AHB bus.
 *
 * This function configures the prescaler for the AHB (Advanced High-performance Bus) to adjust the clock frequency
 * of AHB peripherals. The parameter AHBprescaller determines the division factor.
 *
 * @param AHBprescaller The prescaler configuration for the AHB bus, specified by the enumeration AHBprescaller_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Configure_AHBprescaller(AHBprescaller_t AHBprescaller);

/**
 * @brief Configures the prescaler for the APB1 bus.
 *
 * This function configures the prescaler for the APB1 (Advanced Peripheral Bus 1) to adjust the clock frequency
 * of APB1 peripherals. The parameter APB1prescaller determines the division factor.
 *
 * @param APB1prescaller The prescaler configuration for the APB1 bus, specified by the enumeration APB1prescaller_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Configure_APB1prescaller(APB1prescaller_t APB1prescaller);

/**
 * @brief Configures the prescaler for the APB2 bus.
 *
 * This function configures the prescaler for the APB2 (Advanced Peripheral Bus 2) to adjust the clock frequency
 * of APB2 peripherals. The parameter APB2prescaller determines the division factor.
 *
 * @param APB2prescaller The prescaler configuration for the APB2 bus, specified by the enumeration APB2prescaller_t.
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Configure_APB2prescaller(APB2prescaller_t APB2prescaller);





/**
 * @brief Configures the Phase-Locked Loop (PLL).
 *
 * This function configures the Phase-Locked Loop (PLL) to generate a stable clock signal
 * with a desired frequency and phase relationship from the input clock sources.
 *
 * @note This function is hard Coded to configure the PLL to operate
 * over HSE and having a final value of 84MHZ
 *
 * @return Error status indicating the success or failure of the operation.
 */
RCC_Error_t RCC_Configure_PLL();
#endif