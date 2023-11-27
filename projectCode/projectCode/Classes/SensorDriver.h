/* 
* SensorDriver.h
*
* Created: 27-11-2023 10:14:47
* Author: madse
*/


#ifndef __SENSORDRIVER_H__
#define __SENSORDRIVER_H__

#include "../Utils/SensorClass.h"

class SensorDriver
{
public:
	SensorDriver();
	void setSensorDriver(SensorClass driver);
	
	template <typename T>
	T getSensorValue();
	
	template <typename T>
	void setMaxValue(T value);
	
	template <typename T>
	void setMinValue(T value);
	
	template <typename T>
	T GetMinValue();
	
	template <typename T>
	T GetMaxValue();
protected:
private:
	SensorClass SensorDriver_;
}; //SensorDriver

#endif //__SENSORDRIVER_H__
