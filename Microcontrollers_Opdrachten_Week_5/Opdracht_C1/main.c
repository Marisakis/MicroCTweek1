#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#define BIT(x) ( 1<<x )
#define DDR_SPI DDRB // spi Data direction register
#define PORT_SPI PORTB // spi Output register
#define SPI_SCK 1 // PB1: spi Pin System Clock
#define SPI_MOSI 2 // PB2: spi Pin MOSI
#define SPI_MISO 3 // PB3: spi Pin MISO
#define SPI_SS 0 // PB0: spi Pin Slave Select

// wait(): busy waiting for 'ms' millisecond - used library: util/delay.h
void wait(int ms)
{
	for (int i=0; i<ms; i++)
	_delay_ms(1);
}

void spi_masterInit(void)
{
	DDR_SPI = 0xff; // All pins output: MOSI, SCK, SS, SS_display
	DDR_SPI &= ~BIT(SPI_MISO); // except: MISO input
	PORT_SPI |= BIT(SPI_SS); // SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1); // or: SPCR = 0b11010010;
	// Enable spi, MasterMode, Clock rate fck/64
	// bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0
}

// Write a byte from master to slave
void spi_write( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
}

// Write a byte from master to slave and read a byte from slave - not used here
char spi_writeRead( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
	data = SPDR; // New received data (eventually, MISO) in SPDR
	return data; // Return received byte
}

// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_slaveSelect(0); // Select display chip (MAX7219)
	spi_write(0x09); // Register 09: Decode Mode
	spi_write(0xFF); // -> 1's = BCD mode for all digits
	spi_slaveDeSelect(0); // Deselect display chip
	spi_slaveSelect(0); // Select dispaly chip
	spi_write(0x0A); // Register 0A: Intensity
	// Opdracht_C b2: De intensity moet worden aangepast naar 0x0F deze stond eerste op 0x04
	spi_write(0x0F); // -> Level 4 (in range [1..F])
	spi_slaveDeSelect(0); // Deselect display chip
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0B); // Register 0B: Scan-limit
	// Opdracht_C b1: De scan limit moet worden aangepast naar 0x03 deze stond eerste op 0x01 waardoor bits 0 en 1 ofwel
	//					de segmenten 1 en 2 worden aangestuurd. Met de waarde 0x03 worden alle vier de displays aangestuurd.
	spi_write(0x03); // -> 1 = Display digits 0..1
	spi_slaveDeSelect(0); // Deselect display chip
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x01); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}

// Set display on ('normal operation')
void displayOn()
{
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x01); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}

// Set display off ('shut down')
void displayOff()
{
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x00); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}

// Write value [data] to a single segment with address [address]
void spi_writeWord(unsigned char address, unsigned char data)
{
	spi_slaveSelect(0); // Select display chip
	spi_write(address); // digit adress: (digit place)
	spi_write(data); // digit value: 0
	spi_slaveDeSelect(0); // Deselect display chip
}

// Returns the number of digits in the value given
int getDigitCount(int value)
{	
	int count = 0;
	while(value > 0)
	{
		value /= 10;
		count++;
	}
	return count;
}

// Write value of only positive value to display
void writeLedDisplayA(int value)
{
	if(value < 0 || value > 9999)
		return;
	
	int numberCount = getDigitCount(value);
	char num[numberCount];
	itoa(value, num, 10);
	
	int currentAddress = numberCount;
	for(int i = 4; i >= numberCount; i--)
		spi_writeWord(i, 15);
	for(int i = 0; i < numberCount; i++)
	{
		spi_writeWord(currentAddress, num[i]);
		currentAddress--;
	}
}

// Write value of a negative or positive value to display
void writeLedDisplayB(int value)
{
	if(value > 999 || value < -999)
		return;
	
	int numberCount = getDigitCount(abs(value));
	char num[numberCount];
	itoa(abs(value), num, 10);
	
	for(int i = 4; i >= numberCount + 1; i--)
		spi_writeWord(i, 15);
	spi_writeWord(numberCount + 1, (value < 0) ? 10 : 15);
	int currentAddress = numberCount;
	for(int i = 0; i < numberCount; i++)
	{
		spi_writeWord(currentAddress, num[i]);
		currentAddress--;
	}
}

int main()
{
	DDRB=0x01; // Set PB0 pin as output for display select
	spi_masterInit(); // Initialize spi module
	displayDriverInit(); // Initialize display chip
	// clear display (all zero's)
	for (char i =1; i<=4; i++)
	spi_writeWord(i, 0);

	wait(1000);
	writeLedDisplayA(8739);
	wait(2000);
	writeLedDisplayA(245);
	wait(2000);
	writeLedDisplayA(25);
	wait(2000);
	writeLedDisplayA(4);
	wait(2000);
	writeLedDisplayB(-459);
	wait(2000);
	writeLedDisplayB(-46);
	wait(2000);
	writeLedDisplayB(-5);
	wait(2000);
	return (1);
}