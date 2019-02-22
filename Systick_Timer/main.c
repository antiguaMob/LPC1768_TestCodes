#include <stdio.h>
#include "LPC17xx.h"
#include "lcd.h"
#include "systick.h"

int main()
{
	char str[18];
	int cnt=0;
	SystemInit();
	systick_init(HZ);
	lcd_init();
	lcd_puts(LCD_LINE1, "SysTick Demo");

	while(1)
	{
		sprintf(str, "Count = %d  ",++cnt);
		lcd_puts(LCD_LINE2, str);
		systick_delay(jiffies + HZ);
	}

	return 0;
}


