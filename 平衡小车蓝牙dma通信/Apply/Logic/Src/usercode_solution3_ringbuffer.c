/* 
 * 方案3：环形缓冲区（Ring Buffer）
 * 适用于高频数据接收，不会丢失任何数据
 */

#include "usercode.h"
#include <string.h>

// 环形缓冲区配置
#define RING_BUFFER_SIZE 512
#define MAX_FRAME_SIZE 100

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    volatile uint16_t head;  // 写入位置
    volatile uint16_t tail;  // 读取位置
    volatile uint16_t count; // 当前数据量
} RingBuffer_t;

RingBuffer_t rxRingBuffer = {0};
uint8_t ReceBuf[MAX_FRAME_SIZE];

/* 环形缓冲区写入函数（在中断中调用） */
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
            // 缓冲区满，丢弃旧数据
            rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
            rb->buffer[rb->head] = data[i];
            rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
        }
    }
}

/* 环形缓冲区读取函数（在主循环中调用） */
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

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
    uint16_t rxLen;
    
    printf("Ring Buffer Mode Started\r\n");
    
    while(1)
    {
        OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);

        // 从环形缓冲区读取数据
        rxLen = RingBuffer_Read(&rxRingBuffer, ReceBuf, MAX_FRAME_SIZE);
        if(rxLen > 0)
        {
            // 处理接收到的数据
            Drv_Uart_Transmit_DMA(&demoUart, ReceBuf, rxLen);
        }
    }
}

/*
 * 在 task_irq.c 的串口中断处理函数中修改为：
 * 
 * void USART1_IRQHandler(void)
 * {
 *     uint8_t tempBuf[MAX_FRAME_SIZE];
 *     uint16_t len;
 *     
 *     Drv_Uart_DMA_RxHandler(&demoUart);
 *     
 *     // 读取数据并写入环形缓冲区
 *     len = Drv_Uart_Receive_DMA(&demoUart, tempBuf);
 *     if(len > 0)
 *     {
 *         RingBuffer_Write(&rxRingBuffer, tempBuf, len);
 *     }
 * }
 */

/* 查询环形缓冲区可用数据量 */
uint16_t RingBuffer_Available(RingBuffer_t *rb)
{
    return rb->count;
}

/* 清空环形缓冲区 */
void RingBuffer_Clear(RingBuffer_t *rb)
{
    __disable_irq();
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    __enable_irq();
}
