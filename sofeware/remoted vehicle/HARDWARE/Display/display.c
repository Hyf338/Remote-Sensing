#include "display.h"
#include "oled.h"
#include "key.h"
#include "stdbool.h"

extern int Motor1,Motor2;
extern signed short int Pitch,Roll,Yaw;
extern u8 key_v;
u8 display_page=0;
//enum key_up
//{
//	key_up_1=1,key_up_2,key_up_3,key_up_4
//};
u8 up_dowm=1;
u8 left_right=1;

extern bool start_flag;//true 1  false 0
extern bool mode_flag,recvice_flag;
extern bool stop_flag;

void Page1(void)
{
//	OLED_Clear();
	OLED_ShowString1(12,0,"stop_flag:");
	OLED_ShowString1(12,2,"mode_flag:");
	OLED_ShowString1(12,4,"rec_flag:"); 
	OLED_ShowString1(12,6,"go now? ->"); 
	
	Dis_Float(0,100,stop_flag,0);
	Dis_Float(2,100,mode_flag,0);
	Dis_Float(4,100,recvice_flag,0);	
	if(start_flag==true)
	{
		OLED_ShowString1(95,6,"go");
	}
	else OLED_ShowString1(95,6,"stop");
}

void Page2(void)
{
//	 OLED_Clear();
	 OLED_ShowCHinese1(27,0,0);
	 OLED_ShowCHinese1(45,0,1);
	 OLED_ShowCHinese1(63,0,2);
	 OLED_ShowCHinese1(81,0,3);
	 OLED_ShowString1(0,2,"Pitch");
	 OLED_ShowString1(0,4,"Roll");
	 OLED_ShowString1(0,6,"Yaw");  
	 Dis_Float(2,71,Pitch,2);
	 Dis_Float(4,71,Roll,2);
//	     Dis_String(2,32,"_");
	 Dis_Float(6,71,Yaw,2);	
}



void display()
{
	
	key_v=KEY_Scan(0);

	if(key_v==KEY_MID_PRES) display_page+=1;
	display_page=display_page>3?0:display_page;
	
	if(key_v==KEY_UP_PRES) up_dowm+=1;
	up_dowm=up_dowm>4?1:up_dowm;
	
	if(key_v==KEY_DOWM_PRES) up_dowm-=1;
	up_dowm=up_dowm<1?4:up_dowm;
	
	
	
	switch(display_page)
	{
		case 0:	
		{
			OLED_Clear();			
			Page1();
			switch(up_dowm)
			{
				case 2:OLED_ShowString1(0,2,"*");break;
				case 3:OLED_ShowString1(0,4,"*");break;
				case 4:
				{
					OLED_ShowString1(0,6,"*");
					if(key_v==KEY_LEFT_PRES) 
						start_flag=true;//true 1  false 0
					if(key_v==KEY_RIGHT_PRES) 
						start_flag=false;//true 1  false 0
					

					break;
				}
			}
			break;
		}
		case 1:
		{
		  OLED_Clear();
			Page2();
			break;
		}
		default:  break;
	}
}




