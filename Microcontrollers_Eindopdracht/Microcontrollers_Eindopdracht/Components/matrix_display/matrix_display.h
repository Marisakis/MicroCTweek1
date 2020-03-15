#include "../i2c/i2c.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef MATRIXDISPLAY_H_
#define MATRIXDISPLAY_H_

#ifdef __cplusplus
	extern "C" {
#endif

// Type for storing the address of a matrix display and its initialized state
typedef struct matrix_display_t
{
	uint8_t addr;
	bool isInitialized;
} matrix_display;

// Type for representing the position data and state of a LED for the matrix display
typedef struct matrix_display_value_pair_t
{
	uint8_t x;
	uint8_t y;
	bool isOn;
} matrix_display_value_pair;

// Initializes the matrix display given to the function
void matrix_display_init(matrix_display* matrixDisplay);
// Sets the value (on/off : 1/0) of a pixel on the matrix display given to the function at a certain x and y position
void matrix_display_set_pixel(matrix_display* matrixDisplay, uint8_t x, uint8_t y, bool isOn);
// Sets the values (on/off : 1/0) of multiple pixels on the matrix display given to the function
void matrix_display_set_pixels(matrix_display* matrixDisplay, matrix_display_value_pair* pixelValues, uint8_t size);
// Sets the values of all the pixels of the matrix display given to the function to (off : 0) essentially clear the matrix display
void matrix_display_clear(matrix_display* matrixDisplay);

#ifdef __cplusplus
	}
#endif

#endif /* MATRIXDISPLAY_H_ */