Created on 02/04/2018 by James Kugler

The code present here is to be used to communicate between an ADXL345 accelerometer, raspberry pi, and an atomic clock via I2C
ADXL345 accelerometer data sheet used to create class: http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf

SUMMARY:
	1) i2cdev.c++: base class to open, modify, read, and write to an i2c device
	2) accelerometer.c++: subclass to open up a connection to the ADXL345 accelerometer and display the X, Y, and Z register values
	3) i2c_test.c++: test file to test i2c class functionality
	4) accel_test.c++: test file to test accelerometer class functionality
	
BUILD:
Use g++ on any Linux environment