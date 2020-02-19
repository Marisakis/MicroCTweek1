#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

typedef struct  
{
	char portValue;
	char onOff;
} Led;

Led leds[] =
{
	{ 0b00000001, 0b00000011 },
	{ 0b00000010, 0b00000011 },
	{ 0b00000010, 0b00000110 },
	{ 0b00000100, 0b00000110 },
	{ 0b00000100, 0b00000101 },
	{ 0b00000001, 0b00000101 }
};

void wait(int ms);
void setCharliePlexingLed(int lednr);

int main(void)
{
	DDRD = 0xFF;
	
    while (1) 
    {
		for(int i = 1; i <= 6; i++)
		{
			setCharliePlexingLed(i);
			wait(1000);
		}
    }
}

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
		_delay_ms(1);
}

void setCharliePlexingLed(int lednr)
{
	if(lednr > 0 && lednr <= 6)
	{
		DDRD = leds[lednr - 1].onOff;
		PORTD = leds[lednr - 1].portValue;	
	}
}