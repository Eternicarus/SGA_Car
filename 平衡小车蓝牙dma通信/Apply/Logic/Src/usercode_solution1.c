/* 
 * ˫���� DMA ���շ���
 * �� usercode.c ��ʹ��
 */

#include "usercode.h"

// ����˫������
#define RX_BUFFER_SIZE 100
uint8_t RxBuffer1[RX_BUFFER_SIZE];
uint8_t RxBuffer2[RX_BUFFER_SIZE];
uint8_t ProcessBuffer[RX_BUFFER_SIZE];

uint8_t currentBuffer = 0;  // 0=ʹ��Buffer1, 1=ʹ��Buffer2
uint16_t dataLength = 0;
volatile uint8_t dataReady = 0;

/* �û��߼����� - ˫����汾 */
void UserLogic_Code(void)
{
	printf("hi\r\n");
	
	while(1)
	{
		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);

		// ����Ƿ���������
		if(dataReady)
		{
			// ���������е�����
			Drv_Uart_Transmit_DMA(&demoUart, ProcessBuffer, dataLength);
			
			// �����־
			dataReady = 0;
		}
	}
}

/* 
 * �ڴ����жϴ������е��ã���Ҫ�޸� task_irq.c��
 * ���ԭ���� Drv_Uart_DMA_RxHandler(&demoUart);
 */
void Custom_UART_DMA_RxHandler(void)
{
	uint16_t rxLen;
	
	// ����ԭʼ������
	Drv_Uart_DMA_RxHandler(&demoUart);
	
	// ����������
	rxLen = Drv_Uart_Receive_DMA(&demoUart, currentBuffer ? RxBuffer2 : RxBuffer1);
	if(rxLen > 0)
	{
		// ���Ƶ������������������ݱ����ǣ�
		memcpy(ProcessBuffer, currentBuffer ? RxBuffer2 : RxBuffer1, rxLen);
		dataLength = rxLen;
		dataReady = 1;
		
		// �л�������
		currentBuffer = !currentBuffer;
	}
}
