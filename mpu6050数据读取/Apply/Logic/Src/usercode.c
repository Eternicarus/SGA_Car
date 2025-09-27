#include "usercode.h"		/* usercode头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

/* 用户逻辑代码 */
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
