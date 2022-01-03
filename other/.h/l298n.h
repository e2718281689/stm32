#ifndef __l298n__
#define	__l298n__
#include "stm32f10x.h"

#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM_Period            1999
#define            GENERAL_TIM_Prescaler         719
// TIM3 输出通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_0
// TIM3 输出通道2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH2_PORT          GPIOA
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_1
// TIM3 输出通道3
#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH3_PORT          GPIOA
#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_2

// TIM3 输出通道4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH4_PORT          GPIOA
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_3



void Turn_Right(void);
void Turn_left(void);
void Stop_brake(void);
void fount(void);
void backward(void);
void l298n_init(void);
void l298n_out_in( u16 Compare1,u16 Compare2,u16 Compare3,u16 Compare4);
#endif /*__l298n__*/

