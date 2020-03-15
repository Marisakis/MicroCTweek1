#include "matrix_display.h"

// Initializes the matrix display given to the function
void matrix_display_init(matrix_display* matrixDisplay)
{
	// If matrix was not initialized, initialize it
	if(!matrixDisplay->isInitialized)
	{
		// System setup command
		i2c_write_register(matrixDisplay->addr, 0x21, 0x00);
		// Turn on display with no blinking
		i2c_write_register(matrixDisplay->addr, 0x81, 0x00);
		// Set the matrix to full brightness
		i2c_write_register(matrixDisplay->addr, 0xE7, 0xFF);
		matrixDisplay->isInitialized = true;
	}	
}

// Sets the value (on/off : 1/0) of a pixel on the matrix display given to the function at a certain x and y position
void matrix_display_set_pixel(matrix_display* matrixDisplay, uint8_t x, uint8_t y, bool isOn)
{
	// If matrix was not initialized, initialize it before writing to it
	if(!matrixDisplay->isInitialized)
		matrix_display_init(matrixDisplay);
	
	// LED matrix is 8x8 so x or y values above 7 are not allowed (values are indexed from 0 to 7)
	if(x > 7 || y > 7)
		return;
	
	// Read data of the row specified by y, on the matrix display
	uint8_t rowData = i2c_read_register(matrixDisplay->addr, y * 2);
	
	/* 
		First LED column for some reason is the last bit (0b10000000 : 0x80), so the value written 
		must be shifted one less to the left if the x value is higher than 0 and must be (0b10000000 : 0x80) otherwise
	*/
	//i2c_write_register(matrixDisplay->addr, y * 2, (isOn) ? ((x == 0) ? (0x80) : (1 << (x - 1))) : 0x00);
	uint8_t data;
	if(isOn)
		data = ((x == 0) ? 0x80 : (1 << (x - 1)));
	else
		data = (1 << (x - 1));
	i2c_write_register(matrixDisplay->addr, y * 2, data | rowData);
}

// Sets the values (on/off : 1/0) of multiple pixels on the matrix display given to the function
void matrix_display_set_pixels(matrix_display* matrixDisplay, matrix_display_value_pair* pixelValues, uint8_t size)
{
	// If matrix was not initialized, initialize it before writing to it
	if(!matrixDisplay->isInitialized)
		matrix_display_init(matrixDisplay);
	
	// Loop trough all pixels values pairs given and set corresponding LED values on the matrix display
	for(int i = 0; i < size; i++)
		matrix_display_set_pixel(matrixDisplay, pixelValues[i].x, pixelValues[i].y, pixelValues[i].isOn);
}

// Sets the values of all the pixels of the matrix display given to the function to (off : 0) essentially clear the matrix display
void matrix_display_clear(matrix_display* matrixDisplay)
{
	// If matrix was not initialized, initialize it before writing to it
	if(!matrixDisplay->isInitialized)
		matrix_display_init(matrixDisplay);
	
	// Loop trough all rows of the matrix and turn off the corresponding LED's
	for(int i = 0; i < 8; i++)
		i2c_write_register(matrixDisplay->addr, i * 2, 0x00);
}