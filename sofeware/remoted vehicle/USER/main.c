
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "timer.h"
#include "key.h"
#include "display.h"
#include "control.h"
#include "stdbool.h"

extern u8 buffer[20];
char mode =0 ;
char connect_flag = 0;

int main(void)
{	
	delay_init();
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	KEY_Init(); 
	uart2_init(115200);	 
	OLED_Init();
	TIM1_Int_Init(4999,71);
	TIM3_Int_Init(1999,719);
	while(1)
	{
		mode = mode_select();
		display(mode);
		run(buffer[2]);
	}
}






