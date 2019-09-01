#ifndef _TURBILITY_H
#define _TURBILITY_H
//#include "My_Sensor.h"
#include <Arduino.h>
class Turbility //: public My_Sensor
{
private:
	int m_pin;
	double m_turbility;
public:
	Turbility(int pin);
	~Turbility();
	static char** data_string;
	void setup();
	// update the sensor data
	void  Run();

	// Get the sensor data
	double getValue();
	char** Get_String_Data();
};
#endif