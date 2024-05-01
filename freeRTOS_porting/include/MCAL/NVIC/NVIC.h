/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : NVIC                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : 05/03/2024                                                               */
/* File Details : Header file of NVIC Driver                                               */
/* Target       : STM32f401cc and may be compatbale with any target with M3/M4 MProcessor  */
/*******************************************************************************************/
/********************************** Includes ***********************************************/
#include "./Std_Types.h"
#include "./stm32f401cc.h"
#include "./MCAL/NVIC/stm32f401cc.h"
/********************************** Definitions ********************************************/


/**********************************   Types ************************************************/

/**
 * @brief Enumeration defining types of errors related to NVIC (Nested Vectored Interrupt Controller) peripherals.
 */
typedef enum {
    NVIC_ERROR_NONE = 0,                   /**< No error */
    NVIC_ERROR_OK,                         /**< Success or everything is okay */
    NVIC_ERROR_INVALID_ARGUMENT,           /**< Invalid argument error */
    NVIC_ERROR_OUT_OF_RANGE,               /**< Value out of range error */
    NVIC_ERROR_INTERNAL,                   /**< Internal error */
    NVIC_ERROR_INTERRUPT_NOT_FOUND,        /**< Specified interrupt not found */
    NVIC_ERROR_INTERRUPT_NOT_ENABLED,      /**< Specified interrupt not enabled */
    NVIC_ERROR_INTERRUPT_ALREADY_ENABLED,  /**< Specified interrupt already enabled */
    NVIC_ERROR_INTERRUPT_ALREADY_DISABLED  /**< Specified interrupt already disabled */
} NVIC_Error_t;

/**
 * @brief Enumeration for NVIC Pending Interrupt Status
 *
 * This enumeration defines the possible pending status of interrupts in the 
 * Nested Vectored Interrupt Controller (NVIC) of ARM Cortex-M processors.
 * 
 * Values:
 * - NVIC_PendingStatus_Cleared: Indicates that the interrupt is not pending.
 * - NVIC_PendingStatus_Set: Indicates that the interrupt is pending.
 *
 * Example usage:
 * NVIC_Pending_status_t status = NVIC_PendingStatus_Cleared; // Set status to cleared
 */
typedef enum {
    NVIC_PendingStatus_Cleared = 0,
    NVIC_PendingStatus_Set
} NVIC_PendingStatus_t;


/**
 * @brief Enumeration for NVIC Priority Grouping Options
 *
 * @details This enumeration defines different options for setting the priority grouping of interrupts
 * in the Nested Vectored Interrupt Controller (NVIC) of ARM Cortex-M processors. Each option
 * corresponds to a specific priority grouping value to be written to the AIRCR register of
 * the System Control Block (SCB).
 * 
 * The priority grouping determines how the priority of interrupts is organized and affects
 * how they are handled in the system.
 * 
 * Values:
 * - NVIC_PriorityGroup_0: Priority grouping 0, consisting of 7 bits for the group priority
 *                        and 1 bit for the subgroup priority.
 * - NVIC_PriorityGroup_1: Priority grouping 1, consisting of 6 bits for the group priority
 *                        and 2 bits for the subgroup priority.
 * - NVIC_PriorityGroup_2: Priority grouping 2, consisting of 5 bits for the group priority
 *                        and 3 bits for the subgroup priority.
 * - NVIC_PriorityGroup_3: Priority grouping 3, consisting of 4 bits for the group priority
 *                        and 4 bits for the subgroup priority.
 * - NVIC_PriorityGroup_4: Priority grouping 4, consisting of 3 bits for the group priority
 *                        and 5 bits for the subgroup priority.
 * - NVIC_PriorityGroup_5: Priority grouping 5, consisting of 2 bits for the group priority
 *                        and 6 bits for the subgroup priority.
 * - NVIC_PriorityGroup_6: Priority grouping 6, consisting of 1 bit for the group priority
 *                        and 7 bits for the subgroup priority.
 * - NVIC_PriorityGroup_7: Priority grouping 7, consisting of 0 bits for the group priority
 *                        and 8 bits for the subgroup priority.
 *
 * @warning: The actual implementation of priority grouping may vary depending on the target device. 
 * Some ARM Cortex-M based microcontrollers, such as the STM32 series, might not support all 
 * priority grouping options. It is essential to consult the specific device datasheet and 
 * reference manual to determine the supported priority grouping options.
 *
 * Example usage (for STM32):
 * NVIC_SetPriorityGrouping(NVIC_PriorityGroup_3); // Set priority grouping to Group 3
 */
typedef enum {
    NVIC_PriorityGroup_0 = 0x05FA0000, // 7 bits for group and 1 bit for subgroup   (no supported at stm32     )
    NVIC_PriorityGroup_1 = 0x05FA0100, // 6 bits for group and 2 bits for subgroup  (no supported at stm32     )
    NVIC_PriorityGroup_2 = 0x05FA0200, // 5 bits for group and 3 bits for subgroup  (no supported at stm32     )
    NVIC_PriorityGroup_3 = 0x05FA0300, // 4 bits for group and 4 bits for subgroup  (supported at stm32 4G-0SG )
    NVIC_PriorityGroup_4 = 0x05FA0400, // 3 bits for group and 5 bits for subgroup  (supported at stm32 3G-1SG )
    NVIC_PriorityGroup_5 = 0x05FA0500, // 2 bits for group and 6 bits for subgroup  (supported at stm32 2G-2SG )
    NVIC_PriorityGroup_6 = 0x05FA0600, // 1 bit for group and 7 bits for subgroup   (supported at stm32 1G-3SG )
    NVIC_PriorityGroup_7 = 0x05FA0700,  // 0 bits for group and 8 bits for subgroup (supported at stm32 0G-4SG )
    _Priotiy_Group
} NVIC_PriorityGroup_t;


/**********************************   API's ************************************************/

/**
 * @brief Enables the specified interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param IRQn The interrupt number to be enabled.
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_EnableIRQ(IRQn_t IRQn);

/**
 * @brief Disables the specified interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param IRQn The interrupt number to be disabled.
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_DisableIRQ(IRQn_t IRQn);

/**
 * @brief Sets the pending status of the specified interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param IRQn The interrupt number for which the pending status is to be set.
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_SetPendingIRQ(IRQn_t IRQn);

/**
 * @brief Clears the pending status of the specified interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param IRQn The interrupt number for which the pending status is to be cleared.
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_ClearPendingIRQ(IRQn_t IRQn);

/**
 * @brief Gets the pending status of the specified interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param IRQn The interrupt number for which the pending status is to be retrieved.
 * @param Pending Pointer to a variable where the pending status will be stored.
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_GetPendingIRQ(IRQn_t IRQn, NVIC_PendingStatus_t *Pending);

/**
 * @brief Sets the priority of the specified interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param IRQn The interrupt number for which the priority is to be set.
 * @param priority The priority value to be set for the interrupt.
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_SetPriority(IRQn_t IRQn, uint32 priority);

/**
 * @brief Gets the priority of the specified interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param IRQn The interrupt number for which the priority is to be retrieved.
 * @param priority Pointer to a variable where the priority value will be stored.
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_GetPriority(IRQn_t IRQn, uint32 *priority);

/**
 * @brief Sets the priority grouping field in the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function sets the priority grouping field in the NVIC, which determines how the priority of interrupts is divided into preemption priority and subpriority. 
 * The priority grouping affects the assignment of interrupt priorities and determines the number of bits used for preemption priority and subpriority.
 *
 * @param GRPn The priority grouping value to be set, specified by a value of the enumeration type GRPn_t.
 *
 * @return NVIC_Error_t Error status indicating the success or failure of the operation.
 */
NVIC_Error_t NVIC_SetPriorityGrouping(NVIC_PriorityGroup_t PriorityGroup);

/**
  * @brief  Perform a system reset.
  * @note   This function initiates a system reset.
  * @retval NVIC_Error_t value:
  *           - NVIC_OK: System reset initiated successfully.
  *           - NVIC_ERROR: Error occurred during system reset initiation.
  */
NVIC_Error_t NVIC_SystemReset(void);

/**
  * @brief  Get the priority grouping of the NVIC.
  * @note   This function retrieves the priority grouping configured for the NVIC.
  * @param  PriorityGroup: Pointer to a variable where the priority grouping will be stored.
  * @retval NVIC_Error_t value:
  *           - NVIC_OK: Priority grouping retrieved successfully.
  *           - NVIC_ERROR: Error occurred during priority grouping retrieval.
  */
NVIC_Error_t NVIC_GetPriorityGrouping(uint32* PriorityGroup);

/**
  * @brief  Get the active status of an interrupt.
  * @note   This function checks if an interrupt is active.
  * @param  IRQn: Interrupt number (IRQn_t) to check.
  * @param  Activity: Pointer to a variable where the activity status will be stored.
  * @retval NVIC_Error_t value:
  *           - NVIC_OK: Activity status retrieved successfully.
  *           - NVIC_ERROR: Error occurred during activity status retrieval.
  */
NVIC_Error_t NVIC_GetActive(IRQn_t IRQn, uint32* Activity);

/**
 * @brief Triggers a software interrupt for the specified IRQn.
 *
 * This function triggers a software interrupt for the specified IRQn.
 * The IRQn parameter represents the interrupt number to trigger.
 * Software interrupts can be used for inter-process communication or
 * for signaling within the software.
 *
 * @param IRQn The interrupt number to trigger.
 * @return NVIC_ERROR_OK if the operation is successful,
 *         otherwise an appropriate error code indicating the failure.
 */
NVIC_Error_t NVIC_TriggerSoftwareInterrupt(IRQn_t IRQn);
