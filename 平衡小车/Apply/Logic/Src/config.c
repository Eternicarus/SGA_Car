#include "config.h"

/* PID参数 */
tagPID_T tPID_Balance = 
{
	.fKp = -6.0f,
	.fKi = 0.0f,
	.fKd = -1.8f,

	.fMax_Out = 80.0f,
	
	.fD_lpf_alpha = 0.85f,  /* D项低通滤波系数：0.8表示较强滤波，适合有噪声的场景 */
};

tagPID_T tPID_Velocity = 
{
	.fKp = -0.0f,
	.fKi = -0.0f,
	.fKd = -0.0f,

	.fMax_Out = 0.0f,
};

/* GPIO句柄示例 */
tagGPIO_T demoGPIO[] =
{
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
    [2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
    [3]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
	[4]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_IT_FALLING,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_PULLUP,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		// .tGPIOInit.Speed 	= GPIO_SPEEREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
		.ucPriority			= 2,
		.ucSubPriority		= 2,
	},
};

/* 串口句柄示例 */
tagUART_T demoUart = 
{
	//串口工作模式配置
	.tUARTHandle.Instance 						= USART3,					/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   				= 9600,						/* 串口波特率 */
	//串口DMA接收参数配置
	.tUartDMA.bRxEnable							= true,						/* DMA接收使能 */
	.tRxInfo.usDMARxMAXSize             		= 100,              		/* DMA接收缓冲区大小 大小保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

//	.tUartDMA.ucDMARxPriority					= 1,						/* DMA接收中断优先级 */
//	.tUartDMA.ucDMARxSubPriority				= 1,						/* DMA接收中断子优先级 */
	.tUartDMA.bTxEnable							= true,
	.tTxInfo.usDMATxMAXSize						= 50,						/* DMA发送缓冲区大小 */
////	
//	.ucPriority									= 1,						/* 中断优先级 */
//	.ucSubPriority								= 2,						/* 中断子优先级 */
};

/* OLED示例 */
tagOLED_T tOLED = 
{
	/* SCL线 */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO引脚 */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOB,					/* GPIO分组 */
	
	/* SDA线 */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO引脚 */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOB,					/* GPIO分组 */
};

/* MPU6050示例 */
tagMPU6050_T tMPU6050 = 
{
	/* SCL线 */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_4,				/* GPIO引脚 */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOB,					/* GPIO分组 */
	
	/* SDA线 */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_3,				/* GPIO引脚 */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIO模式 */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOB,					/* GPIO分组 */
};

tagPWM_T PWM[] =
{
	[0] =
	{
		.tPWMHandle.Instance	= TIM1,         	/* 定时器1 */
		.fDuty					= 0,				/* 初始占空比（%） */
		.ulFreq					= 10000,			/* 频率（Hz） */
		.ucChannel				= TIM_CHANNEL_1,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_8,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOA,			/* IO组映射 */
		.tGPIO.ucAFMode			= NO_REMAP,			/* IO重映射模式 */
	},	 	
	[1] =
	{
		.tPWMHandle.Instance	= TIM1,         	/* 定时器1 */
		.fDuty					= 0,				/* 初始占空比（%） */
		.ulFreq					= 10000,			/* 频率（Hz） */
		.ucChannel				= TIM_CHANNEL_4,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_11,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOA,			/* IO组映射 */
		.tGPIO.ucAFMode			= NO_REMAP,		    /* IO重映射模式 */
	},	  
};

// tagTIM_T tTimer2 = 
// {
// 	.tTimerHandle.Instance				= TIM2,						/* 通用定时器2 */
// 	.fTimingLength						= 8,						/* 定时时长(ms) */

// 	.ucPriority							= 2,						/* 中断优先级 */
// 	.ucSubPriority						= 1,						/* 中断子优先级 */
// };

// tagIWDG_T demoIWDG = 
// {
// 	.usResetTime = 2000,			/* 2S喂狗溢出时间 */
// };

// tagTIM_T tTimer3 = 
// {
// 	.tTimerHandle.Instance				= TIM3,						/* 通用定时器3 */
// 	.fTimingLength						= 2,						/* 定时时长(ms) */

// 	.ucPriority							= 2,						/* 中断优先级 */
// 	.ucSubPriority						= 2,						/* 中断子优先级 */
// };

