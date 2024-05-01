#include "MCAL/GPIO/GPIO.h"

typedef struct
{

    U32 GPIOx_MODER;
    U32 GPIOx_OTYPER;
    U32 GPIOx_OSPEEDR;
    U32 GPIOx_PUPDR;
    U32 GPIOx_IDR;
    U32 GPIOx_ODR;
    U32 GPIOx_BSRR;
    U32 GPIOx_LCKR;
    U32 GPIOx_AFRL;
    U32 GPIOx_AFRH;

}GPIOx_Peri_t;




#define OTYPE_OFFSET                        TWO_OFFSET
#define PUPD_OFFSET                         THREE_OFFSET

#define OUTPUT_MODE                         BIT00_MASK

#define GPIO_MODE_Verfier                   BIT28_MASK
#define GPIO_SPEED_Verfire                  BIT29_MASK

#define HALF_WORD_OFFSET                    16

#define NO_MATCH                            0
#define TWO_OFFSET                          2
#define THREE_OFFSET                        3
#define FOUR_OFFSET                         4

/*API*/

    /*Init Function*/
	    GPIO_Error_t GPIO_Init(GPIO_Pin_t *GPIO_pincfg)
        {
            GPIO_Error_t LOC_Status = GPIO_NOK;
            
            /*error handling*/
                if (((GPIOx_Peri_t*)(GPIO_pincfg->Port)) == NULL)
                {
                    LOC_Status = GPIO_NULL_POINER;
                }

                else if( ((GPIO_pincfg->Pin_Mode) & (GPIO_MODE_Verfier)) == NO_MATCH )
                {
                    LOC_Status = GPIO_INVALID_MODE;
                }

                else if( ((GPIO_pincfg->Pin_Speed) & (GPIO_SPEED_Verfire)) == NO_MATCH )
                {
                    LOC_Status = GPIO_INVALID_MODE;
                }
            /*-------------*/

            /*Function*/
                else
                {
                    U32 Local_RegCpy = 0;
                    LOC_Status = GPIO_OK;

                    /*For Mode*/

                        /*Reciece the value of MODE in Local variable*/
                            Local_RegCpy = ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_MODER;    
                        /*-------------------------------------------*/

                        /*Clear the bits needed in the registers*/
                            Local_RegCpy &= ~(FIRST_TWO_BITS_MASK<<((GPIO_pincfg->Pin_num)*TWO_OFFSET));
                        /*--------------------------------------*/

                        /*Write the configured data by the user*/
                            Local_RegCpy |= (((GPIO_pincfg->Pin_Mode)&FIRST_TWO_BITS_MASK)<<(GPIO_pincfg->Pin_num)*TWO_OFFSET);
                        /*-------------------------------------*/

                        /*Send the configuration to the register*/
                            ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_MODER = Local_RegCpy;     
                        /*--------------------------------------*/

                    /*--------*/

                    /*For OTYPE*/
                    // if ( ((GPIO_pincfg->Pin_Mode) & (FIRST_TWO_BITS_MASK)) == OUTPUT_MODE )
                    // {

                        /*Reciece the value of OTYPE in Local variable*/
                            Local_RegCpy = ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_OTYPER;    
                        /*-------------------------------------------*/

                        /*Clear the bits needed in the registers*/
                            Local_RegCpy &= ~(BIT00_MASK<<(GPIO_pincfg->Pin_num));
                        /*--------------------------------------*/

                        /*Write the configured data by the user*/
                            Local_RegCpy |= (((GPIO_pincfg->Pin_Mode)>>OTYPE_OFFSET)&BIT00_MASK<<(GPIO_pincfg->Pin_num));
                        /*-------------------------------------*/

                        /*Send the configuration to the register*/
                            ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_OTYPER = Local_RegCpy;
                        /*--------------------------------------*/
                    // }
                    /*---------*/  

                    /*For PUPDR*/

                        /*Reciece the value of MODE in Local variable*/
                            Local_RegCpy = ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_PUPDR;    
                        /*-------------------------------------------*/

                        /*Clear the bits needed in the registers*/
                            Local_RegCpy &= ~(FIRST_TWO_BITS_MASK<<((GPIO_pincfg->Pin_num)*TWO_OFFSET));
                        /*--------------------------------------*/

                        /*Write the configured data by the user*/
                            Local_RegCpy |= (((GPIO_pincfg->Pin_Mode)>>PUPD_OFFSET)<<((GPIO_pincfg->Pin_num)*TWO_OFFSET));
                        /*-------------------------------------*/

                        /*Send the configuration to the register*/
                            ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_PUPDR = Local_RegCpy; 
                        /*--------------------------------------*/

                    /*--------*/

                    /*For Speed*/
                    // if (((GPIO_pincfg->Pin_Mode) & (FIRST_TWO_BITS_MASK)) == OUTPUT_MODE )
                    // {
                        /*Reciece the value of MODE in Local variable*/
                            Local_RegCpy = ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_OSPEEDR;    
                        /*-------------------------------------------*/

                        /*Clear the bits needed in the registers*/
                            Local_RegCpy &= ~(FIRST_TWO_BITS_MASK<<((GPIO_pincfg->Pin_num)*TWO_OFFSET));
                        /*--------------------------------------*/

                        /*Write the configured data by the user*/
                            Local_RegCpy |= ((GPIO_pincfg->Pin_Speed)<<(GPIO_pincfg->Pin_num)*TWO_OFFSET);
                        /*-------------------------------------*/

                        /*Send the configuration to the register*/
                            ((GPIOx_Peri_t*)(GPIO_pincfg->Port))->GPIOx_OSPEEDR = Local_RegCpy; 
                        /*--------------------------------------*/
                    // }
                    /*--------*/
                }
                
            /*--------*/

            return LOC_Status;
        }
    /*-------------*/

    /*Set Pin value*/
        GPIO_Error_t GPIO_Set_PinValue(void *GPIO_Port_x, U32 GPIO_Pin_x , U32 GPIO_STATE_x)
        {
            GPIO_Error_t LOC_Status = GPIO_NOK;

            /*Error Handling*/
                if (GPIO_Port_x == NULL)
                {
                    LOC_Status = GPIO_NULL_POINER;
                } 

                else if ( GPIO_Pin_x < GPIO_PIN_0 || GPIO_Pin_x > GPIO_PIN_15 )
                {
                    LOC_Status = GPIO_INVALID_PIN;
                }

                else if ( GPIO_STATE_RESET > GPIO_STATE_x || GPIO_STATE_x > GPIO_STATE_SET )
                {
                    LOC_Status = GPIO_INVALID_STATE;
                }
            /*--------------*/

            /*Function*/
                else 
                {
                    LOC_Status = GPIO_OK;

                    switch( GPIO_STATE_x )
                    {

                        case GPIO_STATE_RESET :
                            ((GPIOx_Peri_t *)GPIO_Port_x)->GPIOx_BSRR = 1 << (GPIO_Pin_x + HALF_WORD_OFFSET );
                        break;

                        case GPIO_STATE_SET :
                            ((GPIOx_Peri_t *)GPIO_Port_x)->GPIOx_BSRR = 1 <<  GPIO_Pin_x ;
                        break;

                        default:
                            LOC_Status = GPIO_NOK;
                        break;
                    }
                }
            /*-------*/

            return LOC_Status;

        }
    /*-------------*/	

    /*Get Pin value*/
        GPIO_Error_t GPIO_Get_PinValue(void *GPIO_Port_x, U32 GPIO_Pin_x, U8 *GPIO_Pin_State)
        {
            GPIO_Error_t LOC_Status = GPIO_NOK;

            /*Error Handling*/
                if (GPIO_Port_x == NULL)
                {
                    LOC_Status = GPIO_NULL_POINER;
                } 

                else if ( GPIO_Pin_x < GPIO_PIN_0 || GPIO_Pin_x > GPIO_PIN_15 )
                {
                    LOC_Status = GPIO_INVALID_PIN;
                }

                else if ( GPIO_Pin_State == NULL )
                {
                    LOC_Status = GPIO_INVALID_STATE;
                }
            /*--------------*/     

            /*Function*/

                else
                {
                    LOC_Status = GPIO_OK;
                    *GPIO_Pin_State = (((GPIOx_Peri_t *)GPIO_Port_x)->GPIOx_IDR >> GPIO_Pin_x) & BIT00_MASK;
                }

            /*--------*/       
            
         return LOC_Status;

        }
    /*-------------*/    

    /*Alternate function configuration*/
        GPIO_Error_t GPIO_CFG_AlternateFunction(void *GPIO_Port_x, U32 GPIO_Pin_x, U32 GPIO_FUNC_AFx)
        {
            GPIO_Error_t LOC_Status = GPIO_NOK;

            /*Error Handling*/
                if (GPIO_Port_x == NULL)
                {
                    LOC_Status = GPIO_NULL_POINER;
                } 

                else if ( GPIO_Pin_x < GPIO_PIN_0 || GPIO_Pin_x > GPIO_PIN_15 )
                {
                    LOC_Status = GPIO_INVALID_PIN;
                }

                else if ( GPIO_FUNC_AFx < GPIO_FUNC_AF0 || GPIO_FUNC_AFx > GPIO_FUNC_AF15 )
                {
                    LOC_Status = GPIO_INVALID_AFN;
                }            
            /*--------------*/

            /*Function*/
                else
                {
                    LOC_Status = GPIO_OK;
                    U32 LOC_AFR_Value = 0;

                    if (GPIO_Pin_x > GPIO_PIN_7)
                    {
                        /*Reciece the value of MODE in Local variable*/
                            LOC_AFR_Value = (((GPIOx_Peri_t *)GPIO_Port_x)->GPIOx_AFRH);
                        /*-------------------------------------------*/

                        /*Clear the bits needed in the registers*/
                            LOC_AFR_Value &= ~(FIRST_FOUR_BITS_MASK << (GPIO_Pin_x * FOUR_OFFSET));
                        /*-------------------------------------------*/

                        /*Write the configured data by the user*/
                            LOC_AFR_Value |= (GPIO_FUNC_AFx << (GPIO_Pin_x * FOUR_OFFSET));
                        /*-------------------------------------------*/

                        /*Send the configuration to the register*/
                            (((GPIOx_Peri_t *)GPIO_Port_x)->GPIOx_AFRH) = LOC_AFR_Value;
                        /*-------------------------------------------*/
                    }

                    else
                    {
                        /*Reciece the value of MODE in Local variable*/
                            LOC_AFR_Value = (((GPIOx_Peri_t *)GPIO_Port_x)->GPIOx_AFRL);
                        /*-------------------------------------------*/

                        /*Clear the bits needed in the registers*/
                            LOC_AFR_Value &= ~(FIRST_FOUR_BITS_MASK << (GPIO_Pin_x * FOUR_OFFSET));
                        /*-------------------------------------------*/

                        /*Write the configured data by the user*/
                            LOC_AFR_Value |= (GPIO_FUNC_AFx << (GPIO_Pin_x * FOUR_OFFSET));
                        /*-------------------------------------------*/

                        /*Send the configuration to the register*/
                            (((GPIOx_Peri_t *)GPIO_Port_x)->GPIOx_AFRL) = LOC_AFR_Value;
                        /*-------------------------------------------*/
                    }
                }
                
            /*--------*/

            return LOC_Status;

        }
    /*--------------------------------*/

/*---*/