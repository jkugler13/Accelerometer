#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2cdev.h"

using namespace std;

	/**
	 * Constructor class for i2c device.
	 * Opens and calls ioctl I2C_Slave
	 * @param b i2c bus number that determines what i2c file is in /dev.
	 * @param d i2c device on bus (in hex) 
	 */
	i2cdev::i2cdev(int b, int d){
		this->file = -1;
		this->bus = b;
		this->device = d;
		string i2c_name;
		if(this->bus == 0){
			i2c_name = "/dev/i2c-0";
		} else {
			i2c_name = "/dev/i2c-1";
		}
		if((this->file=open(i2c_name.c_str(), O_RDWR)) < 0){
			perror("Failed to open i2c device\n");
		}
		if(ioctl(this->file, I2C_SLAVE, this->device) < 0) {
			perror("Failed to connect to i2c device\n");
		}
	}

	/**
	 * Write a value to the i2c device. Used to read as well
	 * @param value to be written to the device
	 * @return return -1 for failure
	 */
	int i2cdev::i2cWrite(char value){
		char buf[1];
		if(write(this->file, buf, 1) != 1){
			perror("Failed to write to the device\n");
			return -1;
		}
		return 0;
	}

	/**
	 * Read value from register
	 * @param register address to read from (int hex)
	 * @return register value
	 */
	char i2cdev::i2cRead(int regAddr){
		this->i2cWrite(regAddr);
		char buf[1];
		if(read(this->file, buf, 1) != 1){
			perror("Failed to read the device\n");
			return -1;
		}
		return buf[0];
	}

	/**
	 * Function to write a value to a register address.
	 * @param regAddr register address to write to
	 * @value value to write to register
	 * @return return -1 on failure, 0 on success
	 */	
	int i2cdev::i2cWriteRegister(int regAddr, char value){
		char WriteBuffer[2];
		WriteBuffer[0] = regAddr;
		WriteBuffer[1] = value;
		if(write(this->file, WriteBuffer, 2) != 2){
			perror("Value was not written to Register!");
			return -1;
		}
		return 0;
	}
	
	/**
	 * Function to read multiple registers
	 * ADXL345 has the ability to read multiple registers and it is advised to do so in datasheet
	 * @param number total number of registers to read from
	 * @param addr slave device to read from
	 * @return return pointer to buffer of values, return NULL if failed to read
	 */
	char* i2cdev::i2cReadRegisters(int number, int addr){
		this->i2cWrite(addr);
		char* res = new char[number];
		if(read(this->file, res, number) != number){
			perror("Failed Reading from devices Registers!");
			return NULL;
		}
		return res;
	}
	
	/**
	 * Destructor for i2cdev class.
	 * Closes file descriptor and sets it to -1
	 */
	i2cdev::~i2cdev(){
		if(this->file != -1){
			close(this->file);
			this->file = -1;
		}
	}
