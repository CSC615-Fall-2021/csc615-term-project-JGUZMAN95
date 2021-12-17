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
/*
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
        if(leftDistance > 11.52 && leftDistance < 26.6 && frontDistance > 18.5){
            printf("turn forward  %f\n\n",leftDistance);
            drive_Forward();
            if(leftDistance < 17.28 && leftDistance > 14.56 && frontDistance > 3.90){
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
        */

if(leftDistance > 42.5 ){
    turnLeft();
    printf("left\n");
    if(frontDistance < 70.0 && leftDistance > 43.0){
        drive_Forward();
        while(frontDistance > 0){
            turnRight();
        }

        printf("last Forward\n");

    }
}
if(leftDistance < 40.0 ){
    drive_Forward();
    printf("forward\n");

}
if((leftLineOuput == 1 && rightLineOuput == 1) || (leftLineOuput == 0 && rightLineOuput == 1) ||(leftLineOuput == 1 && rightLineOuput == 0)){
    while(rightLineOuput != 0){
        turnRight();
        if(rightLineOuput == 0 ){
            break;
            break;
        }
    }

}
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
        double leftDistance = leftEchoDistance();

        int previousLeft;
        int previousRight;


// both must be off line we are reading the black line to be able
        //turn left or right

/* ********************** ECHO SENSOR CODE ********************************/
// stop motors between 0 - 15 cm - front echo
        if( 0.0 < frontDistance && frontDistance < 19.5) {
            printf("object\n");
            //adding left sensor
            if(leftDistance > 100.00 || leftDistance > 20.0 && frontDistance < 18.0  ){
               while(leftDistance > 100.00){
                   double frontDistance = frontEchoDistance();
                   double leftDistance = leftEchoDistance();
                    turnRight();
                   if(leftDistance < 24.0){
                       drive_Forward();
                       if(leftLineOuput == 0 && rightLineOuput == 0 && leftDistance < 50.0){
                           printf("avoidance\n");
                           objectAvoidance();
                           break;
                       }

                   }

               }
            }
        }






/* ********************** LINE SENSOR CODE ********************************/
        if(leftLineOuput == 0 && rightLineOuput == 0){
            previousLeft = leftLineOuput;
            previousRight = rightLineOuput;
            drive_Forward();

        }

        //if left line is black then we turn left to follow the line
        //turn until both sensors are on 1 then move forward
        if (leftLineOuput == 0 && rightLineOuput == 1){
            previousLeft = leftLineOuput;
            previousRight = rightLineOuput;
            turnRight();

        }

        //if Right line is on black then we turn right
        //turn until both sensors are on 1 then move forward
        if (leftLineOuput == 1 && rightLineOuput == 0){
            previousLeft = leftLineOuput;
            previousRight = rightLineOuput;
            turnLeft();

        }

        if(leftLineOuput == 1 && rightLineOuput == 1){
            if(previousLeft = 0 && previousRight == 1 ){
                turnRight();
//                drive_Forward();
                delay(615);

                if(leftLineOuput ==  0 && rightLineOuput == 0){
                    drive_Forward();

                }else{
                    turnRight();
                }
            }
            if(previousLeft = 1 && previousRight == 0 ){
                turnLeft();
//                drive_Forward();
                delay(615);
                if(leftLineOuput == 0 && rightLineOuput == 0){
                    turnLeft();
                }else{
                    turnLeft();
                }
                //turnLeft();

            }
        }



    }


    return 0;

}
