#include "task_conf.h"
#include "usercode.h"
#include "config.h"

/**
 * @brief �����ת
 * @param Null
 * @retval Null
 */
void Task_Motor_Forward(void)
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
void Task_Motor_Backward(void)
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
void Task_Motor_Stop(void)
{
    Drv_GPIO_Reset(&demoGPIO[0]);
    Drv_GPIO_Reset(&demoGPIO[1]);
    Drv_GPIO_Reset(&demoGPIO[2]);
    Drv_GPIO_Reset(&demoGPIO[3]);
}

/**
 * @brief ���ת������
 * @param _usspeed-ת��ֵ����Χ0-255
 * @retval Null
 */
void Task_Motor_Setspeed(uint8_t _usspeed)
{
    Drv_PWM_DutyFactorSet(&PWM[0], _usspeed);
    Drv_PWM_DutyFactorSet(&PWM[1], _usspeed);
}

/**
 * @brief ���PID���ƺ���
 * @param _tPid-PID���ָ��
 * @param _fExpValue-����ֵ
 * @retval speed-��ǰ��������ٶ�ֵ
 */
float Task_Motor_Control(tagPID_T *_tPid,float _fExpValue)
{
    float speed;
    float pid_out;
    //PID����
    pid_out = Algo_PID_Calculate(_tPid,tMPU6050.stcAngle.ConPitch,_fExpValue);

    // ����������
	if(pid_out > 0.5f)
		Task_Motor_Forward();
	else if(pid_out < -0.5f)
		Task_Motor_Backward();
	else
		Task_Motor_Stop();
	
    // ȥ�������,����ʵ�ʵ������
	speed = fabsf(pid_out) + MOTOR_DEADZONE;
	
    //�趨�ٶ�
	Task_Motor_Setspeed(speed);

    return speed;
}
