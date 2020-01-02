/************************************************************************************
							本例程提供自以下店铺：
								Ilovemcu.taobao.com
								epic-mcu.taobao.com
							实验相关外围扩展模块均来自以上店铺
							作者：神秘藏宝室							
*************************************************************************************/
#include "stm32f10x.h"
#include "delay.h"
#include "HX711.h"
#include "usart.h"
#include "oled.h"
#include "timer.h"
#include "key.h"
#include "display.h"
#include "control.h"
#include "stdbool.h"
int Motor1=0;
int Motor2=0;
int Motor3=0;
int Motor4=2999;
u8 key_v=0;

//signed short int test_1=0;
//int test_size=0;
u8 receive_data[8]={0,0,0,0,0,0,0,0};
char pitch_L=0,pitch_H=0,roll_L=0,roll_H=0,yaw_L=0,yaw_H=0;
signed short int Pitch=0,Roll=0,Yaw=0;


bool start_flag = false;//true 1  false 0
bool mode_flag=false;


int main(void)
{	
	
	delay_init();
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	KEY_Init(); //IO初始化
	uart_init(115200);	 //串口初始化为9600
	OLED_Init();
	TIM1_Int_Init(800,71);
	TIM3_Int_Init(800,35);
	TIM_Cmd(TIM3, DISABLE);  //
	while(1)
	{

		display();
		data_process();
		run();
		
	}
}






