#include "spi.h"

void spi_init()
{
	//enable SCLK, MOSI, MISO using PINSEL
	LPC_PINCON->PINSEL0 |= (1<<31)|(1<<30);
	LPC_PINCON->PINSEL1 |= (1<<5)|(1<<4)|(1<<3)|(1<<2);

	//keep SSEL as GPIO & make it as output pin
	LPC_PINCON->PINSEL1 &= ~((1<<1)|(1<<0));
	LPC_GPIO0-> FIODIR = (1<<SSEL
	);

	//set SPI bit rate -- SPCCR
	LPC_SPI->SPCCR = CCR_VAL;
	
	//set SPI config -- SPCR
	LPC_SPI->SPCR= (1<<SPCR_CPHA)|(1<<SPCR_CPOL)|(1<<SPCR_MSTR)|(1<<SPCR_LSBF);
	
	//disable slave
	spi_slave_ss1();
	
}

uint8_t spi_transfer(uint8_t val)
{
	uint8_t ret_val;

	//enable slave
	spi_slave_ss0();

	//write data to SPDR
	LPC_SPI->SPDR = val;

	//wait for SPIF
	while(!(LPC_SPI->SPSR & (1<<SPSR_SPIF)));

	//read SPSR reg
	ret_val = LPC_SPI->SPDR;

	//disable slave
	spi_slave_ss1();

	return ret_val;
}

//enable slave
void spi_slave_ss0()
{
	LPC_GPIO0->FIOCLR = (1<<SSEL);
}

//disable slave
void spi_slave_ss1()
{
	LPC_GPIO0->FIOSET |= (1<<SSEL);
}
