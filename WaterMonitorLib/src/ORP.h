#ifndef _ORP_H
#define _ORP_H
//#include "My_Sensor.h"
#include <Arduino.h>
#define ArrayLenth  40
//#define orpArrayIndex  0
class ORP //: public My_Sensor
{
private:
    int m_pin;
    float m_vref;
    float m_offset;
	
    int orpArray[ArrayLenth];    // store the analog value in the array, read from ADC
    float averageVoltage = 0;
    double m_ORPValue = 0;
public:
	ORP(int pin, float vref,float offset);
	~ORP();
	static char** data_string;
	void set_Offset(float offset);
	void setup();
	void Run();
	double getValue();  
	double avergearray(int* arr, int number);
	char** Get_String_Data();
};  
#endif