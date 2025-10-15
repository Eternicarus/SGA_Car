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

extern volatile uint32_t irq_count;  // 外部中断计数

void UserLogic_Code(void)
{
    static uint32_t last_irq = 0;  // 使用 static 确保保留值
    
    printf("hi\r\n");
    while(1)
    {
        OCD_OLED_ShowFloatNum(&tOLED, 0, 2, tMPU6050.stcAngle.ConPitch, 16);

        // 检测是否有新数据
        if(Num != 0)
        {
            // 记录当前中断次数
            uint32_t current_irq = irq_count;
            memcpy(SendBuf, ReceBuf, Num);
            //调试输出：显示接收长度和中断增量
             printf("Recv: %d bytes, IRQ_total: %lu, IRQ_delta: %lu\r\n", 
                    Num, current_irq, current_irq - last_irq);
            
            // 发送回显数据
            Drv_Uart_Transmit_DMA(&demoUart, SendBuf, Num);
            
            // 更新 last_irq
            last_irq = current_irq;
            Num = 0;  // 清除标志
        }
    }
}
