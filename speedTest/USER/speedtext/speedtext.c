#include "speedtext.h"
extern int time;
USER TIME_SAVE = {0,0,0,0,0,0,0,1};//�������β���ʱ��

/**********************************************************************************************************
*�� �� ��: ��س�ʼ������
*����˵��: ��ʼ��
*��    ��: rx_message0
*�� �� ֵ: ��
**********************************************************************************************************/
void InitAll(void){
	
	SystemInit(); //����ϵͳʱ��Ϊ72M //����
	
	GENERAL_TIM_Init();//��ʼ����ʱ������ʼ��ʱ��
	
	OLED_Init();			//��ʼ��OLED 
	
	LED_GPIO_Config();
		
	Senor_GPIOInit();//���ų�ʼ��
	

}	
/**********************************************************************************************************
*�� �� ��: �������ӿڳ�ʼ������
*����˵��: ��ʼ��
*��    ��: 
*�� �� ֵ: ��
**********************************************************************************************************/
void Senor_GPIOInit(void){
			 /*����GPIO��ʼ���ṹ��*/
	 GPIO_InitTypeDef GPIO_InitStructure;
		
		/*����GPIOA��ʱ�ӵĴ���*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_NEED, ENABLE);

	 //ѡ�񰴼�������
	 GPIO_InitStructure.GPIO_Pin = GPIO_Senor1| GPIO_Senor2 ;//| GPIO_Senor2 | GPIO_Senor3 | GPIO_Senor4;
	 // ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	
 //ʹ�ýṹ���ʼ��
		GPIO_Init(GPIO_des, &GPIO_InitStructure);
		GPIO_SetBits(GPIO_des,GPIO_Senor1| GPIO_Senor2);
}

/**********************************************************************************************************
*�� �� ��: �����⺯��
*����˵��: ��⴫����������
*��    ��: rx_message0
*�� �� ֵ: 0Ϊ�й⣬1Ϊ��
**********************************************************************************************************/
uint8_t InputCheck(uint8_t senor_num){
		
}