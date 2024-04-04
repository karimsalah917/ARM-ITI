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
#define INIT_POWER_ON_TIME                 40
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

/**
 * @brief Defines a callback function pointer type.
 * 
 * This typedef defines a callback function pointer type named CB_t. Callback functions of this type
 * take no parameters and return void.
 */
typedef void (*CB_t)(void);


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
    OPERATION_IDLE,
    OPERATION_BUSY
}OPERATION_STATES_t;
typedef enum 
{
    OPERATION_WRTIE_STRING,
    OPERATION_CLEAR_SCREEN,
    OPERATION_SET_POSITION,
    OPERATION_WRITE_NUM
}OPERATION_TYPES_t;

typedef enum 
{
    SEND_CH_LOW=0,
    SEND_CH_HIGH
}OPERATION_WRITE_STRING_STATES_t;
typedef struct
{
    OPERATION_STATES_t STATE;
    uint32 COUNTER;
    uint8 TYPE;
}OPERATION_t;

typedef struct
{
    uint8 STATE;
} OPERATION_THREAD_t;


typedef struct
{
    const     char*s;
    uint8      len;
    uint8 Remaining;
}LCD_OPERATION_SEND_STRING_REQUEST_t;

/************************************[4]INIT GENERAL STATES **********************************/
typedef enum 
{
    INIT_POWER_ON=0,
    INIT_FUNCTION_SET_P1,
    INIT_FUNCTION_SET_P2,    
    INIT_DISPLAY_ON_OFF_P1,
    INIT_DISPLAY_ON_OFF_P2,
    INIT_DISPLAY_CLEAR_P1,
    INIT_DISPLAY_CLEAR_P2,
    INIT_END
}INIT_STATES_t;

typedef struct 
{
    INIT_STATES_t STATE;
    uint32 COUNTER;
}INIT_t;
/*-----------------------------------------------------------------------------------------*/
/*                                  >> variables <<                                        */
/*-----------------------------------------------------------------------------------------*/

/**********************************[1]GENERAL USED *****************************************/
extern const LCD_strLCDConfigration_t PIN_CONFIG[USED_LCD_PIN_NUMS];

/**********************************[2]LCD GENERAL ******************************************/
static LCD_t LCD={.COUNTER=0,.MODE=OFF_MODE};
/**********************************[3]INIT MODE *****************************************/
static INIT_t INIT={.COUNTER=0,.STATE=INIT_POWER_ON};

/**********************************[4]OPERATION MODE *****************************************/
static OPERATION_t OPERATION ={.COUNTER=0,.STATE=OPERATION_IDLE,.TYPE=9999};

static LCD_OPERATION_SEND_STRING_REQUEST_t STRING={.len=0,.s=NULL_PTR,.Remaining=0}; 

static OPERATION_THREAD_t WRITE_STRING={.STATE=SEND_CH_HIGH};
/*-----------------------------------------------------------------------------------------*/
/*                             >> Static functions <<                                      */
/*-----------------------------------------------------------------------------------------*/

/******************************** [1] GENERAL USED THREADS *********************************/

static void LCD_WRITE_PINS_THREAD(uint8 DataORCMD)
{
    for(uint8 idx=0;idx<8;idx++)
    {
        if((DataORCMD>>idx)&0x01)
        {
            GPIO_SetPinValue(PIN_CONFIG[idx].LCD_PortNum,PIN_CONFIG[idx].LCD_PinNum,PIN_STATE_HIGH);
        }else
        {
            GPIO_SetPinValue(PIN_CONFIG[idx].LCD_PortNum,PIN_CONFIG[idx].LCD_PinNum,PIN_STATE_LOW);
        }

    }
}

static void SEND_COMMAND(uint8 CMD)
{
    LCD_WRITE_PINS_THREAD(CMD);
    GPIO_SetPinValue(PIN_CONFIG[LCD_RS_PIN].LCD_PortNum,PIN_CONFIG[LCD_RS_PIN].LCD_PinNum,PIN_STATE_LOW);
}

static void SEND_DATA(uint8 DATA)
{
    LCD_WRITE_PINS_THREAD(DATA);
    GPIO_SetPinValue(PIN_CONFIG[LCD_RS_PIN].LCD_PortNum,PIN_CONFIG[LCD_RS_PIN].LCD_PinNum,PIN_STATE_HIGH);
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
static void INIT_POWER_ON_THREAD(void)
{
    INIT.COUNTER+=UNIT_TIME_PERIOD;
    if(INIT.COUNTER>=INIT_POWER_ON_TIME)
    {
        INIT.STATE=INIT_FUNCTION_SET_P1;
        INIT.COUNTER=0;
    }
       
}

static void INIT_FUNCTION_SET_P1_THREAD(void)
{
    SEND_COMMAND(FUNCTION_SET_CMD);
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_HIGH);
    INIT.STATE=INIT_FUNCTION_SET_P2;
}

static void INIT_FUNCTION_SET_P2_THREAD(void)
{
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_LOW);
    INIT.STATE=INIT_DISPLAY_ON_OFF_P1;
}

static void INIT_DISPLAY_ON_OFF_P1_THREAD(void)
{
    SEND_COMMAND(DISPLAY_ON_OFF_CMD);
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_HIGH);
    INIT.STATE=INIT_DISPLAY_ON_OFF_P2;
}
static void INIT_DISPLAY_ON_OFF_P2_THREAD(void)
{
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_LOW);
    INIT.STATE=INIT_DISPLAY_CLEAR_P1;
}

static void INIT_DISPLAY_CLEAR_P1_THREAD(void)
{
    SEND_COMMAND(DISPLAY_CLEAR_CMD);
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_HIGH);
    INIT.STATE=INIT_DISPLAY_CLEAR_P2;
}

static void INIT_DISPLAY_CLEAR_P2_THREAD(void)
{
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_LOW);
    INIT.STATE=INIT_END;
}

static void INIT_END_THREAD()
{
    LCD.MODE=OPERATION_MODE;
    LCD.COUNTER=0;
    INIT.STATE=INIT_POWER_ON;
}

static void INIT_PROCESS(void)
{

    switch (INIT.STATE)
    {
    case INIT_POWER_ON         : INIT_POWER_ON_THREAD();           break;

    case INIT_FUNCTION_SET_P1  : INIT_FUNCTION_SET_P1_THREAD();    break;

    case INIT_FUNCTION_SET_P2  : INIT_FUNCTION_SET_P2_THREAD();    break;

    case INIT_DISPLAY_ON_OFF_P1: INIT_DISPLAY_ON_OFF_P1_THREAD();  break;

    case INIT_DISPLAY_ON_OFF_P2: INIT_DISPLAY_ON_OFF_P2_THREAD();  break;

    case INIT_DISPLAY_CLEAR_P1 : INIT_DISPLAY_CLEAR_P1_THREAD();   break;
    
    case INIT_DISPLAY_CLEAR_P2 : INIT_DISPLAY_CLEAR_P2_THREAD();   break;
    
    case INIT_END           : INIT_END_THREAD();                   break;                            
    
    default:                                                       break;
    }
}
/************************************** OPERATION PROCESS AND IT's THREADS ********************/

void OPERATION_SET_POS_THREAD(void)
{

}

/*
    if (remaining_chars > 0) 
    {
        if (Global_LCDEnable_State == LCD_enuEnableOff) 
        {
            HLCD_StaticSendCommand(LCD_strUsrData.String[LCD_strUsrData.String_Size - remaining_chars],LCD_RESETVALUE,LCD_ENABLEVALUE);
            Global_LCDEnable_State = LCD_enuEnableOn;
            HLCD_vidStaticSetEnableBit(LCD_enuEnableOn);
        } 
        else
        { 
            Global_LCDEnable_State = LCD_enuEnableOff;
            HLCD_vidStaticSetEnableBit(LCD_enuEnableOff);
            remaining_chars--;
        }
    } 
    else 
    {
        Global_LCDWrite_State = Write_Done; 
    }
*/
void OPERATION_WRITE_STRING_THREAD(void)
{
    if(STRING.Remaining>0){
        switch (WRITE_STRING.STATE)
        {
            case SEND_CH_HIGH:
            SEND_DATA(STRING.s[STRING.len-STRING.Remaining]);
            GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_HIGH);
            WRITE_STRING.STATE=SEND_CH_LOW;
             break;
             case SEND_CH_LOW:
            GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum,PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum,PIN_STATE_LOW);
            WRITE_STRING.STATE=SEND_CH_HIGH;
            STRING.Remaining--;;
             break;
             default:
             break;
        }
    
    }
    else
    {
        OPERATION.STATE==OPERATION_IDLE;
    }
}
void OPERATION_WRITE_NUM_THREAD(void)
{

}
void OPERATION_CLEAR_SCREEN_THREAD(void)
{
    
}

void OPERATION_BUSY_THREAD(void)
{
    switch (OPERATION.TYPE)
    {
    case OPERATION_WRTIE_STRING:
    OPERATION_WRITE_STRING_THREAD();
        break;
    case OPERATION_CLEAR_SCREEN:
    OPERATION_CLEAR_SCREEN_THREAD();
        break;    
    case OPERATION_SET_POSITION:
    OPERATION_SET_POS_THREAD();
        break;
    case OPERATION_WRITE_NUM:
    OPERATION_WRITE_NUM_THREAD();
        break;    
    default:
        break;
    }
}
static void OPERATION_PROCESS(void)
{
    switch (OPERATION.STATE)
    {
    case OPERATION_IDLE:
        /* DO NOTHING */
        break;
    case OPERATION_BUSY:
    OPERATION_BUSY_THREAD();
        break;
    default:
        break;
    }
}

/************************************** LCD MODULE GENERAL RUNNABLE ***************************/

 void LCD_Runnable(void)
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
LCD_Error_t LCD_SetPositionAsync(uint8 x_pos,uint8 y_pos)
{
    
}
LCD_Error_t LCD_WriteStringAsync(const char* String, uint8 Size)
{
    if(OPERATION.STATE==OPERATION_IDLE)
    {
        OPERATION.STATE=OPERATION_BUSY;
        OPERATION.TYPE=OPERATION_WRTIE_STRING;
        STRING.len=Size;
        STRING.s=String;
        STRING.Remaining=Size;
    }  
}

LCD_Error_t LCD_ClearScreenAsync(void)
{

}
