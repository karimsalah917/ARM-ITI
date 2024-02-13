/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : RCC                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 11/2/2024                                                                */
/* File Details : Source file for RCC Driver                                               */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
/********************************** Includes ***********************************************/
#include "RCC.h"
/********************************** Definitions ********************************************/

/**********************************  Types  ************************************************/

typedef struct 
{
    uint32 RCC_CR;
    uint32 RCC_PLLCFGR;
    uint32 RCC_CFGR;
    uint32 RCC_CIR;
    uint32 RCC_AHB1RSTR;
    uint32 RCC_AHB2RSTR;
    uint32 RESERVED1;
    uint32 RESERVED2;
    uint32 RCC_APB1RSTR;
    uint32 RCC_APB2RSTR;
    uint32 RESERVED3;
    uint32 RESERVED4;
    uint32 RCC_AHB1ENR;
    uint32 RCC_AHB2ENR;
    uint32 RESERVED5;
    uint32 RESERVED6;
    uint32 RCC_APB1ENR;
    uint32 RCC_APB2ENR;
    uint32 RESERVED7;
    uint32 RESERVED8;
    uint32 RCC_AHB1LPENR;
    uint32 RCC_AHB2LPENR;
    uint32 RESERVED9;
    uint32 RESERVED10;
    uint32 RCC_APB1LPENR;
    uint32 RCC_APB2LPENR;
    uint32 RESERVED11;
    uint32 RESERVED12;
    uint32 RCC_BDCR;
    uint32 RCC_CSR;
    uint32 RESERVED13;
    uint32 RESERVED14;
    uint32 RCC_SSCGR;
    uint32 RCC_PLLI2SCFGR;
    uint32 RESERVED15;
    uint32 RCC_DCKCFGR;

}RCC_t;
/**********************************  Variables *********************************************/
static RCC_t* const RCC =(uint32*) 0x40023800;
/********************************** Static Functions ***************************************/

/********************************** Implementation *****************************************/
RCC_Error_t RCC_Select_SYSCLOCK(SYSCLOCK_t SYSCLOCK)
{
    RCC_Error_t LOC_RET=RCC_Error_NOK;
    switch (SYSCLOCK)
    {
    case SYSCLOCK_HSI:
        RCC->RCC_CFGR &=SYSCLOCK_HSI;
        LOC_RET=RCC_Error_OK;
        break;
    case SYSCLOCK_HSE:
        RCC->RCC_CFGR |=SYSCLOCK_HSE;
        LOC_RET=RCC_Error_OK;
        break;
    case SYSCLOCK_PLL:
        RCC->RCC_CFGR |=SYSCLOCK_HSE;
        LOC_RET=RCC_Error_OK;
        break;
    default:
    LOC_RET=RCC_Error_NOK;
        break;
    }
    return LOC_RET;
}


RCC_Error_t RCC_Get_SYSCLOCK(uint8 *COPY_Status_variable)
{
*COPY_Status_variable=RCC->RCC_CFGR &SWS;
}


RCC_Error_t RCC_Enable_CLOCK(CLOCK_t CLOCK)
{
    RCC->RCC_CR |=CLOCK;
}

RCC_Error_t RCC_Disable_CLOCK(CLOCK_t CLOCK)
{
    RCC->RCC_CR &=~CLOCK;
}

RCC_Error_t RCC_Enable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral)
{
    RCC->RCC_AHB1ENR |= AHB1peripheral;
}

RCC_Error_t RCC_Disable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral)
{
    RCC->RCC_AHB1ENR &= ~AHB1peripheral;
}

RCC_Error_t RCC_Enable_AHB2Peripheral(AHB2peripheral_t AHB2peripheral)
{
    RCC->RCC_AHB2ENR |= AHB2peripheral;
}
RCC_Error_t RCC_Disable_AHB2Peripheral(AHB2peripheral_t AHB2peripheral)
{
    RCC->RCC_AHB2ENR &= ~AHB2peripheral;
}


RCC_Error_t RCC_Enable_APB1Peripheral(APB1peripheral_t APB1peripheral)
{
    RCC->RCC_APB1ENR |= APB1peripheral;
}
RCC_Error_t RCC_Disable_APB1Peripheral(APB1peripheral_t APB1peripheral)
{
    RCC->RCC_APB1ENR &= ~APB1peripheral;
}

RCC_Error_t RCC_Enable_APB2Peripheral(APB2peripheral_t APB2peripheral)
{
    RCC->RCC_APB2ENR |=APB2peripheral;
}

RCC_Error_t RCC_Disable_APB2Peripheral(APB2peripheral_t APB2peripheral)
{
     RCC->RCC_APB2ENR &=~APB2peripheral;
}


RCC_Error_t RCC_Configure_AHBprescaller(AHBprescaller_t AHBprescaller)
{
    RCC->RCC_CFGR |=AHBprescaller;
}

RCC_Error_t RCC_Configure_APB1prescaller(APB1prescaller_t APB1prescaller)
{
    RCC->RCC_CFGR |=APB1prescaller;
}

RCC_Error_t RCC_Configure_APB2prescaller(APB2prescaller_t APB2prescaller)
{
    RCC->RCC_CFGR |=APB2prescaller;
}


RCC_Error_t RCC_Configure_PLL(uint8 PLLQ,uint8 PLLP, uint8 PLLN,uint8 PLLM,uint8 PLLSRC)
{

}