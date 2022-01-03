#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define LED1_GPIO_PORT    	GPIOA		              /* GPIO端口 */
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED1_GPIO_PIN			GPIO_Pin_2			        

void LED_GPIO_Config(void);
	
#define LED_G_TOGGLE 	{LED1_GPIO_PORT->ODR^=LED1_GPIO_PIN	;}

#endif /* __LED_H */


