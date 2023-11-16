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

void X10Modtager::getNextBit(uint8_t nextBit)
{
	uint8_t nextManchesterArray[32];
	
	for (uint8_t i = 0; i < 31; i++)
	{
		nextManchesterArray[i] = manchesterArray_[i + 1];
	}
	
	nextManchesterArray[31] = nextBit;
	
	// Der må være en smartere måde at gøre nedenstående på.
	for (uint8_t i = 0; i < 32; i++)
	{
		manchesterArray_[i] = nextManchesterArray[i]; 
	}
	
	this->translateFromManchesterCode();
}

bool X10Modtager::protocolAndAddressCorrect()
{
	int initiateProtocol[4] = {1,1,1,0};
	
	for (uint8_t i = 0; i < 4; i++)
	{
		if (!(dataArray_[i] == initiateProtocol[i]))
		{
			return false;
		}
		
		if (!(dataArray_[i+4] == address_[i]))
		{
			return false;
		}
	}
	
	return true;
}

char X10Modtager::getCommand()
{
	uint8_t command[8];
	const uint8_t DATA_START = 8;
	const uint8_t DATA_END = 16;
		
	for (uint8_t j = DATA_START; j < DATA_END; j++)
	{
		command[j - DATA_START] = dataArray_[j];
	}
	
	for (uint8_t i = 0; i < 27; i++) // Der er 26 bogstaver i alfabetet.
	{
		if (this->arraysEqual(asciiLookup_[i].binary, command))
		{
			return asciiLookup_[i].character;
		}
	}
	
	return 'a';
}

void X10Modtager::translateFromManchesterCode()
{
	manchesterError_ = false;

	const uint8_t manchesterArraySize = 32; // Assuming size is 32
	uint8_t dataArrayI = 0;

	for (uint8_t i = 0; i < manchesterArraySize - 1; i += 2)
	{
		if (manchesterArray_[i] == 0 && manchesterArray_[i + 1] == 1)
		{
			dataArray_[dataArrayI] = 1;
		}
		else if (manchesterArray_[i] == 1 && manchesterArray_[i + 1] == 0)
		{
			dataArray_[dataArrayI] = 0;
		}
		else
		{
			manchesterError_ = true;
		}
		
		dataArrayI++;
	}
}

bool X10Modtager::arraysEqual(uint8_t arr1[8], uint8_t arr2[8])
{
    for (int i = 0; i < 8; i++) {
	    if (arr1[i] != arr2[i]) {
		    return false;
	    }
    }
    return true;
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
