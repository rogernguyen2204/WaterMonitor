#include "pH.h"
static char** pH::data_string = new char*();
pH::pH(int pin, float vref)
{
	this->m_pin = pin;
	this->m_vref = vref;
}

pH::~pH()
{
	delete[] *data_string;
	delete data_string;
}
//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the ph sensor
//********************************************************************************************
void pH::setup()
{
	pinMode(this->m_pin, INPUT);
	*data_string = new char[20];
}


//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void pH::Run()
{

	static unsigned long samplingTime = millis();
	static int pHArrayIndex = 0;
  if(millis()-samplingTime > samplingInterval)
  {
      m_pHArray[pHArrayIndex] = analogRead(this->m_pin);
	  pHArrayIndex = pHArrayIndex + 1;
      if(pHArrayIndex == ArrayLenth) pHArrayIndex = 0;
      m_pHvoltage = avergearray(m_pHArray, ArrayLenth)*5.0/1024;
      m_pHValue = 3.5 * m_pHvoltage + m_offset;
      samplingTime = millis();
  }

}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double pH::getValue()
{
	return this->m_pHValue;
}

void pH::setOffset(float offset)
{
	this->m_offset = offset;
}

double pH::avergearray(int* arr, int number){
	int i;
	int max,min;
	double avg;
	long amount=0;
	if(number<=0){
		Serial.println("Error number for the array to avraging!/n");
		return 0;
	}
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

double pH::get_pHvoltage(){
	return this->m_pHvoltage;
}

char** pH::Get_String_Data(){
	
	sprintf(data_string[0], "%s%d","4.pH:" ,(int)m_pHvoltage);
  float phandu;
  phandu = (m_pHvoltage - (int)m_pHvoltage)*100;
  char phandu_temp[20] ="";
  sprintf(phandu_temp, "%s%d","." ,(int)phandu);
  strcat(data_string[0],phandu_temp);
  return data_string;
}