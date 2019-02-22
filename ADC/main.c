#include <stdio.h>
#include "LPC17xx.h"
#include "lcd.h"
#include "adc.h"

int main ()
{
	uint32_t res;
	char str[18];
	SystemInit();
	lcd_init();
	adc_init();

	lcd_puts(LCD_LINE1, "FOKTI EK NO");
	while (1)
	{
		res= adc_read();
		sprintf(str, "Res : %04lu ",res);
		lcd_puts(LCD_LINE2,str);
		SW_DELAY_MS(200);
	}


	return 0;
}
