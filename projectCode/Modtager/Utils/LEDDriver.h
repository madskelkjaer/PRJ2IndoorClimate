/*
* LedDriver.h
*
* Created: 27-11-2023 13:47:41
* Author: madse
*/


#ifndef __LEDDRIVER_H__
#define __LEDDRIVER_H__
#include <avr/io.h>

class LedDriver
{
	public:
	LedDriver();
	void LEDopen();
	void LEDhalf();
	void LEDclosed();
	protected:
	private:
}; //LedDriver

#endif //__LEDDRIVER_H__