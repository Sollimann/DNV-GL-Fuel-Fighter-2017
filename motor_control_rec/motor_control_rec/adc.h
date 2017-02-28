/*
 * adc.h
 *
 * Created: 18.02.2017 10:41:48
 *  Author: olesot
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "definitions.h"
#include <avr/io.h>

void adc_init(void);
void adc_enable(void);
void adc_disenable(void);
void start_conv(void);
uint8_t adc_read(void);



#endif /* ADC_H_ */