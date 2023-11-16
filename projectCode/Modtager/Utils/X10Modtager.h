/* 
* X10Modtager.h
*
* Created: 06-11-2023 18:26:38
* Author: madse
*/


#ifndef __X10MODTAGER_H__
#define __X10MODTAGER_H__

#include <avr/io.h>
#include <stdio.h>

struct asciiTable {
	char character;
	uint8_t binary[8];
};

class X10Modtager
{
public:
	X10Modtager(uint8_t address[4]);
	~X10Modtager();
	void getNextBit(uint8_t nextBit);
	bool protocolAndAddressCorrect();
	char getCommand();
private:
	uint8_t dataArray_[16];
	uint8_t manchesterArray_[32];
	bool manchesterError_;
	uint8_t address_[4];
	void decodeData();
	bool arraysEqual(uint8_t arr1[8], uint8_t arr2[8]);
	void translateFromManchesterCode();
	static asciiTable asciiLookup_[];
}; //X10Modtager

#endif //__X10MODTAGER_H__
