#ifndef __TASK_MOTORSYS_H_
#define __TASK_MOTORSYS_H_

#define MOTOR_DEADZONE       5.0f

void Task_Motor_Forward(void);
void Task_Motor_Backward(void);
void Task_Motor_Stop(void);
void Task_Motor_Setspeed(uint8_t _usspeed);
float Task_Motor_Control(tagPID_T *_tPid,float _fExpValue);

#endif // __TASK_MOTORSYS_H_
