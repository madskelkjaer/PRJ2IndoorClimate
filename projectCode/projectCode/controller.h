/* 
* controller.h
*
* Created: 18-11-2023 19:27:13
* Author: madse
*/


#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define SLAVE_ADDRESS 0x61

#include "Utils/I2C.h"
#include "Utils/SDC30.h"
#include "Utils/UART.h"
#include "Utils/X10Sender.h"

class Controller
{
public:
Controller();
void start(bool debug);
void interrupt();
bool debugMode();
void debugMenu();
protected:
private:
	I2C i2cDriver_;
	SDC30 sdc30Driver_;
	UART uartDriver_;
	X10Sender x10Driver_;
	uint8_t recieverAddress_[4];
	bool debug_;

}; //controller

#endif //__CONTROLLER_H__

