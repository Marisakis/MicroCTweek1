#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Lcd.h"

// Main function (entry point of the program)
void main()
{
	DDRD = 0xFF;						// All pins PORTD are set to output 
	init();								// Initialize LCD display
	display_text("Hello world!");		// Display text
	set_cursor(0);						// Set cursor to position 0
	
	int count = 0;
	
	// Infinite loop to keep program running
	while (1)
	{
		//write_command(0x1E);
		_delay_ms(1000);
		count++;
		set_cursor(count);				// Set cursor position
		if(count == 5)
		{
			count = 0;
			set_cursor(0);				// Set cursor position
		}
	}

	return 1;
}