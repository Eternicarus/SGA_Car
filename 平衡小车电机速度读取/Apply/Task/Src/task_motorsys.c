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
 * @param _usspeed-转速值，范围0-100
 * @retval Null
 */
void Task_Motor_Setspeed(float _fspeed)
{
    Drv_PWM_DutyFactorSet(&PWM[0], _fspeed);
    Drv_PWM_DutyFactorSet(&PWM[1], _fspeed);
}

/**
 * @brief 电机PD位置式控制函数
 * @param _tPid-PID句柄指针
 * @param _fExpValue-期望值
 * @retval speed-当前计算出的速度值
 */
float Task_Motor_PDControl(tagPID_T *_tPid, float _fExpValue)
{
    float speed;
    float error;
    //PID计算
    error = tMPU6050.stcAngle.ConPitch - _fExpValue;
    _tPid->fPout = _tPid->fKp * error;
    _tPid->fDout = _tPid->fKd * tMPU6050.stcGyro.ConGyroX;

    /* D项低通滤波，抑制高频噪声 */
    if (_tPid->fD_lpf_alpha > 0.0f && _tPid->fD_lpf_alpha < 1.0f) {
        _tPid->fDout_lpf = _tPid->fD_lpf_alpha * _tPid->fDout_lpf + (1.0f - _tPid->fD_lpf_alpha) * _tPid->fDout;
    } else {
        _tPid->fDout_lpf = _tPid->fDout;  /* 不启用滤波 */
    }

    speed = _tPid->fPout + _tPid->fDout_lpf;

    /* 输出限幅 */
    if(speed > _tPid->fMax_Out)
        speed = _tPid->fMax_Out;
    else if(speed < -_tPid->fMax_Out)
        speed = -_tPid->fMax_Out;

    return speed;
}

/**
 * @brief 电机控制函数
 * @param _tPid-PID句柄指针
 * @param _fExpValue-期望值
 * @retval speed-当前计算出的速度值
 */
float Task_Motor_Control(tagPID_T *_tPid,float _fExpValue)
{
    float speed;
    float pid_out;
    //PID计算
    pid_out = Task_Motor_PDControl(_tPid,_fExpValue);

    // 电机方向控制
	if(pid_out > 0.5f)
		Task_Motor_Forward();
	else if(pid_out < -0.5f)
		Task_Motor_Backward();
	else
		Task_Motor_Stop();
	
    // 去电机死区,根据实际电机调节
	speed =  fabsf(pid_out) + MOTOR_DEADZONE;
	
    //设定速度
	Task_Motor_Setspeed(speed);

    return speed;
}
