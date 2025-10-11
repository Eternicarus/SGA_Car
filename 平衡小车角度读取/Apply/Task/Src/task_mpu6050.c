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
    
    // 初始化互补滤波角度为当前角度
    OCD_MPU6050_GetData(&tMPU6050, 0);
    OCD_MPU6050_DataConversion(&tMPU6050, MPU6050_READ_INTERVAL_MS, 0);
    tMPU6050.stcFixAngle.FixRoll = tMPU6050.stcAngle.ConRoll;
    tMPU6050.stcFixAngle.FixPitch = tMPU6050.stcAngle.ConPitch;
    tMPU6050.stcFixAngle.FixYaw = tMPU6050.stcAngle.ConYaw;

}

/**
 * @brief  MPU6050数据处理任务
 * @param  dt  时间间隔，单位秒
 * @retval 无
 */
// void Task_MPU6050_DataProcess(void)
// {
//     OCD_MPU6050_GetData(&tMPU6050);
//     OCD_MPU6050_DataConversion(&tMPU6050,MPU6050_READ_INTERVAL_MS);
//     // 减去初始角度偏移
//     tMPU6050.stcAngle.ConRoll -= tMPU6050.stcFixAngle.FixRoll;
//     tMPU6050.stcAngle.ConPitch -= tMPU6050.stcFixAngle.FixPitch;
//     tMPU6050.stcAngle.ConYaw -= tMPU6050.stcFixAngle.FixYaw;
// }

