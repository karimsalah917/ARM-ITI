/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Header file for LCD  Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/**********************************  Includes **********************************************/

/********************************** Definitions ********************************************/

/**********************************   Types ************************************************/

/**
* @brief Created Data Type for the Return value of any function as 
* an error status 
*/
typedef enum 
{
    HAL_NOK=0,
    HAL_OK=1
}HAL_Error_t;
/*********************************** API's *************************************************/
 
 /**
  * @brief Initialise all selected components of this module
  *  
  * @param void 
  * 
  * @return Error message indicating the success or failure of the operation.
  * 
  * @warning this function must be called before using the other API's
 */
HAL_Error_t HAL_INIT(void);

/**
 * @brief
 * 
 * @param
 * @param
 * 
 * @return
*/
