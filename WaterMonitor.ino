#include "My_Sensor.h"
#include "DisplayOn5110.h"
#include "IN_OUT_SD.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>
#include <SD.h>
#include <time.h>

IN_OUT_SD MySD;
//static char data[7][20];  //  data[0] TEMP,data[1] TDS , data[2] Turbility, data[3] pH ... data[4] EC , data[5] ORP
static My_Sensor All_Sensor;
static char **data; //= (char**)malloc(7*sizeof(char*)); // 7 sensor;         //  data[0] TEMP,data[1] TDS , data[2] Turbility, data[3] pH ... data[4] EC , data[5] ORP

//config LCD 5110
Adafruit_PCD8544 display = Adafruit_PCD8544( 8, 7, 6, 5, 4);
DisplayOn5110 MyDisplay;
static Pages_Struct Main_Pages;
static Pages_Struct Result_Pages;
static Pages_Struct Lastest_Result_Pages;
static Pages_Struct SaveToSdcard_Pages;


void Read_sdCard(){
  MySD.Read();
  MyDisplay.Update_PagesLatestResult(&Lastest_Result_Pages,MySD.isSuccess,MySD.DataReaded);
}
void Write_sdCard(){
  MySD.Write(data);
  MyDisplay.Update_SaveToSdcardPages(&SaveToSdcard_Pages,MySD.isSuccess);
}


void setup(void)
{
  data = (char**)malloc(7*sizeof(char*)); // 7 sensor
  for (int i = 0 ; i < 7; i++){
    data[i] = (char*)malloc(20*sizeof(char));
  }
  // start serial port
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP); //CENTER
  pinMode(3, INPUT_PULLUP); //DOWN
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH); //Turn Backlight ON
  
  attachInterrupt(0, checkIfSelectButtonIsPressed, LOW); //Interupt line 0
  attachInterrupt(1, checkIfDownButtonIsPressed, LOW); //Interupt line 1

  display.begin();
  display.setContrast(50); //Set contrast to 50
  display.clearDisplay(); 
  display.display();
  MyDisplay.Run(&Main_Pages,&Result_Pages,&Lastest_Result_Pages,&SaveToSdcard_Pages);
  Draw_Pages(&Main_Pages);
  MySD.Setup(53);
  All_Sensor.Setup_Sensor();

}
void loop(void)
{
  /*
  All_Sensor.Run_Sensor();
    All_Sensor.Get_Data_From_Sensor();
    for (int i = 0; i < 7; i++){
        strcpy(data[i],All_Sensor.m_data[i]);
        Serial.println(data[i]);
      }
      delay(1000);
      */
  if ((!Main_Pages.status && Result_Pages.status)){ 
    All_Sensor.Run_Sensor();
    
    static unsigned long SampleTimeDraw = millis();
    if ((unsigned long)(millis() - SampleTimeDraw) > 200U){
      SampleTimeDraw = millis();
      All_Sensor.Get_Data_From_Sensor();
      for (int i = 0; i < 7; i++){
        strcpy(data[i],All_Sensor.m_data[i]);
        Serial.println(data[i]);
      }
      if (!Result_Pages.status && Main_Pages.status) Draw_Pages(&Main_Pages);
       else if (Result_Pages.status && !Main_Pages.status) Draw_Pages(&Result_Pages);
       //Update LCD
       MyDisplay.Update_PagesResult(&Result_Pages,data);
    }
  }
  
}


void checkIfDownButtonIsPressed()
{
  if ( Main_Pages.status && !Result_Pages.status ){
    Main_Pages.Menu_Items_Current++;
    if (Main_Pages.Menu_Items_Current == (Main_Pages.Number_MenuItems)){
      Main_Pages.Menu_Items_Current = 0;
    }
    Draw_Pages(&Main_Pages); 
    if (digitalRead(3) == LOW) { while (true){
      delay(50);
        if (digitalRead(3) == HIGH) return;
      }
    }
  }
  else if ( Result_Pages.status && !Main_Pages.status ){
    Result_Pages.Menu_Items_Current++;
    if (Result_Pages.Menu_Items_Current == (Result_Pages.Number_MenuItems)){
      Result_Pages.Menu_Items_Current = 0;
    }
    Draw_Pages(&Result_Pages); 
    if (digitalRead(3) == LOW) { while (true){
      delay(50);
        if (digitalRead(3) == HIGH) return;
      }
    }
  }
  else if ( Lastest_Result_Pages.status && !Main_Pages.status ){
    Lastest_Result_Pages.Menu_Items_Current++;
    if (Lastest_Result_Pages.Menu_Items_Current == (Lastest_Result_Pages.Number_MenuItems)){
      Lastest_Result_Pages.Menu_Items_Current = 0;
    }
    Draw_Pages(&Lastest_Result_Pages); 
    if (digitalRead(3) == LOW) { while (true){
      delay(50);
        if (digitalRead(3) == HIGH) return;
      }
    }
  }
  else if ( SaveToSdcard_Pages.status && !Main_Pages.status && !Result_Pages.status){
//    SaveToSdcard_Pages.Menu_Items_Current++;
//    if (SaveToSdcard_Pages.Menu_Items_Current == (SaveToSdcard_Pages.Number_MenuItems)){
//      SaveToSdcard_Pages.Menu_Items_Current = 0;
//    }
    Draw_Pages(&SaveToSdcard_Pages); 
    
  }
   if (digitalRead(3) == LOW) { while (true){
    delay(50);
        if (digitalRead(3) == HIGH) return;
      }
    }
}


void checkIfSelectButtonIsPressed()
{
  if ( Main_Pages.status && !Result_Pages.status && !Lastest_Result_Pages.status){
    if (Main_Pages.Menu_Items_Current == 0){
      Main_Pages.status = false;
      Result_Pages.status = true;
      Draw_Pages(Main_Pages.NameEach[0].My_Pages);
        if (digitalRead(2) == LOW) { 
          while(1){ 
            delay(50);
          if (digitalRead(2) == HIGH) return;
          }
         }
    }
    else if (Main_Pages.Menu_Items_Current == 2){
      Main_Pages.status = false;
      Lastest_Result_Pages.status = true;
      Read_sdCard();
      Draw_Pages(Main_Pages.NameEach[2].My_Pages);
        if (digitalRead(2) == LOW) { 
          while(1){ 
            delay(50);
          if (digitalRead(2) == HIGH) return;
          }
         }
    }
    else if ((Main_Pages.Menu_Items_Current == 1)){
      if (digitalRead(9) == HIGH)
        digitalWrite(9,LOW); 
        else digitalWrite(9,HIGH);
      Draw_Pages(&Main_Pages);
        if (digitalRead(2) == LOW) { while(true){ 
          delay(50);
          if (digitalRead(2) == HIGH) return;
          }
         }
    }
     if (digitalRead(2) == LOW) { while(true){ 
        delay(50);
          if (digitalRead(2) == HIGH) return;
          }
         }
  }
  if ( Result_Pages.status && !Main_Pages.status && !SaveToSdcard_Pages.status){
    if (Result_Pages.Menu_Items_Current == 7 ){
      Result_Pages.status = false;
      Main_Pages.status = false;
      SaveToSdcard_Pages.status = true;
      Draw_Pages(Result_Pages.NameEach[7].My_Pages);
      delay(3000);
      Write_sdCard();
      Draw_Pages(Result_Pages.NameEach[7].My_Pages);
      if (digitalRead(2) == LOW) { while(true){ 
        delay(50);
        if (digitalRead(2) == HIGH) return;
       }
      }
    }
    if (Result_Pages.Menu_Items_Current == 8 ){
      Result_Pages.status = false;
      Main_Pages.status = true;  
      Draw_Pages(Result_Pages.NameEach[8].My_Pages);
      Result_Pages.Menu_Items_Current = 2;
      if (digitalRead(2) == LOW) { while(true){ 
        delay(50);
        if (digitalRead(2) == HIGH) return;
       }
      }
    }
  }
//  if ( Result_Pages.status && !Main_Pages.status && !SaveToSdcard_Pages.status){
//    
//  }
  else if ( !Result_Pages.status && !Main_Pages.status && SaveToSdcard_Pages.status){
    if (SaveToSdcard_Pages.Menu_Items_Current == 1 ){
      Result_Pages.status = true;
      Main_Pages.status = false;  
      SaveToSdcard_Pages.status = false;
      Draw_Pages(SaveToSdcard_Pages.NameEach[1].My_Pages);
      strcpy(SaveToSdcard_Pages.NameEach[0].NameMenuItems," SAVING" ); 
      SaveToSdcard_Pages.Menu_Items_Current = 1;
      if (digitalRead(2) == LOW) { while(true){ 
        delay(50);
        if (digitalRead(2) == HIGH) return;
       }
      }
    }
  }
  if ( Lastest_Result_Pages.status && !Main_Pages.status){
    if (Lastest_Result_Pages.Menu_Items_Current == 8 ){
      Lastest_Result_Pages.status = false;
      Main_Pages.status = true;
      Draw_Pages(Lastest_Result_Pages.NameEach[8].My_Pages);
      Lastest_Result_Pages.Menu_Items_Current = 2;
      if (digitalRead(2) == LOW) { while(true){ 
        delay(50);
        if (digitalRead(2) == HIGH) return;
       }
      }
    }
  }
  if (digitalRead(2) == LOW) { while(true){ 
        delay(50);
        if (digitalRead(2) == HIGH) return;
       }
     }
  delay(300);
}

void Draw_Pages(Pages_Struct *Pages){
    //display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print(Pages->title);
    display.drawFastHLine(0,9,83,BLACK);
    uint8_t i;
    uint8_t y = 13;
    if ( Pages->Menu_Items_Current > 3 ){
      i = Pages->Menu_Items_Current - 3;
    } else i = 0;
    for (i; i < Pages->Number_MenuItems ; i++){
      if (Pages->Menu_Items_Current == i){
         display.setTextColor(WHITE ,BLACK);
        } else display.setTextColor(BLACK, WHITE);
      display.setCursor(0, y);
      display.print(Pages->NameEach[i].NameMenuItems);
        //On Or Off Light
        if (Main_Pages.status && !(Result_Pages.status) && !(SaveToSdcard_Pages.status) && i == 1 ) { 
          if (digitalRead(9) == HIGH) { display.print("ON"); } 
          else { display.print("OFF"); }
          }
      y += 8;
    }
    display.display();
}
