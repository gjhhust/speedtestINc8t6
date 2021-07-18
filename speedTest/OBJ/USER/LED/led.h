#ifndef __LED_H
#define	__LED_H

#include "main.h"


/*****LED********/
#define LED1_GPIO_PORT    	GPIOC		              /* GPIO�˿� */
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define LED1_GPIO_PIN			  GPIO_Pin_13			        
/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
 /* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

 /* �������IO�ĺ� */
#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)//ȡ��
#define LED1_OFF		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)//�ر�
#define LED1_ON			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)//��

void LED_GPIO_Config(void);
///////////////////////////END//////////////////////////////////////////////





#define KEY_ON  1
#define KEY_OFF 0



					
void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
#endif /* __LED_H */
