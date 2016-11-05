#include "timer.h"
#include <avr/interrupt.h>

void Timer_on()
{
	TCCR0 |= (1<<WGM01);	//tryb CTC
	TCCR0 |= (1<<CS02);		//preskaler 256
	OCR0 = 250;				//8000000/256/250 = 125 hz
	TIMSK |= (1<<OCIE0);
}

void Timer_off()
{
	TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));
}
