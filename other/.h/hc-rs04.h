#ifndef _hc_rs04_
#define	_hc_rs04_

#include "stm32f10x.h"
#include "delay.h"

#define            hc_rs04_TIM                   TIM4
#define            hc_rs04_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            hc_rs04_TIM_CLK               RCC_APB1Periph_TIM4
#define            hc_rs04_TIM_Period            1999
#define            hc_rs04_TIM_Prescaler         719

// TIM3 输出通道1
#define            hc_rs04_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            hc_rs04_TIM_CH1_PORT          GPIOB
#define            hc_rs04_TIM_CH1_PIN           GPIO_Pin_6

 #define TRIG_Send(n) n?GPIO_SetBits(GPIOA,GPIO_Pin_4):GPIO_ResetBits(GPIOA,GPIO_Pin_4)
 #define ECHO_Reci(n) n?GPIO_SetBits(GPIOA,GPIO_Pin_5):GPIO_ResetBits(GPIOA,GPIO_Pin_5)
 
void hc_rs04_Init(void);
 float Senor_Using(void) ;
 void SG90(void);
 void SG90_vec(u16 vec);
#endif /* _hc_rs04_ */

//使用定时器三

