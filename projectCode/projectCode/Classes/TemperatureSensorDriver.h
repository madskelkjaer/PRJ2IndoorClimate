/* 
* TemperatureSensorDriver.h
*
* Created: 27-11-2023 17:19:50
* Author: madse
*/


#ifndef __TEMPERATURESENSORDRIVER_H__
#define __TEMPERATURESENSORDRIVER_H__

#include <avr/io.h>
#include "SensorDriver.h"
#include "../Utils/SDC30.h"

class TemperatureSensorDriver : public SensorDriver<double>
{
public:
	TemperatureSensorDriver();
	double readValue() override;
protected:
private:
	SDC30 sensor_;
}; //TemperatureSensorDriver

#endif //__TEMPERATURESENSORDRIVER_H__
