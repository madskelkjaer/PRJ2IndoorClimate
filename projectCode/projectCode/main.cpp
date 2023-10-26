#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Utils/SODA.h"

int main(void)
{
	SODA dataCollector;
	
	dataCollector.setInterval(1);
	dataCollector.start();
}
