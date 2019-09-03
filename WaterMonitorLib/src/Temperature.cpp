#include "Temperature.h"

static char** Temperature::data_string = new char*();
Temperature::Temperature(int pin)
{
	this->obj_oneWire = new OneWire(pin);
	this->sensors = new DallasTemperature(obj_oneWire);
}

Temperature::~Temperature()
{
	delete[] *data_string;
	delete data_string;
}


//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the sensor
//********************************************************************************************
void Temperature::setup()
{
	this->sensors->begin();
	*data_string = new char[20];
}


//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void Temperature::Run()
{
	// call sensors.requestTemperatures() to issue a global temperature
	// request to all devices on the bus
	/********************************************************************/
	this->sensors->requestTemperatures();
	this->m_temperature = this->sensors->getTempCByIndex(0);
	// Send the command to get temperature readings
}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double Temperature::getValue()
{
	//this->m_temperature = this->sensors->getTempCByIndex(0);
	return this->m_temperature;
}
char** Temperature::Get_String_Data(){
	
	sprintf(data_string[0], "%s%d","1.Temp:" ,(int)this->m_temperature);
	float phandu;
	phandu = (this->m_temperature - (int)this->m_temperature)*10;
	char phandu_temp[20] ="";
	sprintf(phandu_temp, "%s%d","." ,(int)phandu);
	strcat(data_string[0],phandu_temp);
	strcat(data_string[0], " *c");
	//Serial.println("TEMP SENSOR");
	//Serial.println(data_string[0]);
	//Serial.println("===============");
	return data_string;
}