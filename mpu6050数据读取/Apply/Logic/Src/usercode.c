#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

uint16_t ID;

/* �û��߼����� */
void UserLogic_Code(void)
{
	ID = MPU6050_GetID(&tMPU6050);
	OCD_OLED_ShowString(&tOLED,0,0,"MPU6050 ID:",16);
	OCD_OLED_ShowNum(&tOLED,96,0,ID,3,16);
	Drv_Delay_Ms(100);
	while(1)
	{
		OCD_MPU6050_GetData(&tMPU6050);
		OCD_MPU6050_DataConversion(&tMPU6050);

		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAcc.ConAccX*1000.0f,16);
		OCD_OLED_ShowFloatNum(&tOLED,0,4,tMPU6050.stcAcc.ConAccY*1000.0f,16);
		OCD_OLED_ShowFloatNum(&tOLED,0,6,tMPU6050.stcAcc.ConAccZ*1000.0f,16);

		OCD_OLED_ShowFloatNum(&tOLED,64,2,tMPU6050.stcGyro.ConGyroX*100.0f,16);
		OCD_OLED_ShowFloatNum(&tOLED,64,4,tMPU6050.stcGyro.ConGyroY*100.0f,16);
		OCD_OLED_ShowFloatNum(&tOLED,64,6,tMPU6050.stcGyro.ConGyroZ*100.0f,16);

		Drv_Delay_Ms(200);
	}
}
