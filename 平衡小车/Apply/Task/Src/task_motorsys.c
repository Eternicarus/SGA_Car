#include "task_conf.h"
#include "usercode.h"
#include "config.h"

/**
 * @brief �����ת
 * @param Null
 * @retval Null
 */
void Motor_Forward(void)
{
    Drv_GPIO_Reset(&demoGPIO[0]);
	Drv_GPIO_Set(&demoGPIO[1]);
	Drv_GPIO_Set(&demoGPIO[2]);
	Drv_GPIO_Reset(&demoGPIO[3]);
}

/**
 * @brief �����ת
 * @param Null
 * @retval Null
 */
void Motor_Backward(void)
{
    Drv_GPIO_Set(&demoGPIO[0]);
    Drv_GPIO_Reset(&demoGPIO[1]);
    Drv_GPIO_Reset(&demoGPIO[2]);
    Drv_GPIO_Set(&demoGPIO[3]);
}
/**
 * @brief ���ֹͣ
 * @param Null
 * @retval Null
 */
void Motor_Stop(void)
{
    Drv_GPIO_Reset(&demoGPIO[0]);
    Drv_GPIO_Reset(&demoGPIO[1]);
    Drv_GPIO_Reset(&demoGPIO[2]);
    Drv_GPIO_Reset(&demoGPIO[3]);
}

/**
 * @brief ���ת������
 * @param _usSpeed-ת��ֵ����Χ0-255
 * @retval Null
 */
void Motor_SetSpeed(float _usSpeed)
{
    if(_usSpeed > 20.0) _usSpeed = 20.0f;

    Drv_PWM_DutyFactorSet(&PWM[0], _usSpeed);
    Drv_PWM_DutyFactorSet(&PWM[1], _usSpeed);
}
