#include "ORP.h"
static char** ORP::data_string = new char*();
ORP::ORP(int pin, float vref,float offset)
{
	this->m_pin = pin;
	this->m_vref = vref;
	this->m_offset = offset;
}

ORP::~ORP()
{
	delete[] *data_string;
	delete data_string;
}


void ORP::setup()
{
	pinMode(this->m_pin,INPUT);
	*data_string = new char[20];
}

void ORP::set_Offset(float offset)
{
	this->m_offset = offset;
}

void ORP::Run()
{

	static unsigned long orpTimer=millis();   //analog sampling interval
	static int orpArrayIndex = 0;
  if(millis() >= orpTimer)
  {
    orpTimer=millis()+20;
    this->orpArray[orpArrayIndex] = analogRead(this->m_pin);    //read an analog value every 20ms
	orpArrayIndex = orpArrayIndex + 1;
    if (orpArrayIndex == ArrayLenth) {
      orpArrayIndex = 0;
    }
    this->m_ORPValue = ((30*(double)this->m_vref*1000)-(75*avergearray(orpArray, ArrayLenth)*this->m_vref*1000/1024))/75-this->m_offset;
  }
}

double ORP::getValue()
{
	return this->m_ORPValue;
}



double ORP::avergearray(int* arr, int number){
	int i;
	int max,min;
	static double avg;
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

char** ORP::Get_String_Data(){
	
    sprintf(data_string[0], "%s%d","6.ORP:" ,(int)this->m_ORPValue);
    float phandu;
    phandu = (this->m_ORPValue - (int)this->m_ORPValue)*100;
    char phandu_temp[20] ="";
	sprintf(phandu_temp, "%s%d","." ,(int)phandu);
	strcat(data_string[0],phandu_temp);
	return data_string;
}