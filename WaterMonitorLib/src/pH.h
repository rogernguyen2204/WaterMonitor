#ifndef _PH_H
#define _PH_H
//#include "My_Sensor.h"
#include <Arduino.h>
#define samplingInterval 20
#define ArrayLenth  30
//#define pHArrayIndex 0
class pH //: public My_Sensor
{
	// ph sensor pin
	int m_pin;

	// offset compensation
	float m_offset;
	float m_vref;
	int m_pHArray[ArrayLenth];    // stores the average value of the sensor return data
	float m_pHvoltage;
	double m_pHValue;

public:
	pH(int pin, float vref);
	~pH();
	static char ** data_string;
	// initialization
	void  setup ();

	// update the sensor data
	void  Run ();

	// Get the sensor data
	double getValue();

	//set offset
	void setOffset(float offset);
	double avergearray(int* arr, int number);
	double get_pHvoltage();
	char** Get_String_Data();
};

#endif