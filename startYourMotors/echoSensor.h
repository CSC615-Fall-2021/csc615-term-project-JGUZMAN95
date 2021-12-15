#ifndef ECHOSENSOR_H
#define ECHOSENSOR_H
#define SPEED_OF_SOUND 34300 // 34300 cm/s

// ECHO SENSOR PINS
#define FRONT_TRIG 24
#define FRONT_ECHO 23
#define LEFT_TRIG 17
#define LEFT_ECHO 27


double frontEchoDistance();
double leftEchoDistance();


#endif
