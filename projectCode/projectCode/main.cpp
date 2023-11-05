#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
// #include "Utils/SODA.h"

#include "Utils/X10Sender.h"
#include "Utils/UART.h"


int main(void)
{
	// SODA dataCollector;
	// dataCollector.setInterval(1);
	// dataCollector.start();
	
	X10Sender sender;
	
	uint8_t address[4] = {1,1,1,1};
	
	sender.sendData('A', address);
	
	UART uart;
	
	uart.transmitString("\r\n:SENDER:\r\n");
	
	for (int i = 0; i < 16; i++)
	{
		int nextbit = sender.getNextBit();
		
		if (nextbit == 1) {
			uart.transmitString("1,");
		} else {
			uart.transmitString("0,");
		}
	}
	
	uart.transmitString("\r\n:SLUT:");
	
	
	
	
}
