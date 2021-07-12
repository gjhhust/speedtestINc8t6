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
	uint32_t  first_time;     // ��һ��ʱ��
	uint8_t		first_start; //��ɱ�־λ
	uint8_t		first_finishing; //��ɱ�־λ
	
	uint32_t  second_time;    // �ڶ���ʱ��
	uint8_t		second_start; //��ɱ�־λ
	uint8_t		second_finishing; //��ɱ�־λ
	
	uint32_t  Interval_time;    // ���ʱ��
	
	uint32_t states;//1.2.3.4
}USER;


#endif