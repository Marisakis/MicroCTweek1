#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#ifndef I2C_H_
#define I2C_H_

#define WRITE_BIT 0
#define READ_BIT 1

#define ACK_VAL 0
#define NACK_VAL 1

#ifdef __cplusplus
	extern "C" {
#endif

void i2c_init();
void i2c_start();
void i2c_stop(void);
void i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t ackOption);

void i2c_write_register(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t i2c_read_register(uint8_t addr, uint8_t reg);
uint8_t i2c_get_status(void);

#ifdef __cplusplus
	}
#endif

#endif /* I2C_H_ */