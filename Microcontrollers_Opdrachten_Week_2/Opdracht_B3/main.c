#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const unsigned char digits[16] = {
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A
	0b01111100, //b
	0b00111001, //C
	0b01011110, //d
	0b01111001, //E
	0b01111011, //e
};

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
		_delay_ms(1);
}

void display(int digit)
{
	if(digit <= 15)
		PORTC = digits[digit];
	else if(digit > 15)
	{
		for(int i = 0; i < 4; i++)
		{	
			PORTC = digits[15];
			wait(200);
			PORTC = 0x00;
			wait(200);
		}
	}
}

int main(void)
{
	DDRC = 0xFF;
	
    while (1) 
    {
		for(int i = 0; i <= 16; i++)
		{			
			display(i);
			wait(1000);
		}
    }
}

