#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

    #include "Std_Types.h"
    #include "Bit_Mask.h"

    /*Macros for the GPIO pins*/
    #define GPIO_PIN_0          0x00000000
    #define GPIO_PIN_1          0x00000001
    #define GPIO_PIN_2          0x00000002
    #define GPIO_PIN_3          0x00000003
    #define GPIO_PIN_4          0x00000004
    #define GPIO_PIN_5          0x00000005
    #define GPIO_PIN_6          0x00000006
    #define GPIO_PIN_7          0x00000007
    #define GPIO_PIN_8          0x00000008
    #define GPIO_PIN_9          0x00000009
    #define GPIO_PIN_10         0x0000000A
    #define GPIO_PIN_11         0x0000000B
    #define GPIO_PIN_12         0x0000000C
    #define GPIO_PIN_13         0x0000000D
    #define GPIO_PIN_14         0x0000000E
    #define GPIO_PIN_15         0x0000000F

    /*Macros for the GPIO ports*/
    #define GPIO_PORT_A_         0x00000000
    #define GPIO_PORT_B_         0x00000001
    #define GPIO_PORT_C_         0x00000002

    /*Macros for the GPIO pin modes*/
    #define GPIO_MODE_IN_FL     0x10000000
    #define GPIO_MODE_IN_PU     0x10000008
    #define GPIO_MODE_IN_PD     0x10000010          

    #define GPIO_MODE_OP_PP     0x10000001
    #define GPIO_MODE_OP_PP_PU  0x10000009
    #define GPIO_MODE_OP_PP_PD  0x10000011
    #define GPIO_MODE_OP_OD     0x10000005
    #define GPIO_MODE_OP_OD_PU  0x1000000D
    #define GPIO_MODE_OP_OD_PD  0x10000015

    #define GPIO_MODE_AF_PP     0x10000002
    #define GPIO_MODE_AF_PP_PU  0x1000000A
    #define GPIO_MODE_AF_PP_PD  0x10000012
    #define GPIO_MODE_AF_OD     0x10000006
    #define GPIO_MODE_AF_OD_PU  0x1000000E
    #define GPIO_MODE_AF_OD_PD  0x10000016

    #define GPIO_MODE_AN        0x10000003

    /*Macros for the GPIO pin speeds*/
    #define GPIO_SPEED_LOW      0x20000000
    #define GPIO_SPEED_MED      0x20000001
    #define GPIO_SPEED_HIGH     0x20000002
    #define GPIO_SPEED_VHIGH    0x20000003

    /*Macros for the GPIO pin alternate functions*/
    #define GPIO_FUNC_AF0       0x00000000
    #define GPIO_FUNC_AF1       0x00000001
    #define GPIO_FUNC_AF2       0x00000002
    #define GPIO_FUNC_AF3       0x00000003
    #define GPIO_FUNC_AF4       0x00000004
    #define GPIO_FUNC_AF5       0x00000005
    #define GPIO_FUNC_AF6       0x00000006
    #define GPIO_FUNC_AF7       0x00000007
    #define GPIO_FUNC_AF8       0x00000008
    #define GPIO_FUNC_AF9       0x00000009
    #define GPIO_FUNC_AF10      0x0000000A
    #define GPIO_FUNC_AF11      0x0000000B
    #define GPIO_FUNC_AF12      0x0000000C
    #define GPIO_FUNC_AF13      0x0000000D
    #define GPIO_FUNC_AF14      0x0000000E
    #define GPIO_FUNC_AF15      0x0000000F

    /*Macros for the GPIO Pin SET/RESET Value*/

    #define GPIO_STATE_RESET    0
    #define GPIO_STATE_SET      1


    #define GPIOA_u32BASEADDRESS 		         0x40020000
    #define GPIO_PORT_A						    ((void* )(GPIOA_u32BASEADDRESS))

    #define GPIOB_u32BASEADDRESS 		         0x40020400
    #define GPIO_PORT_B						    ((void* )(GPIOB_u32BASEADDRESS))

    #define GPIOC_u32BASEADDRESS 		        0x40020800
    #define GPIO_PORT_C						    ((void* )(GPIOC_u32BASEADDRESS))

    #define GPIO_MODE_Verfier                   BIT28_MASK
    #define GPIO_SPEED_Verfire                  BIT29_MASK

    /*Error Enum*/
        typedef enum 
        {

            GPIO_NOK,
            GPIO_NULL_POINER,
            GPIO_INVALID_PORT,
            GPIO_INVALID_PIN,
            GPIO_INVALID_MODE,
            GPIO_INVALID_STATE,
            GPIO_INVALID_SPEED,
            GPIO_INVALID_AFN,
            GPIO_OK

        }GPIO_Error_t;
    /*-----------*/   

    /*Struct for user to write on and config*/
        typedef struct
        {

            void *Port;
            U32 Pin_num;
            U32 Pin_Mode;
            U32 Pin_Speed;
            U8 Pin_Lock_Config;

        }GPIO_Pin_t;
    /*-------------------------------------*/

    /*----------------*/
    /*API*/

        /*Init Function*/
            GPIO_Error_t GPIO_Init(GPIO_Pin_t *GPIO_pincfg);
        /*-------------*/

        /*Set Pin value*/
            GPIO_Error_t GPIO_Set_PinValue(void *GPIO_Port_x, U32 GPIO_Pin_x , U32 GPIO_STATE_x);
        /*-------------*/	

        /*Get Pin value*/
            GPIO_Error_t GPIO_Get_PinValue(void *GPIO_Port_x, U32 GPIO_Pin_x, U8 *GPIO_Pin_State);
        /*-------------*/    

        /*Alternate function configuration*/
            GPIO_Error_t GPIO_CFG_AlternateFunction(void *GPIO_Port_x, U32 GPIO_Pin_x, U32 GPIO_FUNC_AFx);
        /*-------------*/

    /*---*/

#endif
