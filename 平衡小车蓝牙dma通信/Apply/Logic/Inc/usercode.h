#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"
#include "algo_conf.h"
#include "dev_conf.h"

extern uint8_t SendBuf[10];

extern volatile uint8_t Num;

extern uint8_t ReceBuf[100];

void UserLogic_Code(void);

#endif
