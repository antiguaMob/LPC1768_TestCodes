#include<stdio.h>
#include "LPC17xx.h"
#include "lcd.h"
#include "timer.h"
#include "buzzer.h"

int main()
{
	int count=0;
	char str[18];
	SystemInit();
	timer0_init();
	lcd_init();
	buzzer_init();
	lcd_puts(LCD_LINE1, "Blah Blah");
	while (1)
	{
		sprintf(str, "Count = %d  ",count++);
		lcd_puts(LCD_LINE2, str);
		buzzer_beep();
		timer0_delay_ms(1000);


	}

}
