#include "i2c.h"
#include "uart.h"

void i2c_init()
{
	//enable i2c0 pins
	LPC_PINCON->PINMODE1 &= ~((1<<22)|(1<<23)|(1<<24)|(1<<25));
	LPC_PINCON->PINMODE1 |= (1<<22)|(1<<24);
	// setup prescaler
	I2_SCLL= SCLL_VAL;
	I2_SCLH= SCLH_VAL;
	//clear all flags
	LPC_I2C0-> I2CONCLR |= (1<<CON_AA)|(1<<CON_SIF)|(1<<CON_START);(1<<CON_STOP)|(1<<CON_EN);
	//enable i2c
	LPC_I2C0-> I2CONSET |= (1<<CON_EN);
}

void i2c_start()
{
	uart_putstring("Sending START! \r\n");
	//clear SI flag
	I2_CONCLR = (1<<CON_AA)|(1<<CON_SIF)|(1<<CON_START);
	//send start signal
	I2CONSET = (1<<CON_EN)|(1<<CON_START);
	//wait for Transmission
	while((I2_CONSET & (1<<CON_SIF))==0);
	uart_putstring("Sent Start \r\n");
}

void i2c_rep_start()
{
	i2c_start();
}

void i2c_stop()
{
	//clear SI flag
	I2_CONCLR = (1<<CON_SIF);
	//send stop signal
	I2_CONSET = (1<<CON_EN)|(1<<CON_AA)|(1<<CON_STOP);
}

void i2c_send_addr(uint8_t addr)
{
	uart_putstring("Sending Address \r\n");
	//send address
	I2_DAT = addr;
	//clear SI flag
	I2_CONCLR = (1<<CON_AA)|(1<<CON_SIF);
	//set i2c en
	I2_CONSET = (1<<CON_EN);
	//wait for tx
	while((I2_CONSET & (1<<CON_SIF))==0);
	uart_putstring("Sent Address \n\r");
}

void i2c_send_data(uint8_t data)
{
	//send data
	I2_DAT = data;
	//clear SI flag
	I2_CONCLR = (1<<CON_SIF)|(1<<CON_START);
	//set i2c enable
	I2_CONSET = (1<<CON_EN);
	//wait for Tx
	while((I2_CONSET & (1<<CON_SIF))==0);

}

uint8_t i2c_recv_ack()
{
	uint8_t data;
		// clear SI flag 
		I2_CONCLR = (1<<CON_SIF);
		// set i2c en
		I2_CONSET = (1<<CON_EN) | (1<<CON_ACK);	
		// wait for receive
		while((I2_CONSET & (1<<CON_SIF))==0);	
		// recv data
		data = I2_DAT;
		return data;
}

uint8_t i2c_recv_nack()
{
	uint8_t data;
	// clear SI flag 
 	I2_CONCLR = (1<<CON_SIF) | (1<<CON_ACK);	
	// set i2c en
	I2_CONSET = (1<<CON_EN);	
	// wait for receive
	while((I2_CONSET & (1<<CON_SIF))==0);	
	// recv data
	data = I2_DAT;
	return data;
}
