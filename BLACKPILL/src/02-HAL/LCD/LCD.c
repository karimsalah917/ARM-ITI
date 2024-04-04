/*******************************************************************************************/
/* Author       : Karim Salah Fathey                                                       */
/* Authority    : Information Technology Institute                                         */
/* Layer        : Hardware Abstraction Layer (HAL)                                         */
/* Module       : LCD                                                                      */
/* Version      : v1.0                                                                     */
/* Date         : 20/03/2024                                                               */
/* File Details : Source file for LCD Driver                                                */
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

/**********************************[1] GENERAL USED ****************************************/
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
/**********************************[2] INIT PROCESS ****************************************/
#define INIT_POWER_ON_TIME                 40
#define INIT_FUNCTION_SET_TIME          3
#define INIT_DISPLAY_ON_OFF_TIME        3
#define INIT_DISPLAY_CLEAR_TIME         8

#define FUNCTION_SET_CMD  (0b00110000)|(LCD_FONT_MODE<<2)|(LCD_ROWS_MODE<<3)
#define DISPLAY_ON_OFF_CMD (0b00001000)|(LCD_CURSOR_BLINKING_MODE<<0)|(LCD_CURSOR_MODE<<1)|(LCD_DISPLAY_MODE<<2)
#define DISPLAY_CLEAR_CMD  (0b00000001)
#define LCD_SetCursor                 0x80  // Set cursor position
/***********************************[3] OPERATION PROCESS *************************************/


/*-----------------------------------------------------------------------------------------*/
/*                                  >> Types <<                                            */
/*-----------------------------------------------------------------------------------------*/

/**********************************[1] GENERAL USED TYPES ***********************************/

/**
 * @brief Defines a callback function pointer type.
 * 
 * This typedef defines a callback function pointer type named CB_t. Callback functions of this type
 * take no parameters and return void.
 */
typedef void (*CB_t)(void);


/***********************************[2] LCD GENERAL STATES ************************************/
typedef enum 
{
    OFF_MODE,
    INIT_MODE,
    OPERATION_MODE
} LCD_STATES_t;

typedef struct 
{
    LCD_STATES_t mode;
    uint32 counter;
} LCD_t;
/***********************************[3] OPERATION GENERAL STATES ******************************/

typedef enum 
{
    OPERATION_IDLE,
    OPERATION_BUSY
} OPERATION_STATES_t;

typedef enum 
{
    OPERATION_WRITE_STRING,
    OPERATION_COMMAND,
    OPERATION_SET_POSITION
} OPERATION_TYPES_t;

typedef enum 
{
    ENABLE_LOW=0,
    ENABLE_HIGH
} OPERATION_STEPS_STATES_t;

typedef struct
{
    OPERATION_STATES_t state;
    uint32 counter;
    uint8 type;
} OPERATION_t;

typedef struct
{
    uint8 state;
} OPERATION_THREAD_t;

typedef struct
{
    const char *s;
    uint8 len;
    uint8 remaining;
} LCD_OPERATION_SEND_STRING_REQUEST_t;

typedef struct
{
    uint8 X;
    uint8 Y;
}LCD_OPERATION_SET_POSITION_REQUEST_t;

typedef struct
{
    uint8 CMD;
}LCD_OPERATION_SEND_COMMAND_REQUEST_t ;
/************************************[4] INIT GENERAL STATES **********************************/
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
} INIT_STATES_t;

typedef struct 
{
    INIT_STATES_t state;
    uint32 counter;
} INIT_t;

/*-----------------------------------------------------------------------------------------*/
/*                                  >> Variables <<                                        */
/*-----------------------------------------------------------------------------------------*/

/**********************************[1] GENERAL USED ****************************************/
extern const LCD_strLCDConfigration_t PIN_CONFIG[USED_LCD_PIN_NUMS];

/**********************************[2] LCD GENERAL ******************************************/
static LCD_t lcd = {.counter = 0, .mode = OFF_MODE};
/**********************************[3] INIT MODE *****************************************/
static INIT_t init = {.counter = 0, .state = INIT_POWER_ON};

/**********************************[4] OPERATION MODE *****************************************/
static OPERATION_t operation = {.counter = 0, .state = OPERATION_IDLE, .type = 9999};
static LCD_OPERATION_SEND_STRING_REQUEST_t String = {.len = 0, .s = NULL_PTR, .remaining = 0};
static LCD_OPERATION_SET_POSITION_REQUEST_t Position={.X=0,.Y=0};
static LCD_OPERATION_SEND_COMMAND_REQUEST_t command={.CMD=0x01}; 
static OPERATION_THREAD_t write_string = {.state = ENABLE_HIGH};
static OPERATION_THREAD_t set_position={.state=ENABLE_HIGH};
static OPERATION_THREAD_t op_send_command={.state=ENABLE_HIGH};
/*-----------------------------------------------------------------------------------------*/
/*                             >> Static Functions <<                                      */
/*-----------------------------------------------------------------------------------------*/

/******************************** [1] GENERAL USED THREADS *********************************/

/**
 * @brief Sets the pins according to the given data or command.
 * 
 * This function sets the pins according to the given data or command. It is used to send either
 * data or command to the LCD.
 * 
 * @param data_or_cmd The data or command to be sent to the LCD.
 */
static void lcd_write_pins_thread(uint8 data_or_cmd)
{
    for (uint8 idx = 0; idx < 8; idx++)
    {
        if ((data_or_cmd >> idx) & 0x01)
        {
            GPIO_SetPinValue(PIN_CONFIG[idx].LCD_PortNum, PIN_CONFIG[idx].LCD_PinNum, PIN_STATE_HIGH);
        }
        else
        {
            GPIO_SetPinValue(PIN_CONFIG[idx].LCD_PortNum, PIN_CONFIG[idx].LCD_PinNum, PIN_STATE_LOW);
        }

    }
}

/**
 * @brief Sends a command to the LCD.
 * 
 * This function sends a command to the LCD.
 * 
 * @param cmd The command to be sent to the LCD.
 */
static void send_command(uint8 cmd)
{
    lcd_write_pins_thread(cmd);
    GPIO_SetPinValue(PIN_CONFIG[LCD_RS_PIN].LCD_PortNum, PIN_CONFIG[LCD_RS_PIN].LCD_PinNum, PIN_STATE_LOW);
}

/**
 * @brief Sends data to the LCD.
 * 
 * This function sends data to the LCD.
 * 
 * @param data The data to be sent to the LCD.
 */
static void send_data(uint8 data)
{
    lcd_write_pins_thread(data);
    GPIO_SetPinValue(PIN_CONFIG[LCD_RS_PIN].LCD_PortNum, PIN_CONFIG[LCD_RS_PIN].LCD_PinNum, PIN_STATE_HIGH);
}

/******************************** [2] INIT PROCESS AND ITS THREADS *************************/

/**
 * @brief Initializes the pins used for LCD communication.
 * 
 * This function initializes the pins used for LCD communication.
 */
static void lcd_pins_init_thread(void)
{
    GPIO_CONFIG_t lcd_pin;
    lcd_pin.MODE = GPIO_MODE_OUT_PP_FL;
    lcd_pin.SPEED = GPIO_SPEED_HIGH;

    for (uint8 idx = 0; idx < USED_LCD_PIN_NUMS; idx++) 
    {
        lcd_pin.PORT = PIN_CONFIG[idx].LCD_PortNum;
        lcd_pin.PIN = PIN_CONFIG[idx].LCD_PinNum;
        GPIO_INIT_PIN(&lcd_pin);
    }    
}

/**
 * @brief Performs the power-on initialization sequence for the LCD.
 * 
 * This function performs the power-on initialization sequence for the LCD.
 */
static void init_power_on_thread(void)
{
    init.counter += UNIT_TIME_PERIOD;
    if (init.counter >= INIT_POWER_ON_TIME)
    {
        init.state = INIT_FUNCTION_SET_P1;
        init.counter = 0;
    }
}

/**
 * @brief Initializes the function set parameters of the LCD.
 * 
 * This function initializes the function set parameters of the LCD.
 */
static void init_function_set_p1_thread(void)
{
    send_command(FUNCTION_SET_CMD);
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_HIGH);
    init.state = INIT_FUNCTION_SET_P2;
}

/**
 * @brief Completes the function set initialization for the LCD.
 * 
 * This function completes the function set initialization for the LCD.
 */
static void init_function_set_p2_thread(void)
{
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_LOW);
    init.state = INIT_DISPLAY_ON_OFF_P1;
}

/**
 * @brief Initializes the display on/off control parameters of the LCD.
 * 
 * This function initializes the display on/off control parameters of the LCD.
 */
static void init_display_on_off_p1_thread(void)
{
    send_command(DISPLAY_ON_OFF_CMD);
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_HIGH);
    init.state = INIT_DISPLAY_ON_OFF_P2;
}

/**
 * @brief Completes the display on/off control initialization for the LCD.
 * 
 * This function completes the display on/off control initialization for the LCD.
 */
static void init_display_on_off_p2_thread(void)
{
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_LOW);
    init.state = INIT_DISPLAY_CLEAR_P1;
}

/**
 * @brief Initializes the display clear control parameters of the LCD.
 * 
 * This function initializes the display clear control parameters of the LCD.
 */
static void init_display_clear_p1_thread(void)
{
    send_command(DISPLAY_CLEAR_CMD);
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_HIGH);
    init.state = INIT_DISPLAY_CLEAR_P2;
}

/**
 * @brief Completes the display clear control initialization for the LCD.
 * 
 * This function completes the display clear control initialization for the LCD.
 */
static void init_display_clear_p2_thread(void)
{
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_LOW);
    init.state = INIT_END;
}

/**
 * @brief Completes the initialization process for the LCD.
 * 
 * This function completes the initialization process for the LCD.
 */
static void init_end_thread()
{
    lcd.mode = OPERATION_MODE;
    lcd.counter = 0;
    init.state = INIT_POWER_ON;
}

/**
 * @brief Executes the initialization process for the LCD.
 * 
 * This function executes the initialization process for the LCD.
 */
static void init_process(void)
{

    switch (init.state)
    {
    case INIT_POWER_ON         : init_power_on_thread();           break;

    case INIT_FUNCTION_SET_P1  : init_function_set_p1_thread();    break;

    case INIT_FUNCTION_SET_P2  : init_function_set_p2_thread();    break;

    case INIT_DISPLAY_ON_OFF_P1: init_display_on_off_p1_thread();  break;

    case INIT_DISPLAY_ON_OFF_P2: init_display_on_off_p2_thread();  break;

    case INIT_DISPLAY_CLEAR_P1 : init_display_clear_p1_thread();   break;
    
    case INIT_DISPLAY_CLEAR_P2 : init_display_clear_p2_thread();   break;
    
    case INIT_END           : init_end_thread();                   break;                            
    
    default:                                                       break;
    }
}

/************************************** OPERATION PROCESS AND ITS THREADS ********************/

/**
 * @brief Sets the position of the cursor on the LCD.
 * 
 * This function sets the position of the cursor on the LCD.
 */
void operation_set_pos_thread(void)
{
    uint8 LOC_DATA=LCD_SetCursor;
    switch (set_position.state)
    {
    case ENABLE_HIGH:
    if(Position.Y==1)
    {
         LOC_DATA=( ( LCD_SetCursor ) + ( Position.X - 1 ) ); 
    }else if(Position.Y==2)
    {
        LOC_DATA=( ( LCD_SetCursor ) + (64) + ( Position.X - 1 ) );
    }
    send_command(LOC_DATA);
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_HIGH);
    set_position.state=ENABLE_LOW;
        break;
    case ENABLE_LOW:
    GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_LOW);
    set_position.state=ENABLE_HIGH;
    operation.state = OPERATION_IDLE;
    Position.X=0;
    Position.Y=0;
        break;
    
    default:
        break;
    }
}

/**
 * @brief Writes a string to the LCD.
 * 
 * This function writes a string to the LCD.
 */
void operation_write_string_thread(void)
{
    if (String.remaining > 0){
        switch (write_string.state)
        {
            case ENABLE_HIGH:
                send_data(String.s[String.len - String.remaining]);
                GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_HIGH);
                write_string.state = ENABLE_LOW;
                break;
            case ENABLE_LOW:
                GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_LOW);
                write_string.state = ENABLE_HIGH;
                String.remaining--;
                break;
            default:
                break;
        }
    
    }
    else
    {
        operation.state = OPERATION_IDLE;
    }
}

/**
 * @brief Clears the screen of the LCD.
 * 
 * This function clears the screen of the LCD.
 */
void operation_command_thread(void)
{
    switch (op_send_command.state)
    {
    case ENABLE_HIGH:
        op_send_command.state=ENABLE_LOW;
        send_command(command.CMD);
        GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_HIGH);
        break;
     case ENABLE_LOW:
        GPIO_SetPinValue(PIN_CONFIG[LCD_ENABLE_PIN].LCD_PortNum, PIN_CONFIG[LCD_ENABLE_PIN].LCD_PinNum, PIN_STATE_LOW);
        op_send_command.state=ENABLE_HIGH;
        operation.state = OPERATION_IDLE;
        command.CMD=0x01;
        break;   
    default:
        break;
    }  
}

/**
 * @brief Executes the operation process for the LCD.
 * 
 * This function executes the operation process for the LCD.
 */
void operation_busy_thread(void)
{
    switch (operation.type)
    {
    case OPERATION_WRITE_STRING:
        operation_write_string_thread();
        break;
    case OPERATION_COMMAND:
        operation_command_thread();
        break;    
    case OPERATION_SET_POSITION:
        operation_set_pos_thread();
        break;
    default:
        break;
    }
}

/**
 * @brief Executes the operation process for the LCD.
 * 
 * This function executes the operation process for the LCD.
 */
static void operation_process(void)
{
    switch (operation.state)
    {
    case OPERATION_IDLE:
        /* DO NOTHING */
        break;
    case OPERATION_BUSY:
        operation_busy_thread();
        break;
    default:
        break;
    }
}

/************************************** LCD MODULE GENERAL RUNNABLE ***************************/

/**
 * @brief Executes the LCD module's main function.
 * 
 * This function executes the LCD module's main function, which includes the initialization process
 * and the operation process.
 */
void LCD_Runnable(void)
{
    switch (lcd.mode)
    {
    case OFF_MODE:
        /* Don't do anything */
        break;
    case INIT_MODE:
        /* Calling the INIT Process */
        init_process();
        break;
    case OPERATION_MODE:
        /* Code */
        operation_process();
        break;
    default:
        break;
    }
}

/******************************** Interface Functions **************************************/

/**
 * @brief Asynchronously initializes the LCD.
 * 
 * This function asynchronously initializes the LCD.
 */
void lcd_init_async(void)
{
    lcd_pins_init_thread();   
    lcd.mode = INIT_MODE;
}

/**
 * @brief Asynchronously sets the position of the cursor on the LCD.
 * 
 * This function asynchronously sets the position of the cursor on the LCD.
 * 
 * @param x_pos The x-coordinate position of the cursor.
 * @param y_pos The y-coordinate position of the cursor.
 * @return LCD_Error_t The error code indicating the success or failure of the operation.
 */
LCD_Error_t lcd_set_position_async(uint8 x_pos, uint8 y_pos)
{
    uint8 loc_ret = LCD_OK;
    if (x_pos>16||y_pos>2||x_pos<1||y_pos<1||lcd.mode!=OPERATION_MODE||operation.state != OPERATION_IDLE)
    {
        loc_ret = LCD_NOK;
    }
    else
    {
        if (operation.state == OPERATION_IDLE)
        {
            operation.state = OPERATION_BUSY;
            operation.type = OPERATION_SET_POSITION;
            Position.X = x_pos;
            Position.Y = y_pos;
        }
    }
    return loc_ret; 
}

/**
 * @brief Asynchronously writes a string to the LCD.
 * 
 * This function asynchronously writes a string to the LCD.
 * 
 * @param string The string to be written to the LCD.
 * @param size The size of the string.
 * @return LCD_Error_t The error code indicating the success or failure of the operation.
 */
LCD_Error_t lcd_write_string_async(const char* string, uint8 size)
{
    uint8 loc_ret = LCD_OK;
    if (string == NULL_PTR||lcd.mode!=OPERATION_MODE||operation.state != OPERATION_IDLE)
    {
        loc_ret = LCD_NOK;
    }
    else
    {

            operation.state = OPERATION_BUSY;
            operation.type = OPERATION_WRITE_STRING;
            String.len = size;
            String.s = string;
            String.remaining = size;
    }
    return loc_ret;  
}

/**
 * @brief Sends a command asynchronously to the LCD display.
 * 
 * @param CMD The command to be sent.
 * @return LCD_Error_t Returns an error code indicating the success or failure of the operation.
 *                    Possible error codes include:
 *                        - LCD_OK: Operation completed successfully.
 *                        - LCD_NOK: Operation failed.
 * 
 * This function sends a command to the LCD display asynchronously. The CMD parameter specifies
 * the command to be sent. The function returns an error code indicating the success or failure
 * of the operation.
 */
LCD_Error_t lcd_send_command_async(uint8 cmd)
{
    uint8 loc_ret=LCD_OK;
    if (lcd.mode!=OPERATION_MODE||operation.state != OPERATION_IDLE)
    {
        loc_ret = LCD_NOK;
    }else
    {
        operation.state=OPERATION_BUSY;
        operation.type=OPERATION_COMMAND;
        command.CMD=cmd;
    }
    return loc_ret;
}
