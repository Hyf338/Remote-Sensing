#include "usart.h"	
#include "stdbool.h"
#include "datatype.h"

u8 buffer[20]={0};
extern struct angle angle;
extern struct adc adc;

/*******************************
UART1:
  Tx	Rx
  B6	B7
UART2:
  Tx	Rx
  A2	A3
*******************************/
void uart2_init(u32 bound){
  //GPIO�˿�����

	NVIC_InitTypeDef NVIC_InitStrue;
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure; 
	
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//�����˿�B�͸��ù���ʱ�� 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 

	//uart ��GPIO��ӳ��ܽų�ʼ�� 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2; //TX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//������� 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 


	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//�������� 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 

	//���ڲ������ã�9600,8,1������żУ�飬��Ӳ�������� ��ʹ�ܷ��ͺͽ��� 
	USART_InitStructure.USART_BaudRate = bound; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No ; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	USART_Init(USART2, &USART_InitStructure); 
	USART_ITConfig(USART2, USART_IT_RXNE,ENABLE);//���ڽ����ж� 
	USART_Cmd(USART2, ENABLE); 

	NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
	

}

void USART2_IRQHandler(void)                	//����2�жϷ������
{
	static  u8 res=0,step=0,count=0;
	static char *p = NULL;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�
	{
		res=USART_ReceiveData(USART2);
		switch(step)
		{
			case 0:
			{
				if(res == 0xaa)
					step++;
				buffer[0]=res;
			}break;
			case 1:
			{
				if(res == 0x55)
				{
					step++;
					buffer[1]=res;
				}
				else step=0;
			}break;
			//-------ģʽλ-------
			case 2:
			{
				if(res == 0x01)
				{
					buffer[2]=res;
					p=(char *)&angle;
					step = 10;
				}
				else if(res == 0x02)
				{
					step =20;
					p=(char *)&adc;
					buffer[2]=res;
				}
				else 
					step=0;
			}break;
			//------------ң��ģʽ-----------
			case 10:
			{
				if(count<sizeof(struct angle))
				{
					*p=res;
					p++;
					buffer[count+3]=res;
					count++;
				}
				else 
				{
					count=0;
					step=0;
				}
			}break;
			//-----------�Ƹ�ģʽ---------
			case 20:
			{
				if(count<sizeof(struct adc))
				{
					*p=res;
					p++;
					buffer[count+3]=res;
					count++;
				}
				else 
				{
					count=0;
					step=0;
				}
			}break;
			default:
			{
				step=0;
				count=0;
			}break;
		}
	}
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���	
//		USART_SendData(USART1, 'C');
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���	
	

} 

