#include "LPC17xx.h"
#include "buzzer.h"

int main()
{
	int i;
	SystemInit();
	buzzer_init();
	for(i=0; i<3; i++)
	{
		buzzer_beep();
		SW_DELAY_MS(2000);
	}
	while(1);
}

