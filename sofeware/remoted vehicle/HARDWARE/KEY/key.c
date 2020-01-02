#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/**********************************

PaUp	PaDn	RowUp	RowDn	enter	MODE	C1	 C2 	C3	C4
C4		C5		B1		B0		C9		C8		B14  B15  C6	C7

**********************************/

 
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 |GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC0.1.2.3
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_15;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC0.1.2.3
	
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!

/*********************************
* @brief 
* @param whether Continuous press
					mode=1: support Continuous press
					mode=0: do not suporrt
* @retval KEY_PaUp_PRES ---- 1
					KEY_PaDn_PRES ---- 2
*********************************/

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		
  
	if(key_up &&(KEY_PaUp==0||KEY_PaDn==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY_PaUp==0)return KEY_PaUp_PRES;
		else if(KEY_PaDn==0)return KEY_PaDn_PRES;	
		
	}else if(KEY_PaUp==1&&KEY_PaDn==1)key_up=1; 	    //&&KEY2==1&&WK_UP==0
 	return 0;// 无按键按下
}
