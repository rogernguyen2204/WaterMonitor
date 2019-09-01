#ifndef _DISPLAYON5110_H
#define _DISPLAYON5110_H

#include <Arduino.h>

#define NumberMenuItems 3

typedef struct Name_of_MenuItems{
    char NameMenuItems[20];
    struct Pages *My_Pages;
}NameMenuItems;

typedef struct Pages{
  volatile bool status;
  char title[12];
  uint8_t Number_MenuItems;
  volatile uint8_t Menu_Items_Current; 
  NameMenuItems *NameEach;
}Pages_Struct;

class DisplayOn5110
{
public:
	void config_MainPages(Pages_Struct *MainPages,Pages_Struct *ResultPages, Pages_Struct *LastestResultPages);
	void config_PagesResult(Pages_Struct *Result_Pages,Pages_Struct *SaveToSdcard_Pages,Pages_Struct *Main_Pages);
	void config_PagesLatestResult(Pages_Struct *Lastest_Result_Pages,Pages_Struct *Main_Pages);
	void config_SaveToSdcard_Pages(Pages_Struct *SaveToSdcard_Pages,Pages_Struct *Result_Pages);

	DisplayOn5110() {};
	~DisplayOn5110() {};
	void Run(Pages_Struct *MainPages,Pages_Struct *ResultPages, Pages_Struct *LastestResultPages,Pages_Struct *SaveToSdcard_Pages);
	void Update_PagesResult(Pages_Struct *Result_Pages,char **temp);
	void Update_PagesLatestResult(Pages_Struct *LastestResultPages,bool isCheck,char **temp);
	void Update_SaveToSdcardPages(Pages_Struct *SaveToSdcard_Pages,bool isCheck);
};

#endif