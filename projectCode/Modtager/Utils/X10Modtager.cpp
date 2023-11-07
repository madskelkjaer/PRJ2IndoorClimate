/* 
* X10Modtager.cpp
*
* Created: 06-11-2023 18:26:38
* Author: madse
*/


#include "X10Modtager.h"

// default constructor
X10Modtager::X10Modtager(uint8_t address[4])
{
	// Kopierer adressen til privat variabel.
	for (uint8_t i = 0; i < 4; i++)
	{
		address_[i] = address[i];
	}
} //X10Modtager

void X10Modtager::getNextBit()
{
	
}

bool X10Modtager::dataReady()
{
	return dataReady_;
}

dataArray X10Modtager::getData()
{
	dataArray data;
	for (uint8_t i = 0; i < 16; i++)
	{
		data.array[i] = dataArray_[i];
	}
	
	return data;
}

char X10Modtager::getCommand()
{
	// Første 4 bits er for at melde ud af der er en besked på vej.
	const int PROTOCOL_START = 0;
	// de efterfølgende 4 bits er adressen på enheden vi vil snakke til.
	const int ADDRESS_START = 4;
	//
	const int 
	
	// Protokollen starter altid med følgende bits.
	int initiateProtocol[4] = {1,1,1,0};
	
	// Lægger dem i dataArray, så de kan blive sendt.
	for (uint8_t i = 0; i < 4; i++)
	{
		dataArray_[i + PROTOCOL_START] = initiateProtocol[i];
		dataArray_[i + ADDRESS_START] = address[i];
	}
	return 'O';
}



asciiTable X10Modtager::asciiLookup_[] = {
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
