#include "IN_OUT_SD.h"

static bool IN_OUT_SD::isSuccess = true;
static char ** IN_OUT_SD::DataReaded = new char*[Number_Of_Sensor];
static int IN_OUT_SD::index = 0;
static File IN_OUT_SD::myFile;

IN_OUT_SD::~IN_OUT_SD(){
	for (int i = 0; i < Number_Of_Sensor; i++){
		delete [] DataReaded[i];
	}
	delete[] DataReaded;
}

void IN_OUT_SD::Setup(int CSpin){
	if (!SD.begin(53)) {
		Serial.println("initialization failed!");
		this->isSuccess = false;
		return;
	}
	Serial.println("initialization done.");
	for (int i = 0; i < Number_Of_Sensor; i++){
		*DataReaded = new char[20];
	}
}

void IN_OUT_SD::Write(char **data){
	this->myFile = SD.open("Water.txt",FILE_WRITE);
  // if the file opened okay, write to it:
  if (this->myFile) {
    Serial.print("Writing to Water_Parameters.txt...");
    myFile.println("=====================");
    for (int i = 0; i < 7 ; i++){
     myFile.println(data[i]);
    }
    // close the file:
    this->myFile.close();
    Serial.println("done.");
  } else this->isSuccess = false;
  
  this->WriteEachParameter("Temp.txt",data[index++]);
  this->WriteEachParameter("TDS.txt",data[index++]);
  this->WriteEachParameter("Tur.txt",data[index++]);
  this->WriteEachParameter("pH.txt",data[index++]);
  this->WriteEachParameter("EC.txt",data[index++]);
  this->WriteEachParameter("ORP.txt",data[index++]);
  this->WriteEachParameter("DO.txt",data[index++]);
  if (this->index == (Number_Of_Sensor - 1)) this->index = 0;
}
void IN_OUT_SD::Read(){
	this->ReadEachParameter("Temp.txt");
	this->ReadEachParameter("TDS.txt");
	this->ReadEachParameter("Tur.txt");
	this->ReadEachParameter("pH.txt");
	this->ReadEachParameter("EC.txt");
	this->ReadEachParameter("ORP.txt");
	this->ReadEachParameter("DO.txt");
	if (this->index == (Number_Of_Sensor - 1)) this->index = 0;
}
void IN_OUT_SD::WriteEachParameter(char name[] ,char data[]){
	if (!SD.exists(name))
	{
		this->myFile = SD.open(name,FILE_WRITE);
		this->myFile.println(data);
		this->myFile.close();
	} else { 
		SD.remove(name);
		this->myFile = SD.open(name,FILE_WRITE);
		this->myFile.println(data);
		this->myFile.close();
	}
}
void IN_OUT_SD::ReadEachParameter(char name[]){
	if (!SD.exists(name)){
    //strcpy(Lastest_Result_Pages.NameEach[0].NameMenuItems,"EMPTY" );
	strcpy(this->DataReaded[index++],"EMPTY");
  }
  else {
    this->myFile = SD.open(name,FILE_READ);
    
    if (this->myFile) {
      //Serial.println("Results: ");
      char temp[20];
      byte x;
      int i;
      i = 0;
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        //Serial.write(myFile.read());
        x = myFile.read();
        temp[i] = char(x);
        i++;
      }
      //Serial.println(temp);
      //strcpy(Lastest_Result_Pages.NameEach[0].NameMenuItems,temp);
	  char p[20];
	for (int i = 0; i <= (strlen(temp) - 4); i++)
	{
		p[i++] = temp[i];
	}
	  strcpy(this->DataReaded[index++],p);
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening file");
	  this->isSuccess = false;
    }
  }
}