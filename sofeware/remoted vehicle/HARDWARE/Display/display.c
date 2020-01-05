#include "display.h"
#include "oled.h"
#include "key.h"
#include "stdbool.h"
#include "datatype.h"

extern struct angle angle;
extern struct adc adc;
extern u8 buffer[20];


/********************
* @breif : motion mode select
* @param : mode ---> press key to select a mode
* @retval : page : is mode
********************/
u8 mode_select(void)
{
	static char mode=0;
	 OLED_ShowString1(0,0,"*mode->");
	if(buffer[2] == disconnect && (mode !=disconnect))
	{
		mode = disconnect;
		OLED_Clear();
	}
	else if(buffer[2] == sens_mode && (mode !=sens_mode))
	{
		mode = sens_mode;
		OLED_Clear();
	}
	else if(buffer[2] == remote_mode && (mode != remote_mode))
	{
		mode = remote_mode;
		OLED_Clear();
	}
	return mode;
}

/********************
* @breif : Human Machine Interface --display_page
* @param : mode ---> motion mode select
* @retval : none
********************/
void display(u8 mode)
{
	if(mode == disconnect)
		OLED_ShowString1(30,2,"disconnect");
	if(mode == sens_mode)
	{
	 OLED_ShowString1(70,0,"sens");
	 OLED_ShowString1(0,2,"pitch");
	 OLED_ShowString1(0,4,"roll");
	 OLED_ShowString1(0,6,"yaw");  
	 Dis_Float(2,71,angle.pitch,2);
	 Dis_Float(4,71,angle.roll,2);
	 Dis_Float(6,71,angle.yaw,2);	
	}
	if(mode == remote_mode)
	{
	 OLED_ShowString1(70,0,"remote");
		OLED_ShowString1(0,2,"UD:");
		OLED_ShowString1(0,4,"LR:");
		OLED_ShowString1(70,2,"UD:");  
		OLED_ShowString1(70,4,"LR:");  
	 Dis_Float(2,30,adc.adc_left_UD,0);
	 Dis_Float(4,30,adc.adc_left_LR,0);
	 Dis_Float(2,100,adc.adc_right_UD,0);
	 Dis_Float(4,100,adc.adc_right_LR,0);
	}
}
