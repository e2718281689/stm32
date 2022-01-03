#include "adc.h"
#include "dma.h"
 __IO uint16_t ADC_ConvertedValue;
 static void ADCx_GPIO_Config(void)
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	 
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
 }
 static void ADCx_Mode_Config(void)
 {
	 ADC_InitTypeDef  ADC_InitStructure;
	 DMA_InitTypeDef DMA_InitStructure;
	 
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	 
	 DMA_DeInit(DMA1_Channel1);
	
	// 配置 DMA 初始化结构体
	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC1->DR ) );
	
	// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	// 数据源来自外设
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// 缓冲区大小为1，缓冲区的大小应该等于存储器的大小
	DMA_InitStructure.DMA_BufferSize = 1;
	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// 存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// 外设数据大小为半字，即两个字节
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// 循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// 初始化DMA
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	// 使能 DMA 通道
	DMA_Cmd(DMA1_Channel1 , ENABLE);
	 
	 //USARTx_DMA_Config((uint32_t)(&( ADC1->DR )),(uint32_t)&ADC_ConvertedValue);
	 ADC_DeInit(ADC1);
	 ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	 ADC_InitStructure.ADC_ScanConvMode=DISABLE;
	 ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
	 ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	 ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	 ADC_InitStructure.ADC_NbrOfChannel=1;
	 ADC_Init(ADC1,&ADC_InitStructure);
	 
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	 ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_239Cycles5);
	// ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	 
	 ADC_DMACmd(ADC1, ENABLE);
	 	ADC_Cmd(ADC1, ENABLE);
		
   ADC_ResetCalibration(ADC1);
   while (ADC_GetResetCalibrationStatus(ADC1));
   ADC_StartCalibration(ADC1);
   while (ADC_GetCalibrationStatus(ADC1));
	 
	 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
 }

static void ADC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
	ADC_NVIC_Config();
}
void ADC1_2_IRQHandler(void)
{	
	if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET) 
	{
		// 读取ADC的转换值
		ADC_ConvertedValue = ADC_GetConversionValue(ADC1);
	}
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
}

