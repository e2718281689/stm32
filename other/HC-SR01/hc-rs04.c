#include "hc-rs04.h"

u8 overcount=0;
void SG90()
{
	  GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  // ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(hc_rs04_TIM_CH1_GPIO_CLK, ENABLE);
  hc_rs04_TIM_APBxClock_FUN(hc_rs04_TIM_CLK,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  hc_rs04_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(hc_rs04_TIM_CH1_PORT, &GPIO_InitStructure);
	

	
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=hc_rs04_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= hc_rs04_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(hc_rs04_TIM, &TIM_TimeBaseStructure);
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// ����Ƚ�ͨ�� 1
	//TIM_OCInitStructure.TIM_Pulse = 180;
	TIM_OC1Init(hc_rs04_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(hc_rs04_TIM, TIM_OCPreload_Enable);
	

	
	// ʹ�ܼ�����
  TIM_Cmd(hc_rs04_TIM, ENABLE);
}
void SG90_vec(u16 vec)
{
	TIM_SetCompare1(hc_rs04_TIM,vec);
}
void hc_rs04_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_Period=999;
	TIM_TimeBaseStructure.TIM_Prescaler=71;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM3, DISABLE);
}


float Senor_Using(void) 
{
	float lengh=0;
	u16 tim;
	 
  TRIG_Send(1);
	delay_us(20);
	TRIG_Send(0);
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==RESET);
	TIM_Cmd(TIM3,ENABLE);
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==SET);
	TIM_Cmd(TIM3,DISABLE);
	tim=TIM_GetCounter(TIM3);
	lengh=(tim+overcount*1000)/58.0;
	TIM3->CNT=0;
	overcount=0;
	return lengh;
}
void TIM3_IRQHandler(void)
{
 if (TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) 
 {
 TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); 
 overcount++;
 }
}
