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
#include "../../00-LIB/STD.h"
/********************************** Definitions ********************************************/

/**********************************  Types  ************************************************/

typedef struct 
{
    volatile uint32 RCC_CR;
    volatile uint32 RCC_PLLCFGR;
    volatile uint32 RCC_CFGR;
    volatile uint32 RCC_CIR;
    volatile uint32 RCC_AHB1RSTR;
    volatile uint32 RCC_AHB2RSTR;
    volatile uint32 RESERVED1;
    volatile uint32 RESERVED2;
    volatile uint32 RCC_APB1RSTR;
    volatile uint32 RCC_APB2RSTR;
    volatile uint32 RESERVED3;
    volatile uint32 RESERVED4;
    volatile uint32 RCC_AHB1ENR;
    volatile uint32 RCC_AHB2ENR;
    volatile uint32 RESERVED5;
    volatile uint32 RESERVED6;
    volatile uint32 RCC_APB1ENR;
    volatile uint32 RCC_APB2ENR;
    volatile uint32 RESERVED7;
    volatile uint32 RESERVED8;
    volatile uint32 RCC_AHB1LPENR;
    volatile uint32 RCC_AHB2LPENR;
    volatile uint32 RESERVED9;
    volatile uint32 RESERVED10;
    volatile uint32 RCC_APB1LPENR;
    volatile uint32 RCC_APB2LPENR;
    volatile uint32 RESERVED11;
    volatile uint32 RESERVED12;
    volatile uint32 RCC_BDCR;
    volatile uint32 RCC_CSR;
    volatile uint32 RESERVED13;
    volatile uint32 RESERVED14;
    volatile uint32 RCC_SSCGR;
    volatile uint32 RCC_PLLI2SCFGR;
    volatile uint32 RESERVED15;
    volatile uint32 RCC_DCKCFGR;

}RCC_t;
/**********************************  Variables *********************************************/
static RCC_t* const RCC =(RCC_t*) 0x40023800;
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
return RCC_Error_OK;
}


RCC_Error_t RCC_Enable_CLOCK(CLOCK_t CLOCK)
{
    RCC->RCC_CR |=CLOCK;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Disable_CLOCK(CLOCK_t CLOCK)
{
    RCC->RCC_CR &=~CLOCK;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Enable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral)
{
    RCC->RCC_AHB1ENR |= AHB1peripheral;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Disable_AHB1Peripheral(AHB1peripheral_t AHB1peripheral)
{
    RCC->RCC_AHB1ENR &= ~AHB1peripheral;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Enable_AHB2Peripheral(AHB2peripheral_t AHB2peripheral)
{
    RCC->RCC_AHB2ENR |= AHB2peripheral;
    return RCC_Error_OK;
}
RCC_Error_t RCC_Disable_AHB2Peripheral(AHB2peripheral_t AHB2peripheral)
{
    RCC->RCC_AHB2ENR &= ~AHB2peripheral;
    return RCC_Error_OK;
}


RCC_Error_t RCC_Enable_APB1Peripheral(APB1peripheral_t APB1peripheral)
{
    RCC->RCC_APB1ENR |= APB1peripheral;
    return RCC_Error_OK;
}
RCC_Error_t RCC_Disable_APB1Peripheral(APB1peripheral_t APB1peripheral)
{
    RCC->RCC_APB1ENR &= ~APB1peripheral;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Enable_APB2Peripheral(APB2peripheral_t APB2peripheral)
{
    RCC->RCC_APB2ENR |=APB2peripheral;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Disable_APB2Peripheral(APB2peripheral_t APB2peripheral)
{
     RCC->RCC_APB2ENR &=~APB2peripheral;
     return RCC_Error_OK;
}


RCC_Error_t RCC_Configure_AHBprescaller(AHBprescaller_t AHBprescaller)
{
    RCC->RCC_CFGR |=AHBprescaller;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Configure_APB1prescaller(APB1prescaller_t APB1prescaller)
{
    RCC->RCC_CFGR |=APB1prescaller;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Configure_APB2prescaller(APB2prescaller_t APB2prescaller)
{
    RCC->RCC_CFGR |=APB2prescaller;
    return RCC_Error_OK;
}


RCC_Error_t RCC_Configure_PLL(uint32 PLLQ,uint32 PLLP, uint32 PLLN,uint32 PLLM,PLLSRC_t PLLSRC)
{
    uint32 Temp_Mask=0x00000000;
    Temp_Mask = (PLLQ << 24) | (PLLP << 16) | (PLLN << 6) | (PLLM << 0)|(PLLSRC);
    RCC->RCC_PLLCFGR |=Temp_Mask;
    return RCC_Error_OK;

}