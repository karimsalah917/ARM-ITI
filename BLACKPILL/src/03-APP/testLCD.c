#include "../../include/02-HAL/LCD/LCD.h"


void Test_LCD_APP_Runnable(void)
{
	static uint8 loc_variable=0;
	switch (loc_variable)
	{
	case 0:
	lcd_set_position_async(2,2);

	loc_variable=1;
		break;
	case 1:
	lcd_write_string_async("Hassan Eladawy",14);
	loc_variable=2;
		break;
	case 2:
	lcd_send_command_async(LCD_SHIFTING_RIGHT);
		break;
	default:
		break;
	}



}
