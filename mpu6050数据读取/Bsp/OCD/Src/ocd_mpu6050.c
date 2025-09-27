/****************************************************************************

* Sigma团队

* 文件名: ocd_mpu6050.c

* 内容简述：mpu6050模块文件

* 文件历史：

* 版本号		日期	  作者			说明

****************************************************************************/
#include "ocd_mpu6050.h"
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
    Data = Drv_IICSoft_ReadByte(&_tMPU6050->tIIC,0);
    Drv_IICSoft_WaitAck(&_tMPU6050->tIIC);
    Drv_IICSoft_Stop(&_tMPU6050->tIIC);

    return Data;
}

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
