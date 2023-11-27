#include "Controller.h"

#include "HumiditySensorDriver.h"
#include "Utils/UART.h"


#define DEBUG_MODE true

volatile int interruptFlag = 0;

void float_to_string(char* buffer, double value)
{
	int integerPart = (int)value;
	int decimalPart = (int)((value - integerPart) * 100);
	
	sprintf(buffer, "%d.%02d", integerPart, decimalPart);
};

int main(void)
{
	// Controller controller;
	// controller.start(DEBUG_MODE);
	
	UART uart;
	
	HumiditySensorDriver humiditySensor;
	humiditySensor.setMaxValue(60.0);
	humiditySensor.setMinValue(30.0);
	
	char buffer_string[4];
	double measurement;
	
	while(true)
	{
		measurement = humiditySensor.readValue();
		
		
		uart.transmitString("\r\nHU:    ");
		float_to_string(buffer_string, measurement);
		uart.transmitString(buffer_string);
		
	}
	
	
	return 0;
	
	/*while(true)
	{	
		if (interruptFlag == 1) {
			controller.interrupt();
			controller.debugMenu();
			interruptFlag = 0;
		}
		
	}*/
}

ISR(INT4_vect) {
	interruptFlag = 1;
	EIFR = 0x00;
}