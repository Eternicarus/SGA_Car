#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

uint16_t ID;
float Speed;
uint8_t ReceBuf[100];
uint8_t Num;

/* �û��߼����� */
void UserLogic_Code(void)
{
	printf("hi\r\n");
	while(1)
	{
		// OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcGyro.ConGyroX,16);
		// OCD_OLED_ShowFloatNum(&tOLED,0,4,tMPU6050.stcAcc.ConAccY,16);
		OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcAngle.ConPitch,16);

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
			Drv_Uart_Transmit_DMA(&demoUart,ReceBuf,Num);
		}
	}
}
