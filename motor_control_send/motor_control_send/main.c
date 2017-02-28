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
#include "adc.h"
#include "Timer0.h"

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

int main(void) {
	
	cli();			//Setup CAN
	init_can();
	adc_init();
	init_Timer0();
	
	DDRB |= 0b11111111;
	PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	sei();
	
	union can_frame Message;
	Message.id = MOTOR_ID;
	Message.length = 1;
	
	while(1) {
		if(TCNT1 > 15) {
			toggleLed();
			_delay_ms(50);
			toggleLed();
			_delay_ms(50);
		}
		Message.data[0] = adc_read();
		send_can_frame(&Message);
	}
	
}
