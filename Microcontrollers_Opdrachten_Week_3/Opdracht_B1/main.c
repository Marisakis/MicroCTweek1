#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void wait( int ms ) 
{
	for (int i = 0; i < ms; i++) 
		_delay_ms( 1 );
}

void setupTimer(void) {

	cli();

	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	
	OCR1A = 10000;
	
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK |= (1 << OCIE1A);

	sei();
}



ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1<<7);
}


int main(void) 
{
	DDRB = 0xFF;
	setupTimer();
	while (1)  {
		wait(50);
	}
	return 0;
}

