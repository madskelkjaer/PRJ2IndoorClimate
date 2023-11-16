/* 
* X10Sender.h
*
* Created: 02-11-2023 10:38:03
* Author: madse
*/


#ifndef __X10SENDER_H__
#define __X10SENDER_H__
#include <avr/io.h>
#include <stdio.h>

#define TRANSMITTER_TIMER OCR1A
#define TRANSMITTER_TIMER_A TCCR1A
#define TRANSMITTER_TIMER_B TCCR1B

struct asciiTable {
	char character;
	int binary[8];
};

class X10Sender
{
public:
	X10Sender();
	~X10Sender();
	void sendData(char command, uint8_t address[4]);
	bool dataReady();
	uint8_t getNextBit();
	void enableTransmitter();
	void disableTransmitter();
private:
	bool dataReady_;
	uint8_t dataArray_[16];
	uint8_t manchesterArray_[32];
	uint8_t currentBit_;
	uint8_t txPin_;
	void encodeData(char command);
	void translateToManchesterCode();
	static asciiTable asciiLookup_[];
}; //X10Sender

#endif //__X10SENDER_H__
