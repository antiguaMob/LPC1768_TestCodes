#ifndef __ADC_H
#define __ADC_H

#include "LPC17xx.h"

#define PCONP_PCDAC		12
#define PCLK			18000000UL
#define CLKDIV			3
#define RESULT_MASK		0xFFF // 12 bits successive approx ADC

#define ADCR_CHN2		2
#define ADCR_CLKDIV		8
#define ADCR_BURST		16
#define ADCR_PDN		21
#define ADCR_START		24

#define ADDR_RESULT		4
#define ADDR_OVERRUN	30
#define ADDR_DONE		31

void adc_init();
uint16_t adc_read();



#endif
