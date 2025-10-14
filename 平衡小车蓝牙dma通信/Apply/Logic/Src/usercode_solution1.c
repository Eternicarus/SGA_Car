/* 
 * 双缓冲 DMA 接收方案
 * 在 usercode.c 中使用
 */

#include "usercode.h"

// 定义双缓冲区
#define RX_BUFFER_SIZE 100
uint8_t RxBuffer1[RX_BUFFER_SIZE];
uint8_t RxBuffer2[RX_BUFFER_SIZE];
uint8_t ProcessBuffer[RX_BUFFER_SIZE];

uint8_t currentBuffer = 0;  // 0=使用Buffer1, 1=使用Buffer2
uint16_t dataLength = 0;
volatile uint8_t dataReady = 0;

/* 用户逻辑代码 - 双缓冲版本 */
void UserLogic_Code(void)
{
	printf("hi\r\n");
	
	while(1)
	{
		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);

		// 检查是否有新数据
		if(dataReady)
		{
			// 处理缓冲区中的数据
			Drv_Uart_Transmit_DMA(&demoUart, ProcessBuffer, dataLength);
			
			// 清除标志
			dataReady = 0;
		}
	}
}

/* 
 * 在串口中断处理函数中调用（需要修改 task_irq.c）
 * 替代原来的 Drv_Uart_DMA_RxHandler(&demoUart);
 */
void Custom_UART_DMA_RxHandler(void)
{
	uint16_t rxLen;
	
	// 调用原始处理函数
	Drv_Uart_DMA_RxHandler(&demoUart);
	
	// 如果接收完成
	rxLen = Drv_Uart_Receive_DMA(&demoUart, currentBuffer ? RxBuffer2 : RxBuffer1);
	if(rxLen > 0)
	{
		// 复制到处理缓冲区（避免数据被覆盖）
		memcpy(ProcessBuffer, currentBuffer ? RxBuffer2 : RxBuffer1, rxLen);
		dataLength = rxLen;
		dataReady = 1;
		
		// 切换缓冲区
		currentBuffer = !currentBuffer;
	}
}
