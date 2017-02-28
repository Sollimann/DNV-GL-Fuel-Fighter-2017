/*
 * motor_control.c
 *
 * Created: 14.02.2017 14:18:46
 * Author : olesot
 */ 



#define F_CPU 8000000UL
#include "definitions.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "can.h"
#include "pwm.h"

#define SENDADC 0
#define RECIEVE 1

volatile int state = 0;

void toggleLed(){		//switches light on and off
	if (state == 0)		//if off
	{
		PORTB &= ~((1 << PB5)|(1<<PB6)|(1<<PB7));
		state = 1;
		} else {		//if on
		PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
		state = 0;
	}
}

void toggleFargeLed(char farge){ //Extension of toggleLed() that picks a colour depending on the input (int).
	PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	state = 1;
	switch (farge){
		case 'A':		//BLÅ
		PORTB &= ~((0 << PB5)|(0 << PB6)|(1 << PB7));
		break;
		case 'B':		//CYAN
		PORTB &= ~((0 << PB5)|(1 << PB6)|(1 << PB7));
		break;
		case 'C':		//GREEN
		PORTB &= ~((0 << PB5)|(1 << PB6)|(0 << PB7));
		break;
		case 'D':		//YELLOW
		PORTB &= ~((1 << PB5)|(1 << PB6)|(0 << PB7));
		break;
		case 'E':		//RED
		PORTB &= ~((1 << PB5)|(0 << PB6)|(0 << PB7));
		break;
		case 'F':		//VIOLET
		PORTB &= ~((1 << PB5)|(0 << PB6)|(1 << PB7));
		break;
		case 'G':		//WHITE
		PORTB &= ~((1 << PB5)|(1 << PB6)|(1 << PB7));
		break;
		case 'H':		//BLACK
		PORTB |= ((1 << PB5)|(1 << PB6)|(1 << PB7));
		//state = 0;
		break;
	}
}
 
int main(void) {
	 
	cli();			//Setup CAN
	init_can();
	pwm_init();
	DDRB |= 0b11111111;
	PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	sei();
	 
	while(1) {
		if(new_can_frame()) {
			uint8_t val = (read_can_frame()->data[0]);
			if (val == 255) {
				toggleFargeLed('E');
			}
			set_pwm_A(val);
			next_can_frame();
		}
	}
	 
}