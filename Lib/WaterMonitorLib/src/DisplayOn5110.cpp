#include "DisplayOn5110.h"


void DisplayOn5110::config_MainPages(Pages_Struct *MainPages,Pages_Struct *ResultPages, Pages_Struct *LastestResultPages){
  strcpy(MainPages->title,"MAIN MENU");
  MainPages->status = true;
  MainPages->Number_MenuItems = NumberMenuItems;
  MainPages->Menu_Items_Current = 0;
  MainPages->NameEach = (NameMenuItems *)malloc((MainPages->Number_MenuItems) * sizeof(NameMenuItems));
  MainPages->NameEach[0].My_Pages = ResultPages;
  MainPages->NameEach[1].My_Pages = NULL;
  MainPages->NameEach[2].My_Pages = LastestResultPages;
  strcpy(MainPages->NameEach[0].NameMenuItems,"1.Measure" );
  strcpy(MainPages->NameEach[1].NameMenuItems,"2.Light:" );
  strcpy(MainPages->NameEach[2].NameMenuItems,"3.Lastest" );
}

void DisplayOn5110::config_PagesResult(Pages_Struct *Result_Pages,Pages_Struct *SaveToSdcard_Pages,Pages_Struct *Main_Pages){
  strcpy(Result_Pages->title,"RESULTS");
  Result_Pages->status = false;
  Result_Pages->Number_MenuItems = 9;
  Result_Pages->Menu_Items_Current = 0;
  Result_Pages->NameEach = (NameMenuItems *)malloc((Result_Pages->Number_MenuItems) * sizeof(NameMenuItems));
  strcpy(Result_Pages->NameEach[0].NameMenuItems,"1.Temp:..." );
  strcpy(Result_Pages->NameEach[1].NameMenuItems,"2.Tds:..." );
  strcpy(Result_Pages->NameEach[2].NameMenuItems,"3.Tur:..." );
  strcpy(Result_Pages->NameEach[3].NameMenuItems,"4.pH:..." );
  strcpy(Result_Pages->NameEach[4].NameMenuItems,"5.EC:..." );
  strcpy(Result_Pages->NameEach[5].NameMenuItems,"6.ORP:..." );
  strcpy(Result_Pages->NameEach[6].NameMenuItems,"7.DO:..." );
  strcpy(Result_Pages->NameEach[7].NameMenuItems,"Save to Sdcard");
  strcpy(Result_Pages->NameEach[8].NameMenuItems,"->Back to Main");
  Result_Pages->NameEach[7].My_Pages = SaveToSdcard_Pages;
  Result_Pages->NameEach[8].My_Pages = Main_Pages;
}

void DisplayOn5110::config_PagesLatestResult(Pages_Struct *Lastest_Result_Pages,Pages_Struct *Main_Pages){
  strcpy(Lastest_Result_Pages->title,"LASTEST");
  Lastest_Result_Pages->status = false;
  Lastest_Result_Pages->Number_MenuItems = 8;
  Lastest_Result_Pages->Menu_Items_Current = 0;
  Lastest_Result_Pages->NameEach = (NameMenuItems *)malloc((Lastest_Result_Pages->Number_MenuItems) * sizeof(NameMenuItems));
  strcpy(Lastest_Result_Pages->NameEach[0].NameMenuItems,"1.Temp:..." );
  strcpy(Lastest_Result_Pages->NameEach[1].NameMenuItems,"2.Tds:..." );
  strcpy(Lastest_Result_Pages->NameEach[2].NameMenuItems,"3.Tur:..." );
  strcpy(Lastest_Result_Pages->NameEach[3].NameMenuItems,"4.pH:..." );
  strcpy(Lastest_Result_Pages->NameEach[4].NameMenuItems,"5.EC:..." );
  strcpy(Lastest_Result_Pages->NameEach[5].NameMenuItems,"6.ORP:..." );
  strcpy(Lastest_Result_Pages->NameEach[6].NameMenuItems,"7.DO:..." );
  strcpy(Lastest_Result_Pages->NameEach[7].NameMenuItems,"->Back to Main");
  Lastest_Result_Pages->NameEach[8].My_Pages = Main_Pages;
}
void DisplayOn5110::config_SaveToSdcard_Pages(Pages_Struct *SaveToSdcard_Pages,Pages_Struct *Result_Pages){
  strcpy(SaveToSdcard_Pages->title,"STATUS");
  SaveToSdcard_Pages->status = false;
  SaveToSdcard_Pages->Number_MenuItems = 2;
  SaveToSdcard_Pages->Menu_Items_Current = 1;
  SaveToSdcard_Pages->NameEach = (NameMenuItems *)malloc((SaveToSdcard_Pages->Number_MenuItems) * sizeof(NameMenuItems));
  strcpy(SaveToSdcard_Pages->NameEach[0].NameMenuItems,"SAVING..." );
  strcpy(SaveToSdcard_Pages->NameEach[1].NameMenuItems,"->Back" );
  SaveToSdcard_Pages->NameEach[1].My_Pages = Result_Pages;
}

void DisplayOn5110::Run(Pages_Struct *Main_Pages,Pages_Struct *Result_Pages, Pages_Struct *Lastest_Result_Pages,Pages_Struct *SaveToSdcard_Pages){
	config_MainPages(Main_Pages,Result_Pages,Lastest_Result_Pages);
	config_PagesResult( Result_Pages, SaveToSdcard_Pages, Main_Pages);
	config_PagesLatestResult( Lastest_Result_Pages,Main_Pages);
	config_SaveToSdcard_Pages( SaveToSdcard_Pages, Result_Pages);
}

void DisplayOn5110::Update_PagesResult(Pages_Struct *Result_Pages,char **temp){
	  strcpy(Result_Pages->NameEach[0].NameMenuItems,temp[0]);
  strcpy(Result_Pages->NameEach[1].NameMenuItems,temp[1] );
  strcpy(Result_Pages->NameEach[2].NameMenuItems,temp[2] );
  strcpy(Result_Pages->NameEach[3].NameMenuItems,temp[3] );
  strcpy(Result_Pages->NameEach[4].NameMenuItems,temp[4] );
  strcpy(Result_Pages->NameEach[5].NameMenuItems,temp[5] );
    strcpy(Result_Pages->NameEach[6].NameMenuItems,temp[6] );
}
void DisplayOn5110::Update_PagesLatestResult(Pages_Struct *LastestResultPages,bool isCheck,char **temp){
	if (isCheck){
		strcpy(LastestResultPages->NameEach[0].NameMenuItems,temp[0]);
		strcpy(LastestResultPages->NameEach[1].NameMenuItems,temp[1] );
		strcpy(LastestResultPages->NameEach[2].NameMenuItems,temp[2] );
		strcpy(LastestResultPages->NameEach[3].NameMenuItems,temp[3] );
		strcpy(LastestResultPages->NameEach[4].NameMenuItems,temp[4] );
		strcpy(LastestResultPages->NameEach[5].NameMenuItems,temp[5] );
		strcpy(LastestResultPages->NameEach[6].NameMenuItems,temp[6] );
	} else {
		strcpy(LastestResultPages->NameEach[0].NameMenuItems,"EMPTY");
		strcpy(LastestResultPages->NameEach[1].NameMenuItems,"EMPTY");
		strcpy(LastestResultPages->NameEach[2].NameMenuItems,"EMPTY");
		strcpy(LastestResultPages->NameEach[3].NameMenuItems,"EMPTY");
		strcpy(LastestResultPages->NameEach[4].NameMenuItems,"EMPTY");
		strcpy(LastestResultPages->NameEach[5].NameMenuItems,"EMPTY");
		strcpy(LastestResultPages->NameEach[6].NameMenuItems,"EMPTY");
	}
}
void DisplayOn5110::Update_SaveToSdcardPages(Pages_Struct *SaveToSdcard_Pages,bool isCheck){
	if (isCheck)
		strcpy(SaveToSdcard_Pages->NameEach[0].NameMenuItems," ->SAVED");
	else strcpy(SaveToSdcard_Pages->NameEach[0].NameMenuItems,"->NO SDCARD");
}