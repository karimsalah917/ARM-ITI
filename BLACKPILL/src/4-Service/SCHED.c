/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Service Abstraction Layer (SAL)                                          */
/* Module       : OS Scheduler                                                             */
/* Version      : v1.1                                                                     */
/* Date         : 11/03/2024                                                               */
/* File Details : Header file for Scheduler module                                         */
/* Target       : STM32f401cc may be comptaeble with any m3/m4 target                      */
/*******************************************************************************************/
/**********************************  Includes **********************************************/
#include "../../include/4-Service/SCHED.h"
#include "../../include/01-MCAL/SYSTICK/SYSTICK.h"
#include "../../include/4-Service/SCHED_Config.h"
/********************************** Definitions ********************************************/

/**********************************  Types  ************************************************/

/********************************** Variabels **********************************************/

/**
 * variable of pending ticks
*/
static volatile uint32 PendingTicks =0;

/**
 * OS time Stamp
*/
static uint64 TimeStamp =0;

/**
 * List of Tasks
*/
extern const RunnableTask_t RUN_LIST[_Runnable_no];

/********************************** Static Functions ***************************************/
static void TickCallBack(void)
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
    //checing if the instant of the run has come
    if((TimeStamp-RUN_LIST[idx].InitialDelayMS)%RUN_LIST[idx].PeriodicityMS==0)
    {
        //executing the callback if the instant has come
        RUN_LIST[idx].CallBack();
    }
   }
   TimeStamp++;
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
