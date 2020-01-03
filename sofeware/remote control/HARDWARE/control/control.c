#include "control.h"
#include "datatype.h"

//--------相关外设头文件
#include "oled.h"
#include "adc.h"
#include "adc.h"
#include "usart.h"

//---------陀螺仪头文件---------------
#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 


extern struct angle angle;
extern struct adc ADC;
extern u8 buffer[20];



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
* @breif : pake a buffer to be send
* @param : mode ---> to selext the struct to be pakeged
* @retval : none
*********************************/
void data_send_process(u8 mode)
{
	char *p = NULL;
	char i=0;
	if(mode == sens_mode)
	{
		buffer[2] = mode;
		p = (char* )&angle;
		for(i=0;i<=sizeof(struct angle);i++)
		{
			buffer[i+3]=*p;
			p++;
		}
	}
	else if(mode == remote_mode)
	{
		buffer[2] = mode;
		p = (char* )&ADC;
		for(i=0;i<=sizeof(struct adc);i++)
		{
			buffer[i+3]=*p;
			p++;
		}
	}
}





