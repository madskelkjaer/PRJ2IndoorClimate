/* 
* X10Sender.h
*
* Created: 02-11-2023 10:38:03
* Author: madse
*/


#ifndef __X10SENDER_H__
#define __X10SENDER_H__
#include <stdio.h>

#define TRANSMITTER_TIMER TCCR1A
#define TRANSMITTER_TIMER_ON 0b01000000
#define TRANSMITTER_TIMER_OFF 0b00000000

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
	uint8_t currentBit_;
	uint8_t txPin_;
	void encodeData(char command);
	static asciiTable asciiLookup_[];
}; //X10Sender

#endif //__X10SENDER_H__
