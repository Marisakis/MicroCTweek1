#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>


int wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
		if(PINC & 0x80) {
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	DDRD = 0b01111111;
	PORTC = 0x10;
	bool state = true;
	bool clicked = false;
	
	while (1)
	{
		if(PINC & 0x80)
		{
			if(!clicked) {
				clicked = true;
				state = !state;
			}
		}
		else
		{
			clicked = false;
		}
		
		int btnPressed;
		if(state) {
			PORTD = 0x01;
			btnPressed = wait(1000);
			if(btnPressed < 1) {
				PORTD = 0x00;
				wait(1000);
			}
		}
		else {
			PORTD = 0x01;
			btnPressed = wait(250);
			if(btnPressed < 1) {
				PORTD = 0x00;
				btnPressed = wait(250);
			}
		}
		
	}

	return 1;
}

