#include "LPC17xx.h"
#include "spi.h"

int main()
{
	uint8_t data= 0x33;
	SystemInit();
	spi_init();
	while (1)
	{
		spi_transfer(data);
		data = ~data;
		SW_DELAY_MS(1000);
	}


	return 0;
}
