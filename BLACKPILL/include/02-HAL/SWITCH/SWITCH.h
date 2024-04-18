//******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : SWITCH                                                                   */
/* Version      : v1.0                                                                     */
/* Date         : 22/02/2024                                                               */
/* File Details : Header file for SWITCH Driver                                            */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#ifndef SWITCH_H
#define SWITCH_H
/**********************************  Includes **********************************************/
#include "SWITCH_Config.h"
#include "../../00-LIB/STD.h"
/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/

/**
 * @brief Defines a data type for the return value of any function as an error status.
 */
typedef enum 
{
    SWITCH_NOK = 0, /**< Indicates an error status     */
    SWITCH_OK  = 1  /**< Indicates a successful status */
} SWITCH_Error_t;

/**
 * @brief Defines a data type for SWITCH status.
 */
typedef enum 
{
    SWITCH_NotPRESSED =  0, /**< SWITCH is not pressed */
    SWITCH_PRESSED  =    1  /**< SWITCH is pressed     */
} SWITCH_Status_t;

/**
 * @brief Defines a data type for ports available to connect SWITCHs.
 */
typedef enum 
{
    SWITCH_PORTA = 0x0, /**< Port A */
    SWITCH_PORTB = 0x1, /**< Port B */
    SWITCH_PORTC = 0x2  /**< Port C */
} SWITCH_PORT_t;

/**
 * @brief Defines a data type for pins available to connect SWITCHs.
 */
typedef enum 
{
    SWITCH_PIN0  = 0x00000000, /**< Pin 0  */
    SWITCH_PIN1  = 0x00000001, /**< Pin 1  */
    SWITCH_PIN2  = 0x00000002, /**< Pin 2  */
    SWITCH_PIN3  = 0x00000003, /**< Pin 3  */
    SWITCH_PIN4  = 0x00000004, /**< Pin 4  */
    SWITCH_PIN5  = 0x00000005, /**< Pin 5  */
    SWITCH_PIN6  = 0x00000006, /**< Pin 6  */
    SWITCH_PIN7  = 0x00000007, /**< Pin 7  */
    SWITCH_PIN8  = 0x00000008, /**< Pin 8  */
    SWITCH_PIN9  = 0x00000009, /**< Pin 9  */
    SWITCH_PIN10 = 0x0000000A, /**< Pin 10 */
    SWITCH_PIN11 = 0x0000000B, /**< Pin 11 */
    SWITCH_PIN12 = 0x0000000C, /**< Pin 12 */
    SWITCH_PIN13 = 0x0000000D, /**< Pin 13 */
    SWITCH_PIN14 = 0x0000000E, /**< Pin 14 */
    SWITCH_PIN15 = 0x0000000F  /**< Pin 15 */
} SWITCH_PIN_t;


/**
 * @brief Defines a data type for each switch connection type.
 */
typedef enum 
{
    SWITCH_Connection_InPU  = 0x00000008, /**< Internal Pull-Up   */
    SWITCH_Connection_InPD  = 0x00000010, /**< Internal Pull-Down */
    SWITCH_Connection_FL    = 0x00000000  /**< Floating Input     */
} SWITCH_Connection_t;


/**
 * @brief Defines a data type for each SWITCH configuration.
 */
typedef struct
{
    SWITCH_PORT_t        PORT;       /**< Port of the SWITCH            */
    SWITCH_PIN_t         PIN;        /**< Pin of the SWITCH             */
    SWITCH_Connection_t  Connection; /**< Connection type of the SWITCH */
} SWITCH_CONFG_t;




/*********************************** API's *************************************************/
 
/**
 * @brief Initializes all selected components of this module.
 * 
 * @return Error message indicating the success or failure of the operation.
 * 
 * @warning This function must be called before using the other APIs.
 */
SWITCH_Error_t SWITCH_INIT(void);



/**
 * @brief Retrieves the status of a specified switch.
 * 
 * This function retrieves the current status of the specified switch identified by COPY_SWITCH_NAME 
 * and stores it in the memory location pointed to by COPY_SWITCH_STATUS.
 * 
 * @param COPY_SWITCH_NAME The name or identifier of the switch.
 * @param COPY_SWITCH_STATUS Pointer to the memory location where the status of the switch will be stored.
 *                           Upon successful execution, this location will be updated with the current status of the switch.
 * 
 * @return SWITCH_Error_t An error code indicating the success or failure of retrieving the switch status. 
 *         Possible error codes include:
 *         - SWITCH_OK: The operation was successful.
 *         - SWITCH_INVALID_NAME: The provided switch name is invalid or not recognized.
 *         - SWITCH_ERROR: An unspecified error occurred during the operation.
 */
SWITCH_Error_t SWITCH_GetStatus(SWITCHS_t COPY_SWITCH_NAME, uint8* COPY_SWITCH_STATUS);




#endif
