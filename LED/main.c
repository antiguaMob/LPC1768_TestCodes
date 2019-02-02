#include "LPC17xx.h"

#define FIO1DIR (*(uint32_t*)0x2009C020)
#define FIO1SET (*(uint32_t*)0x2009C038)
#define FIO1CLR (*(uint32_t*)0x2009C03C)

#define LED	29

void led_init(void);
void led_on(void);
void led_off(void);

int main()
{
	SystemInit();
	led_init();
	while(1)
	{
		led_on();
		SW_DELAY_MS(1000);
		led_off();
		SW_DELAY_MS(1000);
	}
}

void led_init(void)
{
	//make P1.29 as output
	FIO1DIR |= BV(LED);
	led_off();
}

void led_on(void)
{
	//make P1.29 = 1
	FIO1SET |= BV(LED);
}

void led_off(void)
{
	//make P1.29 = 0
	FIO1CLR = BV(LED);
}


