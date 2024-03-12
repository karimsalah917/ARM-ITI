/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Service Abstraction Layer (SAL)                                          */
/* Module       : OS Scheduler                                                             */
/* Version      : v1.0                                                                     */
/* Date         : 11/03/2024                                                               */
/* File Details : Configuration file for Scheduler module                                  */
/* Target       : STM32f401cc may be comptaeble with any m3/m4 target                      */
/*******************************************************************************************/
#pragma once
/**********************************  Includes **********************************************/
/**********************************   Types ************************************************/
/**
 * @brief Enumeration for defining the order and priority of RunnableTasks.
 * 
 * This enumeration is used to specify the order and priority of RunnableTasks.
 * The order of enumeration members indicates the priority of tasks, with lower
 * values representing higher priority.
 */
typedef enum
{
    Runnable1=0,
    _Runnable_no
} RunnablePriority_t;
