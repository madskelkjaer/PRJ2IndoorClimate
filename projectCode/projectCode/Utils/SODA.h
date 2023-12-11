/* 
* SODA.h
*
* Created: 26-10-2023 11:13:48
* Author: madse
*/


#ifndef __SODA_H__
#define __SODA_H__
#include "UART.h"
#include "SDC30.h"

/*
* SODA - Sensor Observation Data Aggregator
*/

class SODA
{
public:
	SODA();
	void start();
	void setInterval(uint8_t intervalMinutes);
	void collectData(uint8_t numAverage);
	void printData();
	
private:
	uint8_t collectionInterval_;
	SDC30 sdc30_;
	UART uart_;
	double co2_;
	double temperature_;
	double humidity_;
}; //SODA

#endif //__SODA_H__
