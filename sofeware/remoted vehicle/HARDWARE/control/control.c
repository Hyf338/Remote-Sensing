#include "control.h"
#include "sys.h"
#include "timer.h"
#include "stdbool.h"
#include "key.h"
#include "datatype.h"


extern struct angle angle;
extern struct motor motor;
extern struct adc adc;
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


/*********************************
* @brief  set the motor param to make car stop
* @param none
* @retval none
*********************************/
void stop()
{
	motor.motor1 =0;
	motor.motor2 =0;
	motor.motor3 =0;
	motor.motor4 =4999;
}

/*********************************
* @brief base on angle（pitch/yaw） to control car
* @param mode : sens_mode/remote_mode
* @retval none
*********************************/
void angle_mode(void)
{
	if(angle.pitch>2)
	{
		motor.motor1 =200+angle.pitch*100;
		motor.motor3 =200+angle.pitch*100;
		motor.motor2 =0;
		motor.motor4 =4999;
	}
	
	else if(angle.pitch<-2)
	{
		motor.motor2 =-200-angle.pitch*100;
		motor.motor4 =0;
		motor.motor1 =0;
		motor.motor3 =4999-200-angle.pitch*100;
	}
	else 
		stop();
}
/*********************************
* @brief base on putter(adc) to control car
* @param mode : sens_mode/remote_mode
* @retval none
*********************************/
void adc_mode()
{
	motor.motor1 =200+adc.adc_left_UD*100;
	motor.motor3 =200+adc.adc_left_UD*100;
	motor.motor2 =0;
	motor.motor4 =4999;
	
	
}
/*********************************
* @brief choose a mode to run
* @param mode : sens_mode/remote_mode
* @retval none
*********************************/
void run(u8 mode)
{
	if(mode == sens_mode)
		angle_mode();
	else if(mode == remote_mode)
		adc_mode();
	else 
		stop();
	TIM_SetCompare1(TIM1,motor.motor1);
	TIM_SetCompare2(TIM1,motor.motor2);			 
	TIM_SetCompare3(TIM1,motor.motor3);		   
	TIM_SetCompare4( TIM1,motor.motor4);
}

