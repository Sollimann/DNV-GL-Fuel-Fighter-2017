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

void toggleFargeLed(char farge){ //Extension of toggleLed() that picks a colour depending on the input (int).
	PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	state = 1;
	switch (farge){
		case 'A':		//BL�
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
	cli();			//Setup CAN
	init_can();
	adc_init();
	DDRB |= 0b11111111;
	PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);

	sei();

	toggleFargeLed('G');	//HVIT
	_delay_ms(200);
	toggleFargeLed('E');	//R�D
	_delay_ms(200);
	toggleFargeLed('C');	//GR�NN
	_delay_ms(200);
	toggleLed();			//Skrur av lys
	_delay_ms(200);
	
	union can_frame CAN_send;
	CAN_send.id = 0;
	CAN_send.length = 1;
	CAN_send.data[0] = 0x00;

	while(1) { //SPAM
		_delay_ms(1000);
		CAN_send.data[0] = adc_read();
		send_can_frame(&CAN_send);  
	}//end while(1)
}

