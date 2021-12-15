# /**************************************************************
# * Class: CSC-615-01 Fall 2021
# * Name: Antonino Calabrese
# * Student ID: 920831285
# * Github ID: ringnino
# * Project: Assignment 3 Start your Motors
# *
# * File: Makefile
# *
# * Description: Makefile to run C program
# * Credit for makefile blueprint - Robert Bierman at SFSU
# **************************************************************/

ROOTNAME=MotorTest
CC=gcc
CFLAGS= -lwiringPi

$(ROOTNAME):
	$(CC) -o $(ROOTNAME) $(ROOTNAME).c PCA9685_1.c Motors.c  DEV_Config_1.c echoSensor.c -lm $(CFLAGS)


clean:
	rm $(ROOTNAME)

run: $(ROOTNAME)
	./$(ROOTNAME)
