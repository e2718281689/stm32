#include "l298n.h"
void l298n_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  // ����Ƚ�ͨ��1 GPIO ��ʼ��
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
	
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// ����Ƚ�ͨ�� 1
	//TIM_OCInitStructure.TIM_Pulse = 180;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	TIM_OC4Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
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
