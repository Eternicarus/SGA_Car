#include "usercode.h"
#include "drv_hal_conf.h"
#include "task_conf.h"
#include "ocd_conf.h"
#include "dev_conf.h"
#include "algo_conf.h"
#include "config.h"

uint16_t ID;
float Speed;
uint8_t ReceBuf[100];
uint8_t SendBuf[10];
volatile uint8_t Num = 0;

extern volatile uint32_t irq_count;  // �ⲿ�жϼ���

void UserLogic_Code(void)
{
    static uint32_t last_irq = 0;  // ʹ�� static ȷ������ֵ
    
    printf("hi\r\n");
    while(1)
    {
        OCD_OLED_ShowFloatNum(&tOLED, 0, 2, tMPU6050.stcAngle.ConPitch, 16);

        // ����Ƿ���������
        if(Num != 0)
        {
            // ��¼��ǰ�жϴ���
            uint32_t current_irq = irq_count;
            memcpy(SendBuf, ReceBuf, Num);
            //�����������ʾ���ճ��Ⱥ��ж�����
             printf("Recv: %d bytes, IRQ_total: %lu, IRQ_delta: %lu\r\n", 
                    Num, current_irq, current_irq - last_irq);
            
            // ���ͻ�������
            Drv_Uart_Transmit_DMA(&demoUart, SendBuf, Num);
            
            // ���� last_irq
            last_irq = current_irq;
            Num = 0;  // �����־
        }
    }
}
