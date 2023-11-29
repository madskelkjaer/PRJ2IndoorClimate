/*
* LedDriver.cpp
*
* Created: 27-11-2023 13:47:41
* Author: madse
*/


#include "LedDriver.h"

// default constructor
LedDriver::LedDriver()
{
} //LedDriver

void LedDriver::LEDopen()
{
	PORTB |= (1<<PB4);
	PORTB &= ~(1<<PB6);
	PORTB &= ~(1<<PB7);
}

void LedDriver::LEDhalf()
{
	PORTB |= (1<<PB6);
	PORTB &= ~(1<<PB4);
	PORTB &= ~(1<<PB7);
}

void LedDriver::LEDclosed()
{
	PORTB |= (1<<PB7);
	PORTB &= ~(1<<PB6);
	PORTB &= ~(1<<PB4);
}