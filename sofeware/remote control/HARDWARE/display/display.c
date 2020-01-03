#include "display.h"

#include "oled.h"
#include "datatype.h"
#include "control.h"


extern struct angle angle;
extern struct adc ADC;

/********************
* @breif : motion mode select
* @param : mode ---> press key to select a mode
* @retval : page : is mode
********************/
u8 mode_select(u8 mode)
{
	static char page=0;
	if(mode == sens_mode)
	{
		page = sens_mode;
		OLED_Clear();
	}
	else if(mode == remote_mode)
	{
		page = remote_mode;
		OLED_Clear();
	}
	display(page);
	return page;
}


/********************
* @breif : Human Machine Interface --display_page
* @param : mode ---> motion mode select
* @retval : none
********************/
void display(u8 page)
{
	OLED_ShowString(0,0,(u8 *)"*Mode->",16);
	if(page == sens_mode)
	{
		OLED_ShowString(60,0,(u8 *)"sense",16);
		OLED_ShowString(0,16,(u8 *)"Pitch:",16);
		OLED_ShowString(0,32,(u8 *)"Roll:",16);
		OLED_ShowString(0,48,(u8 *)"Yaw:",16);
		OLED_ShowNum(60,16,angle.pitch,4,16);
		OLED_ShowNum(60,32,angle.roll,4,16);
		OLED_ShowNum(60,48,angle.yaw,4,16);
		if(angle.pitch<0)
		{
			OLED_ShowString(65,16,(u8 *)"-",16);
		}
		if(angle.roll<0)
		{
			OLED_ShowString(65,32,(u8 *)"-",16);
		}
		if(angle.yaw<0)
		{
			OLED_ShowString(65,48,(u8 *)"-",16);
		}
		OLED_Refresh_Gram();
	}
	else if(page == remote_mode)
	{
		adc_data_process();
		OLED_ShowString(60,0,(u8 *)"remote",16);
		OLED_ShowString(0,16,(u8 *)"UD:",16);
		OLED_ShowString(0,32,(u8 *)"LR:",16);
		OLED_ShowString(64,16,(u8 *)"UD:",16);
		OLED_ShowString(64,32,(u8 *)"LR:",16);
		OLED_ShowNum(25,16,ADC.adc_left_UD,4,16);
		OLED_ShowNum(25,32,ADC.adc_left_LR,4,16);
		OLED_ShowNum(85,16,ADC.adc_right_UD,4,16);
		OLED_ShowNum(85,32,ADC.adc_right_LR,4,16);
		OLED_Refresh_Gram();
	}
}

