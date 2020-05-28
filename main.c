#include "i2c.h"
#include "delay.h"
#include "MPU9250.h"
#include "LiquidCrystal.h"
double accx,accy,accz,gyrox,gyroy,gyroz,comx,comy,comz,dir;
char strax[8],stray[8],straz[8],strgx[8],strgy[4],strgz[8],strcx[8],strcy[8],strcz[8];
int main(void)
{
LCD_init();
delay(10);
i2c_init();
delay(100);

setCursor(0,0);
LCD_Disp("MPU9250 interface");
setCursor(0,1);
LCD_Disp("With STM32");
setCursor(0,2);
LCD_Disp("STM32 Developers");
delay(5000);	
lcd_clear();
delay(100);
	
MPU9250_beginAccel(ACC_FULL_SCALE_16_G);
MPU9250_beginGyro(GYRO_FULL_SCALE_2000_DPS);
MPU9250_beginMag(MAG_MODE_CONTINUOUS_100HZ);
	

delay(100);
	

while(1){
MPU9250_accelUpdate();
MPU9250_gyroUpdate();
MPU9250_magUpdate();
	

accx=MPU9250_accelX();
accy=MPU9250_accelY();
accz=MPU9250_accelZ();

gyrox=MPU9250_gyroX();
gyroy=MPU9250_gyroY();
gyroz=MPU9250_gyroZ();

	
comx=MPU9250_magX();	
comy=MPU9250_magY();	
comz=MPU9250_magZ();
dir=MPU9250_magHorizDirection();
	
sprintf(strax,"%.1f" ,accx);
sprintf(stray,"%.1f" ,accy);
sprintf(straz,"%.1f" ,accz);

sprintf(strgx,"%.1f" ,gyrox);
sprintf(strgy,"%.1f" ,gyroy);
sprintf(strgz,"%.1f" ,gyroz);

sprintf(strcx,"%.1f" ,comx);
sprintf(strcy,"%.1f" ,comy);
sprintf(strcz,"%.1f" ,comz);


setCursor(0,0); 	LCD_Disp("Se");
setCursor(4,0); 	LCD_Disp("X");
setCursor(10,0);	LCD_Disp("Y"); 
setCursor(16,0); 	LCD_Disp("Z");

setCursor(0,1); LCD_Disp("ac");
setCursor(3,1); LCD_Disp(strax);	LCD_Disp("  "); 
setCursor(9,1); LCD_Disp(stray);	LCD_Disp("  "); 
setCursor(16,1);LCD_Disp(straz);	LCD_Disp("  "); 

setCursor(0,2); LCD_Disp("gy"); 
setCursor(3,2); LCD_Disp(strgx); 	LCD_Disp("  "); 
setCursor(9,2); LCD_Disp(strgy);	LCD_Disp("  "); 
setCursor(16,2);LCD_Disp(strgz);	LCD_Disp("  "); 

setCursor(0,3); LCD_Disp("co");	
setCursor(3,3); LCD_Disp(strcx);  LCD_Disp("  "); 
setCursor(9,3); LCD_Disp(strcy);	LCD_Disp("  "); 
setCursor(16,3);LCD_Disp(strcz);	LCD_Disp("  "); 
delay(1);
}


}

