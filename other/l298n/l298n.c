#include "l298n.h"
void l298n_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  // 输出比较通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE);
  GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH2_PIN;
	GPIO_Init(GENERAL_TIM_CH2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH3_PIN;
	GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH4_PIN;
	GPIO_Init(GENERAL_TIM_CH4_PORT, &GPIO_InitStructure);
	
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// 输出比较通道 1
	//TIM_OCInitStructure.TIM_Pulse = 180;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	TIM_OC4Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	// 使能计数器
  TIM_Cmd(GENERAL_TIM, ENABLE);
	
}
 void l298n_out_in( u16 Compare1,u16 Compare2,u16 Compare3,u16 Compare4)
{
	TIM_SetCompare1(GENERAL_TIM,Compare1);
	TIM_SetCompare2(GENERAL_TIM,Compare2);
	TIM_SetCompare3(GENERAL_TIM,Compare3);
	TIM_SetCompare4(GENERAL_TIM,Compare4);
}
void fount(void)
{
	l298n_out_in(300,0,300,0);
}
void backward(void)
{
	l298n_out_in(0,1998,0,1998);
}
void Turn_left(void)
{
	l298n_out_in(1000,0,300,0);
}
void Turn_Right(void)
{
	l298n_out_in(300,0,1000,0);
}
void Stop_brake(void)
{
	l298n_out_in(0,0,0,0);
}
