# /**************************************************************
# * Class: CSC-615-01 Fall 2021
# * Name: Antonino Calabrese
# * Student ID: 920831285
# * Github ID: ringnino
# * Project: Assignment 3 - Start your Motors
# *
# * File: assignment3.c
# *
# * Description: This file is the main file that needs to be executed
# * to run the motors. We need to initialize the GPIO pins and PCA9685
# * controller for use. After that we have a infinite while loop waiting
# * for the button to be pressed to start the motor in the foward direction.
# * After running foward for at least 2 seconds we slow down to 15% duty
# * cycle and then stop for 1 second. When we start back up again we will
# * be moving in the reverse direction and speed up until we hit 100%
# * duty cycle. Finally we stop the motors so they dont continue to run
# * after the program completes.
# **************************************************************/

#include <stdio.h>
#include "DEV_Config_1.h"
#include "PCA9685_1.h"
#include "wiringPi.h"
#include "FrontMotors.h"
//#include "Motors.c"




int main(int argc, char** argv)
{
  wiringPiSetupGpio();
  Motor_Init();

  Drive_Forward(100);
  delay(1000);

   //Drive_Forward_Left(100);
   //delay(1000);

   //Drive_Forward_Right(100);
   //delay(1000);
   //Drive_Backwards();

  //delay(2000);
  Stop_Motors();

      return 0;
}
