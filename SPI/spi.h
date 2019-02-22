#ifndef __SPI_H
#define __SPI_H

#include "LPC17xx.h"

#define PCLK (SystemCoreClock>>2)

#define SPCR_DL		2
#define SPCR_CPHA	3
#define SPCR_CPOL	4
#define SPCR_MSTR	5
#define SPCR_LSBF	6
#define SPCR_SPIE	7

#define SPSR_ABRT	3
#define SPSR_MODF	4
#define SPSR_RVOR	5
#define SPSR_WCOL	6
#define SPSR_SPIF	7

#define CCR_VAL		8 //=PCLK/SPCCR

#define SSEL		16 //port P0.16

void spi_init();
uint8_t spi_transfer(uint8_t val);
void spi_slave_ss0();
void spi_slave_ss1();

#endif
