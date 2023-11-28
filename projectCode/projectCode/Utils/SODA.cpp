/* 
* SODA.cpp
*
* Created: 26-10-2023 11:13:48
* Author: madse
*/
#define F_CPU 16000000
#include <util/delay.h>
#include "SODA.h"
#include <stdio.h>

#define SLAVE_ADDRESS 0x61

// default constructor
SODA::SODA() :
	sdc30_(SLAVE_ADDRESS), uart_(),
	co2_(0), temperature_(0), humidity_(0)
{
	// default collection_interval
} //SODA

void SODA::start()
{
	uint8_t numAverage = 3;
	while(true)
	{
		collectData(numAverage);
		printData();

		uint32_t intervalInMS = collectionInterval_ * 60000;

		for (uint32_t i=1; i<intervalInMS; i++)
		{
			_delay_ms(1);
		}
	}
}

void SODA::setInterval(uint8_t intervalMinutes)
{
	collectionInterval_ = intervalMinutes;
}

void SODA::collectData(uint8_t numAverage)
{	
	float co2_sum = 0;
	float temp_sum = 0;
	float hum_sum = 0;
	
	for (uint8_t i = 0; i < numAverage; i++)
	{
		sdc30_.measure();
		co2_sum += sdc30_.getCo2();
		temp_sum += sdc30_.getTemperature();
		hum_sum += sdc30_.getHumidity();
		
		_delay_ms(100); // 100ms imellem hver måling.
	}
	
	co2_ = co2_sum / numAverage;
	temperature_ = temp_sum / numAverage;
	humidity_ = hum_sum / numAverage;
	
}

void SODA::printData()
{
	char buffer[100];

	int co2 = (int)co2_;
	int co2_decimal = (int)((co2_ - co2) * 100);
	
	int temp = (int)temperature_;
	int temp_decimal = (int)((temperature_ - temp) * 100);
	
	int humidity = (int)humidity_;
	int humidity_decimal = (int)((humidity_ - humidity) * 100);
	
	sprintf(buffer, "C: %d.%02d T: %d.%02d H: %d.%02d", co2, co2_decimal, temp, temp_decimal, humidity, humidity_decimal);
	uart_.transmitString(buffer);
	uart_.transmitString("\r\n");
}