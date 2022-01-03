#ifndef _iic_h_
#define	_iic_h_
#include "stm32f10x.h"
#include "delay.h"
#include  <math.h> 

#define bool int
#define TRUE 1
#define FALSE 0
#define IIC_GPIOx GPIOB
#define IIC_PIN_SDA GPIO_Pin_6
#define IIC_PIN_SCL GPIO_Pin_7

/*模拟IIC端口输出输入定义*/
#define SCL_H         GPIOB->BSRR = GPIO_Pin_6
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

void delay5ms(void);
void I2C_NoAck(void);
void I2C_Ack(void);
void I2C_Stop(void);
bool I2C_Start(void);
 u8 I2C_RadeByte(void);
void I2C_NoAck(void);

#endif /*_iic_h_*/


