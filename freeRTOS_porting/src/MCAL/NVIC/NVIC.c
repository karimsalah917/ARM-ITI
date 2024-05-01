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
#include "./MCAL/NVIC/NVIC.h"
/********************************** Definitions ********************************************/
#define NVIC_Base_ADDRESS            0xE000E100 /* Base address of NVIC peripheral */
#define SCB_Base_ADDRESS             0xE000ED00 /* Base address of SCB peripheral */
#define InterruptsPerRegister        32

#define SCB_ClearGroupingBits        0x00008FFF

#define NVIC_IPR_Mask                0x00000011

#define NVIC_STIRR               *((volatile uint32 *)0xE000EF00)


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
    
    if(IRQn>=_INT_Num){
        Loc_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
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
    
    if(IRQn>=_INT_Num){
        Loc_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
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
    
    if(IRQn>=_INT_Num){
        Loc_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
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
    
    if(IRQn>=_INT_Num){
        Loc_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        NVIC->NVIC_ICPR[Local_index]=(1<<(IRQn%InterruptsPerRegister));
    }
    return Loc_returnValue;
}

NVIC_Error_t NVIC_GetPendingIRQ(IRQn_t IRQn, NVIC_PendingStatus_t *Pending){
    NVIC_Error_t Local_returnValue=NVIC_ERROR_OK;
    uint8 Local_index=(IRQn>>5);
    if(IRQn>=_INT_Num)
    {
        Local_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
    }else{
        *Pending=(NVIC->NVIC_ISPR[Local_index])&(0x00000001<<(IRQn%InterruptsPerRegister));
    }
    return Local_returnValue;
}
NVIC_Error_t NVIC_GetActive (IRQn_t IRQn,uint32* Activity){
    NVIC_Error_t Local_returnValue=NVIC_ERROR_OK;
    uint8 Local_index=(IRQn>>5);
    if(IRQn>=_INT_Num)
    {
        Local_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
    }else{
        *Activity=(NVIC->NVIC_IABR[Local_index])&(0x00000001<<(IRQn%InterruptsPerRegister));
    }
    return Local_returnValue;
}

NVIC_Error_t NVIC_SetPriority(IRQn_t IRQn, uint32 priority){
    NVIC_Error_t Local_returnValue=NVIC_ERROR_OK;
    uint8 Local_Index=IRQn>>2;//divide by 4
    if(IRQn>=_INT_Num){
        Local_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
    }else{
        uint32 Local_IPR=NVIC->NVIC_IPR[Local_Index]; // reading the register in local variable
        Local_IPR &= ~(NVIC_IPR_Mask<<((IRQn%4)*8));       // Clearing the coresponding bits before adding the new changes
        Local_IPR |=(priority<<((IRQn%4)*8));             // Adding the new changes to the local variable
        NVIC->NVIC_IPR[Local_Index]=Local_IPR;        // Adding the new changes to the physical register
    }
    return Local_returnValue;
}

NVIC_Error_t NVIC_SetPriorityGrouping(NVIC_PriorityGroup_t PriorityGroup){

    //validation to check that the group is right
    NVIC_Error_t Local_returnValue= NVIC_ERROR_OK;
    if((PriorityGroup>=_Priotiy_Group)||(PriorityGroup<NVIC_PriorityGroup_0)){
        Local_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
    }
    else{
        uint32 Local_scbAIRCE =           SCB->AIRCR;  //Read the register value and store it in a local variable
        Local_scbAIRCE       &=SCB_ClearGroupingBits;  //Clearing the needed bits before setting
        Local_scbAIRCE       |=PriorityGroup        ;  //Apply Chosen Group Changes to the local Register
        SCB->AIRCR            =Local_scbAIRCE       ;  //Apply the changes to the physical register
    }
    return Local_returnValue;
}
NVIC_Error_t NVIC_GetPriorityGrouping(uint32* PriorityGroup){
    *PriorityGroup=(SCB->AIRCR);
    return NVIC_ERROR_OK;
}

NVIC_Error_t NVIC_GetPriority(IRQn_t IRQn, uint32 *priority){
    NVIC_Error_t Local_returnValue=NVIC_ERROR_OK;
    uint8 Local_Index=IRQn>>2;//devide by 4
    if(IRQn>=_INT_Num){
        Local_returnValue=NVIC_ERROR_INVALID_ARGUMENT;
    }else{
        *priority=((NVIC->NVIC_IPR[Local_Index])>>((IRQn%4)*8))&(NVIC_IPR_Mask); // reading the register in local variable
    }
    return Local_returnValue;
}
NVIC_Error_t NVIC_SystemReset (void){
return NVIC_ERROR_OK;
}



NVIC_Error_t NVIC_TriggerSoftwareInterrupt(IRQn_t IRQn) {
    NVIC_Error_t Local_ReturnValue = NVIC_ERROR_OK;

    // Check if IRQn is within the valid range
    if (IRQn >= _INT_Num) {
        Local_ReturnValue = NVIC_ERROR_INVALID_ARGUMENT;
    } else {
        // Ensure bits 31:9 are cleared and set bits 8:0 to the interrupt ID
        uint32 stir_value = (IRQn & 0x1FF); // Mask to only keep bits 8:0
        NVIC_STIRR = stir_value;
    }

    return Local_ReturnValue;
}

