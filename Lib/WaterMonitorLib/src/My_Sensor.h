#ifndef _My_SENSOR_H
#define _My_SENSOR_H

#include "Temperature.h"
#include "TDS.h"
#include "Turbility.h"
#include "pH.h"
#include "EC.h"
#include "ORP.h"
#include <string.h>
#include <Arduino.h>


#define Number_Of_Sensor 7

#define ONE_WIRE_BUS 10
#define TdsSensorPin A1
#define Turbility_SensorPin A0 
#define pH_SensorPin A2 
#define EC_PIN A7
#define orpPin A4
#define orp_OFFSET 15  
#define VREF 5.0 


class My_Sensor
{
private:

	Temperature *Temperature_Sensor;
	TDS *TDS_Sensor;
	Turbility *Turbility_Sensor;
	pH *pH_Sensor;
	EC *EC_Sensor;
	ORP *ORP_Sensor;
public:
	
	My_Sensor();
	~My_Sensor();
	static char ** m_data;
	void Setup_Sensor();
	
	void Run_Sensor();
	void Get_Data_From_Sensor();
	//virtual char*  Get_String_Data()=0;
	
};

#endif