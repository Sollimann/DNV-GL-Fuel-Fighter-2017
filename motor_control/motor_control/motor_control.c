/*
 * motor_control.c
 *
 * Created: 14.02.2017 15:52:17
 *  Author: olesot
 */ 

#include "definitions.h"


int MC_init(void){

	pwm_init();

	};

void stop_motors(void){
	//shut down in a safe manner
}

void set_motor_speed_A(uint8_t speed){
	set_pwm_A(speed);
}

void can_recv(){
	
}