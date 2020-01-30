#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0b11111111;
	PORTC = 0x10;
	
	while (1)
	{
		if(PINC & 0x01)
		{
			PORTD = 0x40;
			wait(500);
			PORTD = 0x00;
			wait(500);
		}
		else
		PORTD = 0x00;
	}

	return 1;
}
