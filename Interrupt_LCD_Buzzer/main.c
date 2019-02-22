#include<stdio.h>
#include "LPC17xx.h"
#include "lcd.h"

int main()
{
	SystemInit();
	lcd_init();
	
	lcd_puts(LCD_LINE1, "Test Test");
	lcd_puts(LCD_LINE2, "SUCCESSFULL!!!!");
	
	while (1)
	{
		lcd_send_byte(LCD_CMD,LCD_LEFTSHIFT);
		SW_DELAY_MS(1000);
	}
	
	return 0;
}
