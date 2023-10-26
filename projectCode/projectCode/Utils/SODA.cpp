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
SODA::SODA()
{
	SDC30 sdc(SLAVE_ADDRESS);
	sdc30_ = sdc;
	
	UART uart;
	uart_ = uart;
} //SODA

void SODA::start()
{
	while(true)
	{
		collectData();
		printData();

		_delay_ms(collectionInterval_ * 60000);
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

void SODA::printData() const
{
	char buffer[100];
	sprintf(buffer, "C: %.2f T: %.2f H: %.2f", co2_, temperature_, humidity_);
	uart_.transmitString(buffer);
}