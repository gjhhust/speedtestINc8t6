#ifndef __SPEEDTEXT_H
#define __SPEEDTEXT_H

#include "main.h"

//���崫�����Ľӿ�
#define GPIO_Senor1    GPIO_Pin_0
#define GPIO_Senor2    GPIO_Pin_1


#define GPIO_des    GPIOA

//ʱ��
#define RCC_APB2Periph_NEED     RCC_APB2Periph_GPIOA


uint8_t InputCheck(uint8_t senor_num);//������
void Senor_GPIOInit(void);
void InitAll(void);//ȫ��Ӳ����ʼ��

typedef struct
{   
	uint32_t  time1;     // ��һ��ʱ��
	uint32_t  time2;     
	uint32_t  time3;
	uint32_t  time4;
	uint32_t  time5;
	uint32_t  time6;
	uint32_t  time7;
	
	uint32_t states;//1.2.3.4,//5 6 7 8
}USER;



#endif
