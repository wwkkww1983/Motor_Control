#include "key.h"
#include "led.h"
#include "delay.h"
#include "X_Setup.h"
#include "usart.h"


uint32_t STEP=0;
uint8_t FLAG = 0;



void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}



void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;

    EXTI_InitStructure.EXTI_Line = EXTI_Line9|EXTI_Line8|EXTI_Line7|EXTI_Line6|EXTI_Line5|EXTI_Line4|EXTI_Line3|EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;

    EXTI_Init(&EXTI_InitStructure);
}


void NVIC2_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;   //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;          //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //ʹ���ⲿ�ж�ͨ��

    NVIC_Init(&NVIC_InitStructure);
}


void NVIC3_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;   //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;          //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //ʹ���ⲿ�ж�ͨ��

    NVIC_Init(&NVIC_InitStructure);
}


void NVIC4_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;   //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;          //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
}


void NVIC5_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;              
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;   
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;         
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              

    NVIC_Init(&NVIC_InitStructure);
}


void EXTIX_DISABLE(uint32_t EL)
{
		NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EL;               
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;   
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;         
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;              

    NVIC_Init(&NVIC_InitStructure);
}


void EXTIX_ENABLE(uint32_t EL)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EL;               
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;   
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;         
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              

    NVIC_Init(&NVIC_InitStructure);
}

void EXTIX_Config(void)
{
    KEY_Init();

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource7);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource6);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
    
    // 嵌套向量中断控制器初始化
    NVIC2_Init();
    NVIC3_Init();
    NVIC4_Init();
    NVIC5_Init();

    // 外部中断初始化
	EXTIX_Init();
}


void EXTI2_IRQHandler(void)
{
	
		if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
		{
			delay_ms(10);       
			if(S3 == 0)
			{
				FLAG = 11;
			}
			EXTI_ClearITPendingBit(EXTI_Line2);
		}
}


void EXTI3_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
	{
		delay_ms(10);       
		if(S2 == 0)
		{
			FLAG = 10;
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}


// 启动
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{
		delay_ms(10);       
		if(S1 == 0)
		{
			LED = ~LED;
			FLAG = Start;     // 启动
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}



void EXTI9_5_IRQHandler()
{
		delay_ms(10);       //软件消抖
	
		// printf("FLAG:%d\r\n", FLAG);
		if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
		{
			if(K1==0)
			{
				FLAG = PTE1;      // 光电开关
				LED = ~LED;	
			}
			EXTI_ClearITPendingBit(EXTI_Line5);
		}
		
		if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
		{
			if(K2==0)
			{
				FLAG = PTE2;
				LED = ~LED;
			}
			EXTI_ClearITPendingBit(EXTI_Line6);
			
		}
		
		if(EXTI_GetITStatus(EXTI_Line9)!=RESET)
		{
			if(ZD==0)
			{
					FLAG = Z_DOWN;    // Z下限位
			}
			EXTI_ClearITPendingBit(EXTI_Line9);
		}
		
		
		if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
		{

			if(LX==0)
			{
				FLAG = X_Limit;   // X限位
				//printf("FLAG7:%d\r\n", FLAG);
				//FLAG = Reset;
				
				EXTI_ClearITPendingBit(EXTI_Line7);
			}
		}

	
		if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
		{
			
			if(ZU==0)
			{
        FLAG = Z_UP;      // Z上限位
				//printf("FLAG8:%d\r\n", FLAG);
				EXTI_ClearITPendingBit(EXTI_Line8);	
			}
		}
		
}



