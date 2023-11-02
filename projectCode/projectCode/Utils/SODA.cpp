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
SODA::SODA() : sdc30_(SLAVE_ADDRESS), uart_()
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
	sdc30_.measure();
	
	co2_ = sdc30_.getCo2();
	temperature_ = sdc30_.getTemperature();
	humidity_ = sdc30_.getHumidity();
}

void SODA::printData()
{
	char buffer[100];
	sprintf(buffer, "C: %.2f T: %.2f H: %.2f", co2_, temperature_, humidity_);
	uart_.transmitString(buffer);
}