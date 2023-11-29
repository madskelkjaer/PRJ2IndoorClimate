/* 
* SensorDriver.h
*
* Created: 27-11-2023 17:02:22
* Author: madse
*/


#ifndef __SENSORDRIVER_H__
#define __SENSORDRIVER_H__

/*
SensorDriverTemplate

Her ligger den template der skal bruges til at oprette nye sensorer klasser.
Dette forenkler videreudviklingen af systemet da API'en er ens for alle.

Det eneste man behøver at tage højde for, er at implementere den virtuelle T readValue(), samt at importere ens sensordrivver.
*/


template <class T>
class SensorDriverTemplate
{
public:
	SensorDriverTemplate() {};
	virtual T readValue() = 0;
	void setMaxValue(T value) { maxValue_ = value; };
	void setMinValue(T value) { minValue_ = value; };
	T getMaxValue() { return maxValue_; };
	T getMinValue() { return minValue_; };
	double outsideLimits() { // Hvor langt udenfor limits er vi? 
		T measurement = this->readValue(); // Måler værdi fra sensor
		T range = maxValue_ - minValue_; // Den range vores measurement skal være indenfor.
		
		// Beregner procentdel afvigelse fra rangen.
		if (measurement < minValue_) {
			return (double)((minValue_ - measurement) / range) * 100;
		} else if (measurement > maxValue_) {
			return (double)((measurement - maxValue_) / range) * 100;
		} else {
			return (double)0.0;
		}
	};
protected:
	T maxValue_;
	T minValue_;
}; //SensorDriver

#endif //__SENSORDRIVER_H__
