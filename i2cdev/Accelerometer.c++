/*
 * accelerometer.c++: created on 02/08/2018
 *
 * Flow of operation:
 *  1) Write DATA_FORMAT Register with correct FULL_RES and Range bitset
 * 	2) Turn POWER_CTL Register to "Measure" mode by writing 0x8 to register (Initially in Power Saving Mode)
 *	3) Read from acceleration registers 
 */

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "accelerometer.h"
 
 //Registers present on ADXL345
 #define DEVID 			0x00
 #define THRESH_TAP 	0x1D
 #define OFSX			0x1E
 #define OFSY			0x1F
 #define OFSZ			0x20
 #define DUR			0x21
 #define Latent			0x22
 #define Window			0x23
 #define THRESH_ACT		0x24
 #define THRESH_INACT	0x25
 #define TIME_INACT		0x26
 #define ACT_INACT_CTL	0x27
 #define THRESH_FF		0x28
 #define TIME_FF		0x29
 #define TAP_AXES		0x2A
 #define ACT_TAP_STATUS	0x2B
 #define BW_RATE		0x2C
 #define POWER_CTL		0x2D
 #define INT_ENABLE		0x2E
 #define INT_MAP		0x2F
 #define INT_SOURCE		0x30
 #define DATA_FORMAT	0x31
 #define DATAX0			0x32
 #define DATAX1			0x33
 #define DATAY0			0x34
 #define DATAY1			0x35
 #define DATAZ0			0x36
 #define DATAZ1			0x37
 #define FIFO_CTL		0x38
 #define FIFO_STATUS	0x39
	
		/**
		 * Constructor for ADXL345 accelerometer that opens up i2cdev class to connects
		 * to the accelerometer.
		 * @param i2cBus bus number used to open up connection on i2cdev
		 * @param i2cAddr address number to open
		 */
		 
		accelerometer::accelerometer(int i2cBus, int i2cAddr):
			i2cdev(i2cBus, i2cAddr){
			this->data_form = (NORMAL << 3) | RANGE8;
			this->i2cWriteRegister(DATA_FORMAT, data_form); // Change data format register
			this->i2cWriteRegister(POWER_CTL, 0x08); // Turn on measure mode
			this->updateAccelerations();
			//this->displayAccelerations(5);
		}
		
		/**
		 * Function to update values of registers present on accelerometer class
		 * @return return 0 on pass, -1 on failure to update accelerometers
		 */
		 
		int accelerometer::updateAccelerations(){
			char* accelRegs = i2cReadRegisters(6, 0x32); // Reads only DATAX0, DATAX1, DATAY0, DATAY1, DATAZ0, and DATAZ1 registers
			if(accelRegs == NULL){
				perror("Unable to read acceleration registers");
				return -1;
			}
			this->xAcceleration = this->combineRegs(*accelRegs, *(accelRegs + 1));
			this->yAcceleration = this->combineRegs(*(accelRegs + 2), *(accelRegs + 3));
			this->zAcceleration = this->combineRegs(*(accelRegs + 4), *(accelRegs + 5));
			return 0;
		}
		
		/**
		 * Function to combine two registers
		 * @param reg0 LSB register
		 * @param reg1 MSB register
		 * @return return the combined reg0 and reg1 value
		 */
		 
		short accelerometer::combineRegs(char reg0, char reg1){
			return ((reg1 << 8) | reg0);
		}
		
		/**
		 * Function to display and update the X, Y, and Z axis
		 * @param seconds number of seconds to display the X, Y, and Z axis
		 */
		 
		void accelerometer::displayAccelerations(int seconds){
			int count = seconds;
			while(count > 0){
				cout << "Acceleration in X axis: " << this->xAcceleration << " ";
				cout << "Acceleration in Y axis: " << this->yAcceleration << " ";
				cout << "Acceleration in Z axis: " << this->zAcceleration << "     \r" << flush;
				sleep(1);
				this->updateAccelerations();
				count--;
			}
		}