#ifndef _INOUTSD_H
#define _INOUTSD_H

#define Number_Of_Sensor 7
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class IN_OUT_SD{
public:
	IN_OUT_SD(){};
	~IN_OUT_SD();
	static File myFile;
	static int index;
	static char ** DataReaded;
	static bool isSuccess;
	void Setup(int CSpin);
	void Write(char **data);
	void Read();
	void WriteEachParameter(char name[] ,char data[]);
	void ReadEachParameter(char name[]);
};



#endif