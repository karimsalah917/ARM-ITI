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
#pragma once
/**********************************  Includes **********************************************/
#include "../00-LIB/STD.h"
#include "SCHED_Config.h"
/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/
/**
 * @brief Enumeration for scheduler operation status.
 */
typedef enum 
{
    SCHED_OPERATION_FAILED = 0, /**< Scheduler operation status indicating failure. */
    SCHED_OPERATION_SUCCESS = 1 /**< Scheduler operation status indicating success. */
} SCHED_Status_t;

/**
 * @brief Function pointer type for runnable tasks.
 */
typedef void (*RunnableCB_t) (void);

/**
 * @brief Structure representing a runnable task.
 */
typedef struct 
{
    char*        TaskName;      /**< Name of the runnable task. */
    uint32       PeriodicityMS; /**< Periodicity of the task in milliseconds. */
    uint32       Priority;      /**< Priority of the task. */
    uint32       InitialDelayMS;/**< Initial delay of the task in milliseconds. */
    RunnableCB_t Runnable;      /**< Callback function pointer for the task. */ 
} RunnableTask_t;

/*********************************** API's *************************************************/
/**
 * @brief Initializes the scheduler.
 * 
 * @return Status of the scheduler initialization.
 *         - SCHEDULER_OPERATION_SUCCESS: Initialization successful.
 *         - SCHEDULER_OPERATION_FAILED: Initialization failed.
 */
SCHED_Status_t SCHED_Init(void);

/**
 * @brief Registers a runnable task with the scheduler.
 * 
 * @param RunnableTask Pointer to the runnable task structure to be registered.
 * 
 * @return Status of the registration operation.
 *         - SCHEDULER_OPERATION_SUCCESS: Registration successful.
 *         - SCHEDULER_OPERATION_FAILED: Registration failed.
 */
SCHED_Status_t SCHED_RegisterTask(RunnableTask_t *RunnableTask);

/**
 * @brief Starts the scheduler.
 * 
 * @return Status of the scheduler start operation.
 *         - SCHEDULER_OPERATION_SUCCESS: Scheduler started successfully.
 *         - SCHEDULER_OPERATION_FAILED: Failed to start the scheduler.
 */
SCHED_Status_t SCHED_Start(void);
