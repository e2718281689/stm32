#ifndef _tracker_
#define	_tracker_


#include "stm32f10x.h"
#include "delay.h"

#define    tracker_L_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    tracker_L_GPIO_PORT    GPIOA			   
#define    tracker_L_GPIO_PIN		 GPIO_Pin_4

#define    tracker_C_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    tracker_C_GPIO_PORT    GPIOA		   
#define    tracker_C_GPIO_PIN		  GPIO_Pin_5

#define    tracker_R_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    tracker_R_GPIO_PORT    GPIOA		   
#define    tracker_R_GPIO_PIN		 GPIO_Pin_6

#define    tracker_L   GPIO_ReadInputDataBit(tracker_L_GPIO_PORT,tracker_L_GPIO_PIN)
#define    tracker_C   GPIO_ReadInputDataBit(tracker_C_GPIO_PORT,tracker_C_GPIO_PIN)
#define    tracker_R   GPIO_ReadInputDataBit(tracker_R_GPIO_PORT,tracker_R_GPIO_PIN)
void tracker_GPIO_Config(void);
void AngleControl(void);
#endif /* _tracker_ */


