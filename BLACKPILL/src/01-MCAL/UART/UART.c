/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : UART                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : 01/4/2024                                                                */
/* File Details : Source file for UART Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
/********************************** Includes ***********************************************/
#include "../../../include/01-MCAL/UART/UART.h"
/********************************** Definitions ********************************************/
#define UART_PERI_NUM 3
#define UART_CLK    (uint32)25000000

#define UART6_ADDRESS  0x40011400
#define UART1_ADDRESS  0x40011000
#define UART2_ADDRESS  0x40004400                               
/**********************************  Types  ************************************************/
typedef struct
{
    volatile uint32 SR   ;
    volatile uint32 DR   ;
    volatile uint32 BRR  ; 
    volatile uint32 CR1  ;
    volatile uint32 CR2  ;
    volatile uint32 CR3  ;
    volatile uint32 GTPR ;
} USART_Peri_t;


typedef struct
{
    uint8  *data;
    uint32  pos;
    uint32  size;
} buffer_t;


typedef struct
{
    buffer_t buffer;
    uint8 state;
    UART_CB CallBack;
} TX_Req_t;

typedef struct
{
    buffer_t buffer;
    uint8 state;
    UART_CB CallBack;
} RX_Req_t;
/**********************************  Variables *********************************************/
TX_Req_t TX_Request[UART_PERI_NUM]; //making a variable for each UART instant
RX_Req_t RX_Request[UART_PERI_NUM];

USART_Peri_t*UART[UART_PERI_NUM]={(UART_Peri_t*)UART1_ADDRESS,(UART_Peri_t*)UART2_ADDRESS,(UART_Peri_t*)UART6_ADDRESS};


/********************************** Static Functions ***************************************/

/********************************** Implementation *****************************************/

UART_Status_t UART_SendByte             (uint8 Byte         )
{

}

UART_Status_t UART_ReceiveByte          (uint8 *Container   )
{

}

UART_Status_t UART_TXBufferAsyncZC      (UART_Req_t Request )
{

}
UART_Status_t UART_RXceiveBufferAsyncZC (UART_Req_t Request )
{

}

UART_Status_t UART_Init                 (UART_CFG_t CFG     )
{
    UART_Status_t LOC_Status=UART_NOK;
    float32 LOC_BRRValue    =0;
    uint32 LOC_CR1Value     =0;
    uint32 LOC_CR2Value     =0;
    uint16 LOC_Mantissa     =0;
    uint16 LOC_Fraction     =0;
    uint32 LOC_USARTDIV     =0;
    uint32 LOC_OverSampling =0;

    // validation
    if((CFG.Peri>UART_Peri_6)||(CFG.OverSampling>UART_OverSamplingOption_8))
    {
        LOC_Status=UART_INVALID_INPUT;
    }
    else if((CFG.Parity>UART_ParityOption_EVEN)||(CFG.StopBits>UART_StopBitsOption_2))
    {
        LOC_Status=UART_INVALID_INPUT;
    }else if(CFG.WordLength>UART_WordLengthOption_9)
    {
        LOC_Status=UART_INVALID_INPUT;
    }else
    {
        LOC_Status=UART_OK;
        // read oversampling option
        LOC_OverSampling=CFG.OverSampling/UART_OverSamplingOption_8;
        // calculate USARTDIV valueand multiply it by 1000 to get the fraction as integer
        LOC_USARTDIV = (((uint64)UART_CLK * 1000) / (CFG.BaudRate * (8 * (2 - LOC_OverSampling))));

        LOC_Mantissa=LOC_USARTDIV/1000;
        LOC_Fraction=(LOC_USARTDIV%1000)*(8*(2-LOC_OverSampling));

        if(LOC_Fraction%1000>=500)
        {
             LOC_Fraction = (LOC_Fraction / 1000) + 1;
        }else
        {
            LOC_Fraction = LOC_Fraction / 1000;
        }
    }
}