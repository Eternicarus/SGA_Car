/****************************************************************************

* Sigma团队

* 文件名: ocd_mpu6050.c

* 内容简述：mpu6050模块文件

* 文件历史：

* 版本号		日期	  作者			说明
*  2.7  	2025-09-27	黄仕鹏  	 创建该文件
****************************************************************************/
#include "ocd_mpu6050.h"
/**
 * @brief  读取MPU6050指定寄存器的数据
 * @param  _tMPU6050 MPU6050的句柄指针
 * @param  Reg       要读取的寄存器地址
 * @retval 寄存器读取到的数据
 */
static uint32_t S_MPU6050_Read(tagMPU6050_T *_tMPU6050,uint8_t Reg)
{
    uint8_t Data;
    Drv_IICSoft_Start(&_tMPU6050->tIIC);
    Drv_IICSoft_SendByte(&_tMPU6050->tIIC,MPU6050_WRITEADDR);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);
    Drv_IICSoft_SendByte(&_tMPU6050->tIIC,Reg);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);

    Drv_IICSoft_Start(&_tMPU6050->tIIC);
    Drv_IICSoft_SendByte(&_tMPU6050->tIIC,MPU6050_READADDR);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);
    Data = Drv_IICSoft_ReadByte(&_tMPU6050->tIIC,1);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);
    Drv_IICSoft_Stop(&_tMPU6050->tIIC);

    return Data;
}

/**
 * @brief  向MPU6050指定寄存器写入数据
 * @param  _tMPU6050 MPU6050的句柄指针
 * @param  Reg       要写入的寄存器地址
 * @param  Data      要写入的数据
 * @retval 无
 */
static void S_MPU6050_Write(tagMPU6050_T *_tMPU6050,uint8_t Reg,uint8_t Data)
{
    Drv_IICSoft_Start(&_tMPU6050->tIIC);
    Drv_IICSoft_SendByte(&_tMPU6050->tIIC,MPU6050_WRITEADDR);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);
    Drv_IICSoft_SendByte(&_tMPU6050->tIIC,Reg);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);
    Drv_IICSoft_SendByte(&_tMPU6050->tIIC,Data);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);
    Drv_IICSoft_Stop(&_tMPU6050->tIIC);
}

/**
 * @brief  初始化MPU6050模块
 * @param  _tMPU6050 MPU6050的句柄指针
 * @retval 0表示初始化成功，其他值表示失败
 */
uint8_t OCD_MPU6050_Init(tagMPU6050_T *_tMPU6050)
{
    // 初始化IIC接口
    Drv_IICSoft_Init(&_tMPU6050->tIIC);

    S_MPU6050_Write(_tMPU6050, MPU6050_PWR, 0x80);
    Drv_Delay_Ms(20);
    S_MPU6050_Write(_tMPU6050, MPU6050_PWR, 0x00);

    // 设置陀螺仪量程 ±2000dps（GYRO_CONFIG寄存器，0x1B，0x18）
    S_MPU6050_Write(_tMPU6050, MPU6050_GYRO_CONFIG, 0x18);
    Drv_Delay_Ms(20);

    // 设置加速度计量程 ±2g（ACCEL_CONFIG寄存器，0x1C，0x00）
    S_MPU6050_Write(_tMPU6050, MPU6050_ACCEL_CONFIG, 0x00);
    Drv_Delay_Ms(20);

   // 设置采样率分频（SMPLRT_DIV寄存器，0x19，0x07，采样率1kHz/(1+9)=100Hz）
    S_MPU6050_Write(_tMPU6050, MPU6050_SMPLRT_DIV, 0x09);
    Drv_Delay_Ms(20);

   // 设置低通滤波（CONFIG寄存器，0x1A，0x06）
    S_MPU6050_Write(_tMPU6050, MPU6050_CONFIG, 0x06);
    Drv_Delay_Ms(20);

    // 配置 INT 引脚为低电平有效，推挽输出，保持高电平（INT_PIN_CFG寄存器，0x37，0x80）
    S_MPU6050_Write(_tMPU6050, MPU6050_INT_PIN_CFG, 0x80);
    Drv_Delay_Ms(1);

    // 禁止内部主IIC
    S_MPU6050_Write(_tMPU6050, MPU6050_USER_CTRL_REG, 0x00); 
    Drv_Delay_Ms(1);

    // 关闭FIFO
    S_MPU6050_Write(_tMPU6050, MPU6050_FIFO_EN_REG, 0x00);
    Drv_Delay_Ms(1);

    // 使能数据就绪中断（DATA_RDY_EN=1）
    S_MPU6050_Write(_tMPU6050, MPU6050_INT_ENABLE, 0x01);
    Drv_Delay_Ms(1);
    
    // 检查MPU6050是否正常（读取WHO_AM_I寄存器，0x75，默认值0x68）
    uint8_t id = S_MPU6050_Read(_tMPU6050, MPU6050_WHO_AM_I);
    if (id != 0x68)
    {
        return id; // 初始化失败
    }

    return 0; // 初始化成功
}

/**
 * @brief  获取MPU6050的ID
 * @param  _tMPU6050 MPU6050的句柄指针
 * @retval MPU6050的ID值
 */
uint8_t MPU6050_GetID(tagMPU6050_T *_tMPU6050)
{
	return S_MPU6050_Read(_tMPU6050,MPU6050_WHO_AM_I);		//返回WHO_AM_I寄存器的值
}

/**
 * @brief  获取MPU6050的加速度和角速度数据
 * @param  _tMPU6050 MPU6050的句柄指针
 * @retval 无
 */
void OCD_MPU6050_GetData(tagMPU6050_T *_tMPU6050)
{
    int16_t dataH, dataL;
    // 读取加速度数据
    dataH = S_MPU6050_Read(_tMPU6050, MPU6050_RA_ACCEL_XOUT_H);
    dataL = S_MPU6050_Read(_tMPU6050, MPU6050_RA_ACCEL_XOUT_L);
    _tMPU6050->stcAcc.AccX = (dataH << 8) | dataL;

    dataH = S_MPU6050_Read(_tMPU6050, MPU6050_RA_ACCEL_YOUT_H);
    dataL = S_MPU6050_Read(_tMPU6050, MPU6050_RA_ACCEL_YOUT_L);
    _tMPU6050->stcAcc.AccY = (dataH << 8) | dataL;

    dataH = S_MPU6050_Read(_tMPU6050, MPU6050_RA_ACCEL_ZOUT_H);
    dataL = S_MPU6050_Read(_tMPU6050, MPU6050_RA_ACCEL_ZOUT_L);
    _tMPU6050->stcAcc.AccZ = (dataH << 8) | dataL;

   // 读取角速度数据
   dataH = S_MPU6050_Read(_tMPU6050, MPU6050_RA_GYRO_XOUT_H);
   dataL = S_MPU6050_Read(_tMPU6050, MPU6050_RA_GYRO_XOUT_L);
   _tMPU6050->stcGyro.GyroX = (dataH << 8) | dataL;

   dataH = S_MPU6050_Read(_tMPU6050, MPU6050_RA_GYRO_YOUT_H);
   dataL = S_MPU6050_Read(_tMPU6050, MPU6050_RA_GYRO_YOUT_L);
   _tMPU6050->stcGyro.GyroY = (dataH << 8) | dataL;

   dataH = S_MPU6050_Read(_tMPU6050, MPU6050_RA_GYRO_ZOUT_H);
   dataL = S_MPU6050_Read(_tMPU6050, MPU6050_RA_GYRO_ZOUT_L);
   _tMPU6050->stcGyro.GyroZ = (dataH << 8) | dataL;

}

// float acc_roll;
// float acc_pitch;

// void OCD_MPU6050_DataConversion(tagMPU6050_T *_tMPU6050,float dt,uint8_t Num)
// {
// //    float acc_roll;
// //    float acc_pitch;
//       float alpha; // 动态互补滤波系数
    
//     // 加速度转换，单位g
//     _tMPU6050->stcAcc.ConAccX = (float)_tMPU6050->stcAcc.AccX / 16384.0f;
//     _tMPU6050->stcAcc.ConAccY = (float)_tMPU6050->stcAcc.AccY / 16384.0f;
//     _tMPU6050->stcAcc.ConAccZ = (float)_tMPU6050->stcAcc.AccZ / 16384.0f;

//     // 角速度转换，单位度每秒
//     _tMPU6050->stcGyro.ConGyroX = (float)_tMPU6050->stcGyro.GyroX / 16.4f + FIX_GYROX;
//     _tMPU6050->stcGyro.ConGyroY = (float)_tMPU6050->stcGyro.GyroY / 16.4f;
//     _tMPU6050->stcGyro.ConGyroZ = (float)_tMPU6050->stcGyro.GyroZ / 16.4f;

//     acc_roll = atan2(_tMPU6050->stcAcc.ConAccX, _tMPU6050->stcAcc.ConAccZ) * RAD2DEG;
//     acc_pitch = atan2(_tMPU6050->stcAcc.ConAccY, _tMPU6050->stcAcc.ConAccZ) * RAD2DEG + 6.0f;

//     /* 动态权重分配：角度小时更相信加速度计，角度大时更相信陀螺仪 */
//     float abs_pitch = fabsf(acc_pitch);
    
//     // 根据角度大小动态调整权重（角度越小alpha越小，越相信加速度计）
//     if (abs_pitch < 5.0f) {
//         alpha = 0.90f;  // 小角度：加速度计权重0.10
//     } else if (abs_pitch < 15.0f) {
//         alpha = 0.95f;  // 中角度：加速度计权重0.05
//     } else if (abs_pitch < 30.0f) {
//         alpha = 0.98f;  // 大角度：加速度计权重0.02
//     } else {
//         alpha = 0.99f;  // 极大角度：几乎只用陀螺仪
//     }

//     // 互补滤波（动态权重）
//     _tMPU6050->stcAngle.ConRoll = (_tMPU6050->stcAngle.ConRoll + _tMPU6050->stcGyro.ConGyroY * dt) * alpha + acc_roll * (1.0f - alpha);
//     _tMPU6050->stcAngle.ConPitch = (_tMPU6050->stcAngle.ConPitch + _tMPU6050->stcGyro.ConGyroX * dt) * alpha + acc_pitch * (1.0f - alpha);
//     _tMPU6050->stcAngle.ConYaw = _tMPU6050->stcAngle.ConYaw + _tMPU6050->stcGyro.ConGyroZ * dt; // 无加速度计数据修正
// }
float acc_roll;
float acc_pitch;
void OCD_MPU6050_DataConversion(tagMPU6050_T *_tMPU6050,float dt)
{
    
    float alpha; // 动态互补滤波系数
    
    // 加速度转换，单位g
    _tMPU6050->stcAcc.ConAccX = (float)_tMPU6050->stcAcc.AccX / 16384.0f;
    _tMPU6050->stcAcc.ConAccY = (float)_tMPU6050->stcAcc.AccY / 16384.0f;
    _tMPU6050->stcAcc.ConAccZ = (float)_tMPU6050->stcAcc.AccZ / 16384.0f;

    // 角速度转换，单位度每秒
    _tMPU6050->stcGyro.ConGyroX = (float)_tMPU6050->stcGyro.GyroX / 16.4f + FIX_GYROX;
    _tMPU6050->stcGyro.ConGyroY = (float)_tMPU6050->stcGyro.GyroY / 16.4f;
    _tMPU6050->stcGyro.ConGyroZ = (float)_tMPU6050->stcGyro.GyroZ / 16.4f;

    acc_roll = atan2(_tMPU6050->stcAcc.ConAccX, _tMPU6050->stcAcc.ConAccZ) * RAD2DEG;
    acc_pitch = atan2(_tMPU6050->stcAcc.ConAccY, _tMPU6050->stcAcc.ConAccZ) * RAD2DEG;

    /* 动态权重分配：角度小时更相信加速度计，角度大时更相信陀螺仪 */
    float abs_pitch = fabsf(acc_pitch);
    
    // 根据角度大小动态调整权重（角度越小alpha越小，越相信加速度计）
    if (abs_pitch < 5.0f) {
        alpha = 0.90f;  // 小角度：加速度计权重0.10
    } else if (abs_pitch < 15.0f) {
        alpha = 0.95f;  // 中角度：加速度计权重0.05
    } else if (abs_pitch < 30.0f) {
        alpha = 0.98f;  // 大角度：加速度计权重0.02
    } else {
        alpha = 0.99f;  // 极大角度：几乎只用陀螺仪
    }

    // 互补滤波（动态权重）
    _tMPU6050->stcAngle.ConRoll = (_tMPU6050->stcAngle.ConRoll + _tMPU6050->stcGyro.ConGyroY * dt) * alpha + acc_roll * (1.0f - alpha);
    _tMPU6050->stcAngle.ConPitch = (_tMPU6050->stcAngle.ConPitch + _tMPU6050->stcGyro.ConGyroX * dt) * alpha + acc_pitch * (1.0f - alpha);
    _tMPU6050->stcAngle.ConYaw = _tMPU6050->stcAngle.ConYaw + _tMPU6050->stcGyro.ConGyroZ * dt; // 无加速度计数据修正
}
