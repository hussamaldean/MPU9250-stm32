//interface hitachi lcd with STM32F407VETx using bare metal with 4-bit mode
//PC4 through PC7 for 4-bit data line

//PB5 as RS pin
//PB6 as RW pin
//PB7 as enable pin
//-----------------------


#ifndef __LiquidCrystal__h
#define __LiquidCrystal__h
#include "stdio.h"
#include "delay.h"

#define RS 0x20
#define RW 0x40
#define EN 0x80

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00



void delay(int delay);
void LCD_init(void);
//void GPIO_init(void);
//void display(void);
//void lcd_com(unsigned char c);
//void lcd_data(char c);
void setCursor(int a, int b);
//void setRowOffsets(int row0, int row1, int row2, int row3);
void LCD_Disp( char *p);
//void lcd_nipple_write(char data, unsigned char control);
void lcd_clear();


#endif

