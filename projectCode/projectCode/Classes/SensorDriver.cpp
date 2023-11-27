/*
 * SensorDriver.cpp
 *
 * Created: 27-11-2023 11:38:30
 *  Author: madse
 */ 
#include "SensorDriver.h"

SensorDriver::SensorDriver()
{
	
}

void SensorDriver::setSensorDriver(SensorClass driver)
{
	SensorDriver_ = driver;
}


template <typename T>
T SensorDriver::getSensorValue()
{
	return SensorDriver_.readSensor();
}
