/*
 * adc.c
 *
 * Created: 18.02.2017 10:41:35
 *  Author: olesot
 */ 

//Written for UM

#include "adc.h"


void adc_init(void){
	//Internal 2.56V voltage reference with external capacitor on AREF pin
	set_bit(ADMUX, REFS1);
	set_bit(ADMUX, REFS0);
	//Single ended input on ADC0
	clear_bit(ADMUX, MUX0);
	clear_bit(ADMUX, MUX1);
	clear_bit(ADMUX, MUX2);
	clear_bit(ADMUX, MUX3);
	clear_bit(ADMUX, MUX4);
	
	//ADC Auto trigger Enable
	set_bit(ADCSRA, ADEN);
	
	//Free Running mode
	clear_bit(ADCSRB, ADTS0);
	clear_bit(ADCSRB, ADTS1);
	clear_bit(ADCSRB, ADTS2);
	
	adc_enable();
	start_conv();
	
	
}

void adc_enable(void){
	//Enables ADC, turn off before go into sleep mode
	set_bit(ADCSRA, ADEN);
}

void start_conv(void){
	set_bit(ADCSRA, ADSC);
}

void adc_disenable(void){
	clear_bit(ADCSRA, ADEN);
}
