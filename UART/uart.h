#ifndef __UART_H
#define __UART_H

#include "LPC17xx.h"

#define LCR_WL0		0
#define LCR_WL1		1
#define LCR_STOP	2
#define LCR_PARITY	3
#define LCR_DLAB	7

#define LSR_RDR		0
#define LSR_THRE	5

#define FCR_EN			0
#define FCR_RX_FF_RST	1
#define FCR_TX_FF_RST	2
#define FCR_RX_FF_TRIG0	6
#define FCR_RX_FF_TRIG1	7

#define PCLK	18000000UL

void uart_init(uint32_t baud);
void uart_putch(uint8_t ch);
uint8_t uart_getch();
void uart_puts(char str[]);
void uart_gets(char str[]);


#endif
