#ifndef __DATATYPE_H
#define __DATATYPE_H

enum MODE{
	sens_mode=1,remote_mode
};

struct angle{
	float pitch;
	float roll;
	float yaw;
};

struct adc{
	int adc_left_UD;
	int adc_left_LR;
	int adc_right_UD;
	int adc_right_LR;
};

struct motor{
	int motor1;
	int motor2;
	int motor3;
	int motor4;
};

#endif


