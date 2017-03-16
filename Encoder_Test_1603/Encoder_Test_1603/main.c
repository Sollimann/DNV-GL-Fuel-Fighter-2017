/*
 * Encoder_Test_1603.c
 *
 * Created: 16.03.2017 19:24:56
 * Author : Ultrawack
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "usbdb.h"

#define COUNTCONSTANT 0.234375

uint16_t count = 0;
int rpm = 0;
uint8_t calculate = 0;
uint8_t printCount = 0;


void pin_init(){
	DDRB &= ~(0x01); //setter PB0 til input
	DDRB |= (1<<PB5)|(1<<PB6)|(1<<PB7);
	PORTB |= (1<<PB5)|(1<<PB6)|(1<<PB7);
}

void timer_init(){
	TCCR1B |= (1<<CS11)|(1<<CS10);
	TCNT1 = 0;
	TIMSK1 |= (1<<TOIE1);
}

uint16_t calculateRpm(){
	rpm = count * COUNTCONSTANT;
	
	uint16_t intValue = rpm;
	
	return intValue;
}



int main(void)
{
	cli();
	pin_init();
	usbdbg_init();
	timer_init();
	sei();
	
	uint8_t state = 0;
    
	while (1) 
    {
		if (calculate == 1)
		{
			calculate = 0;
			printf("RPM: %u\n",calculateRpm());
			printf("Count value: %u\n",count);
			count = 0;
			TCNT1 = 0;
		}
		
		if (printCount == 4)
		{
			printCount = 0;
			printf("RPM: %u\n",calculateRpm());
			count = 0;
			TCNT1 = 0;
		}
		
		
		if ((PINB & (1<<PB0)) && !state)
		{
			cli();
			count++;
			sei();	
			state = 1;
			
		} else if (!(PINB & (1<<PB0)) && state){

			state = 0;
		}
			
    }
}

ISR(TIMER1_OVF_vect){
	calculate = 1;	
}