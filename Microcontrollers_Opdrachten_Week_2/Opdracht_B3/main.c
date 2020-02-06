#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	
	int test = 0x7B;
	test = test << 8;
	PORTD = test;
	_delay_ms(1);
	test += 0b01011011;
	PORTD = test;
    /* Replace with your application code */
    while (1) 
    {
		//int test = 0x7B
		//test = test << 8;
		//test += 0b01011011;
		//PORTD = test;
    }
}

