#include "Controller.h"
#include "Classes/TemperatureSensor.h"
#include "Classes/SensorDriver.h"

#define DEBUG_MODE true

volatile int interruptFlag = 0;

int main(void)
{
	Controller controller;
	/*controller.setActionValues('h', 25)*/
	controller.start(DEBUG_MODE);
	
	TemperatureSensor tempDriver;
	
	SensorDriver sensordriver;
	sensordriver.setSensorDriver(tempDriver);
		
	
	
	
	return 0;
	
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