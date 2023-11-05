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
	SDC30 sdc(SLAVE_ADDRESS);
	sdc30_ = sdc;
	
	UART uart;
	uart_ = uart;
	
	// default collection_interval
} //SODA

void SODA::start()
{
	while(true)
	{
		collectData();
		printData();

		uint8_t intervalInMinutes = collectionInterval_ * 60000;

		for (uint8_t i=1; i<intervalInMinutes; i++)
		{
			_delay_ms(1);
		}
	}
}

void SODA::setInterval(uint8_t intervalMinutes)
{
	collectionInterval_ = intervalMinutes;
}

void SODA::collectData()
{
	uint8_t numAverage = 3;
	
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
	sprintf(buffer, "C: %.2f T: %.2f H: %.2f", co2_, temperature_, humidity_);
	uart_.transmitString(buffer);
}