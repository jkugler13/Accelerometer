#include "accelerometer.h"
#include <iostream>

/**
 * Test file to test functionality of accelerometer class
 */

 using namespace std;

 int main(){
	
	accelerometer accel2(1, 0x53); // Construct the accelerometer class which calls i2cdev class to open and control ADXL345
	accel2.displayAccelerations(5); // Display the X, Y, and Z axis register values for 5 seconds
	
	return 0;
 }