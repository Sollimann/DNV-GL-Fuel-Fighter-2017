/*
 * definitions.h
 *
 * Created: 11.02.2017 10:08:49
 *  Author: olesot
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <avr/io.h>


//#include "motor_control.h"

//sets bit "bit" in register "reg"
#define set_bit(reg, bit)		(reg |= (1<<bit))
//same as set_bit only clears all other bits
#define set_bit_ex(reg, bit)	(reg = (1<<bit))
//clears bit "bit" in register "reg"
#define clear_bit(reg, bit)		(reg &=~ (1<<bit))
//tests if bit "bit" is set in register "reg"
#define test_bit(reg, bit)		(reg & (1<<bit))
//toggles bit "bit" in register "reg"
#define toggle_bit(reg, bit)	(reg ^= (1<<bit))

#define MOTOR_ID 0x0

#define MAX_AMP 0xFF

#define F_CPU 8000000UL

void toggleLed(void);

void colorADC(uint8_t val);

#endif /* DEFINITIONS_H_ */