/* 
* X10Modtager.h
*
* Created: 06-11-2023 18:26:38
* Author: madse
*/


#ifndef __X10MODTAGER_H__
#define __X10MODTAGER_H__
#define PROTOCOL_START 0
#define PROTOCOL_END 4
#define ADDRESS_START 4
#define ADDRESS_END 8
#define DATA_START 8
#define DATA_END 16

#include <avr/io.h>
#include <stdio.h>

struct asciiTable {
	char character;
	int binary[8];
};

struct dataArray {
	uint8_t array[16];
};

class X10Modtager
{
public:
	X10Modtager(uint8_t address[4]);
	~X10Modtager();
	void getNextBit();
	bool dataReady();
	dataArray getData();
	char getCommand();
private:
	bool dataReady_;
	uint8_t dataArray_[16];
	uint8_t address_[4];
	void decodeData();
	static asciiTable asciiLookup_[];
}; //X10Modtager

#endif //__X10MODTAGER_H__
