#ifndef _OCD_MPU6050_H_
#define _OCD_MPU6050_H_

#include "drv_hal_conf.h"

#define MPU6050_ADDR                0xD0    /* mpu6050�豸��ַ */
#define MPU6050_PWR                 0x6B    //��Դ
#define MPU6050_SMPLRT_DIV          0x19    //ȡ��ʱ��
#define MPU6050_CONFIG              0x1A    //��ͨ�˲�
#define MPU6050_GYRO_CONFIG			0x1B    //����������(bit3,4)(0-250,1-500,2-1000,3-2000)
#define MPU6050_ACCEL_CONFIG        0x1C    //���ٶȼ�����(bit3,4)(0-2g,1-4g,2-8g,3-16g)
 
#define MPU6050_RA_ACCEL_XOUT_H     0x3B    //���ٶ�
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
 
#define MPU6050_RA_TEMP_OUT_H       0x41    //�¶�
#define MPU6050_RA_TEMP_OUT_L       0x42
 
#define MPU6050_RA_GYRO_XOUT_H      0x43    //ת��������
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48

typedef struct
{
    tagIICSoft_T tIIC;
}tagMPU6050_T;


#endif
