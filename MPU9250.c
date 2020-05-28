#include <math.h>
#include "MPU9250.h"
double accelRange,gyroRange;
uint8_t magBuf[7], magXAdjust, magYAdjust, magZAdjust;
char accelBuf[6],gyroBuf[6];
uint8_t magBuf[7];
int i;
int16_t magXOffset, magYOffset, magZOffset;
//start Accelerometer
void MPU9250_beginAccel(uint8_t mode) {
  switch(mode) {
  case ACC_FULL_SCALE_2_G:
    accelRange = 2.0;
    break;
  case ACC_FULL_SCALE_4_G:
    accelRange = 4.0;
    break;
  case ACC_FULL_SCALE_8_G:
    accelRange = 8.0;
    break;
  case ACC_FULL_SCALE_16_G:
    accelRange = 16.0;
    break;
  default:
    return; // Return without writing invalid mode
  }
  i2c_writeByte(address, MPU9250_ADDR_ACCELCONFIG, mode);
	delay(10);
}

//start gyroscope
void MPU9250_beginGyro(uint8_t mode) {
  
  switch (mode) {
  case GYRO_FULL_SCALE_250_DPS:
    gyroRange = 250.0;
    break;
  case GYRO_FULL_SCALE_500_DPS:
    gyroRange = 500.0;
    break;
  case GYRO_FULL_SCALE_1000_DPS:
    gyroRange = 1000.0;
    break;
  case GYRO_FULL_SCALE_2000_DPS:
    gyroRange = 2000.0;
    break;
  default:
    return; // Return without writing invalid mode
  }
  i2c_writeByte(address, 27, mode);
	delay(10);
}

//start compass




uint8_t MPU9250_accelUpdate(void) {
	i2c_readByte(address,0x3B,&accelBuf[0]);
	i2c_readByte(address,0x3C,&accelBuf[1]);
	i2c_readByte(address,0x3D,&accelBuf[2]);
	i2c_readByte(address,0x3E,&accelBuf[3]);
	i2c_readByte(address,0x3F,&accelBuf[4]);
	i2c_readByte(address,0x40,&accelBuf[5]);	
	return 0;
 
}

float MPU9250_accelGet(uint8_t highIndex, uint8_t lowIndex) {
  int16_t v = ((int16_t) accelBuf[highIndex]) << 8 | accelBuf[lowIndex];
  return ((float) -v) * accelRange / (float) 0x8000; // (float) 0x8000 == 32768.0
}

float MPU9250_accelSqrt(void) {
  return sqrt(pow(MPU9250_accelGet(0, 1), 2) +
              pow(MPU9250_accelGet(2, 3), 2) +
              pow(MPU9250_accelGet(4, 5), 2));
}

float MPU9250_accelX(void) {
  return MPU9250_accelGet(0, 1);
}

float MPU9250_accelY(void) {
  return MPU9250_accelGet(2, 3);
}

float MPU9250_accelZ(void) {
  return MPU9250_accelGet(4, 5);
}


uint8_t MPU9250_gyroUpdate(void) {
	
	i2c_readByte(address,0x43,&gyroBuf[0]);
	i2c_readByte(address,0x44,&gyroBuf[1]);
	i2c_readByte(address,0x45,&gyroBuf[2]);
	i2c_readByte(address,0x46,&gyroBuf[3]);
	i2c_readByte(address,0x47,&gyroBuf[4]);
	i2c_readByte(address,0x48,&gyroBuf[5]);
  return 0;
}

float MPU9250_gyroGet(uint8_t highIndex, uint8_t lowIndex) {
  int16_t v = ((int16_t) gyroBuf[highIndex]) << 8 | gyroBuf[lowIndex];
  return ((float) -v) * gyroRange / (float) 0x8000;
}

float MPU9250_gyroX(void) {
  return MPU9250_gyroGet(0, 1);
}

float MPU9250_gyroY(void) {
  return MPU9250_gyroGet(2, 3);
}

float MPU9250_gyroZ(void) {
  return MPU9250_gyroGet(4, 5);
}


//compass section 
int16_t MPU9250_magGet(uint8_t highIndex, uint8_t lowIndex) {
  return (((int16_t) magBuf[highIndex]) << 8) | magBuf[lowIndex];
}


void magSetMode(uint8_t mode) {
  i2c_writeByte(AK8963_ADDRESS, AK8963_RA_CNTL1, mode);
  delay(10);
}

void magReadAdjustValues(void) {
  magSetMode(MAG_MODE_POWERDOWN);
  magSetMode(MAG_MODE_FUSEROM);
  char buff[3];
	i2c_readByte(AK8963_ADDRESS,0x10,&buff[0]);
	i2c_readByte(AK8963_ADDRESS,0x11,&buff[1]);
	i2c_readByte(AK8963_ADDRESS,0x12,&buff[2]);
  magXAdjust = buff[0];
  magYAdjust = buff[1];
  magZAdjust = buff[2];
}



void magWakeup(void) {
   char bits;
  i2c_readByte(address, MPU9250_ADDR_PWR_MGMT_1, &bits);
  bits &= ~0b01110000; // Turn off SLEEP, STANDBY, CYCLE
  i2c_writeByte(address, MPU9250_ADDR_PWR_MGMT_1, bits);
  delay(10);
}

void magEnableSlaveMode(void) {
   char bits;
	
  i2c_readByte(address, MPU9250_ADDR_INT_PIN_CFG, &bits);
  bits |= 0b00000010; // Activate BYPASS_EN
  i2c_writeByte(address, MPU9250_ADDR_INT_PIN_CFG, bits);
  delay(10);
}

float adjustMagValue(int16_t value, uint8_t adjust) {
  return ((float) value * (((((float) adjust - 128) * 0.5) / 128) + 1));
}

float MPU9250_magX(void) {
  return adjustMagValue(MPU9250_magGet(1, 0), magXAdjust) + magXOffset;
}

float MPU9250_magY(void) {
  return adjustMagValue(MPU9250_magGet(3, 2), magYAdjust) + magYOffset;
}

float MPU9250_magZ(void) {
  return adjustMagValue(MPU9250_magGet(5, 4), magZAdjust) + magZOffset;
}

float MPU9250_magHorizDirection(void) {
  return atan2(MPU9250_magX(), MPU9250_magY()) * 180 / Pi;
}

uint8_t MPU9250_magUpdate(void) {
	i2c_readByte(AK8963_ADDRESS,0x03,(char*)&magBuf[0]);
	i2c_readByte(AK8963_ADDRESS,0x04,(char*)&magBuf[1]);
	i2c_readByte(AK8963_ADDRESS,0x05,(char*)&magBuf[2]);
	i2c_readByte(AK8963_ADDRESS,0x06,(char*)&magBuf[3]);
	i2c_readByte(AK8963_ADDRESS,0x07,(char*)&magBuf[4]);
	i2c_readByte(AK8963_ADDRESS,0x08,(char*)&magBuf[5]);
	i2c_readByte(AK8963_ADDRESS,0x09,(char*)&magBuf[6]);
  return 0;
}

void MPU9250_beginMag(uint8_t mode) {
  
  magWakeup();
  magEnableSlaveMode();
  magReadAdjustValues();
  magSetMode(MAG_MODE_POWERDOWN);
  magSetMode(mode);
  delay(10);
}

