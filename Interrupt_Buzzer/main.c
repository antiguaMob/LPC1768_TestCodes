#include "LPC17xx.h"
#include "buzzer.h"
#include "eint.h"

int main()
{
	SystemInit();
	buzzer_init();
	eint_init();
	buzzer_beep();
	while(1);
}

