
#include <string.h>
#include "uart.h"

int main()
{
	SystemInit();
	uart_init(9600);
	uart_puts("HeLLO DESD  \r \n");
	uart_puts("Borem korun  \r \n");
	while (1);
	return 0;
}
