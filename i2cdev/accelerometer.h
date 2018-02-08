#ifndef Accelerometer_H_
#define Accelerometer_H_
#include "i2cdev.h"

/**
 * @class accelerometer
 * @brief class to test the X, Y, and Z axis of ADXL345 accelerometer
 */

class accelerometer:public i2cdev{
	
	private:
		
		/// Full_Res_Bit and Range_Bit are used for Data_Format register:
		/// D7          D6    D5           D4  D3         D2        D1 D0
		/// SELF_TEST | SPI | INT_INVERT | 0 | FULL_RES | Justify | Range
		
		enum Full_Res_Bit{
			HIGH = 0x01,
			NORMAL = 0x00
		};
		enum Range_Bit{
			RANGE2 = 0x00,
			RANGE4 = 0x01,
			RANGE8 = 0x02,
			RANGE16 = 0x03
		};
		
		char data_form;
		short xAcceleration, yAcceleration, zAcceleration;
		
	public:
		
		accelerometer(int i2cBus, int i2cAddr);
		virtual int updateAccelerations();
		virtual short combineRegs(char reg0, char reg1);
		virtual void displayAccelerations(int seconds);

};
#endif