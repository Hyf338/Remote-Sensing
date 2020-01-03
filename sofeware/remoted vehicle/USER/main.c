
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

extern u8 buffer[20];

int main(void)
{	
	delay_init();
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	KEY_Init(); //IO初始化
	uart2_init(115200);	 //串口初始化为9600
	OLED_Init();
	TIM1_Int_Init(4999,71);
	
	while(1)
	{
		display(mode_select());
		run(buffer[3]);
	}
}






