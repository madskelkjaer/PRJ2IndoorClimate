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
	numSendt_ = 1;
}

void Controller::start(debugTypes debug = AUTO) // default debugmode er AUTO
{
	cli();
	// tænder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // INT4 skal trigger ved stigende kant.
	EIMSK |= (1 << INT4);                 // Tænd INT4
	
	// Bruger timer4 med
	// prescaler 1024
	// CTC mode.
	// til at aktivere en interrupt hvert minut til aflæsening af 
	TCCR4A = 0;
	TCCR4B = 0;
	TCCR4B |= (1 << WGM42) | (1 << CS42) | (1 << CS40); // CTC mode, Prescaler 1024
	
	TCNT4 = 0;
	
	// Set compare match register for 1hz increments
	OCR4A = 15624; // = 16000000 / (1024 * 1) - 1 (must be <65536)
	
	// Enable Timer4 compare interrupt
	TIMSK4 |= (1 << OCIE4A);
	
	// Global tænd for interrupts.
	sei();
	
	// Tænder output PB5. Dette er vores data strøm til x.10 protokollen.
	DDRB |= (1 << PB5);
	
	debugMode_ = debug;
	if (this->debugMode() == COMMAND)
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
	
	// Hvis debugmode er AUTO, så skal vi returnere.
	if (this->debugMode() == AUTO) { return; }
	
	// ellers skriver vi til output hvad der er sendt.
	if (nextBit == 1) {
		uartDriver_.transmitString(" 1 ");
		} else {
		uartDriver_.transmitString(" 0 ");
	}
}

debugTypes Controller::debugMode()
{
	return debugMode_;
}

void Controller::debugMenu()
{
	// Hvis debugmode ikke er commands, så skal vi returnere.
	if (this->debugMode() != COMMAND) return;

	char buffer[10];
	
	if (!x10Driver_.dataReady()) {
		uartDriver_.transmitString("\r\n\nKlar til næste kommando");
		switch (uartDriver_.recieve())
		{
			case 'o':
			{
				this->sendCommandToAllWindows('O');
				
				sprintf(buffer, "%i", numSendt_);
				uartDriver_.transmitString("Sendt: ");
				uartDriver_.transmitString(buffer);
				uartDriver_.transmitString("\r\n");
				numSendt_++;
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
	if (debugMode_ != AUTO) { 
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