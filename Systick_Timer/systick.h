#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "LPC17xx.h"

#define STCTRL_CLKEN 	0
#define STCTRL_INTREN 	1
#define STCTRL_CLKSRC	2
#define STCTRL_INTFLAG 	16

//no of ticks intr generated in one sec
//tick interval = 1/hz sec
#define HZ 		10

#define CCLK	SystemCoreClock

extern volatile uint32_t jiffies;

void systick_init(uint32_t hz);
void SysTick_Handler();

void systick_delay(uint32_t till_jiffies);



#endif
