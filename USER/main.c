#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"


//ALIENTEK ̽����STM32F407������ ʵ��10
//���벶��ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
 
 
 
extern u8  TIM3CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM3CH1_CAPTURE_VAL;	//���벶��ֵ  
  
	
int main(void)
{ 
	long long temp=0;  
	float lenth=0.00;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	LED_Init();
    
 	TIM3_CH1_Cap_Init(0XFFFF,84-1); //��1Mhz��Ƶ�ʼ��� 
   	while(1)
	{
 		delay_ms(10);
		GPIO_SetBits(GPIOF,GPIO_Pin_7 );
		delay_us(10);
		GPIO_ResetBits(GPIOF,GPIO_Pin_7 );
 		if(TIM3CH1_CAPTURE_STA&0X80)        //�ɹ�������һ�θߵ�ƽ
		{
			temp=TIM3CH1_CAPTURE_STA&0X3F; 
			temp*=0XFFFF;		 		         //���ʱ���ܺ�
			temp+=TIM3CH1_CAPTURE_VAL;		   //�õ��ܵĸߵ�ƽʱ��
			if(temp>=80000)
			{
				printf("no trouble\r\n");
			}
			else
			{
			  lenth=((float)temp)*340/1000000/2;
				printf("lenth:%f m\r\n",lenth); //��ӡ�ܵĸߵ�ƽʱ��
				printf("%lld\r\n",temp);
			}
			TIM3CH1_CAPTURE_STA=0;			     //������һ�β���
		}
	}
}
