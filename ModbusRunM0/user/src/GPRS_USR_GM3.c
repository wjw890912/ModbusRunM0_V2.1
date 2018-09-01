

/*
*
*   USR-GM3 module
*	2018-4-1
*	GRPS module
*
*
*/

#include <stdio.h>
#include "port.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "user_mb_app.h"

#include "M051Series.h"
#include "Uart3th.h"



#define NONE    0
#define	CMD1    1    //+++�����
#define	CMD2    2   //a �����
#define	CMD3    3    //+ok �����յ�������AT+E="on"ָ��
#define	CMD3_1  4    //����AT+E="on"�յ� �ȴ�OK

#define CMD4    5
#define CMD4_1  6

#define CMD5    7
#define CMD5_1  8

#define CMD6    9
#define CMD6_1  10

#define CMD7    11
#define CMD7_1  12

#define CMD8    13
#define CMD8_1  14

#define CMD9    15
#define CMD9_1  16

#define CMD10   17

extern unsigned char UartReciveBuf[16*8]; //uart reciver buff 
extern unsigned int  UartLen;		   //uart reciver byte lenth 
extern unsigned char RecivEvent;// 1:recived UART byte to buff 0:empty UART buff
uint8_t gprs_cmd_state = NONE;
uint8_t gprs_net_state =0;//�������� �ɹ� 1  ʧ��0
uint8_t rep=1; 
void GprsConnectNetMode(void)
{

char gprs[10];
	  switch(gprs_cmd_state)
	  {
	  		case  NONE:
			{
			 
				break;
			
			}
	  		case CMD1:
			{
			   if(rep==1)
			   {
						  gprs[0]='+';
						  gprs[1]='+';
						   DrvSYS_Delay(200000);
						  UART_Write(UART1, gprs, 1);//����+++����ȴ��شa
						  gprs[2]='+';
						  DrvSYS_Delay(20000);
						  UART_Write(UART1, gprs, 2);//����+++����ȴ��شa
        				  rep=0; 
			   }
			   break;
			}
	  		case CMD2:
			{

				if(rep==1)
				{
					
				  UART_Write(UART1,"a",1);//����a����ظ�a
					 	rep=0; 
				}
				   break;
			}
	  		case CMD3:
			{
			
			   if(rep==1)
			   {
						
			  UART_Write(UART1,"AT+E=\"on\"\r\n",11);//��������ȴ��ظ�
				 	rep=0; 
			  }
			   break;
			
			}
			case CMD4:
			{
			
			   if(rep==1)
			   {
						
			  UART_Write(UART1,"AT+WKMOD=\"NET\"\r\n",16);//��������ȴ��ظ�
				 	rep=0; 
			  }
			   break;
			
			}
	  	   case CMD5:
			{
			
			   if(rep==1)
			   {
						
			  UART_Write(UART1,"AT+SOCKAEN=\"on\"\r\n",17);//��������ȴ��ظ�
				 	rep=0; 
			  }
			   break;
			
			}
			case CMD6:
			{
			
			   if(rep==1)
			   {
						
			  UART_Write(UART1,"AT+SOCKA=\"TCP\",\"123.59.96.233\",2301\r\n",37);//��������ȴ��ظ�
				 	rep=0; 
			  }
			   break;
			
			}
			case CMD7:
			{
			
			   if(rep==1)
			   {
						
			  UART_Write(UART1,"AT+SOCKASL=\"long\"\r\n",19);//��������ȴ��ظ�
				 	rep=0; 
			  }
			   break;
			
			}
			case CMD8:
			{
			
			   if(rep==1)
			   {
						
			  UART_Write(UART1,"AT+S\r\n",6);//��������ȴ��ظ�
				 	rep=0; 
			  }
			   break;
			
			}
				case CMD9:
			{
			
			   if(rep==1)
			   {
			 DrvSYS_Delay(200000);			
			  UART_Write(UART1,"AT+ENTM\r\n",9);//��������ȴ��ظ�
				 	rep=0; 
			  }
			   break;
			
			}
	  }

	   


  

}

	  
void GprsSentEventPoll(void)
{

	 if(gprs_net_state==0)
	 {
	 
	   GprsConnectNetMode();//����ģ��ע�Ტ���ӵ�����
	 						 
	 }
	 else
	 {
	 

	 //�շ�Ӧ�ò�����
	 
	 }


}	  
void GprsReciveEventPoll(void)
{
		uint8_t sum;
	 if(RecivEvent)
	 {

	   switch(gprs_cmd_state)
	   {
	   	  case  NONE:
			{
			 
				break;
			
			}
	  		case CMD1:
			{
			
			 if(strstr(UartReciveBuf,"a")!=0)
			 {
			 	gprs_cmd_state = CMD2;//�յ�a
				rep=1;
			 
			 }

			   break;
			}
			case CMD2:
			{
			
			 if(strstr(UartReciveBuf,"+ok")!=0)
			 {
			 	gprs_cmd_state = CMD3;//��������ģʽ�ɹ�
			 	  rep=1;
			 }

			  break;
			}
	   
	   	   	case CMD3:
			{
			  if(strstr(UartReciveBuf,"AT+E=\"on\"")!=0)
			 {


			 	gprs_cmd_state = CMD3_1;//�����ȴ�OKָ��
			 	 // rep=1;



			 }

			  break;
			}
			case CMD3_1:
			{
			  if(strstr(UartReciveBuf,"OK\r\n")!=0)
			 {


			 	gprs_cmd_state = CMD4;//��һ��ָ��
			 	  rep=1;



			 }

			  break;
			}

				case CMD4:
			{
			  if(strstr(UartReciveBuf,"AT+WKMOD=\"NET\"")!=0)
			 {


			 	gprs_cmd_state = CMD4_1;//�����ȴ�OKָ��
			 	 // rep=1;



			 }

			  break;
			}
			case CMD4_1:
			{
			  if(strstr(UartReciveBuf,"OK\r\n")!=0)
			 {


			 	gprs_cmd_state = CMD5;//��һ��ָ��
			 	  rep=1;



			 }

			  break;
			}
				case CMD5:
			{
			  if(strstr(UartReciveBuf,"AT+SOCKAEN=\"on\"")!=0)
			 {


			 	gprs_cmd_state = CMD5_1;//�����ȴ�OKָ��
			 	 // rep=1;



			 }

			  break;
			}
			case CMD5_1:
			{
			  if(strstr(UartReciveBuf,"OK\r\n")!=0)
			 {


			 	gprs_cmd_state = CMD6;//��һ��ָ��
			 	  rep=1;



			 }

			  break;
			}
	   	   	case CMD6:
			{
			  if(strstr(UartReciveBuf,"OK")!=0)
			 {


			 	gprs_cmd_state = CMD7;//�����ȴ�OKָ��
			 	  rep=1;



			 }

			  break;
			}
		/*	case CMD6_1:
			{
			  if(strstr(UartReciveBuf,"OK\r\n")!=0)
			 {


			 	gprs_cmd_state = CMD7;//��һ��ָ��
			 	  rep=1;



			 }

			  break;
			}	 */

			 	case CMD7:
			{
			  if(strstr(UartReciveBuf,"AT+SOCKASL=\"long\"")!=0)
			 {


			 	gprs_cmd_state = CMD7_1;//�����ȴ�OKָ��
			 	 // rep=1;



			 }

			  break;
			}
			case CMD7_1:
			{
			  if(strstr(UartReciveBuf,"OK\r\n")!=0)
			 {


			 	gprs_cmd_state = CMD8;//��һ��ָ��
			 	  rep=1;



			 }

			  break;
			}

				case CMD8:
			{
			  if(strstr(UartReciveBuf,"AT+S")!=0)
			 {


			 	gprs_cmd_state = CMD8_1;//�����ȴ�OKָ��
			 	 // rep=1;



			 }

			  break;
			}
			case CMD8_1:
			{
			  if(strstr(UartReciveBuf,"OK\r\n")!=0)
			 {


			 	gprs_cmd_state = CMD9;//��һ��ָ��
			 	  rep=1;



			 }

			  break;
			}

			
	   case CMD9:
			{
			  if(strstr(UartReciveBuf,"AT+ENTM")!=0)
			 {


			 	gprs_cmd_state = CMD9_1;//�����ȴ�OKָ��
			 	 // rep=1;



			 }

			  break;
			}
			case CMD9_1:
			{
			  if(strstr(UartReciveBuf,"OK\r\n")!=0)
			 {


			 	gprs_cmd_state = CMD10;//��һ��ָ��
			 	  rep=1;



			 }

			  break;
			}
	   }	
	   

	  
		//process  reciver byte
		UartLen=0;	//clear reciver byte lenth 
		RecivEvent=0;//reset



	   }




}

void GprsInit(void)
{

 
 x3THPortSerialInit(0,115200,8,MB_PAR_NONE);
 x3THPortTimersInit(( 7UL * 220000UL ) / ( 2UL * /*ulBaudRate*/115200 ))	;
 gprs_cmd_state = CMD1;
}

























































































































