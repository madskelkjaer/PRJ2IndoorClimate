/*
 * CPPFile1.cpp
 *
 * Created: 16-10-2023 14:13:23
 *  Author: madse
 */
#include <avr/io.h>
#include "UART.h"

UART::UART()
{
	// Initialiserer UART med BAUD-rate 9600 (beregnet i cheatsheet)
	// fosc / (16(UBRRn+1)) -solve-> UBRRn = 103,167.
	unsigned int ubrr = 103;
	
	// Set baud rate
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	// Enable transmitter and receiver
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void UART::transmit(unsigned char data) 
{
	// Wait for empty transmit buffer
	while (!(UCSR0A & (1 << UDRE0)));

	// Put data into buffer, sends the data
	UDR0 = data;
}

void UART::transmitString(const char *str) 
{
	// Transmit each character in the string
	while (*str) {
		this->transmit(*str);
		str++;
	}
}

unsigned char UART::recieve() 
{
	// Wait for data to be received
	while (!(UCSR0A & (1 << RXC0)));
	
	// Get and return received data from buffer
	return UDR0;
}

void UART::recieveString(char* buffer, int length) 
{
	int index = 0;
	char receivedChar;
	do {
		receivedChar = recieve();
		if(index < length - 1) {  // Ensure buffer doesn't overflow
			buffer[index++] = receivedChar;
		}
	} while (receivedChar != '\n' && index < length - 1);
	buffer[index] = '\0';  // Null-terminate the string
}