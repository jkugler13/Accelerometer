/*
 * Created on 02/04/2018: i2cdev.harder
 * 
 * I2C header file used to open, read, and write to devices
 * connected to a raspberry pi via I2C.
 */

#ifndef i2cdev_H_
#define i2cdev_H_

using namespace std;

/** 
 * @class i2cdev
 * @brief class to connect, read, or write to i2c devices
 */
class i2cdev{
	
	private:
		
		int bus;
		int device;
		int file;
		
	public:
		
		i2cdev(int b, int d);
		virtual int i2cWrite(char val);
		virtual char i2cRead(int regAddr);
		virtual int i2cWriteRegister(int RegAddr, char value);
		virtual char* i2cReadRegisters(int number, int addr);
		virtual ~i2cdev();
		
};

#endif