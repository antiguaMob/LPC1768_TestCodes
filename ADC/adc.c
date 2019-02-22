#include "adc.h"

void adc_init()
{
	//enable power for ADC
	LPC_SC->PCONP |= (1<<PCONP_PCDAC);
	//enable AD.2 function-- PINSEL1[19:18]=01 for P0.25
	LPC_PINCON->PINSEL1 &= ~(BV(19) | BV(18));
	LPC_PINCON->PINSEL1 |= BV(18);
	//set clkdiv, channel number and power up
	LPC_ADC-> ADCR = ((CLKDIV-1)<<ADCR_CLKDIV)|(1<<ADCR_CHN2);
	LPC_ADC-> ADCR |= (1<<ADCR_PDN);

}

uint16_t adc_read()
{
	uint32_t dr;
	//start conv
	LPC_ADC->ADCR |= (1<<ADCR_START);
	//wait for result
	do{
		dr= LPC_ADC->ADGDR;
	}while (!(dr&(1<<ADDR_DONE)));
	//extract and return result
	return	((dr>>ADDR_RESULT)& RESULT_MASK);
}
