#include "eint.h"
#include "buzzer.h"

void eint_init(void)
{
	//make P2.12 as EINT2 ----> PINSEL4[25:24]=01
	LPC_PINCON->PINSEL4 &= ~((1<<25)|(1<<24));
	LPC_PINCON->PINSEL4 |= (1<<24);

	//config EINT2 as Falling Edge ---->EXTMODE & EXTPLAR
	LPC_SC->EXTMODE |= (1<<EINT2);
	LPC_SC->EXTPOLAR &= ~(1<<EINT2);

	//enable EINT2----> EINT
	LPC_SC->EXTINT |= (1<<EINT2);

	//enable interrupt into NVIC
	NVIC_EnableIRQ(EINT2_IRQn);

}
void EINT2_IRQHandler(void)
{
	//action
	buzzer_beep();
	//clear the interrupt --->EXTINT
	LPC_SC->EXTINT |= (1<<EINT2);
}
