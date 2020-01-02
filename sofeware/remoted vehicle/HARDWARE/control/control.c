#include "control.h"
#include "datatype.h"

//--------相关外设头文件
#include "oled.h"
#include "adc.h"

//---------陀螺仪头文件---------------
#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 


extern struct angle angle;
extern struct adc ADC;

/********************
* @breif : Human Machine Interface
* @param : mode ---> motion mode select
* @retval : none
********************/
void display(u8 mode)
{
	OLED_ShowString(0,0,(u8 *)"*Mode->",16);
	if(mode == 1)
	{
		OLED_ShowString(60,0,(u8 *)"sense",16);
		OLED_ShowString(0,16,(u8 *)"Pitch:",16);
		OLED_ShowString(0,32,(u8 *)"Roll:",16);
		OLED_ShowString(0,48,(u8 *)"Yaw:",16);
		OLED_ShowNum(60,16,angle.pitch,4,16);
		OLED_ShowNum(60,32,angle.roll,4,16);
		OLED_ShowNum(60,48,angle.yaw,4,16);
		OLED_Refresh_Gram();
	}
	else if(mode == 2)
	{
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


/********************************
* @breif : get adc_data ten times to get average value;after process, value is 0-100
* @param : none
* @retval : none
*********************************/
void adc_data_process(void)
{
	ADC.adc_left_LR = Get_Adc_Average(ADC_Channel_13,10);
	ADC.adc_left_UD = Get_Adc_Average(ADC_Channel_12,10);
	ADC.adc_right_LR= Get_Adc_Average(ADC_Channel_11,10);
	ADC.adc_right_UD = Get_Adc_Average(ADC_Channel_10,10);
	
	ADC.adc_left_LR=ADC.adc_left_LR*100/4096;
	ADC.adc_left_UD=100-ADC.adc_left_UD*100/4096;
	ADC.adc_right_LR=ADC.adc_right_LR*100/4096;
	ADC.adc_right_UD=100-ADC.adc_right_UD*100/4096;
	
}



/********************************
* @breif : 
* @param : 
* @retval : 
*********************************/
void data_send_process()
{
	
}





