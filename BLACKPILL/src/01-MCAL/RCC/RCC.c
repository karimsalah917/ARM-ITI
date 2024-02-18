/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : RCC                                                                      */
/* Version      : v1.1                                                                     */
/* Date         : 11/2/2024                                                                */
/* File Details : Source file for RCC Driver                                               */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
/********************************** Includes ***********************************************/
#include "../../../include/01-MCAL/RCC/RCC.h"
#include "../../../include/00-LIB/STD.h"
/********************************** Definitions ********************************************/
/*
* @brief CFGR Register Masks
*/
#define RCC_CFGR_SW_CLEAR              0xfffffffC
#define RCC_CFGR_HPRE_CLEAR            0xffffff0f
#define RCC_CFGR_PPRE1_CLEAR           0xffffe3ff
#define RCC_CFGR_PPRE2_CLEAR           0xffff1fff
#define RCC_CFGR_RTCPRE_CLEAR          0xffE0ffff
#define RCC_CFGR_MCO1PRE_CLEAR         0xf8ffffff
#define RCC_CFGR_MCO2PRE_CLEAR         0xc7ffffff

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
    uint32 Local_tempREG= RCC->RCC_CFGR;
    Local_tempREG &=RCC_CFGR_SW_CLEAR;
    Local_tempREG |=SYSCLOCK;
    RCC->RCC_CFGR =Local_tempREG;
    return RCC_Error_OK;
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
    uint32 Local_tempREG= RCC->RCC_CFGR ;
    Local_tempREG &= RCC_CFGR_HPRE_CLEAR;
    Local_tempREG |= AHBprescaller;
    RCC->RCC_CFGR =Local_tempREG;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Configure_APB1prescaller(APB1prescaller_t APB1prescaller)
{
    uint32 Local_tempREG= RCC->RCC_CFGR ;
    Local_tempREG &= RCC_CFGR_PPRE1_CLEAR;
    Local_tempREG |= APB1prescaller;
    RCC->RCC_CFGR =Local_tempREG;
    return RCC_Error_OK;
}

RCC_Error_t RCC_Configure_APB2prescaller(APB2prescaller_t APB2prescaller)
{
    uint32 Local_tempREG= RCC->RCC_CFGR ;
    Local_tempREG &= RCC_CFGR_PPRE2_CLEAR;
    Local_tempREG |= APB2prescaller;
    RCC->RCC_CFGR =Local_tempREG;
    return RCC_Error_OK;
}


RCC_Error_t RCC_Configure_PLL()
{
    RCC->RCC_PLLCFGR |=0x07415419;
    return RCC_Error_OK;

}
