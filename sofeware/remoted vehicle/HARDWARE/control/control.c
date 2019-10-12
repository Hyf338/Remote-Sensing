#include "control.h"
#include "sys.h"
#include "timer.h"
#include "stdbool.h"
#include "key.h"

/*
	pitch    short     						原始数据
	Pitch    signed short int     强制转化成有符号16位
	pitch_L  short int        		低八位
*/

extern u8 receive_data[8];
extern char pitch_L,pitch_H,roll_L,roll_H,yaw_L,yaw_H;
extern signed short int Pitch,Roll,Yaw;
extern int Motor1,Motor2,Motor3,Motor4;
extern bool start_flag;
extern bool mode_flag;

bool recvice_flag=false;
bool stop_flag=false;

short test=0;



void data_process(void)
{

	test=0;
	test=pitch_H;
	test<<=8;
	test&=0xff00;
	test|=pitch_L;
	Pitch=test;
	
	test=0;
	test=roll_H;
	test<<=8;
	test&=0xff00;
	test|=roll_L;
	Roll=test;
	
	test=0;
	test=yaw_H;
	test<<=8;
	test&=0xff00;
	test|=yaw_L;
	Yaw=test;
	
}

/*
	右轮   TIM1 ch1 ch2 状态
								+		0		前进
								0		0		停止
								0		-		后退
								
	左轮		TIM1 ch3 ch4 状态
								+		0		停止
								+	> +		前进/差越小，速度越快
								0		+		后退	
	备注：通道4仿佛是定时器的pwm模式不一样
*/


void Infrared_mode(void)
{
	
	if(Infrared_rightmost==0&&Infrared_leftmost==0&&Infrared_right==0&&Infrared_left==0&&Infrared_mid==0)
	{
		stop_flag=true;
		TIM_Cmd(TIM3, ENABLE);  //使能TIM1
		Motor1=200;
		Motor2=0;
		Motor3=800;
		Motor4=200;
	}
	
	else
	{
		stop_flag=false;
		if(Infrared_rightmost==1&&Infrared_leftmost==1&&Infrared_right==1&&Infrared_left==1)
		{
			Motor1=450;
			Motor2=0;
			Motor3=800;
			Motor4=400;
		}
		else if(Infrared_rightmost==1)
		{
			Motor1=500;
			Motor2=0;
			Motor3=0;
			Motor4=550;
		}
		else if(Infrared_leftmost==1)
		{
			Motor1=0;
			Motor2=400;
			Motor3=800;
			Motor4=450;
		}
		else if(Infrared_right==1)
		{
			Motor1=300;
			Motor2=0;
			Motor3=800;
			Motor4=200;
		}
		else if(Infrared_left==1)
		{
			Motor1=200;
			Motor2=0;
			Motor3=800;
			Motor4=350;
		}
		else if(Infrared_leftmost==0&&Infrared_left==0&&Infrared_mid==1&&Infrared_right==0&&Infrared_rightmost==0)
		{
			Motor1=350;
			Motor2=0;
			Motor3=800;
			Motor4=400;
		}
	}
}


void angle_mode(void)
{

	if(Pitch>0)
	{
		Motor1=20*Pitch;
		Motor2=0;
		Motor3=800;
		Motor4=15*Pitch;
	}
	else 
	{
		Motor1=0;
		Motor2=-20*Pitch;
		Motor3=800+15*Pitch;
		Motor4=0;
	}
	if(Roll>0)
	{
		Motor1+=15*Roll;
		Motor2=Motor2;
		
	}
	else
	{
		Motor4-=15*Roll;
	}
}


void run()
{
	if(start_flag == true)
	{
		if(mode_flag==false)
		{
			Infrared_mode();
		}
		if(mode_flag==true)
		{
			angle_mode();
		}
		if(recvice_flag==1)
		{
			mode_flag=false;
		}
	}
	if(start_flag==false)
	{
		Motor1=0;
		Motor2=0;
		Motor3=0;
		Motor4=800;
	}
	TIM_SetCompare1(TIM1,Motor1);
	TIM_SetCompare2(TIM1,Motor2);			 
	TIM_SetCompare3(TIM1,Motor3);		   
	TIM_SetCompare4(TIM1,Motor4);
}

