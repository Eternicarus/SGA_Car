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
 * @param _usspeed-ת��ֵ����Χ0-100
 * @retval Null
 */
void Task_Motor_Setspeed(float _fspeed)
{
    Drv_PWM_DutyFactorSet(&PWM[0], _fspeed);
    Drv_PWM_DutyFactorSet(&PWM[1], _fspeed);
}

/**
 * @brief ���PDλ��ʽ���ƺ���
 * @param _tPid-PID���ָ��
 * @param _fExpValue-����ֵ
 * @retval speed-��ǰ��������ٶ�ֵ
 */
float Task_Motor_PDControl(tagPID_T *_tPid, float _fExpValue)
{
    float speed;
    float error;
    //PID����
    error = tMPU6050.stcAngle.ConPitch - _fExpValue;
    _tPid->fPout = _tPid->fKp * error;
    _tPid->fDout = _tPid->fKd * tMPU6050.stcGyro.ConGyroX;

    /* D���ͨ�˲������Ƹ�Ƶ���� */
    if (_tPid->fD_lpf_alpha > 0.0f && _tPid->fD_lpf_alpha < 1.0f) {
        _tPid->fDout_lpf = _tPid->fD_lpf_alpha * _tPid->fDout_lpf + (1.0f - _tPid->fD_lpf_alpha) * _tPid->fDout;
    } else {
        _tPid->fDout_lpf = _tPid->fDout;  /* �������˲� */
    }

    speed = _tPid->fPout + _tPid->fDout_lpf;

    /* ����޷� */
    if(speed > _tPid->fMax_Out)
        speed = _tPid->fMax_Out;
    else if(speed < -_tPid->fMax_Out)
        speed = -_tPid->fMax_Out;

    return speed;
}

/**
 * @brief ������ƺ���
 * @param _tPid-PID���ָ��
 * @param _fExpValue-����ֵ
 * @retval speed-��ǰ��������ٶ�ֵ
 */
float Task_Motor_Control(tagPID_T *_tPid,float _fExpValue)
{
    float speed;
    float pid_out;
    //PID����
    pid_out = Task_Motor_PDControl(_tPid,_fExpValue);

    // ����������
	if(pid_out > 0.5f)
		Task_Motor_Forward();
	else if(pid_out < -0.5f)
		Task_Motor_Backward();
	else
		Task_Motor_Stop();
	
    // ȥ�������,����ʵ�ʵ������
	speed =  fabsf(pid_out) + MOTOR_DEADZONE;
	
    //�趨�ٶ�
	Task_Motor_Setspeed(speed);

    return speed;
}
