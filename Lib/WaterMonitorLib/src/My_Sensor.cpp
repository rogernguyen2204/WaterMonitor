#include "My_Sensor.h"

char** My_Sensor::m_data = new char* [Number_Of_Sensor];

My_Sensor::My_Sensor()
{
	
	Temperature_Sensor = new Temperature(ONE_WIRE_BUS);
	TDS_Sensor = new TDS(TdsSensorPin,VREF,25);
	Turbility_Sensor  = new Turbility(Turbility_SensorPin);
	pH_Sensor = new pH(pH_SensorPin,VREF);
	EC_Sensor = new EC(EC_PIN,25);
	ORP_Sensor = new ORP(orpPin,VREF,orp_OFFSET);
}

My_Sensor::~My_Sensor(){
	for (int i = 0; i < Number_Of_Sensor; i++){
		delete[] m_data[i];
	}
	delete[] m_data;
	delete Temperature_Sensor;
	delete TDS_Sensor;
	delete Turbility_Sensor;
	delete pH_Sensor;
	delete EC_Sensor;
	delete ORP_Sensor;
}

void My_Sensor::Setup_Sensor(){
	for (int i = 0; i < Number_Of_Sensor; i++){
		m_data[i] = new char[20];
	}
	Temperature_Sensor->setup();
	TDS_Sensor->setup();
	Turbility_Sensor->setup();
	pH_Sensor->setup();
	EC_Sensor->setup();
	ORP_Sensor->setup();
}
	
void My_Sensor::Run_Sensor(){
	Temperature_Sensor->Run();
	TDS_Sensor->setTemperature(Temperature_Sensor->getValue());
	TDS_Sensor->Run();
	Turbility_Sensor->Run();
	pH_Sensor->Run();
	EC_Sensor->setTemperature(Temperature_Sensor->getValue());
	EC_Sensor->Run();
	ORP_Sensor->Run();
}

void My_Sensor::Get_Data_From_Sensor(){
	this->m_data[0] = *(Temperature_Sensor->Get_String_Data());
	//Serial.println("getdata from sensor Temperature");
	//Serial.println(this->m_data[0]);
	this->m_data[1] = *(TDS_Sensor->Get_String_Data());
	this->m_data[2] = *(Turbility_Sensor->Get_String_Data());
	this->m_data[3] = *(pH_Sensor->Get_String_Data());
	this->m_data[4] = *(EC_Sensor->Get_String_Data());
	this->m_data[5] = *(ORP_Sensor->Get_String_Data());
	this->m_data[6] = *(Temperature_Sensor->Get_String_Data());

}