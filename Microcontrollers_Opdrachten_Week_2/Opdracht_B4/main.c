/*
 * Opdracht_B4.c
 *
 * Created: 2/12/2020 1:52:19 PM
 * Author : Chiem
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DisplayA 0x01
#define DisplayB 0x02
#define DisplayC 0x04
#define DisplayD 0x08
#define DisplayE 0x10
#define DisplayF 0x20
#define DisplayG 0x40
#define DisplayDP 0x80


typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

PATTERN_STRUCT pattern[] = {
	{DisplayF, 150}, {DisplayG, 150}, {DisplayC, 150}, {DisplayD, 150},
	{DisplayE, 150}, {DisplayG, 150}, {DisplayB, 150}, {DisplayA, 150},
	{0xFF, 0},
};

void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
    DDRC = 0b11111111;					// PORTD all output
    
    while (1)
    {
	    // Set index to begin of pattern array
	    int index = 0;
	    // as long as delay has meaningful content
	    while( pattern[index].delay != 0 ) {
		    // Write data to PORTD
		    PORTC = pattern[index].data;
		    // wait
		    wait(pattern[index].delay);
		    // increment for next round
		    index++;
	    }
    }

    return 1;
}

