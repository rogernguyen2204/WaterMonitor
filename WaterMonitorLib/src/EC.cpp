#include "EC.h"
static char** EC::data_string = new char*();

EC::EC(int pin,float temperature)
{
	this->m_pin = pin;
	this->m_temperature = temperature;
}
EC::~EC()
{
	delete[] *data_string;
	delete data_string;
}
//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the EC sensor
//********************************************************************************************
void EC::setup()
{
	this->object_ec.begin();
	*data_string = new char[20];
}


//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void EC::Run()
{
	static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U)  //time interval: 1s
    {
      timepoint = millis();
      this->m_ecVoltage = analogRead(this->m_pin)/1024.0*5000;  // read the voltage
      this->m_ecValue =  object_ec.readEC(this->m_ecVoltage,this->m_temperature);  // convert voltage to EC with temperature compensation
	}
}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double EC::getValue()
{
	return this->m_ecValue;
}


double EC::get_ecVoltage(){
	return this->m_ecVoltage;
}

void EC::calibration(){
		object_ec.calibration(this->m_ecVoltage,this->m_temperature);
}

void EC::setTemperature(float temp)
{
	this->m_temperature = temp;
}
char** EC::Get_String_Data(){
	
    sprintf(data_string[0], "%s%d","5.EC:" ,(int)this->m_ecValue);
    float phandu;
    phandu = (this->m_ecValue - (int)this->m_ecValue)*100;
    char phandu_temp[20] ="";
  sprintf(phandu_temp, "%s%d","." ,(int)phandu);
  strcat(data_string[0],phandu_temp);
  return data_string;
}