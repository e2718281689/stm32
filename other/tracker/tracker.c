#include "tracker.h"
#include "l298n.h"

u8 xun_l;
u8 xun_r;
u8 xun_c;
void tracker_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(tracker_L_GPIO_CLK,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = tracker_L_GPIO_PIN; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(tracker_L_GPIO_PORT, &GPIO_InitStructure);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = tracker_C_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(tracker_R_GPIO_PORT, &GPIO_InitStructure);	
	
		GPIO_InitStructure.GPIO_Pin = tracker_R_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(tracker_C_GPIO_PORT, &GPIO_InitStructure);	
}
//void SysTick_Handler(void)
//{
//	AngleControl();
//}
void AngleControl(void)
{
	 xun_l=tracker_L;
 xun_r=tracker_R;
 xun_c=tracker_C;
	if(xun_l==0&&xun_c==1&&xun_r==0)//直行
	{
		fount();
	}
	if(xun_l==0&&xun_c==1&&xun_r==1)//左转
	{
		Turn_left();
	}
	if(xun_l==1&&xun_c==1&&xun_r==0)//右转
	{
		Turn_Right();
	}
	if(xun_l==0&&xun_c==0&&xun_r==0)//直行
	{
		Stop_brake();
	}
}

