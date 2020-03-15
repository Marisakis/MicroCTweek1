#include "i2c.h"

void i2c_init()
{
    TWSR = 0x00; //set presca1er bits to zero
	TWBR = 0x0C; //SCL frequency
    TWCR = 0x04; //enab1e TWI module (Set TWEN bit)
}

// Start i2c communication
void i2c_start()
{
    TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
    while (!(TWCR & (1<<TWINT)));
}

// Stop i2c communication
void i2c_stop(void)
{
    TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWSTO));
    _delay_us(100); //wait for a short time
}

// Write 1 byte
void i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = ((1<< TWINT) | (1<<TWEN));
    while (!(TWCR & (1 <<TWINT)));
}

// Read 1 byte using either ACK or NACK bit
uint8_t i2c_read(uint8_t ackOption)
{
	if(ackOption == ACK_VAL)
		TWCR = ((1 << TWINT) | (1 <<TWEN) | (1 << TWEA));
	else if(ackOption == NACK_VAL)
		TWCR = ((1 << TWINT) | (1 <<TWEN));
	else
		return 0;
	
    while ( !(TWCR & (1 <<TWINT)));
    return TWDR;
}

// Write 1 byte to device with address [addr] on register [reg] with data [data]
void i2c_write_register(uint8_t addr, uint8_t reg, uint8_t data)
{
	i2c_start();
	// Address needs to be on the first 7 bits of the first byte send followed by a write bit (write bit has a value of 0)
	i2c_write((addr << 1) | WRITE_BIT);
	i2c_write(reg);
	i2c_write(data);
	i2c_stop();
}

// Read 1 byte from device with address [addr] on register [reg]
uint8_t i2c_read_register(uint8_t addr, uint8_t reg)
{
	i2c_start();
	// Address needs to be on the first 7 bits of the first byte send followed by a write bit (write bit has a value of 0)
	i2c_write((addr << 1) | WRITE_BIT);
	i2c_write(reg);
	i2c_stop();
	
	i2c_start();
	// Address needs to be on the first 7 bits of the first byte send followed by a read bit (read bit has a value of 1)
	i2c_write((addr << 1) | READ_BIT);
	// Read 1 byte from register. Here a NACK bit is needed because it is the last read being done
	uint8_t data = i2c_read(NACK_VAL);
	i2c_stop();
	
	return data;
}

// Get status of i2c bus on the atmega128A
uint8_t i2c_get_status(void)
{
	uint8_t status;
	// We only need the first 3 bits so we mask out the other bits
	status = TWSR & 0xF8;
	return status;
}