#include "i2cdev.h"
#include <iostream>

/**
 * Test file to test functionality of ADXL345 
 */

using namespace std;

int main(){
	i2cdev accel(1,0x53);
	accel.i2cWriteRegister(0x31, 0x09); // Write DATA_FORMAT Register with correct FULL_RES and Range bitset
	accel.i2cWriteRegister(0x2D, 0x08); // Turn POWER_CTL Register to "Measure" mode by writing 0x8 to register (Initially in Power Saving Mode)
	
	short accel_X = accel.i2cRead(0x32); // Single Read of DATAX0 register
	cout << accel_X << endl; // Output DATAX0 to confirm register was read correctly
	
	char* reg = accel.i2cReadRegisters(0x40,0x00); // Read all registers on ADXL345
	short accel_Z = *(reg + 0x36); // Take DATAZ0 register information	
	cout << accel_Z << endl; // Output DATAZ0 to confirm register was read correctly
	
	return 0;
}