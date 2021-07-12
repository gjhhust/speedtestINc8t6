/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "main.h" 
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure1;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure2;
extern TIM_ICUserValueTypeDef showOLED;
extern USER TIME_SAVE;
extern USER temp;
extern u16 STATE;

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}
void GENERAL_TIM_INT_FUN(void)
{
	// ��Ҫ��������źŵ����ڴ��ڶ�ʱ�������ʱʱ����ʱ���ͻ���������������ж�
	// ���ʱ��������Ҫ�������Ķ�ʱ���ڼӵ������źŵ�ʱ������ȥ
	if ( (TIM_GetITStatus ( GENERAL_TIM, TIM_IT_Update) != RESET) && STATE == 0) //������1���              
	{	
		TIM_ICUserValueStructure1.Capture_Period ++;
		TIM_ClearITPendingBit ( GENERAL_TIM, TIM_FLAG_Update ); 		
	}else if( (TIM_GetITStatus ( GENERAL_TIM, TIM_IT_Update) != RESET) && STATE == 1)//������2���
	{
		TIM_ICUserValueStructure2.Capture_Period ++;
		TIM_ClearITPendingBit ( GENERAL_TIM, TIM_FLAG_Update ); 
	}

	
	
	/*********************************������1�����жϴ���**************************************************/
	if ( TIM_GetITStatus (GENERAL_TIM, TIM_IT_CC1 ) != RESET  )//������1�Ĳ����־λ
	{
		
		// ��һ�β���
		if ( TIM_ICUserValueStructure1.Capture_StartFlag == 0 && TIME_SAVE.states == 1)
		{
			// ��������0
			TIM_SetCounter ( GENERAL_TIM, 0 );
			// �Զ���װ�ؼĴ������±�־��0
			TIM_ICUserValueStructure1.Capture_Period = 0;
			// ����ȽϼĴ�����ֵ�ı�����ֵ��0			
			TIM_ICUserValueStructure1.Capture_CcrValue = 0;
						// �Զ���װ�ؼĴ������±�־��0
			TIM_ICUserValueStructure2.Capture_Period = 0;
			// ����ȽϼĴ�����ֵ�ı�����ֵ��0			
			TIM_ICUserValueStructure2.Capture_CcrValue = 0;
			
			
			//��һ�β��������ش���ͷ��һ������������1������һ����Ҫ���񴫸���2��������
			TIME_SAVE.first_start = 1;//������һ�β������
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Falling);
				
			// ��ʼ�����׼��1			
			TIM_ICUserValueStructure1.Capture_StartFlag = 1;
			TIME_SAVE.states = 2;

			
		}else if(TIME_SAVE.first_finishing == 1 && TIME_SAVE.states == 3)
		{
			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵� ��һ�δ������������ڶ����������½� ����ߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture1 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.Interval_time = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + (TIM_ICUserValueStructure1.Capture_CcrValue+1);
			
			// ���ڶ��β�����֮�󣬾ͰѲ����������Ϊ�����أ�һ�ֲ���
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Rising);
			
			// ��������0
			TIM_SetCounter ( GENERAL_TIM, 0 );
			STATE = 1;//ʹ�ô�����
			// �Զ���װ�ؼĴ������±�־��0
			TIM_ICUserValueStructure2.Capture_Period = 0;
			// �沶��ȽϼĴ�����ֵ�ı�����ֵ��0			
			TIM_ICUserValueStructure2.Capture_CcrValue = 0;
			//�����ڶ��β������
			TIME_SAVE.second_start = 1;
			//�ô�����2�����ڶ��ι���
			
			TIM_ICUserValueStructure2.Capture_StartFlag = 1;
			TIME_SAVE.states = 4;
		}
		
		TIM_ClearITPendingBit (GENERAL_TIM,TIM_IT_CC1);
	}		
	/*********************************������2�����жϴ���**************************************************/
	if (TIM_GetITStatus (GENERAL_TIM, TIM_IT_CC2 ) != RESET)
	{
		
		// ������2����
		if ( TIM_ICUserValueStructure2.Capture_StartFlag == 0 && TIME_SAVE.states == 2)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture1 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.first_time = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
				
			//��ɵ�һ��
			TIME_SAVE.first_finishing = 1;
			TIME_SAVE.first_start = 0  ;
			TIME_SAVE.states= 3;
			
			//ͨ��2����׼���½���
			TIM_OC2PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Falling);
				
					
		}else if(TIM_ICUserValueStructure2.Capture_StartFlag == 1 && TIME_SAVE.states == 4)
		{
			//��ȡ����2�ıȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵڶ��ε͵�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure2.Capture_CcrValue = TIM_GetCapture2 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.second_time = TIM_ICUserValueStructure2.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure2.Capture_CcrValue+1); 
			
			
			 //��ɵڶ���
			TIME_SAVE.second_finishing = 1;
			TIME_SAVE.second_start = 0  ;
			TIM_ICUserValueStructure1.Capture_StartFlag = 0;
			TIM_ICUserValueStructure2.Capture_StartFlag = 0;
			TIME_SAVE.states = 1;
			STATE = 0 ;
			
				//ͨ��2����׼���Ͻ���
			TIM_OC2PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Rising);
		}
		
		TIM_ClearITPendingBit (GENERAL_TIM,TIM_IT_CC2);
	}
	
	
			
	
}

/***********else if (TIM_GetITStatus (GENERAL_TIM, TIM_IT_CC2 ) != RESET )// ���񴫸���2��������
		{
			// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
			TIME_SAVE.first_time = TIM_GetCapture1 (GENERAL_TIM);
			TIM_ICUserValueStructure1.Capture_CcrValue = 
			GENERAL_TIM_GetCapturex_FUN (GENERAL_TIM);

			// ���ڶ��β���������֮�󣬾ͰѲ����������Ϊ�½��أ�������βһ�ֲ���
			GENERAL_TIM_OCxPolarityConfig_FUN(GENERAL_TIM, TIM_ICPolarity_Falling);
			//��ɵ�һ�β������
			TIME_SAVE.first_finishing = 1;
			STATE = 1;
			
      // ������2��ʼ�����־1	
			TIM_ICUserValueStructure2.Capture_StartFlag = 1;
      
			//����
			showOLED = TIM_ICUserValueStructure1;
		}else if(TIM_GetITStatus (GENERAL_TIM, TIM_IT_CC1 ) != RESET && STATE == 1)
		{
		
		
		}

		TIM_ClearITPendingBit (GENERAL_TIM,GENERAL_TIM_IT_CCx);	  
		*////
		
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
