/*
 * pwm.h
 *
 * Created: 11.02.2017 10:17:14
 *  Author: olesot
 */ 


#ifndef PWM_H_
#define PWM_H_

void pwm_init(void);
void pwm_A_off(void);
void pwm_B_off(void);
void set_pwm_A(uint8_t duty);
void set_pwm_B(uint8_t duty);


#endif /* PWM_H_ */