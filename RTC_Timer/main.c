#include<stdio.h>
#include "LPC17xx.h"
#include "lcd.h"
#include "rtc.h"


int main()
{
	char str[18];
	char* week_days[]= {"Sun", "Mon","Tue","Wed","Thu","Fri","Sat"};
	rtc_time_t tm= { .hour=23, .min=59, .sec=40,
						.dom=31, .mon=12, .year=2019,
						.dow=2, .doy=365
					};

	SystemInit();
	rtc_init(&tm);
	lcd_init();
	lcd_puts(LCD_LINE1, "HAPPY NEW YEAR");

	while(1)
	{
		while(rtc_flag==0);
		rtc_flag=0;
		rtc_get(&tm);
		sprintf(str," %02d - %02d - %04d %s ",tm.dom,tm.mon,tm.year,week_days[tm.dow]);
		lcd_puts(LCD_LINE1,str);


		sprintf(str," %02d:%02d:%02d %s ",tm.hour,tm.min,tm.sec);

	}
	return 0;
}
