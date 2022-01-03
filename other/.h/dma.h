#ifndef _dma_
#define _dma_
#include "stm32f10x.h"
// ÍâÉè¼Ä´æÆ÷µØÖ·
//#define  USART_DR_ADDRESS        (USART1_BASE+0x04)
void USARTx_DMA_Config(uint32_t PeripheralBase,uint32_t MemoryBase);
#endif /*_dma_*/


