/* 
* controller.cpp
*
* Created: 18-11-2023 19:27:13
* Author: madse
*/
#include "controller.h"

// default constructor
Controller::Controller()
: i2cDriver_(), sdc30Driver_(SLAVE_ADDRESS), uartDriver_(), x10Driver_(), recieverAddress_({0,0,0,1})
{
}

void Controller::start(bool debug = false) // default debugmode er false
{
	// tænder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // Configure INT4 to trigger on rising edge
	EIMSK |= (1 << INT4);                 // Enable INT4
	sei();
	
	// Tænder output PB5.
	DDRB |= (1 << PB5);
	
	debug_ = debug;
	if (debug_)
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
	
	// Hvis debugmode er falsk, så skal vi returnere.
	if (this->debugMode() == false) return;
	
	// ellers skriver vi til output hvad der er sendt.
	if (nextBit == 1) {
		uartDriver_.transmitString("1 ");
		} else {
		uartDriver_.transmitString("0 ");
	}
	
}

bool Controller::debugMode()
{
	return debug_;
}

void Controller::debugMenu()
{		
	// Hvis debugmode er falsk, så skal vi returnere.
	if (this->debugMode() == false) return;
	
	if (!x10Driver_.dataReady()) {
		x10Driver_.sendData('O', recieverAddress_);
		
		uartDriver_.transmitString("\r\n\nKlar til næste kommando");
		switch (uartDriver_.recieve())
		{
			case 'o':
			{
				uartDriver_.transmitString("Sender O\r\n");
				x10Driver_.sendData('O', recieverAddress_);
			}
			break;
			case 'c':
			{
				uartDriver_.transmitString("Sender C\r\n");
				x10Driver_.sendData('C', recieverAddress_);
			}
			break;
			case 'h':
			{
				uartDriver_.transmitString("Sender H\r\n");
				x10Driver_.sendData('H', recieverAddress_);
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

