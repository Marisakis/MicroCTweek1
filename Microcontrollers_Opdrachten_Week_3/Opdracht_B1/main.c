#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

int buttonCount = 0;
int isDown = 0;

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init(void);
void set_cursor(int position);
void write_command(unsigned char byte);
void write_data(unsigned char byte);
void display_text(char *str);
void clear_text();

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
	write_command(128 + position);
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

void clear_text()
{
	write_command(0x01);
}

void wait( int ms ) 
{
	for (int i = 0; i < ms; i++) 
		_delay_ms( 1 );
}

void setupTimer(void) {

	cli();

	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	
	OCR1A = 100;
	
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK |= (1 << OCIE1A);

	sei();
}

ISR(TIMER1_COMPA_vect)
{
	//PORTB ^= (1<<7);
	if(PINA & 0x01)
	{
		if(isDown == 0)
		{
			char snum[5];
			itoa(buttonCount, snum, 10);
			clear_text();
			display_text(snum);
			isDown = 1;
			buttonCount++;	
		}
	}
	else
	{
		if(isDown == 1)
		{
			char snum[5];
			itoa(buttonCount, snum, 10);
			clear_text();
			display_text(snum);
			isDown = 0;
		}
	}
	PORTB = buttonCount;
}


int main(void) 
{
	DDRB = 0xFF;
	DDRA = 0x00;
	
	//---- LCD ----
	DDRD = 0xFF;
	init();
	set_cursor(0);
	//-------------
	
	setupTimer();
	while (1)  {
		wait(50);
	}
	return 0;
}

