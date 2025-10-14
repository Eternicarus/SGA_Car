#include "task_conf.h"
#include "usercode.h"
#include "config.h"


/**
 * @brief �ⲿ�ж�5-9������
 * @retval Null
*/
void EXTI9_5_IRQHandler(void)
{
    //Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* ����ӣ��������޸� */
}

/**
 * @brief �ⲿ�ж�10-15������
 * @retval Null
*/
void EXTI15_10_IRQHandler(void)
{
    //Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* ����ӣ��������޸� */
}

/**
 * @brief ����1�жϷ�����
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* ʾ�� */
    //Drv_Uart_IRQHandler(&tPCUart);		/* ���貿�� */
}

/**
 * @brief ����2�жϷ�����
 * @retval Null
*/
void USART2_IRQHandler(void)
{
	/* ʾ�� */
    //Drv_Uart_IRQHandler(&tJY901B.tUART);		/* ���貿�� */
}
volatile uint32_t irq_count = 0;  // �жϴ�������
/**
 * @brief ����3�жϷ�����
 * @retval Null
*/
void USART3_IRQHandler(void)
{
    uint16_t len;
    
    Drv_Uart_IRQHandler(&demoUart);
    Drv_Uart_DMA_RxHandler(&demoUart);
    
    irq_count++;  // ��¼�жϴ���
    
    // ������ȡ���ݣ����⸲��
    len = Drv_Uart_Receive_DMA(&demoUart, ReceBuf);
    if(len > 0)
    {
        Num = len;
    }
}

void DMA1_Channel2_IRQHandler(void)
{
    Drv_Uart_DMA_IRQHandler(&demoUart);
}

/* ���ڷ�����ɻص����� */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	Drv_Uart_DMA_TxHandler(&demoUart);
}

/**
 * @brief ����4�жϷ�����
 * @retval Null
*/
void UART4_IRQHandler(void)
{

}

/**
 * @brief ����5�жϷ�����
 * @retval Null
*/
void UART5_IRQHandler(void)
{

}

/**
 * @brief ��ʱ��2�жϷ�����
 * @retval Null
*/
void TIM2_IRQHandler(void)
{
    Drv_Timer_IRQHandler(&tTimer2);
    if (++mpu6050_pending <= 5)
       OCD_MPU6050_GetData(&tMPU6050, mpu6050_pending);
}

/**
 * @brief ��ʱ��3�жϷ�����
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* ʾ�� */
   Drv_Timer_IRQHandler(&tTimer3);
   if(mpu6050_pending)
   {
       OCD_MPU6050_DataConversion(&tMPU6050,MPU6050_READ_INTERVAL_MS, mpu6050_pending);
       // ��ȥ��ʼ�Ƕ�ƫ��
       tMPU6050.stcAngle.ConRoll -= tMPU6050.stcFixAngle.FixRoll;
       tMPU6050.stcAngle.ConPitch -= tMPU6050.stcFixAngle.FixPitch;
       tMPU6050.stcAngle.ConYaw -= tMPU6050.stcFixAngle.FixYaw;
       mpu6050_pending--;
   }
}

/**
 * @brief ��ʱ��4�жϷ�����
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* ʾ�� */
    //Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��5�жϷ�����
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* ʾ�� */
    //Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��6�жϷ�����
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* ʾ�� */
    //Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��7�жϷ�����
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* ʾ�� */
    //Drv_Timer_IRQHandler(&demoTIM);
}



