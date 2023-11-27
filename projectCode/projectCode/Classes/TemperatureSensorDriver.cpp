/* 
* TemperatureSensorDriver.cpp
*
* Created: 27-11-2023 17:19:50
* Author: madse
*/


#include "TemperatureSensorDriver.h"

// default constructor
TemperatureSensorDriver::TemperatureSensorDriver()
: sensor_(0x61)
{
} //TemperatureSensorDriver

double TemperatureSensorDriver::readValue()
{
	while (sensor_.ready() == false) {}; // venter indtil sensoren er klar.
	sensor_.measure();
	return sensor_.getTemperature();
}