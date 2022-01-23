#include "l298n.h"
#include "stm32f10x.h"
#include "iic.h"
#include "bsp_usart.h"
#include "delay.h"

#define MPU6050_SLAVE_ADDRESS  (0x68<<1)  
	u16 Accel[3];
	u8 awe[20];
	
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))	 //ȡ��int�ͱ����ĵ��ֽ�
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))	 //	ȡ�洢�ڴ˱�����һ�ڴ��ֽڵ����ݣ����ֽ�
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

/**
  * @brief   д���ݵ�MPU6050�Ĵ���
  * @param   
  * @retval  
  */
void i2c_WriteReg(u8 reg_add,u8 reg_dat)
{
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS);
	i2c_WaitAck();
	i2c_SendByte(reg_add);
	i2c_WaitAck();
	i2c_SendByte(reg_dat);
	i2c_WaitAck();
	i2c_Stop();
}


/**
  * @brief   ��MPU6050�Ĵ�����ȡ����
  * @param   
  * @retval  
  */
void i2c_ReadData(u8 reg_add,unsigned char*Read,u8 num)
{
	unsigned char i;
	
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS);
	i2c_WaitAck();
	i2c_SendByte(reg_add);
	i2c_WaitAck();
	
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS+1);
	i2c_WaitAck();
	
	for(i=0;i<(num-1);i++){
		*Read=i2c_ReadByte(1);
		Read++;
	}
	*Read=i2c_ReadByte(0);
	i2c_Stop();
}

void MPU6050ReadAcc(u16 *accData)
{
    u8 buf[6];
    i2c_ReadData(0x3B, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];

}
int main()
{
	USART_Config();
//	i2c_GPIO_Config();
	while(1)
	{
//		delay_ms(1);
//	i2c_WriteReg(0x6B, 0x00);	    //�������״̬
//	i2c_WriteReg(0x19 , 0x07);	    //�����ǲ����ʣ�1KHz
//	i2c_WriteReg(0x1A , 0x06);	        //��ͨ�˲��������ã���ֹƵ����1K��������5K
//	i2c_WriteReg(0x1C , 0x00);	  //���ü��ٶȴ�����������2Gģʽ�����Լ�
//	i2c_WriteReg(0x1B, 0x18);     //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)

		
		while(1)
		{
			
//MPU6050ReadAcc(Accel);
			u16 sss=0x4434;
			u16 yyy=0x4434;
			u8 zzz=0x23;
		u8 a=0;
		u8 sum=0;
		awe[sum++]=0xAA;
	  awe[sum++]=0xFF;
	  awe[sum++]=0xE1;
	  awe[sum++]=0x05;
	  awe[sum++]=BYTE0(sss);
		awe[sum++]=BYTE1(sss);	
	  awe[sum++]=BYTE0(yyy);
		awe[sum++]=BYTE1(yyy);
		awe[sum++]=zzz;
		u8 sumcheck=0,addcheck=0;
		for(a=0;a<awe[3]+4;a++)
		{
			sumcheck +=awe[a];
			addcheck +=sumcheck;
		}
		awe[sum++]=sumcheck;
		awe[sum++]=addcheck;
			for(int a=0;a<sum;a++)
			{
				Usart_SendByte(DEBUG_USARTx,awe[a]);
			}
			delay_ms(50);
		}
		
		
	}
}