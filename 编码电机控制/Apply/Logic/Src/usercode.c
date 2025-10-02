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
