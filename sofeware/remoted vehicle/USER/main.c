
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "datatype.h"
#include "control.h"


//---------������ͷ�ļ�---------------
#include "mpuiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 


//----------����ͷ�ļ�---------------
#include "usart.h"
#include "oled.h"
#include "key.h"
#include "adc.h"
#include "buzz.h"

//----------�����ǳ�ʼ������--------------
float pitch=0,roll=0,yaw=0; 		//ŷ���ǣ�������---������---����ǣ�
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
short temp;					//�¶�

extern struct angle angle;

int main(void)
 {
	 
	 delay_init();	    	 //��ʱ������ʼ��	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	 uart1_init(115200);	 //���ڳ�ʼ��Ϊ115200
	 buzz_Init();
	 OLED_Init();
	 KEY_Init(); //IO��ʼ��
	 Adc_Init();
   TIM4_Int_Init(50000,107);
	 Boot_Animation();

//	OLED_Clear();

	 
	 //----�����ǳ�ʼ��-------------------
	 MPU_Init();					       //��ʼ��MPU6050
	 while(mpu_dmp_init())       //�������Լ�
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

