#include "display.h"
#include "oled.h"

extern int Motor1,Motor2;
extern u8 Pitch,Roll,Yaw;

void Page1(void)
{
	     //OLED_Clear();
	     OLED_ShowCHinese1(27,0,0);
       OLED_ShowCHinese1(45,0,1);
		   OLED_ShowCHinese1(63,0,2);
       OLED_ShowCHinese1(81,0,3);
	     OLED_ShowString1(0,2,"Motor1");
	     OLED_ShowString1(0,4,"Motor2"); 
	     Dis_Float(4,71,Motor1,2);
//	     Dis_String(2,32,"_");
	     Dis_Float(6,71,Motor2,2);	
}

void Page2(void)
{
	     //OLED_Clear();
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
