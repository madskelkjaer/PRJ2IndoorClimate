#include "Controller.h"

#include "Classes/HumiditySensorDriver.h"
#include "Utils/UART.h"

/*
*** Debug Modes ***
AUTO - Automatisk mode
COMMAND - Tillader at sende kommandoer direkte fra terminal
WATCH - Se hvad sensoren afl�ser og hvad der bliver sendt
SEND - Sender 100 O kommandoer.
*/
#define DEBUG_MODE COMMAND

// Hvor tit skal sensoren m�le v�rdier? Helst over xx sekunder.
#define MEASURE_EVERY_SECONDS 30

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
	uint8_t window1[4] = {0, 0, 0, 1};
	controller.addWindow(window1);

	// Luftfugtighedssensor driver
	HumiditySensorDriver humiditySensor;
	// Hvad er MAX og MIN v�rdier for hvorn�r vinduet skal �bne?
	humiditySensor.setMaxValue(50.0);
	humiditySensor.setMinValue(30.0);
	const uint8_t percentDeviationToHalfOpen = 10;

	// Starter uendelig l�kke.
	while (true)
	{
		// Hvis measureFlag er blevet sat, skal vi afl�se v�rdier fra sensoren.
		if (measureFlag == 1)
		{
			if (controller.debugMode() == WATCH)
			{
				controller.printValue(humiditySensor.readValue());
			}
			// uart.transmitString("MEASURE TRIGGERED\r\n");
			double humidityProcentOff = humiditySensor.outsideLimits();

			if (humidityProcentOff < percentDeviationToHalfOpen && 0 < humidityProcentOff)
			{
				// Hvis vores measurement er under 10% af limits, s� skal vi kun �bne vinduet halvt.
				controller.windowsHalf();
			}
			else if (humidityProcentOff > percentDeviationToHalfOpen)
			{
				// Hvis det er mere end 10%, s� �bner vi vinduet helt.
				controller.windowsOpen();
			}
			else
			{
				// Ellers luk vinduet.
				controller.windowsClosed();
			}

			// Reset flag.
			measureFlag = 0;
		}

		// Ved hver interrupt fra zero-cross detektoren kalder vi controllerens interrupt metode. Samt debug menu (hvis debug er til).
		if (interruptFlag == 1)
		{
			controller.interrupt();
			controller.debugMenu();

			// Reset flag.
			interruptFlag = 0;
		}
	}
}

ISR(INT4_vect)
{
	interruptFlag = 1;
}

ISR(TIMER4_COMPA_vect)
{
	// Da timer 4 er sat til at trigger for hvert sekund (1Hz), skal vi bruge en measureOverflow integer.
	measureOverflow++;

	// Hvis den er st�rre end vores definerede konstant, skal vi s�tte flag for at m�le v�rdier.
	if (measureOverflow >= MEASURE_EVERY_SECONDS)
	{
		measureFlag = 1;
		measureOverflow = 0;
	}
}
