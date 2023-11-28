#include "Controller.h"

#include "Classes/HumiditySensorDriver.h"
#include "Utils/UART.h"

#define DEBUG_MODE WATCH
#define MEASURE_EVERY_SECONDS 5

volatile uint8_t interruptFlag = 0;
volatile uint8_t measureFlag = 0;
volatile uint8_t measureOverflow = 0; 

int main(void)
{
	UART uart;
	
	Controller controller;
	controller.start(DEBUG_MODE);
	
	uint8_t window1[4] = {0,0,0,1};
	
	controller.addWindow(window1);
	
	HumiditySensorDriver humiditySensor;
	humiditySensor.setMaxValue(60.0);
	humiditySensor.setMinValue(30.0);
	
	while(true)
	{	
		if (measureFlag == 1) {
			if (controller.debugMode() == WATCH) {
				controller.printValue(humiditySensor.readValue());
			}
			uart.transmitString("MEASURE TRIGGERED\r\n");
			double humidityProcentOff = humiditySensor.outsideLimits();
			
			if (humidityProcentOff < 10 && 0 < humidityProcentOff ) {
				// Hvis vores measurement er under 10% af limits, så skal vi kun åbne vinduet halvt.
				controller.windowsHalf();
				} else if (humidityProcentOff > 10) {
				// Hvis det er mere end 10%, så åbner vi vinduet helt.
				controller.windowsOpen();
				} else {
				controller.windowsClosed();
			}
			
			measureFlag = 0;
		}
		
		if (interruptFlag == 1) {
			controller.interrupt();
			controller.debugMenu();
			interruptFlag = 0;
		}
		
	}
}

ISR(INT4_vect) {
	interruptFlag = 1;
}

ISR(TIMER4_COMPA_vect) {
	measureOverflow++;
	
	if (measureOverflow >= MEASURE_EVERY_SECONDS)
	{
		measureFlag = 1;
		measureOverflow = 0;
	}
}
