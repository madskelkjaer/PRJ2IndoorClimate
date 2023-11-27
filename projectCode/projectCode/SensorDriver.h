/* 
* SensorDriver.h
*
* Created: 27-11-2023 17:02:22
* Author: madse
*/


#ifndef __SENSORDRIVER_H__
#define __SENSORDRIVER_H__

template <class T>
class SensorDriver
{
public:
	SensorDriver();
	virtual T readValue();
	void setMaxValue(T value);
	void setMinValue(T value);
	T getMaxValue();
	T getMinValue();
protected:
	T maxValue_;
	T minValue_;
}; //SensorDriver

#endif //__SENSORDRIVER_H__
