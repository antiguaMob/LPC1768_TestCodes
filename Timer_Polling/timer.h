#ifndef __TIMER_H
#define __TIMER_H

#include "LPC17xx.h"

#define IR_MR0 	0
#define IR_MR1 	1
#define IR_MR2 	2
#define IR_MR3 	3	
#define IR_CR0 	4
#define IR_CR1 	5

#define TCR_EN 	0
#define TCR_RST 1 

#define CTCR_TIMER_MODE 0x00000000

#define MCR_MR0I	0
#define MCR_MR0R	1
#define MCR_MR0S	2

#define MCR_MR1I	3
#define MCR_MR1R	4
#define MCR_MR1S	5

#define MCR_MR2I	6
#define MCR_MR2R	7
#define MCR_MR2S	8

#define MCR_MR3I	9
#define MCR_MR3R	10
#define MCR_MR3S	11

#define PR_VAL		18
#define PCLCK		18000000UL

void timer0_init();
void timer0_delay_ms(uint32_t sec);


#endif
