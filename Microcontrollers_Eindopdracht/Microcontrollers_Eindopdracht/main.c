#define F_CPU 8000000UL

#include <avr/io.h>
#include "Components/i2c/i2c.h"
#include "Components/matrix_display/matrix_display.h"

int main(void)
{
	i2c_init();
	matrix_display matrixDisplay1 = {
		.addr = 0x70,
		.isInitialized = false,
	};
	matrix_display matrixDisplay2 = {
		.addr = 0x71,
		.isInitialized = false,
	};
	
	//for(int y = 0; y < 8; y++)
		//for(int x = 0; x < 8; x++)
			//matrix_display_set_pixel(&matrixDisplay, x, y, true);
	
	matrix_display_init(&matrixDisplay1);
	matrix_display_init(&matrixDisplay2);
	matrix_display_clear(&matrixDisplay1);
	matrix_display_clear(&matrixDisplay2);
	
	//matrix_display_set_pixel(&matrixDisplay1, 0, 0, true);
	//matrix_display_set_pixel(&matrixDisplay2, 0, 0, true);
	
	matrix_display_value_pair pixelValues[] = {
		// Left eye
		{ 1, 1, true },
		{ 2, 1, true },
		{ 1, 2, true },
		{ 2, 2, true },
		
		// Right eye
		{ 5, 1, true },
		{ 6, 1, true },
		{ 5, 2, true },
		{ 6, 2, true },
		
		// Mouth
		{ 1, 5, true },
		{ 2, 6, true },
		{ 3, 6, true },
		{ 4, 6, true },
		{ 5, 6, true },
		{ 6, 5, true },
	};
	
	matrix_display_set_pixels(&matrixDisplay1, pixelValues, sizeof(pixelValues) / sizeof(matrix_display_value_pair));
	matrix_display_set_pixels(&matrixDisplay2, pixelValues, sizeof(pixelValues) / sizeof(matrix_display_value_pair));
	
	while (1)
	{
		
	}
}