#include "Turbility.h"

static char** Turbility::data_string = new char*();
Turbility::Turbility(int pin)
{
	this->m_pin = pin;
	*data_string = new char[20];
}

Turbility::~Turbility()
{
	delete *data_string;
	delete data_string;
}

void Turbility::setup()
{
	*data_string = new char[20];

}
//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void Turbility::Run()
{
	int sensorValue = analogRead(this->m_pin);// read the input on analog pin 0:
	this->m_turbility = sensorValue * (5.0 / 1024.0);
	
}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double Turbility::getValue()
{
	return this->m_turbility;
}

char** Turbility::Get_String_Data(){

  sprintf(data_string[0], "%s%d","3.Tur:" ,(int)(this->m_turbility) );
  float phandu;
  phandu = (this->m_turbility - (int)this->m_turbility)*10;
  char phandu_temp[20] ="";
  sprintf(phandu_temp, "%s%d","." ,(int)phandu);
  strcat(data_string[0],phandu_temp);
  strcat(data_string[0]," tnu");
	return data_string;
}