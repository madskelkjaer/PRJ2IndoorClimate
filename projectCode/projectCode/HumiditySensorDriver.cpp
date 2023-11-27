/* 
* HumiditySensorDriver.cpp
*
* Created: 27-11-2023 17:57:20
* Author: madse
*/
#include "HumiditySensorDriver.h"

// default constructor
HumiditySensorDriver::HumiditySensorDriver()
: sensor_(0x61)
{
} //HumiditySensorDriver

double HumiditySensorDriver::readValue()
{
	while (sensor_.ready() == false) {}; // venter indtil sensoren er klar.
	sensor_.measure();
	return sensor_.getHumidity();
}