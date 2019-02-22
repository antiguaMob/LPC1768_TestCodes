#include "uart.h"
void uart_init(uint32_t baud)
{

	uint16_t dl;
	
	//enable uart3 --> PINSEL0[1:0] &PINSEL0[3:2]
	LPC_PINCON->PINSEL0 &= ~((1<<3)|(1<<2)|(1<<1)|(1<<0));
	LPC_PINCON->PINSEL0 = (1<<3)|(1<<1);

	//config LCR and enable DLAB
	LPC_UART3->LCR |= (1<<LCR_WL0)|(1<<LCR_WL1)|(1<<LCR_DLAB);
	
	//calculate Baud Rate
	dl= (PCLK)/(baud<<4); //(PCLK>>4)/baud

	//assign Baud Rate
	LPC_UART3->DLL = dl & 0x00FF;
	LPC_UART3->DLM= dl>>8;
	
	//Disable DLAB --- LCR
	LPC_UART3->LCR &= ~(1<<LCR_DLAB);

	//enable FIFO
	LPC_UART3->FCR |= (1<<FCR_EN);
}
//Enter text via UART char by char
void uart_putch(uint8_t ch)
{
	//wait for prev char tx
	while(!(LPC_UART3->LSR & (1<<LSR_THRE
		)));

	//add char into tx reg
	LPC_UART3->THR = ch;
	
}
//Receive text via UART char by char
uint8_t uart_getch()
{
	//wait for char to receive
	while(!(LPC_UART3->LSR & (1<<LSR_RDR)));
	
	//rx char
	return LPC_UART3->RBR;
}

//Enter text via UART string
void uart_puts(char str[])
{
	int i;
	for(i=0; str[i]!='\0';i++)
		uart_putch(str[i]);
}

//Receive text via UART as a string
void uart_gets(char str[])
{
	int i=0;
	char ch;
	do
	{
		ch=uart_getch();
		str[i++]=ch;
	}while (ch!='\r');

	str[i++]= '\n';
	str[i] = '\0';

}
