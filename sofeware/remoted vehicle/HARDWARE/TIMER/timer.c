#include "timer.h"
#include "stm32f10x_tim.h"
#include "stdbool.h"

//��ʱ��3�жϷ�����

extern bool mode_flag;
extern bool recvice_flag;
extern bool stop_flag;

short stop_cpunt=0;

//////////////////////////////////////////////////////////////////////////////////	 
//tim1:ch1234,pa8��9��10��11 ch123n,pb13��14��15 etr,pa12 bkin,pb12
//tim2=103retim5:ch1234,pa0��1��2��3 remap: pa15��pb3��10��11
//tim3:ch1234,pa6��7��pb0��1 remap: pc 6��7��8��9
//tim4:pb 6��7��8��9 100��װremap

// TIM2_CH1 PWM1 PA0
// TIM2_CH2 PWM2 PA1
// TIM2_CH3 PWM3 PB10
// TIM2_CH4 PWM4 PB11
// TIM3_CH1 PWM5 PA6
// TIM3_CH2 PWM6 PA7
// TIM4_CH1 PWM7 PB6
// TIM4_CH2 PWM8 PB7
////////////////////////////////////////////////////////////////////////////////// 	  


void TIM1_Int_Init(u16 arr,u16 psc)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����ģ��ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //ʹ��AFIO���ù���ģ��ʱ��
////	
////	
////	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�JTAG-DP������SW-DP
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE); //Timer3������ӳ��  
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //TIM_CH2|ch1   B4.B5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM1 Channel234 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 OC2
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //

  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);	
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //

//	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//
	TIM_ARRPreloadConfig(TIM1, ENABLE); //
//	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	
}




//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0; 
	

	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�

	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�  5ms�ж�
	{
		if(stop_flag==true)
		{
		stop_cpunt++;
		stop_cpunt=stop_cpunt>2000?2000:stop_cpunt;
		}
		else stop_cpunt=0;
		if(stop_cpunt==2000 && recvice_flag== false)
		{
			mode_flag=true;
		}
	}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}


