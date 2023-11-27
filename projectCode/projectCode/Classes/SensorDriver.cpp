/* 
* SensorDriver.cpp
*
* Created: 27-11-2023 17:02:21
* Author: madse
*/


#include "SensorDriver.h"

// default constructor
template <typename T>
SensorDriver<T>::SensorDriver()
{
} //SensorDriver

template <typename T>
void SensorDriver<T>::setMaxValue(T value)
{
	maxValue_ = value;
}

template <typename T>
void SensorDriver<T>::setMinValue(T value)
{
	minValue_ = value;
}

template <typename T>
T SensorDriver<T>::getMaxValue()
{
	return maxValue_;
}

template <typename T>
T SensorDriver<T>::getMinValue()
{
	return minValue_;
}