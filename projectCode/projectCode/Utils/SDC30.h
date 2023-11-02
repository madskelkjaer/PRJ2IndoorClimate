/* 
* SDC30.h
*
* Created: 18-10-2023 13:01:56
* Author: madse
*/


#ifndef __SDC30_H__
#define __SDC30_H__

#include "I2C.h"

struct dataArray 
{
	float co2;
	float temperature;
	float humidity;	
};

union measurementData 
{
	uint8_t bytes[4];
	float value;
};

class SDC30
{
public:
	SDC30(uint8_t address);
	bool ready();
	void measure();
	double getCo2();
	double getTemperature();
	double getHumidity();
private:
	dataArray data_;
	uint8_t address_;
	uint8_t writeAddress_;
	uint8_t readAddress_;
	I2C i2c_;
	
}; //SDC30

#endif //__SDC30_H__
