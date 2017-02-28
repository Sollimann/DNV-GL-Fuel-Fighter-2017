/*
 * Timer.c
 *
 * Created: 28.02.2017 19:05:54
 *  Author: olesot
 */

#include <avr/io.h>

void init_Timer0() {
	/* Timer clock = I/O clock / 1024 */
	TCCR0A = (1<<CS02)|(1<<CS00);
	/* Clear overflow flag */
	TIFR0 = 1<<TOV0;
	/* Enable Overflow Interrupt */
	TIMSK0 = 1<<TOIE0;
}ISR (TIMER0_OVF_vect)
{
	
}