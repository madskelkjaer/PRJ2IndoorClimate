#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Utils/UART.h"
#include "Utils/X10Modtager.h"

int main(void)
{
	UART uart;
	
	uint8_t recieverAddress[4] = {0,0,0,1};
	
	X10Modtager modtager(recieverAddress);
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

