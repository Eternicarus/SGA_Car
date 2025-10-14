/* 
 * ����3�����λ�������Ring Buffer��
 * �����ڸ�Ƶ���ݽ��գ����ᶪʧ�κ�����
 */

#include "usercode.h"
#include <string.h>

// ���λ���������
#define RING_BUFFER_SIZE 512
#define MAX_FRAME_SIZE 100

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    volatile uint16_t head;  // д��λ��
    volatile uint16_t tail;  // ��ȡλ��
    volatile uint16_t count; // ��ǰ������
} RingBuffer_t;

RingBuffer_t rxRingBuffer = {0};
uint8_t ReceBuf[MAX_FRAME_SIZE];

/* ���λ�����д�뺯�������ж��е��ã� */
static void RingBuffer_Write(RingBuffer_t *rb, uint8_t *data, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        if(rb->count < RING_BUFFER_SIZE)
        {
            rb->buffer[rb->head] = data[i];
            rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
            rb->count++;
        }
        else
        {
            // ��������������������
            rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
            rb->buffer[rb->head] = data[i];
            rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
        }
    }
}

/* ���λ�������ȡ����������ѭ���е��ã� */
static uint16_t RingBuffer_Read(RingBuffer_t *rb, uint8_t *data, uint16_t maxLen)
{
    __disable_irq();
    uint16_t readLen = (rb->count < maxLen) ? rb->count : maxLen;
    
    for(uint16_t i = 0; i < readLen; i++)
    {
        data[i] = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
    }
    rb->count -= readLen;
    __enable_irq();
    
    return readLen;
}

/* �û��߼����� */
void UserLogic_Code(void)
{
    uint16_t rxLen;
    
    printf("Ring Buffer Mode Started\r\n");
    
    while(1)
    {
        OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);

        // �ӻ��λ�������ȡ����
        rxLen = RingBuffer_Read(&rxRingBuffer, ReceBuf, MAX_FRAME_SIZE);
        if(rxLen > 0)
        {
            // ������յ�������
            Drv_Uart_Transmit_DMA(&demoUart, ReceBuf, rxLen);
        }
    }
}

/*
 * �� task_irq.c �Ĵ����жϴ��������޸�Ϊ��
 * 
 * void USART1_IRQHandler(void)
 * {
 *     uint8_t tempBuf[MAX_FRAME_SIZE];
 *     uint16_t len;
 *     
 *     Drv_Uart_DMA_RxHandler(&demoUart);
 *     
 *     // ��ȡ���ݲ�д�뻷�λ�����
 *     len = Drv_Uart_Receive_DMA(&demoUart, tempBuf);
 *     if(len > 0)
 *     {
 *         RingBuffer_Write(&rxRingBuffer, tempBuf, len);
 *     }
 * }
 */

/* ��ѯ���λ��������������� */
uint16_t RingBuffer_Available(RingBuffer_t *rb)
{
    return rb->count;
}

/* ��ջ��λ����� */
void RingBuffer_Clear(RingBuffer_t *rb)
{
    __disable_irq();
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    __enable_irq();
}
