
/****************************************************************************************************
//=========================================��Դ����================================================//
//      5V  ��DC 5V��Դ
//     GND  �ӵ�
//======================================OLED�������߽���==========================================//
//��ģ��������������ΪIIC
//     SCL  ��PB6    // IICʱ���ź�
//     SDA  ��PB7    // IIC�����ź�
//======================================����������==========================================//
      1ģ��DO��  ��PB10
			2ģ��DO��  ��PB11
//=========================================����������=========================================//
//��ģ�鱾��������������Ҫ�Ӵ�������
//============================================================================================//
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/	

/*********************************************************************************
u8 we;
we=flag;
we=' ';
OLED_ShowNum(103,6,we,3,16);//��ʾASCII�ַ�����ֵ 
****************************************************************************************************/

#include "main.h"
#include "string.h"
#define car_length  55 //cm
#define senor_length  5 //cm

Flag FlagS={0,0,0,0,0,0,0,0};
/***********************************��������*************************************/
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure1;//������1�Ľṹ��
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure2;//������2    
extern USER TIME_SAVE ;
TIM_ICUserValueTypeDef showOLED;


USER temp;
//�����0λ����
double time[6];//time[1]�����һ��֮����ٶ�
double speed[5];
double a[4];//
char v1[6]= {0};
char v2[6]= {0};
char a1[6]= {0};
/***********************************��������*************************************/

/***********************************��־λ*************************************/
u16 STATE_USE=0;//����ͨ����־λ 0��ʱ����ͨ��1����1��ͨ��2����
/***********************************END*************************************/

uint32_t get_capture_Time(void);

int show_flag=0;


int main(void)
  {	
		uint32_t TIM_PscCLK = 72000 / (GENERAL_TIM_PSC+1);

		InitAll();
		OLED_Clear(0); 
		
		delay_ms(10000);
		
		

		
		while(1) 
		{	
			
			
			
//			if(show_flag == 0){
//				OLED_Clear(0);
//				OLED_ShowString(6,3,"loading.....",16);
//			//�����¼��һ�α��浽temp����
//			}	
			
			

//			OLED_Clear(0);

//		OLED_ShowString(63,6,"CODE:",16);

//			if(flag == 0){
//				OLED_Clear(0);
//				OLED_ShowString(40,3,"LOADING....",16);
//			}

			if(TIME_SAVE.forth_finishing &&show_flag==0)
			{
				time[1]=TIME_SAVE.first_time/TIM_PscCLK;//�����ms
				time[2]=TIME_SAVE.second_time/TIM_PscCLK;
				time[3]=TIME_SAVE.third_time/TIM_PscCLK;
				time[5]=TIME_SAVE.Interval_time/TIM_PscCLK;
				time[4]=TIME_SAVE.forth_time/TIM_PscCLK;
				
				TIME_SAVE.first_finishing=0;
				TIME_SAVE.second_finishing=0;
				TIME_SAVE.third_finishing=0;
				TIME_SAVE.forth_finishing=0;
				
				speed[1] = 100* senor_length / time[1] ; //1000����m/s
				speed[2] = 100* senor_length / time[2] ;
				speed[3] = 100* senor_length / time[3] ;
				
				a[1] = 10000*2 * senor_length*(time[1] - time[2])/((time[1]+time[2])*time[1]*time[2]);// 10��6����m/s��
				a[2] = 10000*2 * senor_length*(time[2] - time[3])/((time[3]+time[2])*time[3]*time[2]);
//				a = 1000 * (speed2 - speed1) / Inval;// 1000����m/s��
//				
				sprintf(v1, "%.4f", speed[1]);
				v1[5]='\0';
				sprintf(v2, "%.4f", speed[2]);
				v2[5]='\0';
				sprintf(a1, "%.4f", a[1]);
				a1[5]='\0';
				
				show_flag=1;
 
				OLED_Clear(0);
			}
			
			
				OLED_Clear(0);
				OLED_ShowString(6,0,"v1:",16);
				//�����¼��һ�α��浽temp����
				OLED_ShowString(40,0,(u8*)v1,16);
				
				OLED_ShowString(6,3,"v2:",16);
				//�����¼��һ�α��浽temp����
				OLED_ShowString(40,3,(u8*)v2,16);
				
				OLED_ShowString(6,6,"a:",16);
				//�����¼��һ�α��浽temp����
				OLED_ShowString(40,6,(u8*)a1,16);
			if(show_flag == 1){	
				
				delay_ms(1000);

			}
//			OLED_ShowNum(103,6,flag,3,16);

			//delay_ms(50000);
			//delay_ms(500);
			
	//		if(w%20000 == 0){
	//			re();
	//		}
//			flag=InputCheck(1);
//			if(flag==1){
//				LED1_ON;//ȡ��
//			}else{
//				LED1_OFF;
//			}
   	}	  
}



void TIM2_CaptureCallBack(void){
	// ��һ�β���
	if(FlagS.TIM2_CH1 == 1)
	{
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
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Falling);
				
			// ��ʼ�����׼��1			
			TIM_ICUserValueStructure1.Capture_StartFlag = 1;
			TIME_SAVE.states = 2;

			
		}else if(TIME_SAVE.states == 5)
		{
			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵� ��һ�δ������������ڶ����������½� ����ߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture1 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.Interval_time = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + (TIM_ICUserValueStructure1.Capture_CcrValue+1);
			
			// ���ڶ��β�����֮�󣬾ͰѲ����������Ϊ�����أ�һ�ֲ���
			TIM_OC1PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Rising);
			
//			// ��������0
//			TIM_SetCounter ( GENERAL_TIM, 0 );
//			//STATE_USE = 1;//ʹ�ô�����
//			// �Զ���װ�ؼĴ������±�־��0
//			TIM_ICUserValueStructure1.Capture_Period = 0;
//			// �沶��ȽϼĴ�����ֵ�ı�����ֵ��0			
//			TIM_ICUserValueStructure1.Capture_CcrValue = 0;

			//�ô�����2�����ڶ��ι���
			TIM_OC2PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Falling);

			TIME_SAVE.states = 6;
		}
		
		FlagS.TIM2_CH1=0;
		
	}
	
	
	
	/**********************************����ͨ����****************************************/
	// ������2����
	if(FlagS.TIM2_CH2 == 1){
		if (TIME_SAVE.states == 2)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture2 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.first_time = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
				
			//��ɵ�һ��
			TIME_SAVE.first_finishing = 1;
			TIME_SAVE.states= 3;
			
			//ͨ��2����׼���½���
			TIM_OC2PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Falling);
				
					
		}else if( TIME_SAVE.states == 6)
		{
			//��ȡ����2�ıȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵڶ��ε͵�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture2 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.forth_time = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); 
			
			TIME_SAVE.forth_time = TIME_SAVE.forth_time -  TIME_SAVE.Interval_time;
			 //��ɵڶ���
			TIME_SAVE.forth_finishing = 1;
			TIM_ICUserValueStructure1.Capture_StartFlag = 0;
			//TIM_ICUserValueStructure2.Capture_StartFlag = 0;
			TIME_SAVE.states = 1;
			
			STATE_USE = 0 ;
			
				//ͨ��2����׼���Ͻ���
			TIM_OC2PolarityConfig(GENERAL_TIM, TIM_ICPolarity_Rising);
		}
		
			FlagS.TIM2_CH2 = 0;
	}
	
	
		/**********************************����ͨ����****************************************/
	if(FlagS.TIM2_CH3 == 1){
		if (TIME_SAVE.states == 3)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture3 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.second_time = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.second_time = TIME_SAVE.second_time - TIME_SAVE.first_time;//�ڶ���ʱ��
			//��ɵ�һ��
			TIME_SAVE.second_finishing = 1;
			TIME_SAVE.states= 4;
			
			//�ر�ͨ��
			TIM_ITConfig (GENERAL_TIM, TIM_IT_CC3 , DISABLE );
		}
		FlagS.TIM2_CH3 = 0;
	}
	
		/**********************************����ͨ����****************************************/
	if(FlagS.TIM2_CH4 == 1){
		if (TIME_SAVE.states == 4)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture4 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.third_time = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.third_time = TIME_SAVE.third_time - TIME_SAVE.second_time - TIME_SAVE.first_time;//�ڶ���ʱ��
			//��ɵ�һ��
			TIME_SAVE.third_finishing = 1;
			TIME_SAVE.states= 5;
			
			//�ر�ͨ��
			TIM_ITConfig (GENERAL_TIM, TIM_IT_CC4 , DISABLE );
					
		}
		FlagS.TIM2_CH4 = 0;
	}
	
	
	
	
}


///////////////////////////////////////////////////////////////////////