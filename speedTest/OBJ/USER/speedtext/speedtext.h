#ifndef __SPEEDTEXT_H
#define __SPEEDTEXT_H

#include "main.h"

//定义传感器的接口
#define GPIO_Senor1    GPIO_Pin_0
#define GPIO_Senor2    GPIO_Pin_1


#define GPIO_des    GPIOA

//时钟
#define RCC_APB2Periph_NEED     RCC_APB2Periph_GPIOA


uint8_t InputCheck(uint8_t senor_num);//输入检测
void Senor_GPIOInit(void);
void InitAll(void);//全部硬件初始化

typedef struct
{   
	uint32_t  time1;     // 第一段时间
	uint32_t  time2;     
	uint32_t  time3;
	uint32_t  time4;
	uint32_t  time5;
	uint32_t  time6;
	uint32_t  time7;
	
	uint32_t states;//1.2.3.4,//5 6 7 8
}USER;



#endif
