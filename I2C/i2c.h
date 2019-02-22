#ifndef __I2C_H
#define __I2C_H

#include "LPC17xx.h"

#define I2_DAT		LPC_I2C0->I2DAT
#define I2_CONSET	LPC_I2C0->I2CONSET
#define I2_CONCLR	LPC_I2C0->I2CONCLR 
#define I2_STATUS	((LPC_I2C0->I2STAT >>3) & 0x1F)   //bit [7:3]
#define I2_SCLL		LPC_I2C0->I2SCLL
#define I2_SCLH		LPC_I2C0->I2SCLH

enum i2con_bits
{
	CON_AA=2,
	CON_SIF,
	CON_STOP,
	CON_START,
	CON_EN
};

#define PCLK		18000000UL
#define SCLL_VAL	90
#define SCLH_VAL	90

void i2c_init();
void i2c_start();
void i2c_rep_start();
void i2c_stop();
void i2c_send_addr(uint8_t addr);
void i2c_send_data(uint8_t data);

uint8_t i2c_recv_ack();
uint8_t i2c_recv_nack();


#endif
