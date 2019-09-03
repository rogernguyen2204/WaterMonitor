#ifndef _EC_H
#define _EC_H
//#include "My_Sensor.h"
#include <Arduino.h>
#include "DFRobot_EC.h"
#include <EEPROM.h>
class EC //: public My_Sensor
{
public:
	//ec sensor pin
	int m_pin;
	float m_temperature;
private:
	float m_ecVoltage;
	float m_ecValue;
	DFRobot_EC object_ec;
	
public:
	EC(int pin,float temperature );
	~EC() ;
	static char** data_string;
	// initialization
	void  setup ();

	// update the sensor data
	void  Run ();

	// Get the sensor data
	double getValue();
	double get_ecVoltage();
	void calibration();
	void setTemperature(float temp);
	char** Get_String_Data();
};

#endif