#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
// #include "Utils/SODA.h"

#include "Utils/X10Sender.h"
#include "Utils/UART.h"

void interruptSender(X10Sender sender) {
	
}

int main(void)
{
	// SODA dataCollector;
	// dataCollector.setInterval(1);
	// dataCollector.start();
	
	X10Sender sender;
	
	uint8_t windowAddress[4] = {0,0,0,1};
	
	sender.sendData('A', windowAddress);
	
	UART uart;
	
	uart.transmitString("\r\n:SENDER:\r\n");
	
	for (int i = 0; i < 16; i++)
	{
 		int nextbit = sender.getNextBit();
		
		if (nextbit == 1) {
			uart.transmitString("1,");
			sender.enableTransmitter();
			_delay_ms(1000);
			sender.disableTransmitter();
		} else {
			sender.disableTransmitter();
			_delay_ms(1000);
			uart.transmitString("0,");
			
		}
	}
	
	uart.transmitString("\r\n:SLUT:");
	
	
	
	
}
