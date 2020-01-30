#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main( void )
{
	DDRD = 0b11111111;			// All pins PORTD are set to output 
	PORTD = 0x01;
	
	while (1)
	{	
		PORTD = PORTD << 1;			// Write 01000000 PORTD
		wait( 50 );	
		if (PORTD == 0)
		{
			PORTD = 0x01;
			wait(50);
		}		
	}

	return 1;
}
