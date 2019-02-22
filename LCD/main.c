#include<stdio.h>
#include "LPC17xx.h"
#include "lcd.h"

int main()
{
	SystemInit();
	lcd_init();
	lcd_puts(LCD_LINE1, "Lets Begin Coding");
	lcd_puts(LCD_LINE2, "Go go go!!");
	return 0;
}
