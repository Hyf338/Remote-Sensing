#include "usart.h"	
#include "stdbool.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	

u8 recvice_data[8]={0};                //接收到的数据包
u8 recvice_data_number = 0;						 //接收到的数据位数
extern char pitch_L,pitch_H,roll_L,roll_H,yaw_L,yaw_H;
extern bool mode_flag;
extern bool recvice_flag;

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void uart_init(u32 bound){
  //GPIO端口设置

	NVIC_InitTypeDef NVIC_InitStrue;
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//开启端口B和复用功能时钟 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);//使能端口重映射 

	//uart 的GPIO重映射管脚初始化 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6; //TX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽输出 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB,&GPIO_InitStructure); 


	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//悬空输入 
	GPIO_Init(GPIOB,&GPIO_InitStructure); 





	//串口参数配置：9600,8,1，无奇偶校验，无硬流量控制 ，使能发送和接收 
	USART_InitStructure.USART_BaudRate = bound; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No ; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);//串口接收中断 
	USART_Cmd(USART1, ENABLE); 

	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
	

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
//		test=USART_ReceiveData(USART1);
	  recvice_data[recvice_data_number++]=USART_ReceiveData(USART1);
		

		if(recvice_data[0]==0xaa)
		{
			if(recvice_data_number>1)
			{
				pitch_L=recvice_data[1];
				pitch_H=recvice_data[2];
				roll_L=recvice_data[3];
				roll_H=recvice_data[4];
				yaw_L=recvice_data[5];
				yaw_H=recvice_data[6];
				recvice_flag=recvice_data[7];
			}
		}
		else recvice_data_number=0;
		recvice_data_number=recvice_data_number>7?0:recvice_data_number;

//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束	
//		USART_SendData(USART1, 'C');
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束	
	
  } 


	

} 
#endif	

