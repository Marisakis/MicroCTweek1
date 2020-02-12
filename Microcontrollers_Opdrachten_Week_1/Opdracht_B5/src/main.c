#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	uint8_t* port;
	unsigned char data;
	unsigned int delay;
} LOOKUP;

void wait(int ms);

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0xFF;
	
	LOOKUP pattern[] =
	{
		{&PORTD, 0x00, 100}, {&PORTD, 0x01,100}, {&PORTD, 0x00, 0x00}
		//{0x02,100},{0x04,100},{0x08,100},{0x10,100},{0x20,100},{0x40,100},{0x80,100},
		//{0x00, 100}, {0xFF, 100},
		//{0x00, 100},{0x00, 0x00}
	};
	
	while(1)
	{
		int index = 0;

		while(pattern[index].delay != 0) 
		{
			*pattern[index].port = pattern[index].data;
			
			wait(pattern[index].delay);
			
			index++;
		}
	}
	return 1;
}
