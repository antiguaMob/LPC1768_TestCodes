#ifndef __EEPROM_H
#define __EEPROM_H

#include "LPC17xx.h"
#include "i2c.h"

#define EEPROM_W		0xA0
#define EEPROM_R		0xA1

void eeprom_init();
void eeprom_write(uint16_t addr, uint8_t byte[], uint8_t n);
void eeprom_read(uint16_t addr, uint8_t byte[], uint8_t n);


#endif
