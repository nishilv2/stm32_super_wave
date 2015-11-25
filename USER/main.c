#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"


//ALIENTEK 探索者STM32F407开发板 实验10
//输入捕获实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
 
 
 
extern u8  TIM3CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM3CH1_CAPTURE_VAL;	//输入捕获值  
  
	
int main(void)
{ 
	long long temp=0;  
	float lenth=0.00;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200
	LED_Init();
    
 	TIM3_CH1_Cap_Init(0XFFFF,84-1); //以1Mhz的频率计数 
   	while(1)
	{
 		delay_ms(10);
		GPIO_SetBits(GPIOF,GPIO_Pin_7 );
		delay_us(10);
		GPIO_ResetBits(GPIOF,GPIO_Pin_7 );
 		if(TIM3CH1_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
		{
			temp=TIM3CH1_CAPTURE_STA&0X3F; 
			temp*=0XFFFF;		 		         //溢出时间总和
			temp+=TIM3CH1_CAPTURE_VAL;		   //得到总的高电平时间
			if(temp>=80000)
			{
				printf("no trouble\r\n");
			}
			else
			{
			  lenth=((float)temp)*340/1000000/2;
				printf("lenth:%f m\r\n",lenth); //打印总的高点平时间
				printf("%lld\r\n",temp);
			}
			TIM3CH1_CAPTURE_STA=0;			     //开启下一次捕获
		}
	}
}
