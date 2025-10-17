#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

uint16_t ID;
float Speed;
extern float acc_pitch;

/* �û��߼����� */
void UserLogic_Code(void)
{
//	ID = MPU6050_GetID(&tMPU6050);
//	OCD_OLED_ShowString(&tOLED,0,0,"MPU6050 ID:",16);
//	OCD_OLED_ShowNum(&tOLED,96,0,ID,3,16);
//	Drv_Delay_Ms(100);
	while(1)
	{
		// Task_MPU6050_DataProcess(); // 8ms����
		
//		OCD_OLED_PageClear(&tOLED,0);
		// OCD_OLED_ShowNum(&tOLED,0,0,mpu6050_pending,1,16);
		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcGyro.ConGyroX,16);
		OCD_OLED_ShowFloatNum(&tOLED,0,4,acc_pitch,16);
		OCD_OLED_ShowFloatNum(&tOLED,0,6,tMPU6050.stcAngle.ConPitch,16);
		// Speed = -Algo_PID_Calculate(&tPID_Balance,tMPU6050.stcAngle.ConPitch,0.0f);
		// OCD_OLED_ShowFloatNum(&tOLED,0,0,Speed,16);

		// if(Speed > 1.0f)
		// 	Motor_Forward();
		// else if(Speed < -1.0f)
		// 	Motor_Backward();
		// else
		// 	Motor_Stop();
		
		// if(Speed > 20.0f) Speed = 20.0f;
		// if(Speed < -20.0f) Speed = -20.0f;

		// OCD_OLED_ShowFloatNum(&tOLED,0,2,Speed,16);
		// Motor_SetSpeed(abs(Speed));

		// Drv_Delay_Ms(2);
	}
}
