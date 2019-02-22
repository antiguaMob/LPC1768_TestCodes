#include "timer.h"
#include "buzzer.h"

volatile int t0_flag=1;

void timer0_init(uint32_t sec)
{
	uint32_t count;
	//disable counter and reset timer
	LPC_TIM0->TCR = (1<<TCR_RST);
	//set mode as timer mode --CTCR
	LPC_TIM0->CTCR = CTCR_TIMER_MODE;
	//set prescaler
	LPC_TIM0->PR = PR_VAL-1;

	//set MR0 -- Max count
	count = (PCLK/1000)*(sec/PR_VAL);
	LPC_TIM0->MR0 = count-1;
	//set MCR--Reset and interrupt on MR0 match
	LPC_TIM0->MCR |= ((1<<MCR_MR0R)|(1<<MCR_MR0I));
	//enable timer interrupt into NVIC
	NVIC_EnableIRQ(TIMER0_IRQn);
	//enable timer
	LPC_TIM0->TCR = (1<<TCR_EN);
}

void timer0_delay_ms(uint32_t ms)
{
		uint32_t count;
		// set MR0 -- max count
		count = ( PCLK / 1000) * ms / PR_VAL;
		LPC_TIM0->MR0 = count - 1;
		// set MCR -- reset & interrupt on MR0 match
		LPC_TIM0->MCR |= (BV(MCR_MR0I) | BV(MCR_MR0R));
		// enable timer
		LPC_TIM0->TCR = BV(TCR_EN);	
		// wait for MR0 interrupt flag
		while(!(LPC_TIM0->IR & BV(IR_MR0)));
		//clear MR0 interrupt flag
		LPC_TIM0->IR |= BV(IR_MR0);
			
}


void TIMER0_IRQHandler()
{
	t0_flag=1;
	//clear MR0 interrupt flag
	LPC_TIM0->IR = (1<<IR_MR0);
}
