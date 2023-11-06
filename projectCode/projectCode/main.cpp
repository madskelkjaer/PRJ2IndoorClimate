#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
// #include "Utils/SODA.h"

#include "Utils/X10Sender.h"
#include "Utils/UART.h"

volatile int interruptFlag = 0;

int main(void)
{
	// tænder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // Configure INT4 to trigger on rising edge
	EIMSK |= (1 << INT4);                 // Enable INT4

	sei();
	
	// SODA dataCollector;
	// dataCollector.setInterval(1);
	// dataCollector.start();
	UART uart;
	uart.transmitString("Menu:\r\n");
	uart.transmitString("o - Aaben vindue\r\n");
	uart.transmitString("c - Luk vindue\r\n");
	uart.transmitString("h - Halvt aabent\r\n");
	uart.transmitString("m - Denne menu\r\n");
	
	X10Sender sender;
	uint8_t windowAddress[4] = {0,0,0,1};
	
	char recievedChar;
	while(true)
	{
		if (!sender.dataReady()) {
			uart.transmitString("\r\n\nKlar til næste kommando");
			recievedChar = uart.recieve();
			switch (recievedChar)
			{
				case 'o':
				{
					uart.transmitString("Sender O\r\n");
					sender.sendData('O', windowAddress);
				}
				break;
				case 'c':
				{
					uart.transmitString("Sender C\r\n");
					sender.sendData('C', windowAddress);
				}
				break;
				case 'h':
				{
					uart.transmitString("Sender H\r\n");
					sender.sendData('H', windowAddress);
				}
				break;
				case 'm':
				{
					uart.transmitString("Menu:\r\n");
					uart.transmitString("o - Aaben vindue\r\n");
					uart.transmitString("c - Luk vindue\r\n");
					uart.transmitString("h - Halvt aabent\r\n");
					uart.transmitString("m - Denne menu\r\n");
				}
				break;
			}	
		}
		
		if (interruptFlag == 1) {
			uint8_t nextBit = sender.getNextBit();
			
			DDRB |= (1 << PB5);
			PORTB |= (1 << PB5);
			
			if (nextBit == 2) {
				// Hvis der ikke skal ske noget, skal der sendes et 1 tal.
				//DDRB |= (1 << PB5);
				//PORTB |= (1 << PB5);
			} else if (nextBit == 1) {
				uart.transmitString("1 ");
				sender.enableTransmitter();
				_delay_ms(1);
				sender.disableTransmitter();
			} else {
				uart.transmitString("0 ");
				sender.disableTransmitter(); // Måske skal denne bare ændres til 1;
				_delay_ms(1);
			}
			
			DDRB |= (0 << PB5);
			PORTB |= (0 << PB5);
						
			interruptFlag = 0;
		}
		
	}
}

ISR(INT4_vect) {
	interruptFlag = 1;	
	EIFR = 0x00;
}