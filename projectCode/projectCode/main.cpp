#include "Controller.h"

#define DEBUG_MODE true

volatile int interruptFlag = 0;

int main(void)
{
	Controller controller;
	
	controller.start(DEBUG_MODE);
	
	
	while(true)
	{	
		if (interruptFlag == 1) {
			controller.interrupt();
			controller.debugMenu();
			interruptFlag = 0;
		}
		
	}
}

ISR(INT4_vect) {
	interruptFlag = 1;
	EIFR = 0x00;
}