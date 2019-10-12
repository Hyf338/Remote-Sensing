#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY_UP  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//��ȡ����UP
#define KEY_DOWM  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//��ȡ����DOWM
#define KEY_LEFT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����LEFT 
#define KEY_RIGHT   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//��ȡ����RIGHT 
#define KEY_MID   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����MID 

#define Infrared_leftmost GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����ߵĺ���
#define Infrared_left GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ��ߵĺ���
#define Infrared_mid GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ�м�ĺ���
#define Infrared_right GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ�ҵĺ���
#define Infrared_rightmost GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ���ұߵĺ���

 

#define KEY_UP_PRES 	1	//KEY0����
#define KEY_DOWM_PRES	2	//KEY1����
#define KEY_LEFT_PRES	3	//KEY2����
#define KEY_RIGHT_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)
#define KEY_MID_PRES   5	//KEY_UP����(��WK_UP/KEY_UP)
#define KEY0_PRES   6	//KEY_UP����(��WK_UP/KEY_UP)
#define KEY1_PRES   7	//KEY_UP����(��WK_UP/KEY_UP)



void KEY_Init(void);//IO��ʼ��
void Infrared_Init(void);//����ӿڳ�ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��			
u8 Infrared_Scan(void);
#endif
