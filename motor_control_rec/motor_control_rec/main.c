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
void colorADC(uint8_t val) {
	if (val == 0) {
		toggleFargeLed('D');
		} else if (val <=50) {
		toggleFargeLed('F');
		} else if (val <=100) {
		toggleFargeLed('B');
		} else if (val <=150) {
		toggleFargeLed('A');
		} else if (val <=200) {
		toggleFargeLed('C');
		} else if (val <=250) {
		toggleFargeLed('E');
	}
}
 
int main(void) 

{
	//init_all_ports();
	
	

	init_can();
	pwm_init();
	DDRB |= 0b11111111;
	PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	sei();

	toggleFargeLed('E');	//RØD
	_delay_ms(200);
	toggleFargeLed('D');	//GUL
	_delay_ms(200);
	toggleFargeLed('C');	//GRØNN
	_delay_ms(200);
	toggleLed();			//Skrur av lys
	_delay_ms(200);
	
	//	init_all_ports();

	while(1) {

		if (new_can_frame()) //Receiving
		{
			uint8_t val = read_can_frame()->data[0];
			set_pwm_A(val);
			next_can_frame();
		}//end of receiving
	}
}
