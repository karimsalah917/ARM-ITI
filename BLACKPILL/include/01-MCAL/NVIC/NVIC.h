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
#include "../../00-LIB/STD.h"
#include "stm32f401cc.h"
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

typedef enum {
NVIC_Pending_status_Cleared=0,
NVIC_Pending_status_Set
}NVIC_Pending_status_t;

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
NVIC_Error_t NVIC_GetPendingIRQ(IRQn_t IRQn, NVIC_Pending_status_t *Pending);

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

