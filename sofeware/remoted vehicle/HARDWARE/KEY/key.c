#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/**********************************

PaUp	PaDn	RowUp	RowDn	enter	MODE	C1	 C2 	C3	C4
C4		C5		B1		B0		C9		C8		B14  B15  C6	C7

**********************************/

 
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 |GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC0.1.2.3
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_15;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOC0.1.2.3
	
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!

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
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		
  
	if(key_up &&(KEY_PaUp==0||KEY_PaDn==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY_PaUp==0)return KEY_PaUp_PRES;
		else if(KEY_PaDn==0)return KEY_PaDn_PRES;	
		
	}else if(KEY_PaUp==1&&KEY_PaDn==1)key_up=1; 	    //&&KEY2==1&&WK_UP==0
 	return 0;// �ް�������
}
