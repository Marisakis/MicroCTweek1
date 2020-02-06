#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init(void);
void set_cursor(int position);
void write_command(unsigned char byte);
void write_data(unsigned char byte);
void display_text(char *str);

void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

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

void set_cursor(int position)
{
	write_command(0x02);
	for(int i = 0; i < position; i++)
		write_command(0x1E);
	//write_command(128 + position);
}

void write_command(unsigned char byte)
{
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}


void write_data(unsigned char byte)
{
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}


void display_text(char *str)
{
	for(;*str; str++){
		write_data(*str);
	}
}

void main()
{
	DDRD = 0xFF;
	init();
	display_text("Hello world!");
	set_cursor(0);
	
	int count = 0;
	
	while (1)
	{
		//write_command(0x1E);
		_delay_ms(1000);
		count++;
		set_cursor(count);
		if(count == 5)
		{
			count = 0;
			set_cursor(0);
		}
	}

	return 1;
}