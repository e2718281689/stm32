#ifndef _ds18b20_
#define _ds18b20_

#include "stm32f10x.h"
/************************** DS18B20 连接引脚定义********************************/
#define      DS18B20_DQ_GPIO_PORT                      GPIOA
#define      DS18B20_DQ_GPIO_PIN                       GPIO_Pin_0

/************************** DS18B20 函数宏定义********************************/
#define      DS18B20_DQ(n)	                           (n)? GPIO_ResetBits ( DS18B20_DQ_GPIO_PORT, DS18B20_DQ_GPIO_PIN ): GPIO_SetBits ( DS18B20_DQ_GPIO_PORT, DS18B20_DQ_GPIO_PIN )                          

#define      DS18B20_DQ_IN()	                          GPIO_ReadInputDataBit ( DS18B20_DQ_GPIO_PORT, DS18B20_DQ_GPIO_PIN ) 




#endif /*_iic_h_*/


