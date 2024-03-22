#define APP2
#ifdef APP2

#include "../../include/02-HAL/LED/LED.h"
#include "../../include/00-LIB/STD.h"
#include "../../include/03-APP/StateMachine.h"

/**
 * Traffic light state machine application.
 * 
 * This function implements a state machine for controlling traffic lights.
 * It manages the transition of traffic light colors (RED, YELLOW, GREEN) based on predefined time periods.
 * The sequence of state transitions is as follows:
 *   RED -> YELLOW -> GREEN -> YELLOW -> RED -> ...
 * 
 * State Transition Graph:
 * 
 *           RED                 YELLOW                GREEN
 *            |                     |                     |
 *            v                     v                     v
 *       [Set RED LED ON]    [Set YELLOW LED ON]   [Set GREEN LED ON]
 *            |                     |                     |
 *            |---- RED_TIME_PERIOD ----->|                 |
 *            |                     |<---- YELLOW_TIME_PERIOD -----|
 *            |<------- GREEN_TIME_PERIOD --------|          |
 *            |                     |                     |
 *            v                     v                     v
 *         YELLOW               GREEN                 YELLOW
 * 
 * Function Flow:
 * - It updates the state of the traffic light based on the current state and elapsed time.
 * - Sets the appropriate LEDs to indicate the current state of the traffic light.
 * - Handles the transition between different states according to the specified time periods.
 * 
 * @note This function is intended to be called periodically by a scheduler or main loop.
 */



#define RED 0
#define YELLOW 1
#define GREEN 2
#define UNIT_TIME_PERIOD 100
#define RED_TIME_PERIOD 3000
#define YELLOW_TIME_PERIOD 4000
#define GREEN_TIME_PERIOD 2000

void TrafficLight_Init()
{
    LED_INIT();
}


void TrafficLight_Runnable(void)
{
    static uint8  Current_State=RED;
    static uint8  Prev_State;
    static uint32 Counter=0;

    Counter+=UNIT_TIME_PERIOD;
    switch (Current_State)
    {
    case RED:
        LED_SetStatus(TL_RED,LED_ON);
        LED_SetStatus(TL_YELLOW,LED_OFF);
        LED_SetStatus(TL_GREEN,LED_OFF);
        if(Counter==RED_TIME_PERIOD)
        {
            Counter=0;
            Current_State=YELLOW;
            Prev_State=RED;
        }
        break;
     case YELLOW:
        LED_SetStatus(TL_RED,LED_OFF);
        LED_SetStatus(TL_YELLOW,LED_ON);
        LED_SetStatus(TL_GREEN,LED_OFF);
        if(Counter==YELLOW_TIME_PERIOD)
        {
            Counter=0;
            if (Prev_State==RED)
            {
                Current_State=GREEN;
            }
            else if(Prev_State==GREEN)
            {
                Current_State=RED;
            }
            Prev_State=YELLOW;
            
        }
        break;       
    case GREEN:
        LED_SetStatus(TL_RED,LED_OFF);
        LED_SetStatus(TL_YELLOW,LED_OFF);
        LED_SetStatus(TL_GREEN,LED_ON);
        if(Counter==GREEN_TIME_PERIOD)
        {
            Counter=0;
            Current_State=YELLOW;
            Prev_State=GREEN;
        }
        break;    
    default:
        break;
    }
}



#endif