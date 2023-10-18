/* 
* I2C.h
*
* Created: 17-10-2023 13:12:24
* Author: madse
*/


#ifndef __I2C_H__
#define __I2C_H__


class I2C
{
public:
	I2C();
	void start();
	void stop();
	void write(uint8_t data);
	uint8_t read_ack();
	uint8_t read_nack();
private:
}; //I2C

#endif //__I2C_H__
