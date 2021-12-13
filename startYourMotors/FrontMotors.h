//To turn left, the left wheels turn more slowly than the right ones.
//To turn right, the left wheels turn more slowly than the right ones
#ifndef __TB6612FMG_
#define __TB6612FMG_

#include "DEV_Config_1.h"
#include "PCA9685_1.h"

//#################### PWM #######################
#define PWM_LEFTSIDE      PCA_CHANNEL_0
#define PWM_RIGHTSIDE      PCA_CHANNEL_5

//#################### RIGHT FRONT #######################
#define AIN1_LEFTSIDE     PCA_CHANNEL_1
#define AIN2_LEFTSIDE      PCA_CHANNEL_2


//#################### RIGHT REAR #######################
#define BIN1_RIGHTSIDE        PCA_CHANNEL_3
#define BIN2_RIGHTSIDE        PCA_CHANNEL_4


void Change_Motor_Speed(int side, int speed);
void Stop_Motors();
void Motor_Init(void);
void Motor_Handler(int signo);
void Drive_Forward(int speed);
void Drive_Backwards();
void Drive_Forward_Left();
void Drive_Forward_Right();
void Change_Motor_Speed(int side, int speed);


#endif
