/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Service Abstraction Layer (SAL)                                          */
/* Module       : OS Scheduler                                                             */
/* Version      : v1.0                                                                     */
/* Date         : 11/03/2024                                                               */
/* File Details : Header file for Scheduler module                                         */
/* Target       : STM32f401cc may be comptaeble with any m3/m4 target                      */
/*******************************************************************************************/
/**********************************  Includes **********************************************/
#include "../../include/4-Service/SCHED.h"
#include "../../include/01-MCAL/SYSTICK/SYSTICK.h"
#include "../../include/4-Service/SCHED_Config.h"
/********************************** Definitions ********************************************/
#define TICK_TIME_MS 1
/**********************************  Types  ************************************************/
typedef struct 
{
    RunnableTask_t *Runnable;
    uint32 RemainningTimeMS;
}RunnableInfo_t;

/********************************** Variabels **********************************************/
static RunnableInfo_t RunnableArr[ _Runnable_no];
static uint32 PendingTicks=0;
/********************************** Static Functions ***************************************/
void TickCallBack(void)
{
	PendingTicks++;
}
static void SCHED(void)
{
    /**
     * functionlaties of the SCHED function
     * [1] Looping over the Array of Runnables and check the remaining time of each one 
     * so execute it rigth now or not now
    */
   uint32 idx=0;
   for(idx=0;idx<_Runnable_no;idx++)
   {
        if((RunnableArr[idx].Runnable)&&(RunnableArr[idx].Runnable->CallBack)&&(RunnableArr[idx].RemainningTimeMS==0))
        {
            RunnableArr[idx].Runnable->CallBack();
            RunnableArr[idx].RemainningTimeMS=RunnableArr[idx].Runnable->PeriodicityMS;
        }
        RunnableArr[idx].RemainningTimeMS -=TICK_TIME_MS;
   }
}
/********************************** Implementation *****************************************/


SCHED_Status_t SCHED_Init() //done
{
    /**
     * Functionalities of init function
     * [1] Configuring SysTick Tick time
     * [2] Configuring SysTick CallBack 
    */
   SCHED_Status_t Local_returnvariable=SCHED_OPERATION_SUCCESS;
   SysTick_SetTickMS(TICK_TIME_MS);
   SysTick_SetCallBack(TickCallBack);
   return Local_returnvariable;
}


SCHED_Status_t SCHED_RegisterTask(RunnableTask_t *RunnableTask)//done
{
    /**
     * Functionalities of RegisterTask function
     * [1] Register any Task to the Runnables info array
     *  1-Register the runnable itself
     *  2-Register the remaainning time
    */
   /*This means there is runnable and this runnable has prioirty which is not used before*/
   SCHED_Status_t Local_returnVariable=SCHED_OPERATION_SUCCESS;
   if(RunnableTask&&RunnableArr[RunnableTask->Priority].Runnable==NULL_PTR)
   {
        RunnableArr[RunnableTask->Priority].Runnable=RunnableTask;
        RunnableArr[RunnableTask->Priority].RemainningTimeMS=RunnableTask->InitialDelayMS;     
   }else
   {
    Local_returnVariable=SCHED_OPERATION_FAILED;
   }
   return Local_returnVariable;
}

SCHED_Status_t SCHED_Start(void)
{
    /**
     * Functionalites of start function
     * [1] Enable the SysTick Counter
     * [2] having the superloop inside it 
     *  1-Check for pending ticks
     *  2-if there call the SCHEDULAR to handle it
     */   
    SysTick_EnableCounterPeriodic();
    while(1)
    {
        if (PendingTicks)
        {
            PendingTicks--;
            SCHED();
        }
        
    }
}
