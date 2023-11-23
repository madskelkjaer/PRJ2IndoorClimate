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

#include "Utils/I2C.h"
#include "Utils/SDC30.h"
#include "Utils/UART.h"
#include "Utils/X10Sender.h"

struct reciever {
	X10Sender com;
	uint8_t windowAddress[4];
};


class Controller
{
public:
Controller();
void start(bool debug);
protected:
private:
}; //controller

#endif //__CONTROLLER_H__

