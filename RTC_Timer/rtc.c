#include "rtc.h"


volatile int rtc_flag=0;

void rtc_init(rtc_time_t *t)
{
	//clock dsiable and reset
	LPC_RTC-> CCR &= ~(1<<CCR_EN);
	LPC_RTC-> CCR |= (1<<CCR_RST);

	//init time and day regrs
	LPC_RTC->SEC = t->sec;
	LPC_RTC->MIN = t->min;
	LPC_RTC->HOUR = t->hour;
	LPC_RTC->DOM = t->dom;
	LPC_RTC->MONTH = t->mon;
	LPC_RTC->YEAR = t->year;
	LPC_RTC->DOW = t->dow;
	LPC_RTC->DOY = t->doy;


	//enable secs incr intr
	LPC_RTC->CIIR |= (1<<CIIR_IMSEC);

	//enable rtc intr in NVIC
	NVIC_EnableIRQ(RTC_IRQn);
	
	//clock enable
	LPC_RTC-> CCR |= (1<<CCR_EN);
	
}

void rtc_get(rtc_time_t *t)
{
	//get time and day regrs
	t->sec = LPC_RTC->SEC;
	t->min = LPC_RTC->MIN;
	t->hour = LPC_RTC->HOUR;
	t->dom = LPC_RTC->DOM;
	t->dow = LPC_RTC->DOW;
	t->doy = LPC_RTC->DOY;
	t->mon = LPC_RTC->MONTH;
	t->year = LPC_RTC->YEAR;
}

void RTC_IRQHandler()
{

	rtc_flag=1;
	//clear timer intr
	if(LPC_RTC->ILR & (1<<ILR_CIF))
		LPC_RTC->ILR |= (1<<ILR_CIF);
	
}
