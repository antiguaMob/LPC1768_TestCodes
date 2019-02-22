#include "systick.h"


volatile uint32_t jiffies=0;

void systick_init(uint32_t hz)
{
	uint32_t count;
	//disable systick
	SysTick->CTRL =0;
	//calc count
	count= CCLK /hz;
	//init RELOAD value
	SysTick->LOAD = count -1;
	//enable systick and enable tick intr
	SysTick->CTRL = (1<<STCTRL_CLKSRC)|(1<<STCTRL_CLKEN)|(1<<STCTRL_INTREN);

}

void SysTick_Handler()
{ 
	++jiffies;
	//clear systick intr
	(void)SysTick->CTRL;
}

void systick_delay(uint32_t till_jiffies)
{
	while(jiffies<till_jiffies);

}
