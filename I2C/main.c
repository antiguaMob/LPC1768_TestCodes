#include "LPC17xx.h"
#include "uart.h"
#include "eeprom.h"
#include <stdio.h>

// EEPROM --> P0.28 [SCL0] & P0.27 [SDA0] --> I2C0
char string[32];
int main()
{
	int choice;
	SystemInit();
	uart_init(9600);
	uart_putstring("I2C EEPROM DEMO!\r\n");
	eeprom_init();
	while(1)
	{
		uart_putstring("\r\n1. Write EEPROM\r\n2. Read EEPROM\r\nEnter Choice : \r\n");
		uart_getstring(string);
		sscanf(string, "%d", &choice);
		switch(choice)
		{
		case 1:
			uart_putstring("Enter string to write (max 32 chars) : \r\n");
			uart_getstring(string);
			uart_putstring("Data writing to EEPROM\r\n");
			eeprom_write(0x0000, (uint8_t*)string, sizeof(string));
			uart_putstring("Data written to EEPROM\r\n");
			break;
		case 2:
			uart_putstring("String reading from EEPROM : \r\n");
			eeprom_read(0x0000, (uint8_t*)string, sizeof(string));
			uart_putstring("String read from EEPROM : \r\n");
			uart_putstring(string);
			uart_putstring("\r\n");
			break;
		default:
			sprintf(string, "Invalid Choice : %d\r\n", choice);
			uart_putstring(string);
		}
	}
}

