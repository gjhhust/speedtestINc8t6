
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
#define senor_length  1.7 //cm

Flag FlagS={0,0,0,0,0,0,0,0};
/***********************************��������*************************************/
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure1;//������1�Ľṹ��
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure2;//������2    
extern USER TIME_SAVE ;
TIM_ICUserValueTypeDef showOLED;
uint32_t beforeTime=0;//��¼֮ǰ����ʱ��
int r1=0;

USER temp;
//�����0λ����
double time[8] = {0};//time[1]�����һ��֮����ٶ�
double speed[8] = {0};
double a[8] = {0};//
char v[8][10]= {0};
char t[8][10]= {0};
char a_char[8][10]= {0};
char a_average[10];//���м��ٶ�ƽ��ֵ
/***********************************��������*************************************/

/***********************************��־λ*************************************/
u16 STATE_USE=0;//����ͨ����־λ 0��ʱ����ͨ��1����1��ͨ��2����
/***********************************END*************************************/

uint32_t get_capture_Time(void);

int show_flag=0;


int main(void)
  {	
		short i,j=0;
		float sum_a=0;
		uint32_t TIM_PscCLK = 72000 / (GENERAL_TIM_PSC+1);

		InitAll();
		OLED_Clear(0); 
		
		delay_ms(10000);
		
		

		
		while(1) 
		{	
			
			
			if(TIME_SAVE.states == 8 && show_flag==0)
			{
				//time[1]=TIME_SAVE.time1/TIM_PscCLK;//�����ms
				time[2]=TIME_SAVE.time2/1000.0f;
				time[3]=TIME_SAVE.time3/1000.0f;
				time[4]=TIME_SAVE.time4/1000.0f;
				time[5]=TIME_SAVE.time5/1000.0f;
				time[6]=TIME_SAVE.time6/1000.0f;
				time[7]=TIME_SAVE.time7/1000.0f;
				
				
				//speed[1] = 100* senor_length / time[1] ; //m/s
				speed[2] =  senor_length / time[2] /10 ;
				speed[3] =  senor_length / time[3] /10;
				speed[4] =  senor_length / time[4] /10; 
				speed[5] =  senor_length / time[5] /10;
				speed[6] =  senor_length / time[6] /10;
				speed[7] =  senor_length / time[7] /10;
				
				//a[1] = 100*2 * senor_length*(time[1] - time[2])/((time[1]+time[2])*time[1]*time[2]);// 10��6����m/s�� //�ڶ���������ʱ�̵ļ��ٶ�
				a[2] = 100*2 * senor_length*(time[2] - time[3])/((time[3]+time[2])*time[3]*time[2]);//�ü��ٶ�˲ʱʱ��Ϊ��ȷֵ
				a[3] = 100*2 * senor_length*(time[3] - time[4])/((time[3]+time[4])*time[3]*time[4]);
				a[4] = 100*2 * senor_length*(time[4] - time[5])/((time[4]+time[5])*time[4]*time[5]);
				a[5] = 100*2 * senor_length*(time[5] - time[6])/((time[5]+time[6])*time[5]*time[6]);
				a[6] = 100*2 * senor_length*(time[6] - time[7])/((time[6]+time[7])*time[6]*time[7]);
				a[7] = 100 * (speed[7]*speed[7] - speed[2]*speed[2]) / (2 * senor_length * 6);//10��6��m/s����ƽ�����ٶ�
//				

				for(i = 2 ;i<8 ; i++)
				{
					sprintf(v[i], "%f", speed[i]);
					v[i][9]='\0';
					
					sprintf(t[i], "%f", time[i]);
					t[i][9]='\0';
					
					sprintf(a_char[i], "%f", a[i]);
					a_char[i][9]='\0';
					
					sum_a = a[i];
				}
				sum_a = sum_a/6;
				sprintf(a_average, "%f",sum_a);
				a_average[9]='\0';
				
				show_flag=1;
 
				OLED_Clear(0);
			}
			
			if(show_flag == 0)
			{
				OLED_ShowString(40,4,"loading....",16);
			}
			
			if(show_flag == 1){
					for(i = 2 ;i<=8 ; i++){
						if(i<8)
						{
							OLED_Clear(0);
				
							
							OLED_ShowNum(6,0,i,3,16);
							OLED_ShowString(40,0,(u8*)t[i],16);
							OLED_ShowChar(5,0,'t',16);
							
							OLED_ShowNum(6,3,i,3,16);
							OLED_ShowString(40,3,(u8*)v[i],16);
							OLED_ShowChar(5,3,'v',16);
							
							
							OLED_ShowNum(6,6,i,3,16);	
							OLED_ShowString(40,6,(u8*)a_char[i],16);
							OLED_ShowChar(5,6,'a',16);
							
							delay_use(40000000);
						}

					
					if(i == 8) {
						OLED_Clear(0);
						i=2;
						OLED_ShowString(6,3,"a_average:",16);
						OLED_ShowString(6,5,(u8*)a_average,16);
						delay_use(40000000);
					}
				}
			}

			
   	}	  
}



void TIM2_CaptureCallBack(void){

	
	
	/**********************************����ͨ����****************************************/
	// ������2����
	if(FlagS.TIM2_CH2 == 1){
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
			
			
				
			// ��ʼ�����׼��1			
			TIM_ICUserValueStructure1.Capture_StartFlag = 1;
			TIM_ITConfig (TIM2, TIM_IT_CC2 , DISABLE );
			TIME_SAVE.states = 2;
			
		}
		FlagS.TIM2_CH2 = 0;
	}
	
	
		/**********************************����ͨ����****************************************/
	if(FlagS.TIM2_CH3 == 1){
		if (TIME_SAVE.states == 2)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture3 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.time2 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);

						
			
			TIME_SAVE.time2 = TIME_SAVE.time2 -TIME_SAVE.time1;//�ڶ���ʱ��
			
			

			//��ɵ�һ��
			TIME_SAVE.states= 3;
			
			//�ر�ͨ��
			TIM_ITConfig (TIM2, TIM_IT_CC3 , DISABLE );
		}
		FlagS.TIM2_CH3 = 0;
	}
	
		/**********************************����ͨ����****************************************/
	if(FlagS.TIM2_CH4 == 1){
		if (TIME_SAVE.states == 3)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture4 (GENERAL_TIM);//�ݴ�
			TIME_SAVE.time3 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time3 = TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;//�ڶ���ʱ��
			//��ɵ�һ��
			TIME_SAVE.states= 4;
			
			//�ر�ͨ��
			TIM_ITConfig (TIM2, TIM_IT_CC4 , DISABLE );
					
		}
		FlagS.TIM2_CH4 = 0;
	}
}


void TIM3_CaptureCallBack(void)
{
		// ��1�β���
	if(FlagS.TIM3_CH1 == 1)
	{
			if  (TIME_SAVE.states == 4)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//�ݴ�
			TIME_SAVE.time4 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time4 = TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;//�ڶ���ʱ��
			//��ɵ�һ��
			TIME_SAVE.states= 5;
			
			//�ر�ͨ��
			TIM_ITConfig (TIM3, TIM_IT_CC1 , DISABLE );
					
		}
		FlagS.TIM3_CH1=0;
		
	}
	
	
	
	/**********************************����ͨ����****************************************/
	// ������2����
	if(FlagS.TIM3_CH2 == 1){
		if (TIME_SAVE.states == 5)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//�ݴ�
			TIME_SAVE.time5 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
				
			//��ɵ�һ��
			TIME_SAVE.time5 = TIME_SAVE.time5 - TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;
			TIME_SAVE.states= 6;
			
			//�ر�ͨ��
			TIM_ITConfig (TIM3, TIM_IT_CC2 , DISABLE );
				
					
		}
			FlagS.TIM3_CH2 = 0;
	}
	
	
		/**********************************����ͨ����****************************************/
	if(FlagS.TIM3_CH3 == 1){
		if (TIME_SAVE.states == 6)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//�ݴ�
			TIME_SAVE.time6 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time6 = TIME_SAVE.time6 - TIME_SAVE.time5 - TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;
			//��ɵ�һ��

			TIME_SAVE.states= 7;
			
			//�ر�ͨ��
			TIM_ITConfig (TIM3, TIM_IT_CC3 , DISABLE );
		}
		FlagS.TIM3_CH3 = 0;
	}
	
		/**********************************����ͨ����****************************************/
	if(FlagS.TIM3_CH4 == 1){
		if (TIME_SAVE.states == 7)
		{

			//��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĵ�һ�θߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//�ݴ�
			TIME_SAVE.time7 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n��øߵ�ƽ����ʱ�䣺%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time7 =TIME_SAVE.time7 - TIME_SAVE.time6 - TIME_SAVE.time5 - TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;;
			
			//��ɵ�һ��
			TIME_SAVE.states= 8;
			
			//�ر�ͨ��
			TIM_ITConfig (TIM3, TIM_IT_CC4 , DISABLE );
					
		}
		FlagS.TIM3_CH4 = 0;
	}
}

///////////////////////////////////////////////////////////////////////

void delay_use(int time){

	while(time!=0) time--;
}