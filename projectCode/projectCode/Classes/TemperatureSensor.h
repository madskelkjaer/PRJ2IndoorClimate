/* 
* TemperatureSensor.h
*
* Created: 27-11-2023 10:39:32
* Author: madse
*/


#ifndef __TEMPERATURESENSOR_H__
#define __TEMPERATURESENSOR_H__

#include <stdio.h>
#include "../Utils/SensorClass.h"
#include "../Utils/SDC30.h"

#define SENSOR_ADDRESS 0x61

class TemperatureSensor : public SensorClass
{
public:
	TemperatureSensor();
	float readSensor();
}; //TemperatureSensor

#endif //__TEMPERATURESENSOR_H__
