#include "uart.h"

static char *tx_string= "";
static int tx_index;
static volatile int tx_flag=1;

void uart_init(uint32_t baud)
{
	uint16_t dl;

	//enable UART3 RX and TX pins
	//PINSEL0[1:0]=10(Tx), PINSEL0[3:2]=10(Rx)
	LPC_PINCON->PINSEL0 &= ~((1<<3)|(1<<2)|(1<<1)|(1<<0));
	LPC_PINCON->PINSEL0 |= (1<<3)|(1<<1);


	//config FCR--- enable FF
	LPC_UART3->FCR |= (1<<FCR_EN);
	
	//Config LCR -- 8bit, no parity,1 stop bits, DLAB-->accessible
	LPC_UART3-> LCR |= (1<<LCR_WL0)|(1<<LCR_WL1)|(1<<LCR_DLAB);
	LPC_UART3-> LCR &= ~((1<<LCR_STOP)|(1<<LCR_PARITY));
	

	//calculate div latch value -dl=(PCLK/16)/baud
	dl= (PCLK>>4)/baud;
	
	//set divisor latch (DLM & DLL)
	LPC_UART3->DLL = 0x00FF & dl;
	LPC_UART3->DLM = dl>>8;

	//LCR --DLAB =0 (not accessible)
	LPC_UART3-> LCR &= ~(1<<LCR_DLAB);
	//enable Tx interrupt in UART & NVIC
	LPC_UART3 -> IER = (1<<IER_THRE);
	NVIC_EnableIRQ(UART3_IRQn);

}

void uart_putch(uint8_t ch)
{
}

uint8_t uart_getch(void)
{
	
	
	//wait while 8-bits of data is received 
	while(!(LPC_UART3-> LSR & (1<<LSR_RDR)));

	//read & return char
	return LPC_UART3->RBR;

}

void uart_puts(char str[])
{
	//wait for last string
	while(tx_flag==0);

	//reset string
	tx_string = str;
	tx_index =0;
	tx_flag =0;

	//send first char
	LPC_UART3->THR = tx_string[tx_index++];

}

void uart_gets(char str[])
{
	int i=0;
	char ch;
do {
		ch=uart_getch();
		str[i++]=ch;
	}while (ch!= '\r');
	str[i++]= '\n';
	str[i]= '\0';
}

void UART3_IRQHandler(void)
{
	uint32_t iir,iid;

while(!((iir=LPC_UART3->IIR) & (1<<IIR_PEND)));

	iid= (iir>>1) & 7;
	if(iid==IIR_ID_THRE)
	{
		//send next char
		if(tx_string[tx_index]!='\0')
			LPC_UART3->THR = tx_string[tx_index++];
		else //string is done
			tx_flag=1;
	}

	if(iid== IIR_ID_RDA)
	{
		//handle RDA intr
	}


}


