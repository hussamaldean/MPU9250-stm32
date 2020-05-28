#include "LiquidCrystal.h"
#include "stm32f4xx.h"                  // Device header

unsigned int _displayfunction;
unsigned int _displaycontrol;
unsigned int _displaymode;
unsigned int _initialized;
unsigned int _numlines;
unsigned int _row_offsets[4];

void delay(int delayms);
void LCD_init(void);
void GPIO_init(void);
void display(void);
void lcd_com(unsigned char c);
void lcd_data(char c);
void setCursor(int a, int b);
void setRowOffsets(int row0, int row1, int row2, int row3);
void LCD_Disp( char *p);
void lcd_nibble_write(char data, unsigned char control);


void LCD_init(void)
{
GPIO_init();
lcd_com(0x01);
delay(1);
lcd_com(0x02);
delay(1);
lcd_com(0x28);
delay(4);
lcd_com(0x06);
delay(1);
lcd_com(0x0c);
delay(1);
lcd_com(0x80);
delay(4);
}
//initialize the gpio pins for the lcd
void GPIO_init(void){
RCC->AHB1ENR=RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_GPIOCEN;
GPIOB->MODER|=GPIO_MODER_MODER5_0|GPIO_MODER_MODER7_0|GPIO_MODER_MODER0_0;
GPIOB->BSRR=(RS<<16)|(EN<<16);;
GPIOC->MODER|=GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0;
//GPIOB->OSPEEDR|=0x03;
}
void lcd_nibble_write(char data, unsigned char control)
{
GPIOC->BSRR|=0x00F00000; //clear data pins
GPIOC->BSRR=data&0xF0;
if(control &RS)
{
GPIOB->BSRR=RS;
}
else{GPIOB->BSRR=RS<<16;}

GPIOB->BSRR=EN;
delay(0);
GPIOB->BSRR=(EN<<16);
delay(0);
}


//lcd commands
void lcd_com(unsigned char c)
	{
lcd_nibble_write(c&0xF0,0); //upper data
lcd_nibble_write(c<<4,0); //lower data
if(c<4){delay(4);
}
else{delay(1);
}
}
// send command to the lcd
void lcd_data(char c)
	{
lcd_nibble_write(c&0xF0,RS);
lcd_nibble_write(c<<4,RS);
//delay(1);
}

void setCursor(int a, int b)
{
	int i=0;
	switch(b){
	case 0:lcd_com(0x80);break;
	case 1:lcd_com(0xC0);break;
	case 2:lcd_com(0x94);break;
	case 3:lcd_com(0xd4);break;}
	for(i=0;i<a;i++)
	lcd_com(0x14);
}
void LCD_Disp( char *p)
{
	while(*p!='\0')
	{
		lcd_data(*p);
		p++; delay(1);
	}
}
void lcd_clear(){
lcd_com(LCD_CLEARDISPLAY);
delay(3);
}

