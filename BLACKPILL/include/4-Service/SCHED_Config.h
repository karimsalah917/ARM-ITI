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
 * 
 * Example usage:
 * 
 * typedef enum {
 *     TASK_HIGH_PRIORITY,
 *     TASK_MEDIUM_PRIORITY,
 *     TASK_LOW_PRIORITY
 * } RunnablePriority_t;
 * 
 * In this example, TASK_HIGH_PRIORITY has the highest priority, followed by
 * TASK_MEDIUM_PRIORITY, and TASK_LOW_PRIORITY.
 */
typedef enum
{
    RUNNABLE_PRIORITY_0=0, /**< Highest priority for RunnableTasks. */
    RUNNABLE_PRIORITY_1, /**< Priority level 1 for RunnableTasks. */
    RUNNABLE_PRIORITY_2, /**< Priority level 2 for RunnableTasks. */
    _Runnable_no
} RunnablePriority_t;
