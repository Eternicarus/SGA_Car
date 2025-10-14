/* 
 * ����2���ж���������������
 * �޸� usercode.c
 */

#include "usercode.h"

uint16_t ID;
float Speed;
uint8_t ReceBuf[100];
uint8_t TempBuf[100];  // ��������ʱ������
uint8_t Num = 0;
volatile uint8_t NewDataFlag = 0;  // ���������ݾ�����־

/* �û��߼����� */
void UserLogic_Code(void)
{
	printf("hi\r\n");
	while(1)
	{
		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);

		// ����Ƿ��������ݣ�ʹ�ñ�־λ��������ѯ��
		if(NewDataFlag)
		{
			// �ر��жϣ���ֹ���ݱ�����
			__disable_irq();
			memcpy(ReceBuf, TempBuf, Num);
			uint8_t len = Num;
			NewDataFlag = 0;
			__enable_irq();
			
			// ���ͻ���
			Drv_Uart_Transmit_DMA(&demoUart, ReceBuf, len);
		}
	}
}

/*
 * �� task_irq.c �Ĵ����жϴ���������ӣ�
 * 
 * void USART1_IRQHandler(void)  // ����ʹ�õĴ��ں�
 * {
 *     Drv_Uart_DMA_RxHandler(&demoUart);
 *     
 *     // ������������ȡ����������
 *     uint16_t len = Drv_Uart_Receive_DMA(&demoUart, TempBuf);
 *     if(len > 0)
 *     {
 *         Num = len;
 *         NewDataFlag = 1;
 *     }
 * }
 */
