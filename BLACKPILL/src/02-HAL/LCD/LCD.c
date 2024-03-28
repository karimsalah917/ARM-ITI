/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Source file for LCD  Driver                                              */
/* Target       : STM32f401cc                                                              */
/*******************************************************************************************/

/*-----------------------------------------------------------------------------------------*/
/*                                  >> Includes <<                                         */
/*-----------------------------------------------------------------------------------------*/

#include "../../../include/02-HAL/LCD/LCD.h"
#include "../../../include/02-HAL/LCD/LCD_Config.h"
#include "../../../include/01-MCAL/GPIO/GPIO.h"

/*-----------------------------------------------------------------------------------------*/
/*                                  >> Definitions <<                                      */
/*-----------------------------------------------------------------------------------------*/

/**********************************[1]GENERAL USED *****************************************/
#define UNIT_TIME_PERIOD                2
#define LCD_D0_PIN                      0
#define LCD_D1_PIN                      1
#define LCD_D2_PIN                      2
#define LCD_D3_PIN                      3
#define LCD_D4_PIN                      4
#define LCD_D5_PIN                      5
#define LCD_D6_PIN                      6
#define LCD_D7_PIN                      7
#define LCD_ENABLE_PIN                  8
#define LCD_RW_PIN                      9
#define LCD_RS_PIN                     10
/**********************************[2]INIT PROCESS *****************************************/
#define INIT_START_TIME                 40
#define INIT_FUNCTION_SET_TIME          3
#define INIT_DISPLAY_ON_OFF_TIME        3
#define INIT_DISPLAY_CLEAR_TIME         8

#define FUNCTION_SET_CMD  (0b00110000)|(LCD_FONT_MODE<<2)|(LCD_ROWS_MODE<<3)
#define DISPLAY_ON_OFF_CMD (0b00001000)|(LCD_CURSOR_BLINKING_MODE<<0)|(LCD_CURSOR_MODE<<1)|(LCD_DISPLAY_MODE<<2)
#define DISPLAY_CLEAR_CMD  (0b00000001)
/***********************************[3]OPERATION PROCESS *************************************/


/*-----------------------------------------------------------------------------------------*/
/*                                  >> Types <<                                            */
/*-----------------------------------------------------------------------------------------*/

/**********************************[1]GENERAL USED TYPES ***********************************/
typedef enum 
{
    PROCESS_READY,      // The process is ready to execute
    PROCESS_RUNNING,    // The process is currently running
    PROCESS_BLOCKED,    // The process is blocked, waiting for an event or resource
    PROCESS_DONE,       // The process has completed its execution
    PROCESS_TERMINATED  // The process has terminated
} PROCESS_STATE_t;


typedef enum
{
    TRIGGER_ENABLE_ON=0,
    TRIGGER_ENABLE_OFF,
    TRIGGER_ENABLE_DONE
}TRIGGER_ENABLE_STATES_t;
typedef struct 
{
    TRIGGER_ENABLE_STATES_t STATE;
    uint32 COUNTER;
}TRIGGER_ENABLE_t;


/***********************************[2]LCD GENERAL STATES ************************************/
typedef enum 
{
    OFF_MODE,
    INIT_MODE,
    OPERATION_MODE
}LCD_STATES_t;

typedef struct 
{
    LCD_STATES_t MODE;
    uint32 COUNTER;
}LCD_t;
/***********************************[3]OPERATION GENERAL STATES ******************************/

typedef enum 
{
    WRITE,
    CLEAR,
    SETPOS
}OPERATION_STATES_t;
typedef struct
{
    OPERATION_STATES_t STATE;
    uint32 COUNTER;
}OPERATION_t;

/************************************[4]INIT GENERAL STATES **********************************/
typedef enum 
{
    INIT_START=0,
    INIT_FUNCTION_SET,
    INIT_DISPLAY_ON_OFF,
    INIT_DISPLAY_CLEAR,
    INIT_END
}INIT_STATES_t;

typedef struct 
{
    INIT_STATES_t STATE;
    uint32 COUNTER;
}INIT_t;


/**
 * EVERY THREAD STATES
*/
typedef enum 
{
    SEND_COMMAND=0,
    WAIT
}INIT_THREAD_STATES_t;

/**
 * FUNCTION SET RECORD
*/
typedef struct
{
    INIT_THREAD_STATES_t STATE;
    uint32 COUNTER;
}FUNCTION_SET_t;

/**
 * DISPLAY ON OFF RECORD
*/
typedef struct
{
    INIT_THREAD_STATES_t STATE;
    uint32 COUNTER;
}DISPLAY_ON_OFF_t;

typedef struct 
{
    INIT_THREAD_STATES_t STATE;
    uint32 COUNTER;
}DISPLAY_CLEAR_t;
/*-----------------------------------------------------------------------------------------*/
/*                                  >> variables <<                                        */
/*-----------------------------------------------------------------------------------------*/

/**********************************[1]GENERAL USED *****************************************/
extern const LCD_strLCDConfigration_t PIN_CONFIG[USED_LCD_PIN_NUMS];

static TRIGGER_ENABLE_t TRIGGER_ENABLE ={.STATE=TRIGGER_ENABLE_ON,.COUNTER=0};
/**********************************[2]LCD GENERAL ******************************************/
static LCD_t LCD={.COUNTER=0,.MODE=OFF_MODE};
/**********************************[3]INIT PROCESS *****************************************/
static INIT_t INIT={.COUNTER=0,.STATE=INIT_START};

static FUNCTION_SET_t FUNCTION_SET ={.STATE=SEND_COMMAND,.COUNTER=0};
static DISPLAY_ON_OFF_t DISPLAY_ON_OFF={.COUNTER=0,.STATE=SEND_COMMAND};
static DISPLAY_CLEAR_t DISPLAY_CLEAR={.STATE=SEND_COMMAND,.COUNTER=0};
/**********************************[4]INIT PROCESS *****************************************/

/*-----------------------------------------------------------------------------------------*/
/*                             >> Static functions <<                                      */
/*-----------------------------------------------------------------------------------------*/

/******************************** [1] GENERAL USED THREADS *********************************/

static void WRITE_DataPins(uint8 DataORCMD)
{
    for(uint8 idx=0;idx<8;idx++)
    {
        GPIO_SetPinValue(PIN_CONFIG[idx].LCD_PortNum,PIN_CONFIG[idx].LCD_PinNum,((DataORCMD>>idx)&0x01));
    }
}

static PROCESS_STATE_t SEND_CommandAsync(uint8 CMD)
{

}

static PROCESS_STATE_t SEND_DataAsync(uint8 DATA)
{

}

static PROCESS_STATE_t TriggerEnableAsync(void)
{
    TRIGGER_ENABLE.COUNTER+=UNIT_TIME_PERIOD;
    switch (TRIGGER_ENABLE.STATE)
    {
    case TRIGGER_ENABLE_ON:
        GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_HIGH);
        if(TRIGGER_ENABLE.COUNTER>=1)
        {
            TRIGGER_ENABLE.STATE=TRIGGER_ENABLE_OFF;
            TRIGGER_ENABLE.COUNTER=0;
        }
        break;

    case TRIGGER_ENABLE_OFF:
        GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_LOW);
        if(TRIGGER_ENABLE.COUNTER>=1)
        {
            TRIGGER_ENABLE.STATE=TRIGGER_ENABLE_OFF;
            TRIGGER_ENABLE.COUNTER=0;
        }
        break;    
    default:
        break;
    }
}

/******************************** [2] INIT PROCESS AND IT'S THREADS *************************/

static void LCD_PINS_INIT_THREAD(void)
{
    GPIO_CONFIG_t LCD;
    LCD.MODE=GPIO_MODE_OUT_PP_FL;
    LCD.SPEED=GPIO_SPEED_HIGH;

    for(uint8 IDX=0;IDX<USED_LCD_PIN_NUMS;IDX++) 
    {
        LCD.PORT=PIN_CONFIG[IDX].LCD_PortNum;
        LCD.PIN=PIN_CONFIG[IDX].LCD_PinNum;
        GPIO_INIT_PIN(&LCD);
    }    
}
static void INIT_START_THREAD(void)
{
    if(INIT.COUNTER>=INIT_START_TIME)
    {
        INIT.STATE=INIT_FUNCTION_SET;
        INIT.COUNTER=0;
    }
       
}

static void INIT_FUNCTION_SET_THREAD(void)
{
    uint8 ret;
    switch (FUNCTION_SET.STATE)
    {
    case SEND_COMMAND:  
    ret=SEND_CommandAsync(FUNCTION_SET_CMD);
    if(PROCESS_DONE==ret){FUNCTION_SET.STATE=WAIT;}
        break;

    case WAIT:
    if(INIT.COUNTER>=INIT_FUNCTION_SET_TIME)
    {
        INIT.STATE=INIT_DISPLAY_ON_OFF;
        INIT.COUNTER=0;
    }
        break;    
    default:
        break;
    }

}

static void INIT_DISPLAY_ON_OFF_THREAD(void)
{
    uint8 ret;
    switch (DISPLAY_ON_OFF.STATE)
    {
    case SEND_COMMAND:
    ret=SEND_CommandAsync(DISPLAY_ON_OFF_CMD);
    if(PROCESS_DONE==ret){FUNCTION_SET.STATE=WAIT;}
        break;
    case WAIT:
    if(INIT.COUNTER>=INIT_DISPLAY_ON_OFF_TIME)
    {
        INIT.STATE=INIT_DISPLAY_CLEAR;
        INIT.COUNTER=0;
    }
    default:
        break;
    }

}

static void INIT_DISPLAY_CLEAR_THREAD(void)
{
    uint8 ret;
    switch (DISPLAY_CLEAR.STATE)
    {
    case SEND_COMMAND:
    ret=SEND_CommandAsync(DISPLAY_CLEAR_CMD);
    if(PROCESS_DONE==ret){FUNCTION_SET.STATE=WAIT;}
        break;

    case WAIT:
    if(INIT.COUNTER>=INIT_DISPLAY_CLEAR_TIME)
    {
        INIT.STATE=INIT_END;
        INIT.COUNTER=0;
    }    
    default:
        break;
    }

}

static void INIT_END_THREAD()
{
    LCD.MODE=OPERATION_MODE;
    LCD.COUNTER=0;
}

static void INIT_Process(void)
{


    INIT.COUNTER+=UNIT_TIME_PERIOD;
    switch (INIT.STATE)
    {
    case INIT_START         : INIT_START_THREAD();           break;

    case INIT_FUNCTION_SET  : INIT_FUNCTION_SET_THREAD();    break;

    case INIT_DISPLAY_ON_OFF: INIT_DISPLAY_ON_OFF_THREAD();  break;
        
    case INIT_DISPLAY_CLEAR : INIT_DISPLAY_CLEAR_THREAD();   break;
    
    case INIT_END           : INIT_END_PROCESS_THREAD();     break;                            
    
    default:                                                 break;
    }
}
/************************************** OPERATION PROCESS AND IT's THREADS ********************/
static void OPERATION_PROCESS(void)
{

}

/************************************** LCD MODULE GENERAL RUNNABLE ***************************/

static void LCD_Runnable(void)
{

    switch (LCD.MODE)
    {
    case OFF_MODE:
        /*Dont do anything*/
        break;
    case INIT_MODE:
        /* Calling the INIT Process */
        INIT_PROCESS();
        break;
    case OPERATION_MODE:
        /* code */
        OPERATION_PROCESS();
        break;
    default:
        break;
    }
}
/******************************** Interface functions **************************************/

void LCD_InitAsync(void)
{
    LCD_PINS_INIT_THREAD();   
    LCD.MODE=INIT_MODE;
}

LCD_Error_t LCD_WriteStringAsync(const char* String, uint8 Size, uint8 X_Postion, uint8 Y_Postion)
{

}

LCD_Error_t LCD_ClearScreenAsync(void)
{

}

LCD_Status_t LCD_GetStatus(void)
{

}