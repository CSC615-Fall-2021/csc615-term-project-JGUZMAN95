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
#include "echoSensor.h"

//#include "Motors.c"

//assign pins
#define LINE_SENSOR_ONE 10
#define LINE_SENSOR_TWO 22

//values of linesensor to to know wether on or off line
//0 == on the line
//1 == off the line
int leftLineOuput ;
int rightLineOuput ;

void lineInterrupt(void);



PI_THREAD (myThread){
        for (;;){

            if (wiringPiISR(LINE_SENSOR_ONE, INT_EDGE_BOTH, &lineInterrupt) < 0) {
                printf("error");
            }
            delay(100);
            if (wiringPiISR(LINE_SENSOR_TWO, INT_EDGE_BOTH, &lineInterrupt) < 0) {
                printf("error");
            }
            delay(100);
        }

}

void lineInterrupt(void){
    leftLineOuput = 0;
    rightLineOuput = 0;
    if(digitalRead(LINE_SENSOR_ONE) == 1){
        leftLineOuput = 1;
    }
    if(digitalRead(LINE_SENSOR_TWO) == 1){
        rightLineOuput = 1;
    }

}

// turn right until between 0 - 15 cm - left echo
// drive foward until left echo is greater than 15
// turn left for now delay
// drive foward if both left & front echo greater than 15

void objectAvoidance(void){
    double frontDistance;
    double leftDistance;
    for(;;) {

        leftDistance = leftEchoDistance();
        frontDistance = frontEchoDistance();

// turn right until between 0 - 15 cm - left echo
//0.0 < frontDistance && frontDistance <= 15.0

        if (leftDistance > 7.7 && frontDistance < 20.0 && frontDistance > 7.5) {
            turnRight();
            printf("turn Right%f\n\n",frontDistance);
        }

//    if (leftDistance > 16.0 && leftDistance < 25.0  ) {
//      drive_Forward();
//      printf("forward%f\n\n",leftDistance);
//
//    }

//     if(leftDistance > 10.0 && leftDistance < 16.6 && frontDistance > 20.0){
        if(leftDistance > 11.52 && leftDistance < 25.6 && frontDistance > 18.5){
            printf("turn forward  %f\n\n",leftDistance);
            drive_Forward();
            if(leftDistance <= 18.28 && leftDistance >= 13.56 && frontDistance >= 3.85){
                printf("turn left\n");
                turnLeft();
            }else{
                drive_Forward();
            }
        }
        if(leftLineOuput == 0 && rightLineOuput == 1){
            turnRight();
            printf("out\n");
            break;

        }



        //if( )

    }

}

int main(int argc, char** argv)
{
    wiringPiSetupGpio();
    Motor_Init();

    int x = piThreadCreate(myThread);

    if (x != 0) {
        printf("it didn't start\n");
    }
/*
  printf("Calibrating... \n");

  if(leftLineOuput == 0){
    printf("...\n");
  }
  delay(1);

  if(rightLineOuput == 0){
    printf("...\n ");
  }
  delay(1);
  printf("Calibrating done\n");

  //Stop_Motors();
*/
/*
for(;;){
  //turnLeft();
  Stop_Motors();

}
*/


    //Stop_Motors();
    //delay(1000*10);

    /*for(;;) {
  turnRight();
  printf("left\n");
    }*/
/*
  turnRight();
  printf("right\n");

  delay(1000*10);

  reverse();
  printf("reverse\n");
  delay(1000*10);

  drive_Forward(100);
  printf("forward\n");

  delay(1000*10);

  Stop_Motors();
  delay(1000*10);

========
}
  */
    //turnRight();
    //delay(1000);

    //reverse();
    //delay(1000);

    Stop_Motors();
    delay(1000*3);// delay(1000*10);

    for(;;){
        double frontDistance = frontEchoDistance();


// both must be off line we are reading the black line to be able
        //turn left or right

/* ********************** ECHO SENSOR CODE ********************************/
// stop motors between 0 - 15 cm - front echo
        if( 0.0 < frontDistance && frontDistance <= 13.0) {
            Stop_Motors();
            turnRight();
            if(leftLineOuput == 0 && rightLineOuput == 0){
                objectAvoidance();
            }else{
                drive_Forward();
            }

        }





/* ********************** LINE SENSOR CODE ********************************/
        if(leftLineOuput == 0 && rightLineOuput == 0){
            drive_Forward();

        }

        //if left line is black then we turn left to follow the line
        //turn until both sensors are on 1 then move forward
        if (leftLineOuput == 0 && rightLineOuput == 1){
            turnRight();

        }

        //if Right line is on black then we turn right
        //turn until both sensors are on 1 then move forward
        if (leftLineOuput == 1 && rightLineOuput == 0){
            turnLeft();

        }
        if(leftLineOuput == 1 && rightLineOuput == 1){

            drive_Forward();

        }




    }


    return 0;

}
