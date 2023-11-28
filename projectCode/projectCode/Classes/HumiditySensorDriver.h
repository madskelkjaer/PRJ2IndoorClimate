/* 
* HumiditySensorDriver.h
*
* Created: 27-11-2023 17:57:20
* Author: madse
*/


#ifndef __HUMIDITYSENSORDRIVER_H__
#define __HUMIDITYSENSORDRIVER_H__

#include <avr/io.h>
#include "SensorDriverTemplate.h"
#include "../Utils/SDC30.h"

class HumiditySensorDriver: public SensorDriverTemplate<double>
{
public:
	HumiditySensorDriver();
	double readValue() override;
protected:
private:
	SDC30 sensor_;
}; //HumiditySensorDriver

#endif //__HUMIDITYSENSORDRIVER_H__
