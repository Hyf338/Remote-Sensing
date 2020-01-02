#include "timer.h"
#include "stm32f10x_tim.h"
#include "stdbool.h"

//定时器3中断服务函数

extern bool mode_flag;
extern bool recvice_flag;
extern bool stop_flag;

short stop_cpunt=0;

//////////////////////////////////////////////////////////////////////////////////	 
//tim1:ch1234,pa8、9、10、11 ch123n,pb13、14、15 etr,pa12 bkin,pb12
//tim2=103retim5:ch1234,pa0、1、2、3 remap: pa15、pb3、10、11
//tim3:ch1234,pa6、7、pb0、1 remap: pc 6、7、8、9
//tim4:pb 6、7、8、9 100封装remap

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
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设模块时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //使能AFIO复用功能模块时钟
////	
////	
////	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭JTAG-DP，启用SW-DP
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE); //Timer3部分重映射  
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //TIM_CH2|ch1   B4.B5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM1 Channel234 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC2
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //

  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);	
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //

//	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//
	TIM_ARRPreloadConfig(TIM1, ENABLE); //
//	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
	
}




//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0; 
	

	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断

	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断  5ms中断
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
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}


