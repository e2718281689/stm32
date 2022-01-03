#include "bsp_time.h"
 uint32_t time;
static void BASIC_TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	 NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
static void BASIC_TIM_Mode_Config(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=999;
	TIM_TimeBaseStructure.TIM_Prescaler=71;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	//TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6,ENABLE);	
	
		
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = 150;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
void pwm_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  // ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH3_GPIO_CLK, ENABLE);
	
  RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH2_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
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
												TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
												// ����Ƚ�ͨ�� 1
												//TIM_OCInitStructure.TIM_Pulse = 180;
												TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	
								// ����ΪPWMģʽ2
								TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
								// ���ʹ��
								TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
								
								// ���ͨ����ƽ��������	
								TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
								// ����Ƚ�ͨ�� 1
								//TIM_OCInitStructure.TIM_Pulse = 180;
								TIM_OC2Init(GENERAL_TIM, &TIM_OCInitStructure);
	
						// ����ΪPWMģʽ3
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
					// ���ʹ��
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
					
					// ���ͨ����ƽ��������	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
					// ����Ƚ�ͨ�� 1
					//TIM_OCInitStructure.TIM_Pulse = 180;
					TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
	
				// ����ΪPWMģʽ4
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			// ���ʹ��
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			
			// ���ͨ����ƽ��������	
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
			// ����Ƚ�ͨ�� 1
			//TIM_OCInitStructure.TIM_Pulse = 180;
			TIM_OC4Init(GENERAL_TIM, &TIM_OCInitStructure);
	

	
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
			TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
				TIM_OC4PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
  TIM_Cmd(GENERAL_TIM, ENABLE);
	
}
void BASIC_TIM_Init(void)
{
	//BASIC_TIM_NVIC_Config();
	BASIC_TIM_Mode_Config();
}
void pwn_in( u16 Compare1,u16 Compare2,u16 Compare3,u16 Compare4)
{
	TIM_SetCompare1(GENERAL_TIM,Compare1);
	TIM_SetCompare1(GENERAL_TIM,Compare2);
	TIM_SetCompare1(GENERAL_TIM,Compare3);
	TIM_SetCompare1(GENERAL_TIM,Compare4);
}
void TIM6_IRQHandler()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update))
	{
		time++;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}



