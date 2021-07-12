/******************* ********************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����
 *          
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�-----------------
 *          |   PC13 - LED1   |
 *          |       
 *          |                 |
 *           ----------------- 
 * ��汾  ��ST3.0.0  																										  
*********************************************************/
#include "led.h"


 /***************  ����LED�õ���I/O�� *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( LED1_GPIO_CLK, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	//ѡ���Ӧ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC�˿�
  GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN );	 // �ر�����LED
}



/** ��������Key_GPIO_Config 
* ���� �����ð����õ���I/O�� 
* ���� ��
* ��� ���� 
*/ 
void Key_GPIO_Config(void) 
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	/*���������˿ڣ�PE5����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
} 


 /** ��������Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
* ���� ������Ƿ��а������� 
* ���� ��GPIOx��x ������ A��B��C��D���� E 
GPIO_Pin������ȡ�Ķ˿�λ 
* ��� ��KEY_OFF(û���°���)��KEY_ON�����°����� 
*/
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin) 
{
	/*����Ƿ��а������� */ 
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )
		{ 
			/*��ʱ����*/ 
			delay_ms(10000);
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
				{ 
					/*�ȴ������ͷ� */ 
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON); 
					return KEY_ON;
				} 
			else return KEY_OFF; 
	} 
	else return KEY_OFF; 
} 
