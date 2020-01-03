
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
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	KEY_Init(); //IO��ʼ��
	uart2_init(115200);	 //���ڳ�ʼ��Ϊ9600
	OLED_Init();
	TIM1_Int_Init(4999,71);
	
	while(1)
	{
		display(mode_select());
		run(buffer[3]);
	}
}






