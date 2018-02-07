Created on 02/04/2018 by James Kugler

The code present here is to be used to communicate between an ADXL345 accelerometer, raspberry pi, and an atomic clock via I2C
ADXL345 accelerometer data sheet used to create class: http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf

SUMMARY:
	1) i2cdev.c++: class to open, modify, read, and write to ADXL345
	
BUILD:
Use g++ on any Linux environment