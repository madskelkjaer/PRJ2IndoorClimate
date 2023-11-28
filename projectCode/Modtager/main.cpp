#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "Utils/UART.h"
#include "Utils/X10Modtager.h"

volatile int interruptFlag = 0;

int main(void)
{
	// t�nder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // Configure INT4 to trigger on rising edge
	EIMSK |= (1 << INT4);                 // Enable INT4
	sei();
	
	// S�tter PORTB som input port.
	DDRB &= ~(1 << PB5);
	
	UART uart;
	uart.transmitString("KLAR!!!!");
	
	uint8_t recieverAddress[4] = {0,0,0,1};
	
	X10Modtager modtager(recieverAddress);
	
	char command = 'a';
	
	uint8_t recievedBit = 0;
	uint8_t numRecieved = 0;
	char buffer[10];
	
	_delay_us(5000);
	
	while (1) 
    {		
		if (interruptFlag == 1)
		{
			_delay_us(500);
			recievedBit = PINB & (1 << PB5) ? 1 : 0;
			
			// Gem data ved interrupt.
			if (recievedBit == 1) {
				uart.transmitString("1 ");
			} else {
				uart.transmitString("0 ");
			}
			modtager.getNextBit(recievedBit);
			
			command = 'a';
			if (modtager.protocolAndAddressCorrect()) {
				command = modtager.getCommand();
			}
			
			if (command == 'O')
			{
				uart.transmitString("MODTOG KOMMANDO O\r\n");
				// �ben vindue.
				numRecieved++;
				
				sprintf(buffer, "%i", numRecieved);
				
				uart.transmitString("Modtaget: ");
				uart.transmitString(buffer);
			}
			
			if (command == 'C')
			{
				uart.transmitString("MODTOG KOMMANDO C\r\n");
				// Luk vindue
			}
			
			if (command == 'H')
			{
				uart.transmitString("MODTOG KOMMANDO H\r\n");
				// Halvt �bent vindue
			}
			
			interruptFlag = 0;
		}
    }
}


ISR(INT4_vect) {
	interruptFlag = 1;
	EIFR = 0x00;
}