#include "config.h"

/* PID���� */
tagPID_T tPID_Balance = 
{
	.fKp = -6.0f,
	.fKi = 0.0f,
	.fKd = -1.8f,

	.fMax_Out = 80.0f,
	
	.fD_lpf_alpha = 0.85f,  /* D���ͨ�˲�ϵ����0.8��ʾ��ǿ�˲����ʺ��������ĳ��� */
};

tagPID_T tPID_Velocity = 
{
	.fKp = -0.0f,
	.fKi = -0.0f,
	.fKd = -0.0f,

	.fMax_Out = 0.0f,
};

/* GPIO���ʾ�� */
tagGPIO_T demoGPIO[] =
{
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
    [2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
    [3]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
	[4]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_IT_FALLING,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_PULLUP,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		// .tGPIOInit.Speed 	= GPIO_SPEEREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
		.ucPriority			= 2,
		.ucSubPriority		= 2,
	},
};

/* ���ھ��ʾ�� */
tagUART_T demoUart = 
{
	//���ڹ���ģʽ����
	.tUARTHandle.Instance 						= USART3,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   				= 9600,						/* ���ڲ����� */
	//����DMA���ղ�������
	.tUartDMA.bRxEnable							= true,						/* DMA����ʹ�� */
	.tRxInfo.usDMARxMAXSize             		= 100,              		/* DMA���ջ�������С ��С������Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

//	.tUartDMA.ucDMARxPriority					= 1,						/* DMA�����ж����ȼ� */
//	.tUartDMA.ucDMARxSubPriority				= 1,						/* DMA�����ж������ȼ� */
	.tUartDMA.bTxEnable							= true,
	.tTxInfo.usDMATxMAXSize						= 50,						/* DMA���ͻ�������С */
////	
//	.ucPriority									= 1,						/* �ж����ȼ� */
//	.ucSubPriority								= 2,						/* �ж������ȼ� */
};

/* OLEDʾ�� */
tagOLED_T tOLED = 
{
	/* SCL�� */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO���� */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOB,					/* GPIO���� */
	
	/* SDA�� */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO���� */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOB,					/* GPIO���� */
};

/* MPU6050ʾ�� */
tagMPU6050_T tMPU6050 = 
{
	/* SCL�� */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_4,				/* GPIO���� */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOB,					/* GPIO���� */
	
	/* SDA�� */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_3,				/* GPIO���� */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_OD,		/* GPIOģʽ */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_PULLUP,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOB,					/* GPIO���� */
};

tagPWM_T PWM[] =
{
	[0] =
	{
		.tPWMHandle.Instance	= TIM1,         	/* ��ʱ��1 */
		.fDuty					= 0,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 10000,			/* Ƶ�ʣ�Hz�� */
		.ucChannel				= TIM_CHANNEL_1,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_8,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOA,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},	 	
	[1] =
	{
		.tPWMHandle.Instance	= TIM1,         	/* ��ʱ��1 */
		.fDuty					= 0,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 10000,			/* Ƶ�ʣ�Hz�� */
		.ucChannel				= TIM_CHANNEL_4,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_11,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOA,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= NO_REMAP,		    /* IO��ӳ��ģʽ */
	},	  
};

// tagTIM_T tTimer2 = 
// {
// 	.tTimerHandle.Instance				= TIM2,						/* ͨ�ö�ʱ��2 */
// 	.fTimingLength						= 8,						/* ��ʱʱ��(ms) */

// 	.ucPriority							= 2,						/* �ж����ȼ� */
// 	.ucSubPriority						= 1,						/* �ж������ȼ� */
// };

// tagIWDG_T demoIWDG = 
// {
// 	.usResetTime = 2000,			/* 2Sι�����ʱ�� */
// };

// tagTIM_T tTimer3 = 
// {
// 	.tTimerHandle.Instance				= TIM3,						/* ͨ�ö�ʱ��3 */
// 	.fTimingLength						= 2,						/* ��ʱʱ��(ms) */

// 	.ucPriority							= 2,						/* �ж����ȼ� */
// 	.ucSubPriority						= 2,						/* �ж������ȼ� */
// };

