#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define LED1_GPIO_PORT    	GPIOA		              /* GPIO�˿� */
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LED1_GPIO_PIN			GPIO_Pin_2			        

void LED_GPIO_Config(void);
	
#define LED_G_TOGGLE 	{LED1_GPIO_PORT->ODR^=LED1_GPIO_PIN	;}

#endif /* __LED_H */


