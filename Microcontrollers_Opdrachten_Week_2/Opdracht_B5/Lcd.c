#include "Lcd.h"

// Toggles the E bit to apply command
void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);
}

// Initializes the LCD display
void init(void)
{
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();

	//// Clear screen
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x01;
	lcd_strobe_lcd_e();
}

// Sets the position of the cursor
void set_cursor(int position)
{
	write_command(128 + position);
}

// Writes command to the LCD display
void write_command(unsigned char byte)
{
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

// Writes data to the LCD display
void write_data(unsigned char byte)
{
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

// Displays specified text on LCD display
void display_text(char *str)
{
	for(;*str; str++){
		write_data(*str);
	}
}