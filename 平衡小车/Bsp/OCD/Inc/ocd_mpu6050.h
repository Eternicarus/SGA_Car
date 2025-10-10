#ifndef _OCD_MPU6050_H_
#define _OCD_MPU6050_H_

#include "drv_hal_conf.h"

#define MPU6050_WHO_AM_I           	0x75
#define MPU6050_WRITEADDR           0xD0    // mpu6050设备写入地址 
#define MPU6050_READADDR            0xD1    // mpu6050设备读取地址 
#define MPU6050_PWR                 0x6B    //电源
#define MPU6050_SMPLRT_DIV          0x19    //取样时钟
#define MPU6050_CONFIG              0x1A    //低通滤波
#define MPU6050_GYRO_CONFIG			0x1B    //陀螺仪量程(bit3,4)(0-250,1-500,2-1000,3-2000)
#define MPU6050_ACCEL_CONFIG        0x1C    //加速度计量程(bit3,4)(0-2g,1-4g,2-8g,3-16g)
 
#define MPU6050_RA_ACCEL_XOUT_H     0x3B    //加速度
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
 
#define MPU6050_RA_TEMP_OUT_H       0x41    //温度
#define MPU6050_RA_TEMP_OUT_L       0x42
 
#define MPU6050_RA_GYRO_XOUT_H      0x43    //转速陀螺仪
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48

#define RAD2DEG (180.0f / 3.14159265358979323846f) // 弧度转角度
#define FIX_GYROX 1.6f // X轴角速度每秒的偏移

/* 加速度数据结构体 */
typedef struct 
{
	/* 原始数据 */
	short AccX;
	short AccY;
	short AccZ;
	short T;

	/* 转换后的数据 */
	float ConAccX;
	float ConAccY;
	float ConAccZ;
}tagMPU6050Acc;

/*角速度数据结构体*/
typedef struct 
{
    /* 原始数据 */
    short GyroX;
    short GyroY;
    short GyroZ;
    
    /* 转换后的数据 */
    float ConGyroX;
    float ConGyroY;
    float ConGyroZ;
}tagMPU6050Gyro;

/*欧拉角数据结构体*/
typedef struct 
{
    /* 计算出的数据 */
    float ConRoll;
    float ConPitch;
    float ConYaw;
}tagMPU6050Angle;

typedef struct 
{
    /* 互补滤波后的数据 */
    float FixRoll;
    float FixPitch;
    float FixYaw;
}tagMPU6050FixAngle;

typedef struct
{
    tagIICSoft_T        tIIC;
    tagMPU6050Acc       stcAcc;   
    tagMPU6050Gyro      stcGyro; 
    tagMPU6050Angle     stcAngle; 
    tagMPU6050FixAngle  stcFixAngle;
}tagMPU6050_T;

uint8_t OCD_MPU6050_Init(tagMPU6050_T *_tMPU6050);
uint8_t MPU6050_GetID(tagMPU6050_T *_tMPU6050);
void OCD_MPU6050_GetData(tagMPU6050_T *_tMPU6050);
void OCD_MPU6050_DataConversion(tagMPU6050_T *_tMPU6050,float dt);

#endif
