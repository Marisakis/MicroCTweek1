#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef LCD_H_
#define LCD_H_

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init(void);
void set_cursor(int position);
void write_command(unsigned char byte);
void write_data(unsigned char byte);
void display_text(char *str);

#endif /* LCD_H_ */