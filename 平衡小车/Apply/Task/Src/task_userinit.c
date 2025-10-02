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

	if (!OCD_MPU6050_Init(&tMPU6050) == 0)
	{
 		uint8_t Num = OCD_MPU6050_Init(&tMPU6050);
		OCD_OLED_ShowString(&tOLED,0,0,"MPU6050 Err",16);
		OCD_OLED_ShowNum(&tOLED,0,2,Num,10,16);
		while(1);	
 	}
}
