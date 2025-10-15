#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"
#include "algo_conf.h"
#include "dev_conf.h"

extern volatile uint8_t ReceBuf[100];
extern volatile uint8_t Num;

void UserLogic_Code(void);

#endif
