/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : NVIC                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : 05/03/2024                                                               */
/* File Details : Source file of NVIC Driver                                               */
/* Target       : STM32f401cc and may be compatbale with any target with M3/M4 MProcessor  */
/*******************************************************************************************/
/********************************** Includes ***********************************************/
#include "../../../include/01-MCAL/NVIC/NVIC.h"
/********************************** Definitions ********************************************/
#define NVIC_Base_ADDRESS            0xE000E100 /* Base address of NVIC peripheral */
#define SCB_Base_ADDRESS             0xE000ED00 /* Base address of SCB peripheral */
#define InterruptsPerRegister        32
/**********************************  Types  ************************************************/
typedef struct
{

    /* Interrupt set-enable register  */
    uint32 NVIC_ISER[8];
    /* Reserved Bits */
    uint32 RESERVED1[24];
    /*Interrupt clear-enable register   */
    uint32 NVIC_ICER[8];
    /* Reserved Bits */
    uint32 RESERVED2[24];
    /* Interrupt set-pending register */
    uint32 NVIC_ISPR[8];
    /* Reserved Bits */
    uint32 RESERVED3[24];
    /* Interrupt clear-pending register  */
    uint32 NVIC_ICPR[8];
    /* Reserved Bits */
    uint32 RESERVED4[24];
    /* Interrupt active bit register  */
    uint32 NVIC_IABR[8];
    /* Reserved Bits */
    uint32 RESERVED5[56];
    /* Interrupt priority register  */
    uint32 NVIC_IPR[60];
    /* Reserved Bits */
    uint32 RESERVED6[580];
    /* Software trigger interrupt register */
    uint32 NVIC_STIR;
} NVIC_PERI_t;

typedef struct
{
    uint32 CPUID;
    uint32 ICSR;
    uint32 VTOR;
    uint32 AIRCR;
    uint32 SCR;
    uint32 CCR;
    uint32 SHPR1;
    uint32 SHPR2;
    uint32 SHPR3;
    uint32 SHCSR;
    uint32 CFSR;
    uint32 HFSR;
    uint32 MMAR;
    uint32 BFAR;
    uint32 AFSR;
} SCB_PERI_t;

/**********************************  Variables *********************************************/
volatile NVIC_PERI_t* const NVIC=(volatile NVIC_PERI_t*)NVIC_Base_ADDRESS;
volatile SCB_PERI_t* const SCB=(volatile SCB_PERI_t*)SCB_Base_ADDRESS;

/********************************** Static Functions ***************************************/

/********************************** Implementation *****************************************/

NVIC_Error_t NVIC_EnableIRQ(IRQn_t IRQn){
    NVIC_Error_t Loc_returnValue=NVIC_ERROR_OK;
    uint8 Local_index=IRQn/InterruptsPerRegister;
    
    if(IRQn>_INT_Num){
        Loc_returnValue=NVIC_ERROR_OUT_OF_RANGE;
    }
    else
    {
        NVIC->NVIC_ISER[Local_index]=(1<<(IRQn%InterruptsPerRegister));
    }
    return Loc_returnValue;

}

NVIC_Error_t NVIC_DisableIRQ(IRQn_t IRQn){
    NVIC_Error_t Loc_returnValue=NVIC_ERROR_OK;
    uint8 Local_index=IRQn/InterruptsPerRegister;
    
    if(IRQn>_INT_Num){
        Loc_returnValue=NVIC_ERROR_OUT_OF_RANGE;
    }
    else
    {
        NVIC->NVIC_ICER[Local_index]=(1<<(IRQn%InterruptsPerRegister));
    }
    return Loc_returnValue;
}
NVIC_Error_t NVIC_SetPendingIRQ(IRQn_t IRQn){
    NVIC_Error_t Loc_returnValue=NVIC_ERROR_OK;
    uint8 Local_index=IRQn/InterruptsPerRegister;
    
    if(IRQn>_INT_Num){
        Loc_returnValue=NVIC_ERROR_OUT_OF_RANGE;
    }
    else
    {
        NVIC->NVIC_ISPR[Local_index]=(1<<(IRQn%InterruptsPerRegister));
    }
    return Loc_returnValue;
}

NVIC_Error_t NVIC_ClearPendingIRQ(IRQn_t IRQn){
    NVIC_Error_t Loc_returnValue=NVIC_ERROR_OK;
    uint8 Local_index=IRQn/InterruptsPerRegister;
    
    if(IRQn>_INT_Num){
        Loc_returnValue=NVIC_ERROR_OUT_OF_RANGE;
    }
    else
    {
        NVIC->NVIC_ICPR[Local_index]=(1<<(IRQn%InterruptsPerRegister));
    }
    return Loc_returnValue;
}

NVIC_Error_t NVIC_GetPendingIRQ(IRQn_t IRQn, NVIC_Pending_status_t *Pending){

}
NVIC_Error_t NVIC_SetPriority(IRQn_t IRQn, uint32 priority){

}
NVIC_Error_t NVIC_GetPriority(IRQn_t IRQn, uint32 *priority){

}
NVIC_Error_t NVIC_SetPriorityGrouping(GRPn_t GRPn){
    
}
