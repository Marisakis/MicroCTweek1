#define F_CPU 8000000

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
	//int pordC = pordC;
	//pordC = pordC << 1;
	//if(pordC == 0x00)
	//	pordC = 0x01;
	//PORTC |= pordC;
	PORTC = PORTC << 1;			
	if (PORTC == 0)
	{
		PORTC = 0x01;
	}
	wait(0); // temporary solution to prevent mnultiple interrupts from one press
}

ISR(INT1_vect)
{
	//int pordC = PORTC;
	//if(pordC == 0x00)
	//	pordC = 0xFF;
	//PORTC |= pordC;
	PORTC = PORTC >> 1;
	if (PORTC == 0)
	{
		PORTC = 0x80;
	}
		wait(0); // temporary solution to prevent mnultiple interrupts from one press
}

int main(void)
{
	DDRD = 0x80;
	DDRC = 0xFF;
	PORTC = 0x00;
	
	
	EICRA |= 0x0B;
	EIMSK |= 0x03;
	
	sei();
	
    while (1) 
    {
		PORTD ^= 0x80;
		wait(500);
    }
	
	return 0;
}

