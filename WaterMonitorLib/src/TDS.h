#ifndef _TDS_H
#define _TDS_H
//#include "My_Sensor.h"
#include <Arduino.h>
#define COUNT  20
//#define analogBufferIndex  0
//#define copyIndex  0
class TDS //: public My_Sensor
{
private:
    int m_pin;
    float m_vref;
    float m_temperature;
	
    int analogBuffer[COUNT];    // store the analog value in the array, read from ADC
	int analogBufferTemp[COUNT];
    float averageVoltage = 0;
    double tdsValue = 0;
    float getMedianNum(int* dataArray, int arrayLength);
public:
	TDS(int pin, float vref,float temperature);
	~TDS();
	static char ** data_string;
	void setTemperature(float temp);
	void setup();
	void Run();
	double getValue();  
	char** Get_String_Data();
};  

#endif