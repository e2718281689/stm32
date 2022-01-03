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
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC1->DR ) );
	
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������СΪ1���������Ĵ�СӦ�õ��ڴ洢���Ĵ�С
	DMA_InitStructure.DMA_BufferSize = 1;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	// ʹ�� DMA ͨ��
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
		// ��ȡADC��ת��ֵ
		ADC_ConvertedValue = ADC_GetConversionValue(ADC1);
	}
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
}

