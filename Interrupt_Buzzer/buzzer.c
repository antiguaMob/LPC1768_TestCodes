#include "buzzer.h"

void buzzer_init(void)
{
	//BUZZER_GPIO->FIODIR |= BV(BUZZER);
	SRAM_BB_ALIAS(&BUZZER_GPIO->FIODIR, BUZZER) = 1;
	buzzer_off();
}

void buzzer_on(void)
{
	//BUZZER_GPIO->FIOCLR = BV(BUZZER);
	SRAM_BB_ALIAS(&BUZZER_GPIO->FIOCLR, BUZZER) = 1;
}

void buzzer_off(void)
{
	//BUZZER_GPIO->FIOSET |= BV(BUZZER);
	SRAM_BB_ALIAS(&BUZZER_GPIO->FIOSET, BUZZER) = 1;
}

void buzzer_beep(void)
{
	buzzer_on();
	SW_DELAY_MS(2000);
	buzzer_off();
}

