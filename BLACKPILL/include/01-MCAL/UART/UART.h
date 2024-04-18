/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Module       : UART                                                                     */
/* Version      : v1.0                                                                     */
/* Date         : 01/4/2024                                                                */
/* File Details : Header file for UART Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/
#pragma      once   //Header Guard                                          
/********************************** Includes ***********************************************/
#include "../../00-LIB/STD.h"
/********************************** Definitions ********************************************/


/**********************************   Types ************************************************/
/**
 * @brief return error status that may uart API's return 
*/
typedef enum {
    UART_OK = 0,            // Operation successful
    UART_NOK,
    UART_ERROR,             // Generic error
    UART_BUSY,              // UART is busy, cannot initiate operation
    UART_TIMEOUT,           // Timeout occurred during operation
    UART_DATA_RECEIVED,     // Data has been received and is ready to be read
    UART_TX_COMPLETE,       // Transmission of data is complete
    UART_RX_COMPLETE,       // Reception of data is complete
    UART_PARITY_ERROR,      // Parity error detected in received data
    UART_FRAME_ERROR,       // Framing error detected in received data
    UART_OVERRUN_ERROR      // Overrun error occurred in UART receive buffer
} UART_Status_t;

typedef enum 
{
    UART_Peri_1,
    UART_Peri_2,
    UART_Peri_3
}UART_Peri_t;

typedef enum 
{
    UART_ParityOption_Disable,
    UART_ParityOption_Odd,
    UART_ParityOption_EVEN
}UART_ParityOption_t;

typedef enum 
{
    UART_WordLengthOption_8,
    UART_WordLengthOption_9
}UART_WordLengthOption_t;

typedef enum 
{
    UART_StopBitsOption_1,
    UART_StopBitsOption_2
}UART_StopBitsOption_t;

typedef enum 
{
UART_OverSamplingOption_16,
UART_OverSamplingOption_8
}UART_OverSamplingOption_t;

typedef void (*UART_CB)(void);

typedef uint8* UART_Buffer;

typedef struct  
{
    uint32                         UART_BaudRate     ;
    UART_WordLengthOption_t        UART_WordLength   ;
    UART_ParityOption_t            UART_Parity       ;
    UART_StopBitsOption_t          UART_StopBits     ;
    UART_OverSamplingOption_t      UART_OverSampling ;
}UART_CFG_t;

typedef struct
{
    UART_Peri_t   UART_Peri ;
    UART_Buffer   Buffer    ;
    uint16        Lenght    ;
    UART_CB       CB        ;
}UART_Req_t;

/**********************************   API's ************************************************/

UART_Status_t UART_SendByte             (uint8 Byte         );

UART_Status_t UART_ReceiveByte          (uint8 *Container   );

UART_Status_t UART_TXBufferAsyncZC      (UART_Req_t Request );

UART_Status_t UART_RXceiveBufferAsyncZC (UART_Req_t Request );

UART_Status_t UART_Init                 (UART_CFG_t CFG     );