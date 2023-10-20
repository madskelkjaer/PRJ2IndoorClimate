/* 
* I2C.cpp
*
* Created: 17-10-2023 13:12:24
* Author: madse
*/
#define F_CPU 16000000
#include <avr/io.h>
#include "I2C.h"

// default constructor
I2C::I2C()
{
	// Set prescaler to 1
	TWSR = 0;

	// Set bit rate register (Baud rate)
	TWBR = ((F_CPU / 100000) - 16) / 2;
} //I2C

void I2C::start() {
	// Send start condition
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void I2C::stop() {
	// Send stop condition
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void I2C::write(uint8_t data) {
	// Load data into TWI data register
	TWDR = data;

	// Enable TWI and clear interrupt flag
	TWCR = (1 << TWEN) | (1 << TWINT);

	// Wait until TWI finish its current job (Write operation)
	while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C::read_ack() {
	// Enable TWI, generation of ack and clear interrupt flag
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

	// Wait until TWI finish its current job (read operation)
	while (!(TWCR & (1 << TWINT)));

	return TWDR;
}

uint8_t I2C::read_nack() {
	// Enable TWI and clear interrupt flag
	TWCR = (1 << TWEN) | (1 << TWINT);

	// Wait until TWI finish its current job (read operation)
	while (!(TWCR & (1 << TWINT)));

	return TWDR;
}