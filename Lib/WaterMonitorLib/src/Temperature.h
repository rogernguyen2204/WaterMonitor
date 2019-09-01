#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

//#include "My_Sensor.h"
#include <Arduino.h>
#include "OneWire.h"
#include "DallasTemperature.h"
class Temperature //: public My_Sensor
{
private:
	OneWire *obj_oneWire;
	DallasTemperature *sensors;
public:
	static char** data_string;
	double m_temperature;
	Temperature(int pin);
	~Temperature();

	// initialization
	void  setup();

	// update the sensor data
	void  Run();

	// Get the sensor data
	double getValue();
	char** Get_String_Data();
};

#endif