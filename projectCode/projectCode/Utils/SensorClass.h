/* 
* SensorClass.h
*
* Created: 27-11-2023 10:35:22
* Author: madse
*/


#ifndef __SENSORCLASS_H__
#define __SENSORCLASS_H__


class SensorClass
{
public:
	template <typename T>
	SensorClass(T sensorClass): sensorClass_(SensorClass);
	template <typename T>
	T readSensor();
private:
	template <typename T>
	T sensorClass_;
}; //SensorClass

#endif //__SENSORCLASS_H__
