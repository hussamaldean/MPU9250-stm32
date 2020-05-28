#ifndef __MPU9250__H__
#define __MPU9250__H__

#include "i2c.h"
#include "stdint.h"


#define Pi 3.14159
#define MPU9250_ADDRESS_AD0_LOW  0x68
#define MPU9250_ADDRESS_AD0_HIGH 0x69

#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18

#define GYRO_FULL_SCALE_250_DPS  0x00
#define GYRO_FULL_SCALE_500_DPS  0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define MAG_MODE_POWERDOWN        0x0
#define MAG_MODE_SINGLE           0x1
#define MAG_MODE_CONTINUOUS_8HZ   0x2
#define MAG_MODE_EXTERNAL         0x4
#define MAG_MODE_CONTINUOUS_100HZ 0x6
#define MAG_MODE_SELFTEST         0x8
#define MAG_MODE_FUSEROM          0xF
#define AK8963_ADDRESS  0x0C
#define AK8963_RA_HXL   0x03
#define AK8963_RA_CNTL1 0x0A
#define AK8963_RA_ASAX  0x10

#define MPU9250_ADDR_ACCELCONFIG  0x1C
#define MPU9250_ADDR_INT_PIN_CFG  0x37
#define MPU9250_ADDR_ACCEL_XOUT_H 0x3B
#define MPU9250_ADDR_GYRO_XOUT_H  0x43
#define MPU9250_ADDR_PWR_MGMT_1   0x6B
#define MPU9250_ADDR_WHOAMI       0x75
#define address 0x68
//accelerartion part 
void MPU9250_beginAccel(uint8_t mode);
float MPU9250_accelX(void);
float MPU9250_accelY(void);
float MPU9250_accelZ(void);
uint8_t MPU9250_accelUpdate(void);


//gyro part
void MPU9250_beginGyro(uint8_t mode);
uint8_t MPU9250_gyroUpdate(void);
float MPU9250_gyroX(void);
float MPU9250_gyroY(void);
float MPU9250_gyroZ(void);

//compass part 
void MPU9250_beginMag(uint8_t mode);
uint8_t MPU9250_magUpdate(void);
float MPU9250_magX(void);
float MPU9250_magY(void);
float MPU9250_magZ(void);
float MPU9250_magHorizDirection(void);

#endif

