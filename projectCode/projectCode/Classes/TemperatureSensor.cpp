/* 
* TemperatureSensor.cpp
*
* Created: 27-11-2023 10:39:32
* Author: madse
*/


#include "TemperatureSensor.h"

// default constructor
TemperatureSensor::TemperatureSensor(SENSOR_ADDRESS)
{
	uint8_t sensorAddress = 0x61;
	sdc30_(sensorAddress);
} //TemperatureSensor

float TemperatureSensor::readSensor()
{
	while (sdc30_.ready() == false) {}; // Imens sensoren ikke er klar, skal vi vente.
	sdc30_.measure(); // sensoren måler værdier.
	return sdc30_.getTemperature(); // vi returnerer temperaturen.
}