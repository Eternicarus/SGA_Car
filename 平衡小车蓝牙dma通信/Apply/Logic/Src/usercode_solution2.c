/* 
 * 方案2：中断中立即复制数据
 * 修改 usercode.c
 */

#include "usercode.h"

uint16_t ID;
float Speed;
uint8_t ReceBuf[100];
uint8_t TempBuf[100];  // 新增：临时缓冲区
uint8_t Num = 0;
volatile uint8_t NewDataFlag = 0;  // 新增：数据就绪标志

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	printf("hi\r\n");
	while(1)
	{
		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);

		// 检查是否有新数据（使用标志位，避免轮询）
		if(NewDataFlag)
		{
			// 关闭中断，防止数据被覆盖
			__disable_irq();
			memcpy(ReceBuf, TempBuf, Num);
			uint8_t len = Num;
			NewDataFlag = 0;
			__enable_irq();
			
			// 发送回显
			Drv_Uart_Transmit_DMA(&demoUart, ReceBuf, len);
		}
	}
}

/*
 * 在 task_irq.c 的串口中断处理函数中添加：
 * 
 * void USART1_IRQHandler(void)  // 或您使用的串口号
 * {
 *     Drv_Uart_DMA_RxHandler(&demoUart);
 *     
 *     // 新增：立即读取并保存数据
 *     uint16_t len = Drv_Uart_Receive_DMA(&demoUart, TempBuf);
 *     if(len > 0)
 *     {
 *         Num = len;
 *         NewDataFlag = 1;
 *     }
 * }
 */
