
// #include "Utils/SODA.h"

#include "Controller.h"

X10Sender sender;
reciever window = {sender, {0,0,0,1}};

volatile int interruptFlag = 0;

int main(void)
{
	// tænder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // Configure INT4 to trigger on rising edge
	EIMSK |= (1 << INT4);                 // Enable INT4
	sei();
	
	DDRB |= (1 << PB5);
	
	
	
	Controller controller;
	
	// tænder interrupts.
	EICRB |= (1 << ISC41) | (1 << ISC40); // Configure INT4 to trigger on rising edge
	EIMSK |= (1 << INT4);                 // Enable INT4

	sei();
	
	DDRB |= (1 << PB5);
	
	UART uart;
	uart.transmitString("Menu:\r\n");
	uart.transmitString("o - Aaben vindue\r\n");
	uart.transmitString("c - Luk vindue\r\n");
	uart.transmitString("h - Halvt aabent\r\n");
	uart.transmitString("m - Denne menu\r\n");
	
	X10Sender sender;
	uint8_t windowAddress[4] = {0,0,0,1};
	
	char recievedChar;
	char buffer[10];
	uint8_t sendtNum = 0;
	
	_delay_ms(5000);
	
	while(true)
	{
		if (!sender.dataReady()) {
			sender.sendData('O', windowAddress);
			sendtNum++;
			
			sprintf(buffer, "%i", sendtNum);
			uart.transmitString("Sendt: ");
			uart.transmitString(buffer);
			uart.transmitString("\r\n");
			
			if (sendtNum == 1000) {
				return 0;	
			}
			
			/*uart.transmitString("\r\n\nKlar til næste kommando");
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
			}*/
		}
		
		if (interruptFlag == 1) {
			uint8_t nextBit = sender.getNextBit();

			sender.transmit(nextBit);
			
			if (nextBit == 1) {
				uart.transmitString("1 ");
				} else {
				uart.transmitString("0 ");
			}
			
			interruptFlag = 0;
		}
		
	}
}

ISR(INT4_vect) {
	interruptFlag = 1;
	EIFR = 0x00;
}