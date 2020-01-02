#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"



#define KEY_PaUp  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//��ȡ����UP
#define KEY_PaDn  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����DOWM
#define KEY_RowUp  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ����DOWM
#define KEY_RowDn  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//��ȡ����DOWM
#define KEY_enter  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//��ȡ����DOWM
#define KEY_MODE  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//��ȡ����DOWM
#define KEY_C1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����DOWM
#define KEY_C2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����DOWM
#define KEY_C3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//��ȡ����DOWM
#define KEY_C4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//��ȡ����DOWM


#define KEY_PaUp_PRES 	1	//KEYUP����
#define KEY_PaDn_PRES	2	//KEYDW����
#define KEY_RowUp_PRES	3
#define KEY_RowDn_PRES	4
#define KEY_enter_PRES	5
#define KEY_MODE_PRES	6
#define KEY_C1_PRES	7
#define KEY_C2_PRES	8
#define KEY_C3_PRES	9
#define KEY_C4_PRES	10



void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
