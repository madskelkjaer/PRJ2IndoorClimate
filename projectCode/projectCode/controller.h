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

// Antal vinduer der kan tilkobles systemet.
#define MAX_RECIEVERS 10

#include "Utils/UART.h"
#include "Utils/X10Sender.h"
#include "Classes/SensorDriverTemplate.h"

struct windows {
	uint8_t address[4];
};

enum debugTypes {
	COMMAND,
	WATCH,
	AUTO
};

class Controller
{
public:
	Controller();
	void start(debugTypes debug);
	void interrupt();
	void setDebug(debugTypes debug);
	debugTypes debugMode();
	void debugMenu();
	void addWindow(uint8_t address[4]);
	void windowsOpen();
	void windowsHalf();
	void windowsClosed();
	template <typename T>
	void printValue(T value);
protected:
private:
	void sendCommandToAllWindows(char command);
	UART uartDriver_;
	X10Sender x10Driver_;
	uint8_t windowState_;
	windows windows_[MAX_RECIEVERS];
	uint8_t windowsInSystem_;
	debugTypes debugMode_;
}; //controller

#endif //__CONTROLLER_H__

