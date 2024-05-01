#include "MCAL/GPIO/GPIO.h"
#include "HAL/LED/LED.h"

extern const LED_strLEDConfig_t LED_arrOfStrLEDs[NUM_OF_LEDS];

GPIO_Error_t LED_Init ()
{
	GPIO_Error_t LOC_Status = GPIO_NOK;
	GPIO_Pin_t Led;

	Led.Pin_Mode  = GPIO_MODE_OP_PP;
	Led.Pin_Speed = GPIO_SPEED_HIGH;

	for ( U8 idx = 0 ; idx < NUM_OF_LEDS ; idx++ )
	{
		Led.Pin_num         = LED_arrOfStrLEDs[idx].Pin;
		Led.Port            = LED_arrOfStrLEDs[idx].Port;
		LOC_Status          = GPIO_Init (&Led);

		if (LOC_Status == GPIO_OK)
		{
			LOC_Status = GPIO_Set_PinValue(LED_arrOfStrLEDs[idx].Port , LED_arrOfStrLEDs[idx].Pin  , LED_arrOfStrLEDs[idx].Connection ^ LED_arrOfStrLEDs[idx].Init_Value);
		}
	}
	return LOC_Status;
}

GPIO_Error_t LED_SetStatus ( LEDs_t LED_NAME , U32 LED_STATUS )
{
	GPIO_Error_t LOC_Status = GPIO_NOK;

	LOC_Status = GPIO_Set_PinValue(LED_arrOfStrLEDs[LED_NAME].Port , LED_arrOfStrLEDs[LED_NAME].Pin  , LED_arrOfStrLEDs[LED_NAME].Connection ^ LED_STATUS);

	return LOC_Status;
};