/* 
* controller.cpp
*
* Created: 18-11-2023 19:27:13
* Author: madse
*/
#include "controller.h"

// default constructor
Controller::Controller()
: uartDriver_(), x10Driver_()
{
	windowsInSystem_ = 0;
}

void Controller::start(debugTypes debug = NONE) // default debugmode er false
{
	// tænder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // Configure INT4 to trigger on rising edge
	EIMSK |= (1 << INT4);                 // Enable INT4
	sei();
	
	// Tænder output PB5.
	DDRB |= (1 << PB5);
	
	debugMode_ = debug;
	if (debugMode_ == COMMAND)
	{
		uartDriver_.transmitString("Menu:\r\n");
		uartDriver_.transmitString("o - Aaben vindue\r\n");
		uartDriver_.transmitString("c - Luk vindue\r\n");
		uartDriver_.transmitString("h - Halvt aabent\r\n");
		uartDriver_.transmitString("m - Denne menu\r\n");
	}
}

void Controller::interrupt()
{
	uint8_t nextBit = x10Driver_.getNextBit();
	
	x10Driver_.transmit(nextBit);
	
	// Hvis debugmode er NONE, så skal vi returnere.
	if (this->debugMode() == NONE) return;
	
	// ellers skriver vi til output hvad der er sendt.
	if (nextBit == 1) {
		uartDriver_.transmitString(" 1 ");
	} else {
		uartDriver_.transmitString(" 0 ");
	}
	
}

bool Controller::debugMode()
{
	return debugMode_;
}

void Controller::debugMenu()
{
	// Hvis debugmode ikke er commands, så skal vi returnere.
	if (this->debugMode() != COMMAND) return;
	
	/*if (!x10Driver_.dataReady()) {
		this->sendCommandToAllWindows('O');
	}*/
	
	if (!x10Driver_.dataReady()) {
		uartDriver_.transmitString("\r\n\nKlar til næste kommando");
		switch (uartDriver_.recieve())
		{
			case 'o':
			{
				this->sendCommandToAllWindows('O');
			}
			break;
			case 'c':
			{
				this->sendCommandToAllWindows('C');
			}
			break;
			case 'h':
			{
				this->sendCommandToAllWindows('H');
			}
			break;
			case 'm':
			{
				uartDriver_.transmitString("Menu:\r\n");
				uartDriver_.transmitString("o - Aaben vindue\r\n");
				uartDriver_.transmitString("c - Luk vindue\r\n");
				uartDriver_.transmitString("h - Halvt aabent\r\n");
				uartDriver_.transmitString("m - Denne menu\r\n");
			}
			break;
		}
	}
}


void Controller::addWindow(uint8_t address[4])
{
	if (windowsInSystem_ < MAX_RECIEVERS) {
		for (uint8_t i = 0; i < 4; i++)
		{
			windows_[windowsInSystem_].address[i] = address[i];
		}
		
		windowsInSystem_++;
	}
}

void Controller::sendCommandToAllWindows(char command)
{
	if (debugMode_ != NONE) { 
		uartDriver_.transmitString("\r\nSENDER ");
		uartDriver_.transmit(command);
		uartDriver_.transmitString("\r\n");
	}
	
	x10Driver_.sendData(command, windows_[0].address);
	
	// Nedenstående implementering har nogle disadvantages.
	/*for (uint8_t i = 0; i < windowsInSystem_; i++)
	{
		x10Driver_.sendData(command, windows_[i].address);
	}*/
	
	
}

void Controller::windowsOpen()
{
	if (windowState_ == 100) return;
	this->sendCommandToAllWindows('O');
	windowState_ = 100;
}

void Controller::windowsHalf()
{
	if (windowState_ == 50) return;
	this->sendCommandToAllWindows('H');
	windowState_ = 50;
}

void Controller::windowsClosed()
{
	if (windowState_ == 0) return;
	this->sendCommandToAllWindows('C');
	windowState_ = 0;
}

// Specialization for int
/*
template <>
void Controller::printValue<int>(int value) {
	if (x10Driver_.dataReady()) {return;} // Hvis der sendes data, vil vi ikke forstyrre.
	char buffer[50];
	sprintf(buffer, "\r\nInteger: %d", value);
	uartDriver_.transmitString(buffer);
}*/

// Specialization for double
template <>
void Controller::printValue<double>(double value) {
	// if (x10Driver_.dataReady()) {return;} // Hvis der sendes data, vil vi ikke forstyrre.
	char buffer[50];
	int integerPart = (int)value;
	int decimalPart = (int)((value - integerPart) * 100);
	
	sprintf(buffer, "\r\nDouble: %d.%02d", integerPart, decimalPart);
	uartDriver_.transmitString(buffer);
}

// Specialization for const char*
/*
template <>
void Controller::printValue<const char*>(const char* value) {
	if (x10Driver_.dataReady()) {return;} // Hvis der sendes data, vil vi ikke forstyrre.
	char buffer[100];
	sprintf(buffer, "\r\nString: %s", value);
	uartDriver_.transmitString(buffer);
}*/