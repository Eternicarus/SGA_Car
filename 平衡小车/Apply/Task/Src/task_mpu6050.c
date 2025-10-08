#include "task_conf.h"
#include "usercode.h"
#include "config.h"

volatile uint8_t mpu6050_pending = 0;

void Task_MPU6050_Init(void)
{
    OCD_MPU6050_Init(&tMPU6050);
    Drv_Delay_Ms(100);
    
    if (!OCD_MPU6050_Init(&tMPU6050) == 0)
	{
 		uint8_t Num = OCD_MPU6050_Init(&tMPU6050);
		OCD_OLED_ShowString(&tOLED,0,0,"MPU6050 Err",16);
		OCD_OLED_ShowNum(&tOLED,0,2,Num,10,16);
		while(1);	
 	}
}

/**
 * @brief  MPU6050数据处理任务
 * @param  dt  时间间隔，单位秒
 */
void Task_MPU6050_DataProcess(void)
{
    while(mpu6050_pending)
    {
        mpu6050_pending--;
        OCD_MPU6050_GetData(&tMPU6050);
        OCD_MPU6050_DataConversion(&tMPU6050,MPU6050_READ_INTERVAL_MS);
    }
}

/**
 * @brief  MPU6050数据补偿
 * @param  无
 * @retval 无
 */
void Task_MPU6050_DataCompensation(void)
{
    // 数据补偿算法
    float gyro_x = tMPU6050.stcGyro.GyroX;
    float gyro_y = tMPU6050.stcGyro.GyroY;
    float gyro_z = tMPU6050.stcGyro.GyroZ;

    // 进行数据补偿
    
}
