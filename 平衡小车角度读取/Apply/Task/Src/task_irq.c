#include "task_conf.h"
#include "usercode.h"
#include "config.h"


/**
 * @brief �ⲿ�ж�5-9������
 * @retval Null
*/
void EXTI9_5_IRQHandler(void)
{
    Drv_GPIO_EXTI_IRQHandler(&demoGPIO[4]);	/* ����ӣ��������޸� */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    Task_MPU6050_DataProcess(); // 8ms����
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

/**
 * @brief ����3�жϷ�����
 * @retval Null
*/
void USART3_IRQHandler(void)
{

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
    // Drv_Timer_IRQHandler(&tTimer2);
    // if (++mpu6050_pending <= 5)
    //     OCD_MPU6050_GetData(&tMPU6050, mpu6050_pending);
    // {
    //     count = 0;
        // mpu6050_pending++;
        // if (mpu6050_pending > 5)  // ��ֹ����ѻ�
        //     mpu6050_pending = 5;
    // }
    // Task_MPU6050_DataProcess(); // 8ms����
}

/**
 * @brief ��ʱ��3�жϷ�����
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* ʾ�� */
    // Drv_Timer_IRQHandler(&tTimer3);
    // uint8_t cnt = 0;
    // while(cnt < mpu6050_pending)
    // {
    //     OCD_MPU6050_DataConversion(&tMPU6050,MPU6050_READ_INTERVAL_MS, cnt);
    //     // ��ȥ��ʼ�Ƕ�ƫ��
    //     tMPU6050.stcAngle.ConRoll -= tMPU6050.stcFixAngle.FixRoll;
    //     tMPU6050.stcAngle.ConPitch -= tMPU6050.stcFixAngle.FixPitch;
    //     tMPU6050.stcAngle.ConYaw -= tMPU6050.stcFixAngle.FixYaw;
    //     cnt++;
    // }
    // mpu6050_pending = 0;
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



