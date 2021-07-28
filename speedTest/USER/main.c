
/****************************************************************************************************
//=========================================电源接线================================================//
//      5V  接DC 5V电源
//     GND  接地
//======================================OLED屏数据线接线==========================================//
//本模块数据总线类型为IIC
//     SCL  接PB6    // IIC时钟信号
//     SDA  接PB7    // IIC数据信号
//======================================传感器接线==========================================//
      1模拟DO口  接PB10
			2模拟DO口  接PB11
//=========================================触摸屏接线=========================================//
//本模块本身不带触摸，不需要接触摸屏线
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
OLED_ShowNum(103,6,we,3,16);//显示ASCII字符的码值 
****************************************************************************************************/

#include "main.h"
#include "string.h"
#define car_length  55 //cm
#define senor_length  1.7 //cm

Flag FlagS={0,0,0,0,0,0,0,0};
/***********************************声明变量*************************************/
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure1;//传感器1的结构体
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure2;//传感器2    
extern USER TIME_SAVE ;
TIM_ICUserValueTypeDef showOLED;
uint32_t beforeTime=0;//记录之前所有时间
int r1=0;

USER temp;
//数组第0位不用
double time[8] = {0};//time[1]代表第一次之间的速度
double speed[8] = {0};
double a[8] = {0};//
char v[8][10]= {0};
char t[8][10]= {0};
char a_char[8][10]= {0};
char a_average[10];//所有加速度平均值
/***********************************声明变量*************************************/

/***********************************标志位*************************************/
u16 STATE_USE=0;//捕获通道标志位 0的时候是通道1捕获，1是通道2捕获
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
				//time[1]=TIME_SAVE.time1/TIM_PscCLK;//算出来ms
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
				
				//a[1] = 100*2 * senor_length*(time[1] - time[2])/((time[1]+time[2])*time[1]*time[2]);// 10的6倍的m/s方 //第二个传感器时刻的加速度
				a[2] = 100*2 * senor_length*(time[2] - time[3])/((time[3]+time[2])*time[3]*time[2]);//该加速度瞬时时刻为精确值
				a[3] = 100*2 * senor_length*(time[3] - time[4])/((time[3]+time[4])*time[3]*time[4]);
				a[4] = 100*2 * senor_length*(time[4] - time[5])/((time[4]+time[5])*time[4]*time[5]);
				a[5] = 100*2 * senor_length*(time[5] - time[6])/((time[5]+time[6])*time[5]*time[6]);
				a[6] = 100*2 * senor_length*(time[6] - time[7])/((time[6]+time[7])*time[6]*time[7]);
				a[7] = 100 * (speed[7]*speed[7] - speed[2]*speed[2]) / (2 * senor_length * 6);//10的6倍m/s方，平均加速度
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

	
	
	/**********************************捕获通道二****************************************/
	// 传感器2捕获
	if(FlagS.TIM2_CH2 == 1){
			if ( TIM_ICUserValueStructure1.Capture_StartFlag == 0 && TIME_SAVE.states == 1)
		{
			// 计数器清0
			TIM_SetCounter ( GENERAL_TIM, 0 );
			// 自动重装载寄存器更新标志清0
			TIM_ICUserValueStructure1.Capture_Period = 0;
			// 捕获比较寄存器的值的变量的值清0			
			TIM_ICUserValueStructure1.Capture_CcrValue = 0;
						// 自动重装载寄存器更新标志清0
			TIM_ICUserValueStructure2.Capture_Period = 0;
			// 捕获比较寄存器的值的变量的值清0			
			TIM_ICUserValueStructure2.Capture_CcrValue = 0;
			
			
				
			// 开始捕获标准置1			
			TIM_ICUserValueStructure1.Capture_StartFlag = 1;
			TIM_ITConfig (TIM2, TIM_IT_CC2 , DISABLE );
			TIME_SAVE.states = 2;
			
		}
		FlagS.TIM2_CH2 = 0;
	}
	
	
		/**********************************捕获通道三****************************************/
	if(FlagS.TIM2_CH3 == 1){
		if (TIME_SAVE.states == 2)
		{

			//获取捕获比较寄存器的值，这个值就是捕获到的第一次高电平的时间的值
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture3 (GENERAL_TIM);//暂存
			TIME_SAVE.time2 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n测得高电平脉宽时间：%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);

						
			
			TIME_SAVE.time2 = TIME_SAVE.time2 -TIME_SAVE.time1;//第二段时间
			
			

			//完成第一次
			TIME_SAVE.states= 3;
			
			//关闭通道
			TIM_ITConfig (TIM2, TIM_IT_CC3 , DISABLE );
		}
		FlagS.TIM2_CH3 = 0;
	}
	
		/**********************************捕获通道四****************************************/
	if(FlagS.TIM2_CH4 == 1){
		if (TIME_SAVE.states == 3)
		{

			//获取捕获比较寄存器的值，这个值就是捕获到的第一次高电平的时间的值
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCapture4 (GENERAL_TIM);//暂存
			TIME_SAVE.time3 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n测得高电平脉宽时间：%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time3 = TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;//第二段时间
			//完成第一次
			TIME_SAVE.states= 4;
			
			//关闭通道
			TIM_ITConfig (TIM2, TIM_IT_CC4 , DISABLE );
					
		}
		FlagS.TIM2_CH4 = 0;
	}
}


void TIM3_CaptureCallBack(void)
{
		// 第1次捕获
	if(FlagS.TIM3_CH1 == 1)
	{
			if  (TIME_SAVE.states == 4)
		{

			//获取捕获比较寄存器的值，这个值就是捕获到的第一次高电平的时间的值
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//暂存
			TIME_SAVE.time4 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n测得高电平脉宽时间：%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time4 = TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;//第二段时间
			//完成第一次
			TIME_SAVE.states= 5;
			
			//关闭通道
			TIM_ITConfig (TIM3, TIM_IT_CC1 , DISABLE );
					
		}
		FlagS.TIM3_CH1=0;
		
	}
	
	
	
	/**********************************捕获通道二****************************************/
	// 传感器2捕获
	if(FlagS.TIM3_CH2 == 1){
		if (TIME_SAVE.states == 5)
		{

			//获取捕获比较寄存器的值，这个值就是捕获到的第一次高电平的时间的值
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//暂存
			TIME_SAVE.time5 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n测得高电平脉宽时间：%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
				
			//完成第一次
			TIME_SAVE.time5 = TIME_SAVE.time5 - TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;
			TIME_SAVE.states= 6;
			
			//关闭通道
			TIM_ITConfig (TIM3, TIM_IT_CC2 , DISABLE );
				
					
		}
			FlagS.TIM3_CH2 = 0;
	}
	
	
		/**********************************捕获通道三****************************************/
	if(FlagS.TIM3_CH3 == 1){
		if (TIME_SAVE.states == 6)
		{

			//获取捕获比较寄存器的值，这个值就是捕获到的第一次高电平的时间的值
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//暂存
			TIME_SAVE.time6 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n测得高电平脉宽时间：%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time6 = TIME_SAVE.time6 - TIME_SAVE.time5 - TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;
			//完成第一次

			TIME_SAVE.states= 7;
			
			//关闭通道
			TIM_ITConfig (TIM3, TIM_IT_CC3 , DISABLE );
		}
		FlagS.TIM3_CH3 = 0;
	}
	
		/**********************************捕获通道三****************************************/
	if(FlagS.TIM3_CH4 == 1){
		if (TIME_SAVE.states == 7)
		{

			//获取捕获比较寄存器的值，这个值就是捕获到的第一次高电平的时间的值
			TIM_ICUserValueStructure1.Capture_CcrValue = TIM_GetCounter (TIM2);//暂存
			TIME_SAVE.time7 = TIM_ICUserValueStructure1.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure1.Capture_CcrValue+1); //printf ( "\r\n测得高电平脉宽时间：%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK ); uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
			
			TIME_SAVE.time7 =TIME_SAVE.time7 - TIME_SAVE.time6 - TIME_SAVE.time5 - TIME_SAVE.time4 - TIME_SAVE.time3 - TIME_SAVE.time2 - TIME_SAVE.time1;;
			
			//完成第一次
			TIME_SAVE.states= 8;
			
			//关闭通道
			TIM_ITConfig (TIM3, TIM_IT_CC4 , DISABLE );
					
		}
		FlagS.TIM3_CH4 = 0;
	}
}

///////////////////////////////////////////////////////////////////////

void delay_use(int time){

	while(time!=0) time--;
}