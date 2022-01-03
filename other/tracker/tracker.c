#include "tracker.h"
#include "l298n.h"

u8 xun_l;
u8 xun_r;
u8 xun_c;
void tracker_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(tracker_L_GPIO_CLK,ENABLE);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = tracker_L_GPIO_PIN; 
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(tracker_L_GPIO_PORT, &GPIO_InitStructure);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = tracker_C_GPIO_PIN; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(tracker_R_GPIO_PORT, &GPIO_InitStructure);	
	
		GPIO_InitStructure.GPIO_Pin = tracker_R_GPIO_PIN; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
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
	if(xun_l==0&&xun_c==1&&xun_r==0)//ֱ��
	{
		fount();
	}
	if(xun_l==0&&xun_c==1&&xun_r==1)//��ת
	{
		Turn_left();
	}
	if(xun_l==1&&xun_c==1&&xun_r==0)//��ת
	{
		Turn_Right();
	}
	if(xun_l==0&&xun_c==0&&xun_r==0)//ֱ��
	{
		Stop_brake();
	}
}

