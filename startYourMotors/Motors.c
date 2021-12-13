#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <signal.h>
#include <wiringPi.h>

#include "DEV_Config_1.h"
#include "PCA9685_1.h"
#include "FrontMotors.h"

#define LEFTSIDE   0
#define RIGHTSIDE  1

int CURRENTSPEEDLEFT = 0;
int CURRENTSPEEDRIGHT = 0;

/****************************
    CAR MOTOR LOCATION
          FRONT
      1           2
 LEFT               RIGHT
      3           4
          BACK
****************************/


void Motor_Init(void){
    // The address range from 0x40 to 0x5F.
    PCA9685_Init(0x40, 0x41);
    PCA9685_SetPWMFreq(100);
}

void Motor_Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:Motor Stop\r\n");

    //stop code here
    Stop_Motors();

    DEV_ModuleExit();
    exit(0);
}
void Stop_Motors(){

        PCA9685_SetPwmDutyCycle(PWM_LEFTSIDE, 0);
        PCA9685_SetPwmDutyCycle(PWM_RIGHTSIDE, 0);
}

void Drive_Forward(int speed){
    if(speed > 100){

        speed = 100;
        printf("Speed is <= 100\n Speed was set to 100\n");

    }
     // leftside
     // an1 = 1, an2 = 0 backwards
     // an1 = 0, an2 = 1 forwards
     CURRENTSPEEDLEFT = speed;
     CURRENTSPEEDRIGHT = speed;
     PCA9685_SetPwmDutyCycle(PWM_LEFTSIDE, CURRENTSPEEDLEFT);
     PCA9685_SetLevel(AIN1_LEFTSIDE, 0);
     PCA9685_SetLevel(AIN2_LEFTSIDE, 1);

    // rightside
    // bn1 = 1, bn2 = 0 backwards
    // bn1 = 0, bn2 = 1 forwards
    PCA9685_SetPwmDutyCycle(PWM_RIGHTSIDE, CURRENTSPEEDRIGHT);
    PCA9685_SetLevel(BIN1_RIGHTSIDE , 1);
    PCA9685_SetLevel(BIN2_RIGHTSIDE, 0);


}
void Drive_Backwards(){
    //leftside
    PCA9685_SetPwmDutyCycle(PWM_LEFTSIDE, CURRENTSPEEDLEFT);
    PCA9685_SetLevel(BIN1_RIGHTSIDE  , 0);
    PCA9685_SetLevel(BIN2_RIGHTSIDE , 1);

    //rightside
    PCA9685_SetPwmDutyCycle(PWM_RIGHTSIDE, CURRENTSPEEDRIGHT);
    PCA9685_SetLevel(AIN1_LEFTSIDE, 1);
    PCA9685_SetLevel(AIN2_LEFTSIDE, 0);
}

//To turn left, the left wheels turn more slowly than the right ones.
//WE NEED TO CHANGE SPEED AGIN TO HAVE BOTH WHEELS RUNNING AT SAME SPEED
// ONCE TURN IS FINISHED
void Drive_Forward_Right(){
    //rightside
    PCA9685_SetPwmDutyCycle(PWM_LEFTSIDE, 50);
    PCA9685_SetLevel(BIN1_RIGHTSIDE  , 1);
    PCA9685_SetLevel(BIN2_RIGHTSIDE  , 0);

    //leftside
    PCA9685_SetPwmDutyCycle(PWM_RIGHTSIDE, 100);
    PCA9685_SetLevel(AIN1_LEFTSIDE, 0);
    PCA9685_SetLevel(AIN2_LEFTSIDE, 1);

}

//To turn right, the RIGHT wheels turn more slowly than the right ones
//WE NEED TO CHANGE SPEED AGIN TO HAVE BOTH WHEELS RUNNING AT SAME SPEED
// ONCE TURN IS FINISHED
void Drive_Forward_Left(){
    //leftside
    PCA9685_SetPwmDutyCycle(PWM_LEFTSIDE, 100);
    PCA9685_SetLevel(BIN1_RIGHTSIDE , 1);
    PCA9685_SetLevel(BIN2_RIGHTSIDE  , 0);

    //rightside
    PCA9685_SetPwmDutyCycle(PWM_RIGHTSIDE, 50);
    PCA9685_SetLevel(AIN1_LEFTSIDE, 0);
    PCA9685_SetLevel(AIN2_LEFTSIDE, 1);
}

void Change_Motor_Speed(int side, int speed){

/*
    if(side == LEFTSIDE ){
        if (CURRENTSPEEDLEFT > speed) {
            while (CURRENTSPEEDLEFT > speed) {
                CURRENTSPEEDLEFT -= 10;
                PCA9685_SetPwmDutyCycle(PWM_LEFT_REAR, CURRENTSPEEDLEFT);
                PCA9685_SetPwmDutyCycle(PWM_LEFT_FRONT, CURRENTSPEEDLEFT);
            }
        } else {
            while (CURRENTSPEEDLEFT < speed) {
                CURRENTSPEEDLEFT += 10;
                PCA9685_SetPwmDutyCycle(PWM_LEFT_REAR, CURRENTSPEEDLEFT);
                PCA9685_SetPwmDutyCycle(PWM_LEFT_FRONT, CURRENTSPEEDLEFT);
            }
        }
    }

    else {
        if (CURRENTSPEEDRIGHT > speed) {
            while (CURRENTSPEEDRIGHT > speed) {
                CURRENTSPEEDRIGHT -= 10;
                PCA9685_SetPwmDutyCycle(PWM_RIGHT_REAR, CURRENTSPEEDRIGHT);
                PCA9685_SetPwmDutyCycle(PWM_RIGHT_FRONT, CURRENTSPEEDRIGHT);
            }
        }else{
            while (CURRENTSPEEDRIGHT < speed) {
                CURRENTSPEEDRIGHT += 10;
                PCA9685_SetPwmDutyCycle(PWM_RIGHT_REAR, CURRENTSPEEDRIGHT);
                PCA9685_SetPwmDutyCycle(PWM_RIGHT_FRONT, CURRENTSPEEDRIGHT);
            }
        }
    }
    */

}
