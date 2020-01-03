#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/*********************************
* @brief KEY_Init
* @param none
* @retval none
*********************************/
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 |GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC0.1.2.3
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
	
}

/*********************************
* @brief Infrared_Init
* @param none
* @retval none
*********************************/
void Infrared_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_6;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOC0.1.2.3
}



/*********************************
* @brief  key_scan
* @param whether Continuous press
					mode=1: support Continuous press
					mode=0: do not suporrt
* @retval KEY_UP_PRES ---- 1
					KEY_DOWM_PRES ---- 2
*********************************/
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up &&(KEY_UP==0||KEY_DOWM==0||KEY_LEFT==0||KEY_RIGHT==0||KEY_MID==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY_UP==0)return KEY_UP_PRES;
		else if(KEY_DOWM==0)return KEY_DOWM_PRES;	
		else if(KEY_LEFT==0)return KEY_LEFT_PRES;	
		else if(KEY_RIGHT==0)return KEY_RIGHT_PRES;
		else if(KEY_MID==0)return KEY_MID_PRES;
		
	}else if(KEY_UP==1&&KEY_DOWM==1&&KEY_LEFT==1&&KEY_RIGHT==1&&KEY_MID==1)key_up=1; 	    //&&KEY2==1&&WK_UP==0
 	return 0;// 无按键按下
}



