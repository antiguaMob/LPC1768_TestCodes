#include "timer.h"


void timer0_init()
{
	//disable counter and reset timer
	LPC_TIM0->TCR = (1<<TCR_RST);
	//set mode as timer mode --CTCR
	LPC_TIM0->CTCR = CTCR_TIMER_MODE;
	//set prescaler
	LPC_TIM0->PR = PR_VAL-1;
}

void timer0_delay_ms(uint32_t sec)
{
	uint32_t count;
	//set MR0 -- Max count
	count = (PCLCK/1000)*(sec/PR_VAL);
	LPC_TIM0->MR0 = count-1;
	//set MCR--Reset and interrupt on MR0 match
	LPC_TIM0->MCR |= ((1<<MCR_MR0R)|(1<<MCR_MR0I));
	//enable timer
	LPC_TIM0->TCR = (1<<TCR_EN);
	//wait for MR0 interrupt flag
	while(!(LPC_TIM0->IR & (1<<IR_MR0)));
	//clear MR0 interrupt flag
	LPC_TIM0->IR = (1<<IR_MR0);

}
