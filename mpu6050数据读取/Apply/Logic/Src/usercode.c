#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

/* �û��߼����� */
void UserLogic_Code(void)
{
	Drv_IICSoft_Init(&tMPU6050.tIIC);
//	Drv_IICSoft_Start(&tMPU6050.tIIC);
//	Drv_IICSoft_SendByte(&tMPU6050.tIIC,MPU6050_ADDR);
//	Drv_IICSoft_WaitAck(&tMPU6050.tIIC);
//	Drv_IICSoft_Stop(&tMPU6050.tIIC);
	Drv_IICSoft_Start(&tMPU6050.tIIC);
	Drv_IICSoft_SendByte(&tMPU6050.tIIC,MPU6050_ADDR);
	Drv_IICSoft_WaitAck(&tMPU6050.tIIC);
	Drv_IICSoft_SendByte(&tMPU6050.tIIC,0x75);
	Drv_IICSoft_WaitAck(&tMPU6050.tIIC);
	
	Drv_IICSoft_Start(&tMPU6050.tIIC);
	Drv_IICSoft_SendByte(&tMPU6050.tIIC,MPU6050_ADDR | 0x01);
	Drv_IICSoft_WaitAck(&tMPU6050.tIIC);
//	Drv_IICSoft_SendByte(&tMPU6050.tIIC,0x75);
//	Drv_IICSoft_WaitAck(&tMPU6050.tIIC);
	
//	Drv_IICSoft_Start(&tMPU6050.tIIC);
	int Num = Drv_IICSoft_ReadByte(&tMPU6050.tIIC,1);
	Drv_IICSoft_Stop(&tMPU6050.tIIC);

	OCD_OLED_ShowNum(&tOLED,0,0,Num,10,16);
	Drv_Delay_Ms(50);
//    OCD_OLED_ShowNum(&tOLED,0,0,123,3,16);
//    Drv_Delay_Ms(50);
	while(1)
	{
	
	}
}
