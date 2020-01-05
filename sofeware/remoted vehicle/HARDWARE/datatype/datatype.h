#ifndef __DATATYPE_H
#define __DATATYPE_H


#define left_offset 200
#define right_offset 300
#define putter_offset 50


enum MODE{
 disconnect,sens_mode,remote_mode
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


