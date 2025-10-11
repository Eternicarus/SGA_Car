#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"
#include "algo_conf.h"
#include "dev_conf.h"

/* 用户句柄声明包含区 */

extern tagGPIO_T demoGPIO[];

extern tagUART_T demoUart;

extern tagOLED_T tOLED;

extern tagPWM_T PWM[];

extern tagMPU6050_T tMPU6050;

extern tagPID_T tPID_Balance;

extern tagTIM_T tTimer2;

extern tagTIM_T tTimer3;

#endif
