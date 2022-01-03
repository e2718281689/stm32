#include "bsp_A4988.h"
 void Step_DIR_Init()
 {
	 		/*¶¨ÒåÒ»¸öGPIO_InitTypeDefÀàÐÍµÄ½á¹¹Ìå*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*¿ªÆôLEDÏà¹ØµÄGPIOÍâÉèÊ±ÖÓ*/
		RCC_APB2PeriphClockCmd( dirPinx_Pin_CLK|dirPiny_Pin_CLK , ENABLE);
		/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOÒý½Å*/
		GPIO_InitStructure.GPIO_Pin = dirPinx_Pin;	

		/*ÉèÖÃÒý½ÅÄ£Ê½ÎªÍ¨ÓÃÍÆÍìÊä³ö*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*ÉèÖÃÒý½ÅËÙÂÊÎª50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*µ÷ÓÃ¿âº¯Êý£¬³õÊ¼»¯GPIO*/
		GPIO_Init(dirPinx_PORT, &GPIO_InitStructure);	
	 
	 
		/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOÒý½Å*/
		GPIO_InitStructure.GPIO_Pin = dirPiny_Pin;	

		/*ÉèÖÃÒý½ÅÄ£Ê½ÎªÍ¨ÓÃÍÆÍìÊä³ö*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*ÉèÖÃÒý½ÅËÙÂÊÎª50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*µ÷ÓÃ¿âº¯Êý£¬³õÊ¼»¯GPIO*/
		GPIO_Init(dirPiny_PORT, &GPIO_InitStructure);	
 }
void  Stepx_Pulse_Init(u16 arr,u16 psc)
{
	
	  GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	
	
  // ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(A4988_TIM_CH1_GPIO_CLK, ENABLE);
  RCC_APB1PeriphClockCmd(A4988_TIM_CLK,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = A4988_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(A4988_TIM_CH1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = A4988_TIM_CH2_PIN;
	GPIO_Init(A4988_TIM_CH2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = A4988_TIM_CH3_PIN;
	GPIO_Init(A4988_TIM_CH3_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = A4988_TIM_CH4_PIN;
	GPIO_Init(A4988_TIM_CH4_PORT, &GPIO_InitStructure);
	
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Period=arr;	
  //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_Prescaler=psc;	
	    //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	//TIM向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(A4988_TIM, &TIM_TimeBaseStructure);
	
	//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	//输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// ����Ƚ�ͨ�� 1
	//TIM_OCInitStructure.TIM_Pulse = 180;
	TIM_OC1Init(A4988_TIM, &TIM_OCInitStructure);
	//TIM_OC1PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	TIM_OC2Init(A4988_TIM, &TIM_OCInitStructure);
	//TIM_OC2PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	TIM_OC3Init(A4988_TIM, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	TIM_OC4Init(A4988_TIM, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	  TIM_CCxCmd(TIM2,TIM_Channel_1,TIM_CCx_Disable);//关闭TIM4通道1
    TIM_CCxCmd(TIM2,TIM_Channel_2,TIM_CCx_Disable);//关闭TIM4通道2
    TIM_CCxCmd(TIM2,TIM_Channel_3,TIM_CCx_Disable);//关闭TIM4通道3
    TIM_CCxCmd(TIM2,TIM_Channel_4,TIM_CCx_Disable);//关闭TIM4通道4
	//先不使能TIM4
  TIM_Cmd(A4988_TIM, DISABLE);
	
}

void  Stepy_Pulse_Init(u16 arr,u16 psc)
{
	
	  GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	
	
  // ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Period=arr;	
  //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_Prescaler=psc;	
	    //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	//TIM向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	//输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// ����Ƚ�ͨ�� 1
	//TIM_OCInitStructure.TIM_Pulse = 180;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	//TIM_OC1PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	//TIM_OC2PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(A4988_TIM, TIM_OCPreload_Enable);
	
	  TIM_CCxCmd(TIM3,TIM_Channel_1,TIM_CCx_Disable);//关闭TIM4通道1
    TIM_CCxCmd(TIM3,TIM_Channel_2,TIM_CCx_Disable);//关闭TIM4通道2
    TIM_CCxCmd(TIM3,TIM_Channel_3,TIM_CCx_Disable);//关闭TIM4通道3
    TIM_CCxCmd(TIM3,TIM_Channel_4,TIM_CCx_Disable);//关闭TIM4通道4
	//先不使能TIM4
  TIM_Cmd(TIM3, DISABLE);
	
}
void Mstepx_move(u8 dir,u16 frequency)
{
	 // MDIR = dir;     
	if(dir==1)
	{
		dirPinx_1;
	}
	else if(dir==0)
	{
		dirPinx_0;
	}
    Stepx_Pulse_Init((u16)(100000/frequency-1),719);
    TIM_SetCompare1(TIM2,(u16)(50000/frequency));
   	TIM_CCxCmd(TIM2,TIM_Channel_1,TIM_CCx_Enable);//开启TIM2通道4
    TIM_Cmd(TIM2, ENABLE);//必须放在最后使能
}

void Mstepy_move(u8 dir,u16 frequency)
{
	 // MDIR = dir;     
	if(dir==1)
	{
		dirPiny_1;
	}
	else if(dir==0)
	{
		dirPiny_0;
	}
    Stepy_Pulse_Init((u16)(100000/frequency-1),719);
    TIM_SetCompare1(TIM3,(u16)(50000/frequency));
   	TIM_CCxCmd(TIM3,TIM_Channel_1,TIM_CCx_Enable);//开启TIM2通道4
    TIM_Cmd(TIM3, ENABLE);//必须放在最后使能
}




