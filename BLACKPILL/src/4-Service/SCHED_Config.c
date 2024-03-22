/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Service Abstraction Layer (SAL)                                          */
/* Module       : OS Scheduler                                                             */
/* Version      : v1.1                                                                     */
/* Date         : 11/03/2024                                                               */
/* File Details : Configuration file for Scheduler module                                  */
/* Target       : STM32f401cc may be comptaeble with any m3/m4 target                      */
/*******************************************************************************************/
/**********************************  Includes **********************************************/
#include "../../include/4-Service/SCHED.h"
#include "../../include/4-Service/SCHED_Config.h"
/********************************** Definitions ********************************************/
/**********************************   Types ************************************************/
const RunnableTask_t RUN_LIST[_Runnable_no]=
{
    [Run1]=
    {
        .TaskName="LED State Machine",
        .PeriodicityMS=100,
        .InitialDelayMS=0,
        .CallBack=TrafficLight_Runnable
    }
};