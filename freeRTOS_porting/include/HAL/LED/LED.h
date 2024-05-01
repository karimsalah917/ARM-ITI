#ifndef LED_H_
#define LED_H_

    #include "MCAL/GPIO/GPIO.h"
    #include "HAL/LED/LED_Config.h"
	#include "Std_Types.h"

    /*Macros to be used by user*/
    #define LED_Connection_FW      0
    #define LED_Connection_RV      1

    #define LED_SET_OFF            0  
    #define LED_SET_ON             1
    /*-------------------------*/

    /* -------------Struct for the LED Configuration-------------- */
        typedef struct
        {  
            void *Port;
            U32  Pin;
            U8   Connection;                                         
            U8   Init_Value;
        }LED_strLEDConfig_t;
    /*-------------------------------------------------------------*/
    
    // typedef enum{

    //     LED_enumOK,
    //     LED_enumNOK,
    //     LED_NullPointer,
    //     LED_enumWrong_PortNo,
    //     LED_enumWrong_PinNo,
    //     LED_enumWrong_ActiveState,
    //     LED_enumWrong_OutputState

    // }LED_enumLEDerrorState_t;

    /**
    * @brief Initializes all the leds configured in configure files
    * 
    * @return GPIO_Error_t as the led is a HAL that uses MCAL GPIO functions the error would be GPIO_Error_t with a terminology that can be understod from your LED_Driver
    * 
    * @note LEDs Must be configured in LED_config.h and LED_config.c files before using this function
    */
    GPIO_Error_t LED_Init (void);

    /**
    * @brief Sets the State of the Specified LED (ON or OFF)
    * 
    * @param Copy_Led Name of the LED as defined in LED_config.h
    * @param Copy_State The State to set the LED to                 Options are ( LED_SET_OFF , LED_SET_ON )
    * @return GPIO_Error_t as the led is a HAL that uses MCAL GPIO functions the error would be GPIO_Error_t with a terminology that can be understod from your LED_Driver       
    * 
    * @note LEDs must be initialized first by calling LED_Init() function
    */

    GPIO_Error_t LED_SetStatus ( LEDs_t LED_NAME , U32 LED_STATUS );

#endif