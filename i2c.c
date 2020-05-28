#include "i2c.h"

void i2c_init(void){
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; //enable gpiob clock
RCC->APB1ENR|=RCC_APB1ENR_I2C1EN; //enable i2c1 clock
GPIOB->MODER|=0xA0000; //set pb8and9 to alternative function
GPIOB->AFR[1]|=0x44;
GPIOB->OTYPER|=GPIO_OTYPER_OT8|GPIO_OTYPER_OT9; //set pb8 and pb9 as open drain
I2C1->CR1=I2C_CR1_SWRST;
I2C1->CR1&=~I2C_CR1_SWRST;	
I2C1->CR2|=16;
I2C1->CCR=80; 
I2C1->TRISE=17; //output max rise 
I2C1->CR1|=I2C_CR1_PE;
}

char i2c_readByte(char saddr,char maddr, char *data)
{

volatile int tmp;
while(I2C1->SR2&I2C_SR2_BUSY){;}
I2C1->CR1|=I2C_CR1_START;
while(!(I2C1->SR1&I2C_SR1_SB)){;}
I2C1->DR=saddr<<1;
while(!(I2C1->SR1&I2C_SR1_ADDR)){;}
tmp=I2C1->SR2;
while(!(I2C1->SR1&I2C_SR1_TXE)){;}
I2C1->DR=maddr;
while(!(I2C1->SR1&I2C_SR1_TXE)){;}
I2C1->CR1|=I2C_CR1_START;
while(!(I2C1->SR1&I2C_SR1_SB)){;}	
I2C1->DR=saddr<<1|1;
while(!(I2C1->SR1&I2C_SR1_ADDR)){;}
I2C1->CR1&=~I2C_CR1_ACK;
tmp =I2C1->SR2;
I2C1->CR1|=I2C_CR1_STOP;
while(!(I2C1->SR1&I2C_SR1_RXNE)){;}
*data++=I2C1->DR;
return 0;
}

void i2c_writeByte(char saddr,char maddr,char data){

while (I2C1->SR2 & 2);                               //wait until bus not busy
I2C1->CR1 |= 0x100;                                 //generate start
while (!(I2C1->SR1 & 1)){;}
	
	volatile int Temp;
I2C1->DR = saddr<< 1;                 	 // Send slave address
while (!(I2C1->SR1 & 2)){;}                            //wait until address flag is set
Temp = I2C1->SR2; 
	
while (!(I2C1->SR1 & 0x80));                          //Wait until Data register empty
I2C1->DR = maddr;                      // send memory address
while (!(I2C1->SR1 & 0x80));                         //wait until data register empty
I2C1->DR = data; 	
while (!(I2C1->SR1 & 4));                             //wait until transfer finished
I2C1->CR1 |= 0x200;
}

void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length){

	
	while (I2C1->SR2 & 2);                               //wait until bus not busy
I2C1->CR1 |= 0x100;                                 //generate start
while (!(I2C1->SR1 & 1)){;}
	
	volatile int Temp;
I2C1->DR = saddr<< 1;                 	 // Send slave address
while (!(I2C1->SR1 & 2)){;}                            //wait until address flag is set
Temp = I2C1->SR2; 
	
while (!(I2C1->SR1 & 0x80));                          //Wait until Data register empty
I2C1->DR = maddr;                      // send memory address
while (!(I2C1->SR1 & 0x80));                         //wait until data register empty

for (uint8_t i=0;i<length;i++)
 { 
 I2C1->DR=buffer[i]; //filling buffer with command or data
	while (!(I2C1->SR1 & 4));
 }	
                             //wait until transfer finished
I2C1->CR1 |= 0x200;

}