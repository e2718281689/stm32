#ifndef _A4988_h
#define _A4988_h
#include "stm32f10x.h"
#include "delay.h"

#define						dirPinx_Pin_CLK         		 	RCC_APB2Periph_GPIOA
#define 					dirPinx_Pin   								GPIO_Pin_4
#define 					dirPinx_PORT  								GPIOA
#define 					dirPinx_0	   								GPIO_ResetBits(dirPinx_PORT, dirPinx_Pin)
#define						dirPinx_1	   								GPIO_SetBits(dirPinx_PORT, dirPinx_Pin)

#define						dirPiny_Pin_CLK         		 	RCC_APB2Periph_GPIOA
#define 					dirPiny_Pin   								GPIO_Pin_5
#define 					dirPiny_PORT  								GPIOA
#define 					dirPiny_0	   								GPIO_ResetBits(dirPiny_PORT, dirPiny_Pin)
#define						dirPiny_1	   								GPIO_SetBits(dirPiny_PORT, dirPiny_Pin)

#define           A4988_TIM                   TIM2
#define           A4988_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define           A4988_TIM_CLK               RCC_APB1Periph_TIM2
#define           A4988_TIM_Period            1999
#define           A4988_TIM_Prescaler         719
// TIM3 ���ͨ��1
#define           A4988_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define           A4988_TIM_CH1_PORT          GPIOA
#define           A4988_TIM_CH1_PIN           GPIO_Pin_0
// TIM3 ���ͨ��2
#define           A4988_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define           A4988_TIM_CH2_PORT          GPIOA
#define           A4988_TIM_CH2_PIN           GPIO_Pin_1
// TIM3 ���ͨ��3
#define           A4988_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOA
#define           A4988_TIM_CH3_PORT          GPIOA
#define           A4988_TIM_CH3_PIN           GPIO_Pin_2

// TIM3 ���ͨ��4
#define           A4988_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOA
#define           A4988_TIM_CH4_PORT          GPIOA
#define           A4988_TIM_CH4_PIN           GPIO_Pin_3
void Mstepy_move(u8 dir,u16 frequency);
void Mstepx_move(u8 dir,u16 frequency);
void Stepx_Pulse_Init(u16 arr,u16 psc);
void Stepy_Pulse_Init(u16 arr,u16 psc);
 void Step_DIR_Init(void);


#endif /*_A4988_h*/


