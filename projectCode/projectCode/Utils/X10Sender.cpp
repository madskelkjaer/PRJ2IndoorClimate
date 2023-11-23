/* 
* X10Sender.cpp
*
* Created: 02-11-2023 10:38:03
* Author: madse
*/
#define F_CPU 16000000
#include <util/delay.h>
#include "X10Sender.h"

// default constructor
X10Sender::X10Sender()
{
	currentBit_ = 0;
	dataReady_ = false;
	dataArray_[0] = 0;
	dataArray_[1] = 0;
	dataArray_[2] = 0;
	dataArray_[3] = 0;
	dataArray_[4] = 0;
	dataArray_[5] = 0;
	dataArray_[6] = 0;
	dataArray_[7] = 0;
	
	// PORTB er output.
	DDRB = 0b00000000;
	
	// Timer 1 til CTC mode.
	// Prescaler = 1
	// Toggle compare match.
	TRANSMITTER_TIMER_A = 0b01000000;
	TRANSMITTER_TIMER_B = 0b00001001;
	
	TRANSMITTER_TIMER = 0;
	
	// Pin som der bliver sendt 120kHz på.
	// txPin_ = DDRB;
	// txPin_ = 0xFF;
} //X10Sender

// default destructor
X10Sender::~X10Sender()
{
// 	delete[] dataArray_;
// 	delete[] asciiLookup_;
} //~X10Sender

void X10Sender::sendData(char command, uint8_t address[4])
{
	if (dataReady_) return; // Hvis der allerede er data, skal der ikke sendes en kommando.
	
	
	// Første 4 bits er for at melde ud af der er en besked på vej.
	const int PROTOCOL_START = 0;
	// de efterfølgende 4 bits er adressen på enheden vi vil snakke til.
	const int ADDRESS_START = 4;
	
	// Protokollen starter altid med følgende bits.
	int initiateProtocol[4] = {1,1,1,0};
	
	// Lægger dem i dataArray, så de kan blive sendt.
	for (uint8_t i = 0; i < 4; i++)
	{
		dataArray_[i + PROTOCOL_START] = initiateProtocol[i];
		dataArray_[i + ADDRESS_START] = address[i];
	}
	
	this->encodeData(command);
	this->translateToManchesterCode();
}

bool X10Sender::dataReady()
{
  	return dataReady_;
}

uint8_t X10Sender::getNextBit()
{
	// Hvis vi er nået til enden af vores dataArray_ så sender vi bare 0'ere for resten.
	if (currentBit_ >= 32 || dataReady_ == false) 
	{
		dataReady_ = false;
		return 0;
	}
	
	uint8_t nextBit = manchesterArray_[currentBit_];
	currentBit_++;
	return nextBit;
}

void X10Sender::enableTransmitter() 
{
	DDRB = 0b00100000; // Sætter PORTB (OC1A el. PB5) til output.
	TRANSMITTER_TIMER = 66; // 120Khz
}

void X10Sender::disableTransmitter() 
{
	DDRB = 0b00000000; // Slukker PORTB.
	TRANSMITTER_TIMER = 0;
}

void X10Sender::transmit(uint8_t bit)
{
	if (bit == 1) {
		this->enableTransmitter();
		_delay_ms(1);
		this->disableTransmitter();
	} else {
		this->disableTransmitter();
		_delay_ms(1);
	}
}

void X10Sender::encodeData(char command)
{	
	const int DATA_START = 8;
	const int DATA_END = 16;
	
	for (uint8_t i = 0; i < 27; i++) // Der er 26 bogstaver i alfabetet.
	{
		if (asciiLookup_[i].character == command) 
		{	
			// Kopierer binært data fra lookup tabellen til dataArray fra index 8 og frem.
			for (uint8_t j = DATA_START; j < DATA_END; j++)
			{
				dataArray_[j] = asciiLookup_[i].binary[j - DATA_START];
			}
			
			// sætter dataReady og currentbit til standard værdier.
			dataReady_ = true;
			currentBit_ = 0;
			
			return;
		}
	}
}

void X10Sender::translateToManchesterCode()
{
	uint8_t manchesterI = 0;
	for (uint8_t i = 0; i< 16; i++)
	{
		manchesterArray_[manchesterI] = dataArray_[i] == 0 ? 1 : 0;
		manchesterArray_[manchesterI + 1] = dataArray_[i] == 0 ? 0 : 1;
		
		manchesterI += 2;
	}
}

// Der er 100p en bedre måde at gøre det her på. Jeg magter bare ikke.
// sikkert noget med at minus med antallet af bogstaver før A i ascii. idk. bøvlet.
asciiTable X10Sender::asciiLookup_[] = {
	{'A', {0,1,0,0,0,0,0,1}},
	{'B', {0,1,0,0,0,0,1,0}},
	{'C', {0,1,0,0,0,0,1,1}},
	{'D', {0,1,0,0,0,1,0,0}},
	{'E', {0,1,0,0,0,1,0,1}},
	{'F', {0,1,0,0,0,1,1,0}},
	{'G', {0,1,0,0,0,1,1,1}},
	{'H', {0,1,0,0,1,0,0,0}},
	{'I', {0,1,0,0,1,0,0,1}},
	{'J', {0,1,0,0,1,0,1,0}},
	{'K', {0,1,0,0,1,0,1,1}},
	{'L', {0,1,0,0,1,1,0,0}},
	{'M', {0,1,0,0,1,1,0,1}},
	{'N', {0,1,0,0,1,1,1,0}},
	{'O', {0,1,0,0,1,1,1,1}},
	{'P', {0,1,0,1,0,0,0,0}},
	{'Q', {0,1,0,1,0,0,0,1}},
	{'R', {0,1,0,1,0,0,1,0}},
	{'S', {0,1,0,1,0,0,1,1}},
	{'T', {0,1,0,1,0,1,0,0}},
	{'U', {0,1,0,1,0,1,0,1}},
	{'V', {0,1,0,1,0,1,1,0}},
	{'W', {0,1,0,1,0,1,1,1}},
	{'X', {0,1,0,1,1,0,0,0}},
	{'Y', {0,1,0,1,1,0,0,1}},
	{'Z', {0,1,0,1,1,0,1,0}},
};