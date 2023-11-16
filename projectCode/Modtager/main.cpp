#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Utils/UART.h"
#include "Utils/X10Modtager.h"

volatile int interruptFlag = 0;

int main(void)
{
	// tænder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // Configure INT4 to trigger on rising edge
	EIMSK |= (1 << INT4);                 // Enable INT4
	sei();
	
	// Sætter PORTB som input port.
	DDRB |= (0 << PB5);
	PORTB |= (0 << PB5);
	
	
	UART uart;
	
	uint8_t recieverAddress[4] = {0,0,0,1};
	
	X10Modtager modtager(recieverAddress);
	
	char command = 'a';
	
    while (1) 
    {
		// Hvis vi ikke har fået interrupt, skal vi blot fortsætte.
		if (interruptFlag == 0)
		{
			continue;	
		}
		
		// Gem data ved interrupt.
		uint8_t recievedBit = PORTB;
		modtager.getNextBit(recievedBit);
		
		command = 'a';	
		if (modtager.protocolAndAddressCorrect()) {
			command = modtager.getCommand();
		}
		
		if (command == 'O')
		{
			uart.transmitString("MODTOG KOMMANDO O");
			// Åben vindue.
		}
		
		if (command == 'C')
		{
			uart.transmitString("MODTOG KOMMANDO C");
			// Luk vindue
		}
		
		if (command == 'H')
		{
			uart.transmitString("MODTOG KOMMANDO H");
			// Halvt åbent vindue
		}
		
		interruptFlag = 0;
    }
}


ISR(INT4_vect) {
	interruptFlag = 1;
	EIFR = 0x00;
}