#include "task_conf.h"
#include "usercode.h"
#include "config.h"

/**
 * @brief 电机正转
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
 * @brief 电机反转
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
 * @brief 电机停止
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
 * @brief 电机转速设置
 * @param _usspeed-转速值，范围0-255
 * @retval Null
 */
void Task_Motor_Setspeed(uint8_t _usspeed)
{
    Drv_PWM_DutyFactorSet(&PWM[0], _usspeed);
    Drv_PWM_DutyFactorSet(&PWM[1], _usspeed);
}

/**
 * @brief 电机PID控制函数
 * @param _tPid-PID句柄指针
 * @param _fExpValue-期望值
 * @retval speed-当前计算出的速度值
 */
float Task_Motor_Control(tagPID_T *_tPid,float _fExpValue)
{
    float speed;
    float pid_out;
    //PID计算
    pid_out = Algo_PID_Calculate(_tPid,tMPU6050.stcAngle.ConPitch,_fExpValue);

    // 电机方向控制
	if(pid_out > 0.5f)
		Task_Motor_Forward();
	else if(pid_out < -0.5f)
		Task_Motor_Backward();
	else
		Task_Motor_Stop();
	
    // 去电机死区,根据实际电机调节
	speed = fabsf(pid_out) + MOTOR_DEADZONE;
	
    //设定速度
	Task_Motor_Setspeed(speed);

    return speed;
}
