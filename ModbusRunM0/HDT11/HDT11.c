 /******************************************************************
 *	ʱ�䣺2012��
 *	�ص㣺����
 *	�ļ�����"HDT11.c"
 *  ��ע��All rights reserved��
 ******************************************************************/
#include "M051Series.h"
#include "HDT11.h"
#include "user_mb_app.h"

   //shm11

#define	 GET_DATA	P16	
#define  DATA_UP    P16=1 
#define  DATA_DOWN  P16=0
extern USHORT   usSRegHoldBuf[S_REG_HOLDING_NREGS] ;
extern void DrvSYS_Delay(uint32_t us);

   void Delayms(int t)
{
		
		do
		{	
		DrvSYS_Delay(1000);
		t--;
		}while(t);
}
/******************************************************************

 *	ʱ�䣺2012��
 *	���ܣ���HDT11
 *	���룺	��
 *	�����	��
 ******************************************************************/
uint16_t Read_HDT11(void)
{
      uint8_t a,b,c,d,e;
	  uint16_t temperature;
	//   __disable_irq(); //closed global interruput
	   DATA_DOWN;
	 //  __enable_irq();	//open global interruput
	   Delayms(20);	//30
	  //  __disable_irq(); //closed global interruput
	   DATA_UP;
	   	
	   DrvSYS_Delay(50); //50
	   // __enable_irq();	//open global interruput
	   __disable_irq(); //closed global interruput	
	  if(!GET_DATA)	 //ACKӦ���Ƿ���
	   {
		 
		 while(!GET_DATA);//0=

		 while(GET_DATA);//1=
	   	
		  a=Read_8byte_data();
		  b=Read_8byte_data();
		  c=Read_8byte_data();
		  d=Read_8byte_data();
		  e=Read_8byte_data();
		 	__enable_irq();	//open global interruput
		 if((a+b+c+d)==e)
		 {
		 
		 	temperature=a;
		    temperature<<=8;
			temperature+=c;

			return temperature;
		 }
		



	   }
	    __enable_irq();	//open global interruput 
      /* DATA_UP;
	  DATA_DOWN ;
	  DrvSYS_Delay(20000); 
	  DATA_UP;
	  DrvSYS_Delay(35); 
	  DrvSYS_Delay(50); 
	 	  if(!GET_DATA)
		  {
	  

	  	while(!GET_DATA);//0=

	   while(GET_DATA);//1=
		   				a=Read_8byte_data(); //ʪ�ȸ�λ
						b=Read_8byte_data();//ʪ��С��
						temperature=Read_8byte_data();//�¶�����
						d=Read_8byte_data(); //�¶�С��
						e=Read_8byte_data(); //У���8bit
						 f=a+b+temperature+d;
				if(f==e) //У����ǲ�����ͬ��ͬ������Ч
				{	

						  
							temperature+=1;//�¶Ȳ���
						temperature_msb=temperature/10; //�¶�
					    temperature_lsb=temperature%10;
                        humidity_msb=a/10; //ʪ��
						humidity_lsb=a%10;
							 

				 }
						  
		  }	 */

		 
		   //У�����
		 return 0;
		 

}
/******************************************************************
 *	ʱ�䣺2012��
 *	���ܣ���HDT11һ���ֽ�
 *	���룺��
 *	��������������ֽ�
 ******************************************************************/
uint8_t   Read_8byte_data(void)
{
			 uint8_t i,k;
			 uint8_t da=0;

			 for(i=0;i<8;i++)
			 {
			 //  __disable_irq();   //closed global interruput
			 while(!GET_DATA) ;//0=
			  // __enable_irq();	//open global interruput
			    
			   DrvSYS_Delay(50); //50US
			  // __disable_irq(); //closed global interruput
				 k=GET_DATA;
				  da=da<<1;
			   if(k==1)
			   {
			   	da=da|0x01;
				while(GET_DATA) ;//1
				
			   
			   }
			   else
			   {
			   
			   	da=da&0xfe;
			
			   
			   }
			 
			 

			   

			 
			 }
			 //__enable_irq();	//open global interruput 

	  return da;

}


extern unsigned long  Systick;
       unsigned long  DHT11ReadTime=0;
void DHT11EventPoll(void)
{
			uint16_t Dht11;
	if(Systick-DHT11ReadTime>=(1000))
	{
	     DHT11ReadTime=Systick;
	 
			  Dht11=  Read_HDT11();
			  if(Dht11>0)	{
		   usSRegHoldBuf[15]=(Dht11>>8)&0xff; //ʪ��
		   usSRegHoldBuf[16]=Dht11&0xff;	  //�¶�
		   usSRegHoldBuf[16]=Dht11;//�洢��ʪ��ֵ

						}

	}


}	