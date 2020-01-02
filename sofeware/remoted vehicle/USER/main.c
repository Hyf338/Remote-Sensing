
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "datatype.h"
#include "control.h"


//---------陀螺仪头文件---------------
#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 


//----------外设头文件---------------
#include "usart.h"
#include "oled.h"
#include "key.h"
#include "adc.h"
#include "buzz.h"

//----------陀螺仪初始化数据--------------
float pitch=0,roll=0,yaw=0; 		//欧拉角（俯仰角---翻滚角---横向角）
short aacx,aacy,aacz;		//加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
short temp;					//温度

extern struct angle angle;

int main(void)
 {
	 
	 delay_init();	    	 //延时函数初始化	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级

	 uart1_init(115200);	 //串口初始化为115200
	 buzz_Init();
	 OLED_Init();
	 KEY_Init(); //IO初始化
	 Adc_Init();
   TIM4_Int_Init(50000,107);
	 Boot_Animation();

//	OLED_Clear();

	 
	 //----陀螺仪初始化-------------------
	 MPU_Init();					       //初始化MPU6050
	 while(mpu_dmp_init())       //陀螺仪自检
   {
		 OLED_ShowString(0,3,(u8 *)"Error",12);
		 OLED_Refresh_Gram();
		 delay_ms(200);
   }
	 
		OLED_Clear();
	 
	
		while(1)
		{
			mpu_dmp_get_data(&angle.pitch,&angle.roll,&angle.yaw);
			display(2);
			adc_data_process();
		}	 
} 

