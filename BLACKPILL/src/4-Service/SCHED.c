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
/********************************** Definitions ********************************************/

/**********************************  Types  ************************************************/
typedef struct 
{
    RunnableTask_t *Runnable;
    uint32 RemainningTimeMS;
}RunnableInfo_t;

/********************************** Variabels **********************************************/
static RunnableInfo_t RunnableArr[ _Runnable_no];
/********************************** Static Functions ***************************************/
static void SCHED(void)
{
    
}
/********************************** Implementation *****************************************/


SCHED_Status_t SCHED_Init(void){}


SCHED_Status_t SCHED_RegisterTask(RunnableTask_t *RunnableTask){}

SCHED_Status_t SCHED_Start(void){}