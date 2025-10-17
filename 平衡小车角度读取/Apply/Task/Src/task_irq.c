#include "task_conf.h"
#include "usercode.h"
#include "config.h"


/**
 * @brief 外部中断5-9服务函数
 * @retval Null
*/
void EXTI9_5_IRQHandler(void)
{
    Drv_GPIO_EXTI_IRQHandler(&demoGPIO[4]);	/* 必须加，参数需修改 */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    Task_MPU6050_DataProcess(); // 8ms周期
}

/**
 * @brief 外部中断10-15服务函数
 * @retval Null
*/
void EXTI15_10_IRQHandler(void)
{
    //Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* 必须加，参数需修改 */
}

/**
 * @brief 串口1中断服务函数
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* 示例 */
    //Drv_Uart_IRQHandler(&tPCUart);		/* 必需部分 */
}

/**
 * @brief 串口2中断服务函数
 * @retval Null
*/
void USART2_IRQHandler(void)
{
	/* 示例 */
    //Drv_Uart_IRQHandler(&tJY901B.tUART);		/* 必需部分 */
}

/**
 * @brief 串口3中断服务函数
 * @retval Null
*/
void USART3_IRQHandler(void)
{

}

/**
 * @brief 串口4中断服务函数
 * @retval Null
*/
void UART4_IRQHandler(void)
{

}

/**
 * @brief 串口5中断服务函数
 * @retval Null
*/
void UART5_IRQHandler(void)
{

}

/**
 * @brief 定时器2中断服务函数
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
        // if (mpu6050_pending > 5)  // 防止过多堆积
        //     mpu6050_pending = 5;
    // }
    // Task_MPU6050_DataProcess(); // 8ms周期
}

/**
 * @brief 定时器3中断服务函数
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* 示例 */
    // Drv_Timer_IRQHandler(&tTimer3);
    // uint8_t cnt = 0;
    // while(cnt < mpu6050_pending)
    // {
    //     OCD_MPU6050_DataConversion(&tMPU6050,MPU6050_READ_INTERVAL_MS, cnt);
    //     // 减去初始角度偏移
    //     tMPU6050.stcAngle.ConRoll -= tMPU6050.stcFixAngle.FixRoll;
    //     tMPU6050.stcAngle.ConPitch -= tMPU6050.stcFixAngle.FixPitch;
    //     tMPU6050.stcAngle.ConYaw -= tMPU6050.stcFixAngle.FixYaw;
    //     cnt++;
    // }
    // mpu6050_pending = 0;
}

/**
 * @brief 定时器4中断服务函数
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* 示例 */
    //Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器5中断服务函数
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* 示例 */
    //Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器6中断服务函数
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* 示例 */
    //Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器7中断服务函数
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* 示例 */
    //Drv_Timer_IRQHandler(&demoTIM);
}



