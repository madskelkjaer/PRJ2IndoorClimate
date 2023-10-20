/* 
* SDC30.cpp
*
* Created: 18-10-2023 13:01:56
* Author: madse
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "SDC30.h"


SDC30::SDC30(uint8_t address)
{
	address_ = address;
	I2C i2c;
	i2c_ = i2c;
	
	writeAddress_ = address_ << 1; // 0 i LSB for at skrive til sensor.
	readAddress_ = (address_ << 1) | 0x01; // 1 i LSB for at læse;
	
} //SDC30

bool SDC30::ready()
{
	uint8_t dataReadyMSB;
	uint8_t dataReadyLSB;
	uint16_t dataReady;
	
	i2c_.start();
	i2c_.write(writeAddress_);
	i2c_.write(0x02); // Get data ready adresse er 0x0202. Interface datablad.
	i2c_.write(0x02);
	i2c_.stop();
	
	_delay_ms(100); // afventer sensor i 100ms. Fundet i kode eksempel fra producenten.
	// https://github.com/Sensirion/arduino-i2c-scd30/blob/master/src/SensirionI2cScd30.cpp#L52
	
	i2c_.start();
	i2c_.write(readAddress_);
	dataReadyMSB = i2c_.read_ack(); // aflæser data bytes.
	dataReadyLSB = i2c_.read_nack();
	i2c_.stop();
	
	// sammesætter bytes til én 16 bit.
	dataReady = ((uint16_t)dataReadyMSB << 8) | (uint16_t)dataReadyLSB;
	
	return dataReady == 1; // Hvis dataReady er 1, returner true.
}

float SDC30::getCo2()
{
	return data_.co2;
}

float SDC30::getTemperature()
{
	return data_.temperature;
}

float SDC30::getHumidity()
{
	return data_.humidity;
}

void SDC30::Measure()
{
	dataArray data;
	measurementData mData;
	
	uint8_t co2_mmsb, co2_mlsb, co2_lmsb, co2_llsb;
	uint8_t t_mmsb, t_mlsb, t_lmsb, t_llsb;
	uint8_t h_mmsb, h_mlsb, h_lmsb, h_llsb;
		
	while(!this->ready()) {}
	
	i2c_.start();
	i2c_.write(writeAddress_);
	
	i2c_.write(0x03); // Read measurement adresse er 0x0300;
	i2c_.write(0x00);

	i2c_.stop();
	
	_delay_ms(50); // Afventer sensor i 50ms.
	
	i2c_.start();
	i2c_.write(readAddress_);

	// Læser data ifølge databladet.
	co2_mmsb = i2c_.read_ack();
	co2_mlsb = i2c_.read_ack();
	i2c_.read_ack(); // CRC
	co2_lmsb = i2c_.read_ack();
	co2_llsb = i2c_.read_ack();
	i2c_.read_ack(); // CRC
	t_mmsb = i2c_.read_ack();
	t_mlsb = i2c_.read_ack();
	i2c_.read_ack(); // CRC
	t_lmsb = i2c_.read_ack();
	t_llsb = i2c_.read_ack();
	i2c_.read_ack(); // CRC
	h_mmsb = i2c_.read_ack();
	h_mlsb = i2c_.read_ack();
	i2c_.read_ack(); // CRC
	h_lmsb = i2c_.read_ack();
	h_llsb = i2c_.read_ack();
	i2c_.read_nack(); // CRC

	// Send stop condition
	i2c_.stop();

	// Sensoren returnerer data i big-endian notation.
	// Arduinoen bruger litte-endian notation. Derfor skal vi vende alle bits om.
	
	// Co2 måling
	mData.bytes[3] = co2_mmsb;
	mData.bytes[2] = co2_mlsb;
	mData.bytes[1] = co2_lmsb;
	mData.bytes[0] = co2_llsb;
	
	data.co2 = mData.value;
	
	// Temperatur måling
	mData.bytes[3] = t_mmsb;
	mData.bytes[2] = t_mlsb;
	mData.bytes[1] = t_lmsb;
	mData.bytes[0] = t_llsb;
	
	data.temperature = mData.value;
	
	// Luftfugtighed måling
	mData.bytes[3] = h_mmsb;
	mData.bytes[2] = h_mlsb;
	mData.bytes[1] = h_lmsb;
	mData.bytes[0] = h_llsb;
	
	data.humidity = mData.value;
	
	data_ = data; // Gemmer i privat klasse variable.
	// return data;
}