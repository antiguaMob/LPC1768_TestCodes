#include "buzzer.h"

void buzzer_init(void)
{
	BUZZER_GPIO->FIODIR |= BV(BUZZER);
	buzzer_off();
}

void buzzer_on(void)
{
	BUZZER_GPIO->FIOCLR = BV(BUZZER);
}

void buzzer_off(void)
{
	BUZZER_GPIO->FIOSET |= BV(BUZZER);
}

void buzzer_beep(void)
{
	buzzer_on();
	SW_DELAY_MS(2000);
	buzzer_off();
}

