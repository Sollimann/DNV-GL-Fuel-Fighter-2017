/*
 * pwm.c
 *
 * Created: 11.02.2017 10:09:00
 *  Author: olesot
 */ 

#include "definitions.h"


//Initiating PE3 and PE4 (OC3A/OC3B) as PWM 
void pwm_init(void){
	
	//OC3A & B pin as output
	PORTE &= ~(1<<PE3);
	DDRE |= (1<<PE3);
	PORTE &= ~(1<<PE4);
	DDRE |= (1<<PE4);
	
	//fast pwm, mode 14, TOP at ICR
	set_bit(TCCR3B, WGM33);
	set_bit(TCCR3B, WGM32);
	set_bit(TCCR3A,WGM31);
	clear_bit(TCCR3A,WGM30);

	// Set low on compare match for 3A&B
	set_bit(TCCR3A, COM3A1);
	clear_bit(TCCR3A, COM3A0);
	set_bit(TCCR3A, COM3B1);
	clear_bit(TCCR3A, COM3B0);
	
	//Set prescale clk/256 for timer 3
	set_bit(TCCR3B, CS32);
	clear_bit(TCCR3B, CS31);
	clear_bit(TCCR3B, CS30);
	
	//Set top value for timer 3
	ICR3 = 0xFF;
	
	//Set off 3A&B
	OCR3A = 0x00;
	OCR3B = 0x00;
}




void pwm_A_off(void){
	OCR3A = 0x00;
}
void pwm_B_off(void){
	OCR3B = 0x00;
}

void set_pwm_A(uint8_t duty){
	//range from 0x00 to ICR3 value(see init)
	OCR3A = duty;
}

void set_pwm_B(uint8_t duty){
	//range from 0x00 to ICR3 value(see init)
	OCR3B = duty;
}

