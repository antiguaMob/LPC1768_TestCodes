#ifndef __BUZZER_H
#define __BUZZER_H

#include "LPC17xx.h"

#define BUZZER_GPIO		LPC_GPIO2
#define	BUZZER			11

void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);
void buzzer_beep(void);

#define SRAM_BB_START 0x20000000
#define SRAM_BBALS_START 0x22000000

#define SRAM_BB_ALIAS(bbrgr,bit) (*(uint32_t*)(SRAM_BBALS_START+((((uint32_t)bbrgr-SRAM_BB_START)<<5)+(bit<<2))))

#endif


