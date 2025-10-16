#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

uint16_t ID;
float Speed;
volatile uint8_t ReceBuf[100];
volatile uint8_t Num;
char Analysis[4][10];
uint8_t AnalysisNum = 0;

/* �û��߼����� */
void UserLogic_Code(void)
{
	printf("hi\r\n");
	while(1)
	{
		// OCD_OLED_ShowFloatNum(&tOLED,0,2,tMPU6050.stcGyro.ConGyroX,16);
		// OCD_OLED_ShowFloatNum(&tOLED,0,4,tMPU6050.stcAcc.ConAccY,16);
//		 OCD_OLED_ShowFloatNum(&tOLED,0,4,tMPU6050.stcAngle.ConPitch,16);

		// if(strcmp((char *)ReceBuf,"PID") == 0)
		// {

		// }
		if(Num != 0)
		{
			memset(Analysis,0,sizeof(Analysis));
			// ��������
			AnalysisNum = sscanf((char *)ReceBuf,"%s %s %s %s",Analysis[0],Analysis[1],Analysis[2],Analysis[3]);
			// printf("Num=%d\r\n",AnalysisNum);
			Drv_Uart_Transmit_DMA(&demoUart,Analysis[0],3);
			if(!strcmp(Analysis[0],"PID"))
			{
				tPID_Balance.fKp = strtof(Analysis[1], NULL);
				tPID_Balance.fKi = strtof(Analysis[2], NULL);
				tPID_Balance.fKd = strtof(Analysis[3], NULL);
				printf("Kp=%.2f Ki=%.2f Kd=%.2f\r\n",tPID_Balance.fKp,tPID_Balance.fKi,tPID_Balance.fKd);
			}
			Num = 0;
		}

		Speed = Algo_PID_Calculate(&tPID_Balance,tMPU6050.stcAngle.ConPitch,-1.0f);
//		 OCD_OLED_ShowFloatNum(&tOLED,0,0,Speed,16);

		if(Speed > 0.5f)
			Motor_Forward();
		else if(Speed < -0.5f)
			Motor_Backward();
		else
			Motor_Stop();
		
		Speed += 5.0f;
		
//		OCD_OLED_ShowFloatNum(&tOLED,0,2,Speed,16);
		Motor_SetSpeed(fabsf(Speed));

	}
}
