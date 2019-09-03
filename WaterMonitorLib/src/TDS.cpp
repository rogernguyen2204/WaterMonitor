#include "TDS.h"

static char** TDS::data_string = new char*();

TDS::TDS(int pin, float vref,float temperature)
{
	this->m_pin = pin;
	this->m_vref = vref;
	this->m_temperature = temperature;
}

TDS::~TDS()
{
	delete[] *data_string;
	delete data_string;
}


void TDS::setup()
{
	pinMode(this->m_pin,INPUT);
	*data_string = new char[20];

}

void TDS::setTemperature(float temp)
{
	this->m_temperature = temp;
}

void TDS::Run()
{

	static unsigned long analogSampleTimepoint = millis();
	static int copyIndex,analogBufferIndex = 0;
  if ((unsigned long)(millis() - analogSampleTimepoint) > 20U)   //every 20 milliseconds,read the analog value from the ADC
  {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(this->m_pin);    //read the analog value and store into the buffer
    analogBufferIndex = analogBufferIndex + 1;
    if (analogBufferIndex == COUNT)
      analogBufferIndex = 0;
  }
  
  static unsigned long printTimepoint = millis();
  if ((unsigned long)(millis() - printTimepoint) > 500U)
  {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < COUNT; copyIndex++)
    analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    averageVoltage = getMedianNum(analogBufferTemp, COUNT) * (float)this->m_vref / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient = 1.0 + 0.02 * (this->m_temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge = averageVoltage / compensationCoefficient; //temperature compensation
    this->tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
    
	}
}

double TDS::getValue()
{
	return this->tdsValue;
}

float TDS::getMedianNum(int* dataArray, int arrayLength)
{
	int i, j;
	static	int tempValue;


	// Bubble sort array

	for (j = 0; j < arrayLength - 1; j++)
	{
		for (i = 0; i < arrayLength - 1 - j; i++)
		{
			if (dataArray[i] > dataArray[i + 1])
			{
				tempValue = dataArray[i];
				dataArray[i] = dataArray[i + 1];
				dataArray[i + 1] = tempValue;
			}
		}
	}

	// Calculate median
	if ((arrayLength & 1) > 0)
	{
		// The array has an odd number of elements, returning one element in the middle

		tempValue = dataArray[(arrayLength - 1) / 2];
	}
	else
	{
		// The array has an even number of elements, returning the average of the two elements in the middle

		tempValue = (dataArray[arrayLength / 2] + dataArray[arrayLength / 2 - 1]) / 2;
	}
	return tempValue;
}

char** TDS::Get_String_Data(){
	
	sprintf(data_string[0], "%s%d","2.Tds:" ,(int)(this->tdsValue));
    strcat(data_string[0], " ppm");
	return data_string;
}