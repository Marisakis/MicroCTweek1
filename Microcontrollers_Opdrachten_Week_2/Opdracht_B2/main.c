#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms( 1 );
	}
}

ISR(INT0_vect)
{
	int pordD = PORTD;
	pordD = pordD << 1;
	if(pordD == 0x00)
		pordD = 0x01;
	PORTD |= pordD;
}

ISR(INT1_vect)
{
	int pordD = PORTD;
	if(pordD == 0x00)
		pordD = 0xBF;
	PORTD |= pordD;
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0x01;
	
	PORTD = 0x01;
	
	EICRA |= 0x0B;
	EIMSK |= 0x03;
	
	sei();
	
    while (1) 
    {
		PORTC ^= 0x01;
		wait(500);
    }
	
	return 0;
}

