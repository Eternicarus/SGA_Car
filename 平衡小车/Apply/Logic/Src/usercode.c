#include "usercode.h"		/* usercode头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

uint16_t ID;
float Speed;
uint8_t ReceBuf[100];
uint8_t Num;

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	// ID = MPU6050_GetID(&tMPU6050);
//	OCD_OLED_ShowString(&tOLED,0,0,"MPU6050 ID:",16);
//	OCD_OLED_ShowNum(&tOLED,96,0,ID,3,16);
//	Drv_Delay_Ms(100);
//	OCD_OLED_ShowString(&tOLED,0,0,"Receive:",16);
	printf("hi\r\n");
	while(1)
	{
		// OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcGyro.ConGyroX,16);
		// OCD_OLED_ShowFloatNum(&tOLED,0,4,tMPU6050.stcAcc.ConAccY,16);
		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);
//		 memset(ReceBuf,0,sizeof(ReceBuf));
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

		Num = Drv_Uart_Receive_DMA(&demoUart,ReceBuf);
		if(Num != 0)
		{
			// Drv_Uart_Transmit_DMA(&demoUart,ReceBuf,Num);
			printf("%s\r\n",ReceBuf);
			printf("%d\r\n",Num);
////			OCD_OLED_ShowString(&tOLED,0,0,"Hello SGA!",16);
////			OCD_OLED_ShowFloatNum(&tOLED,0,4,tMPU6050.stcAngle.ConPitch,16);
		}
		// else
		// 	memset(ReceBuf,0,10);
//		Drv_Uart_Transmit_DMA(&demoUart,"Hello",40);
		Drv_Delay_Ms(100);
	}
}
