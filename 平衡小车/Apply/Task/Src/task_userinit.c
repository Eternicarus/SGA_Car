#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

/* 外设初始化函数 */
void Task_UserInit(void)
{
	Drv_GPIO_Init(demoGPIO, 4);
    
    Drv_Uart_ITInit(&demoUart);
	
	OCD_OLED_Init(&tOLED);

	Drv_PWM_Init(PWM,2);

	Task_MPU6050_Init();

	Drv_Uart_DMAInit(&demoUart);

//	Drv_IWDG_Init(&demoIWDG);

	Drv_Timer_Init(&tTimer2);
	Drv_Timer_Enable(&tTimer2);

//	Drv_Timer_Init(&tTimer3);
//	Drv_Timer_Enable(&tTimer3);
}
