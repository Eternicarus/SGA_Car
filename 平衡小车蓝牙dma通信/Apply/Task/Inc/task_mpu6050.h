#ifndef __TASK_MPU6050_H_
#define __TASK_MPU6050_H_

#define MPU6050_READ_INTERVAL_MS 0.008f  // MPU6050读取间隔时间，单位毫秒

extern volatile uint8_t mpu6050_pending;

void Task_MPU6050_Init(void);
void Task_MPU6050_DataProcess(void);

#endif
