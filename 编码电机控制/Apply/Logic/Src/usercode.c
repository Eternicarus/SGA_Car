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
	
    Drv_GPIO_Reset(&demoGPIO[1]);
	Drv_GPIO_Set(&demoGPIO[0]);
	Drv_GPIO_Set(&demoGPIO[3]);
	Drv_GPIO_Reset(&demoGPIO[2]);
	while(1)
	{
		Drv_PWM_DutyFactorSet(&PWM[0],20);
		Drv_PWM_DutyFactorSet(&PWM[1],20);
		Drv_Delay_Ms(100);
	}
}
