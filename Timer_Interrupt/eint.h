#ifndef __EINT_H
#define __EINT_H

#include "LPC17xx.h"

#define EINT2 2

void eint_init(void);
void EINT2_IRQHandler(void);

#endif
