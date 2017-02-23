/*
 * motor_control.c
 *
 * Created: 14.02.2017 14:18:46
 * Author : olesot
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "definitions.h"

void init(void){
	pwm_init();
}



//int max_allowed = nax_value(30km/t,15A)

int main(void)
{
    pwm_init();
	adc_init();
	
	uint16_t a_value;
	
	while (1)
	{
		
		/*
		uint8_t pwm_value;
		if (new_can_frame())
		{
			union can_frame *can_engin_rpm;
			can_engin_rpm = read_can_frame;
			if (can_engin_rpm->id == MOTOR_ID)
			{
				pwm_value = can_engin_rpm->data[0];
			}
			new_can_frame();
		}
		//roof=max_value(speed, amp)
		/*
		if (pwm_value>roof)
		{
			pwm_value = max_allowed;
		}
		
	
		set_pwm_A(pwm_value);
		*/
		
		
		a_value = adc_read();
		_delay_ms(10);
		//printf(a_val);
		set_pwm_A(a_value);
		set_pwm_B(a_value);
	}
    
}

