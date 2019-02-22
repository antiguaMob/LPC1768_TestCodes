#include<stdio.h>
#include "LPC17xx.h"
#include "lcd.h"
#include "timer.h"
#include "buzzer.h"

extern volatile int t0_flag;

int main()
{
	int count=0;
	char str[18];
	SystemInit();
	timer0_init(1000);
	lcd_init();
	buzzer_init();
	lcd_puts(LCD_LINE1, "Blah Blah");
	while (1)
	{
		while(t0_flag == 0);
		t0_flag = 0;
		sprintf(str, "Count = %d  ",count++);
		lcd_puts(LCD_LINE2, str);

	}

}
