#include "Controller.h"

#include "Classes/HumiditySensorDriver.h"
#include "Utils/UART.h"

/*
*** Debug Modes ***
NONE - Automatisk mode
COMMAND - Tillader at sende kommandoer direkte fra terminal
WATCH - Se hvad sensoren aflæser og hvad der bliver sendt
*/
#define DEBUG_MODE COMMAND

// Hvor tit skal sensoren måle værdier? Helst over xx sekunder.
#define MEASURE_EVERY_SECONDS 5

// Interrupt flags.
volatile uint8_t interruptFlag = 0;
volatile uint8_t measureFlag = 0;
volatile uint8_t measureOverflow = 0; 

int main(void)
{
	// UART uart;
	
	Controller controller;
	controller.start(DEBUG_MODE);
	
	// Modtagerens adresse.
	uint8_t window1[4] = {0,0,0,1};
	controller.addWindow(window1);
	
	// Luftfugtighedssensor driver
	HumiditySensorDriver humiditySensor;
	// Hvad er MAX og MIN værdier for hvornår vinduet skal åbne?
	humiditySensor.setMaxValue(50.0);
	humiditySensor.setMinValue(30.0);
	const uint8_t percentDeviationToHalfOpen = 20;
	
	// Starter uendelig løkke.
	while(true)
	{	
		// Hvis measureFlag er blevet sat, skal vi aflæse værdier fra sensoren.
		if (measureFlag == 1 && controller.debugMode() == WATCH) {
			if (controller.debugMode() == WATCH) {
				controller.printValue(humiditySensor.readValue());
			}
			// uart.transmitString("MEASURE TRIGGERED\r\n");
			double humidityProcentOff = humiditySensor.outsideLimits();
			
			if (humidityProcentOff < percentDeviationToHalfOpen && 0 < humidityProcentOff ) {
				// Hvis vores measurement er under 10% af limits, så skal vi kun åbne vinduet halvt.
				controller.windowsHalf();
			} else if (humidityProcentOff > percentDeviationToHalfOpen) {
				// Hvis det er mere end 10%, så åbner vi vinduet helt.
				controller.windowsOpen();
			} else {
				// Ellers luk vinduet.
				controller.windowsClosed();
			}
			
			// Reset flag.
			measureFlag = 0;
		}
		
		// Ved hver interrupt fra zero-cross detektoren kalder vi controllerens interrupt metode. Samt debug menu (hvis debug er til).
		if (interruptFlag == 1) {
			controller.interrupt();
			controller.debugMenu();
			
			// Reset flag.
			interruptFlag = 0;
		}
		
	}
}

ISR(INT4_vect) {
	interruptFlag = 1;
}

ISR(TIMER4_COMPA_vect) {
	// Da timer 4 er sat til at trigger for hvert sekund (1Hz), skal vi bruge en measureOverflow integer.
	measureOverflow++;
	
	// Hvis den er større end vores definerede konstant, skal vi sætte flag for at måle værdier.
	if (measureOverflow >= MEASURE_EVERY_SECONDS)
	{
		measureFlag = 1;
		measureOverflow = 0;
	}
}
