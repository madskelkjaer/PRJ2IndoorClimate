/* 
* SensorDriver.cpp
*
* Created: 27-11-2023 17:02:21
* Author: madse
*/


#include "SensorDriver.h"

// default constructor
template <class T>
SensorDriver<T>::SensorDriver()
{
} //SensorDriver

template <class T>
void SensorDriver<T>::setMaxValue(T value)
{
	maxValue_ = value;
}

template <class T>
void SensorDriver<T>::setMinValue(T value)
{
	minValue_ = value;
}

template <class T>
T SensorDriver<T>::getMaxValue()
{
	return maxValue_;
}

template <class T>
T SensorDriver<T>::getMinValue()
{
	return minValue_;
}
