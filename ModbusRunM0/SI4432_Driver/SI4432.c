// File Name:SI4432.C
// Author:СARM�˲�
// Date: 2012��
 //Q Q:925295580

#include <stdio.h>
#include"SI4432.H"
#include "M051Series.h"
#include "main.h"
#include <string.h>
#include "user_mb_app.h"
#include <stdint.h>

#ifdef USED_SI4432
extern  uint8_t tx_timeout_en,tx_timeout;
 uint8_t RSSI;
 extern USHORT   usSRegHoldBuf[S_REG_HOLDING_NREGS] ;
extern unsigned long  Systick;
uint32_t RfTime=0;

 //��ʼ���ӳٺ���
extern void DrvSYS_Delay(uint32_t us);
uint8_t RX_Buf[64];
uint8_t TX_Buf[64];
uint8_t TxSi4432Len=0;
uint8_t RxSi4432Len=0;
unsigned char RE_RSSI(void)
{
	  
	RSSI = spi_rw(0x26, 0x00);
	return RSSI;


}


 signed char  save_rec_data(unsigned char *recbuf_pt)
{
			 uint8_t leg,i;

	

		 if(!GET_NIRQ)
			{
			  i = RE_RSSI();
             clr_interruput_si4432();
		        leg =spi_rw(0x4b,0);              
				SCK_DOWN;
				nSEL_DOWN; 
				spi_byte(0x7f);		
				for(i=0;i<leg;i++)	
				{
					*(recbuf_pt+i) = spi_byte(0x00);
				}
				nSEL_UP;
				spi_rw(0x07|0x80, SI4432_PWRSTATE_READY);	
				  
			   spi_rw(0x03,0x00);; //read the Interrupt Status1 register
               spi_rw(0x04,0x00);; //read the Interrupt Status2 register
			 rx_data();	
			
		      return leg; 
			  }
			
		  	  return 0;
}
 
void clr_interruput_si4432(void)
{

 spi_rw(0x03,0x00);	
 spi_rw(0x04,0x00);	

}

/*����㲥����*/
void ProcesBoadcast(unsigned char *ptr,unsigned char len)
{
	  if(ptr[0]==0xff)
	  {
	   	switch(ptr[1]){
		
					case 0xBB:
					{
					 RfTime=0;//ͬ��ʱ��
				     Systick=0;break;
					 }
					case 0xFF:
					{
					
					  TX_Buf[0]=usSRegHoldBuf[19];
				      TX_Buf[1]=0;
					  TX_Buf[2]=0;
					  TX_Buf[3]=0;
					  TX_Buf[4]=0;
					  TxSi4432Len=5; //����д��Ӧ��

					 break;
					}
		
		}
	  	
	  
	  
	  
	  
	  
	  }




}
/*����������*/
void ProcesMyselfFun(unsigned char *ptr,unsigned char len)
{
			unsigned char addr=0;
			unsigned short  data=0;
			uint8_t i;
			  /*�ӻ���ַ8bit[0]+������8bit[1]+��ʼ��ַ8bit[2]+����MSB8bit[3]+����LSB8bit[4]*
			  

			  10:��д��һ����Ԫ����
			  03���Ƕ�ȡһ����Ԫ����

			  ���磺�������������ݾ�����������
��ȡһ��ID 01 ��0��ַ hold�Ĵ�������
FF AA 02 ��01 03 00 00 00��  AA FF 24 0D 0A

д��һ��ID 01 ��0��ַ hold�Ĵ�������Ϊ0x0234
FF AA 02 ��01 10 00 12 34��  AA FF 24 0D 0A




			  */
	  if(ptr[0]==usSRegHoldBuf[19])//�Ǹ����ǵģ�
	  {
	  		switch(ptr[1]){
			
							 case 0x10:{
									   //д1��Ԫ����

									  addr=	ptr[2];
									  data=ptr[3]<<8;
									  data&=0xff00;
									  data+=ptr[4];

									 usSRegHoldBuf[addr]=data ;	//д��hold�Ĵ�����
									  TX_Buf[0]=usSRegHoldBuf[19];
									  TX_Buf[1]=0x10;
									  TX_Buf[2]=addr;
									  TX_Buf[3]=0;
									  TX_Buf[4]=1;
									  TxSi4432Len=5; //����д��Ӧ��

							 
							 break;}
							 case 0x03:{
							 		  //��ȡһ��Ԫ����


									addr=	ptr[2];
									data = usSRegHoldBuf[addr];
									  TX_Buf[0]=usSRegHoldBuf[19];
									  TX_Buf[1]=0x03;
									  TX_Buf[2]=addr;
									  TX_Buf[3]=data>>8;
									  TX_Buf[4]=data;
									  TxSi4432Len=5; //��������

							 
							 break;}
			
			
			}
	  
	  
	  
	  
	  
	  
	  }



	/*	if(RX_Buf[0]==usSRegHoldBuf[19]) //�Ǳ�����ַ
			{

			

			 TX_Buf[0]=usSRegHoldBuf[19];
			 TX_Buf[1]=2;
			 TX_Buf[2]=3;
			 TX_Buf[3]=4;
			 TX_Buf[4]=5;
			 TxSi4432Len=5;
			
			}
			else 
			if(RX_Buf[0]==0xff)	//�㲥��ַ��Ҫ���ϱ�ID
			{
			 TX_Buf[0]=usSRegHoldBuf[19]; //�ӻ���ַ
			 TX_Buf[1]=0;
			 TX_Buf[2]=0;
			 TX_Buf[3]=0;
			 TX_Buf[4]=RE_RSSI();
			 TxSi4432Len=5;
			 if(RX_Buf[1]==0xbb)
			 {
			 
			   RfTime=0;//ͬ��ʱ��
			   Systick=0;
			   usSRegHoldBuf[32]=usSRegHoldBuf[19]*10+2540;//10ms �ķ�����
			   										   

			 }
			} */

}




void  Si4432Thread(uint32_t t)
{
/*
	  
 ʹ��14�żĴ������洢������̼Ũ��
  usSRegHoldBuf[14]= (UartReciveBuf[2]<<8)+UartReciveBuf[3];//get CO2	MSB and LSB

  (int16_t)usSRegHoldBuf[8];//CO2����,
  
  ʹ��15\16�żĴ������洢��ʪ��DHT11
		   usSRegHoldBuf[15]=(Dht11>>8)&0xff; //ʪ��
		   usSRegHoldBuf[16]=Dht11&0xff;	  //�¶�
  usSRegHoldBuf[17]=m_Lux>>16 ; //��16bit
   	  usSRegHoldBuf[18]=m_Lux ;	  //��16bit

	  �����û�����ù��ĵ�ַĬ����254
�����Ҫ���õ�ֱַ�Ӷ� usSRegHoldBuf[19]����д���ݼ��ɣ�ע����Ч��ַ1-254 �� 

16������PM2.5  ģ��
   �����洢 PM25��PM10ֵ��
 	usSRegHoldBuf[20]= (UartReciveBuf[4]<<8)+UartReciveBuf[5];//get PM25	MSB and LSB
	usSRegHoldBuf[21]= (UartReciveBuf[2]<<8)+UartReciveBuf[3];//get PM10	MSB and LSB
	usSRegHoldBuf[22]�����洢�������Ƿ񿪻��������д1���ػ�д0���ɡ�	Ĭ���ϵ��ǹػ��ġ�	  
	  
*/	  

	if( Check_si4432_HW()==1)	
	{
	




	usSRegHoldBuf[31]=RE_RSSI();//����RSSI ֵ

	RxSi4432Len= save_rec_data(RX_Buf);


		if(RxSi4432Len>0)//���ܵ�����
		{
		   	if(RX_Buf[0]==usSRegHoldBuf[19]) //�Ƿ���ڱ�����ַ��
			 {
			  ProcesMyselfFun(RX_Buf,RxSi4432Len);//��������ַ�¼�
			 }
			 else
			 if(RX_Buf[0]==0xff)		   //�Ƿ�㲥��ַ��
			 {
			 
			  ProcesBoadcast(RX_Buf,RxSi4432Len);//����㲥�¼�
			 }

			RxSi4432Len=0;//ע�������¼�
		}
		else
		if((TxSi4432Len>0)&&(TxSi4432Len<60)) //���������Ҫ����
		{
				  
		   if( usSRegHoldBuf[31]<30){
					  
		   tx_data(TX_Buf,TxSi4432Len);
					TxSi4432Len=0;
						}
						else
						{
					 TxSi4432Len=TxSi4432Len; //�ȴ�����
		   
		                 }
		
		}
	/*	else
		if((RX_Buf[1]==0xaa))	//�Զ��ϱ�ģʽ��һ��ʱ���ϱ�һ������
		{
		
				if(Systick-RfTime>=usSRegHoldBuf[32])
				{
				 //��ʱѭ������
				
					 RfTime=Systick;
			 TX_Buf[0]=usSRegHoldBuf[19]; //�ӻ���ַ
			 TX_Buf[1]=0;;
			 TX_Buf[2]=RE_RSSI();;
			 TX_Buf[3]=RE_RSSI();;
			 TX_Buf[4]=RE_RSSI();
			 TxSi4432Len=5;



				}
		
		}*/						  		  		 
   }




}

void initsi4432(void)
{
	   int k;
	 

	 /* Configure P04-NSEL P07-SCLK P05-MOSI pins */
	 /* Configure P06-MISO pins */
	 /* Configure P03-NIRQ pins */
	 /* Configure P41-SDN pins */

 GPIO_SetMode(P0, BIT7|BIT5|BIT4, GPIO_PMD_QUASI);//si4423 
 GPIO_SetMode(P4, BIT1,GPIO_PMD_QUASI);//si4423 
 GPIO_SetMode(P0, BIT6|BIT3,GPIO_PMD_QUASI);//si4423 


      DrvSYS_Delay(10000);
	  SDN_DOWN;
 	  DrvSYS_Delay(200000);

	   k=spi_rw(0x36, 0);

	  SI4432_init();  
  	  TX0_RX0;
	  k=100+1 ;
	
  
}
 

void rx_data(void)
{	
	  uint8_t k;
	 	  k=k;

		k=spi_rw(0x02, 0);

	spi_rw(0x07|0x80, SI4432_PWRSTATE_READY);
	k=spi_rw(0x07, 0);
	k=spi_rw(0x02, 0);
 	TX0_RX1;	

	spi_rw(0x08|0x80, 0x03);  
	spi_rw(0x08|0x80, 0x00);  
		
	spi_rw(0x07|0x80,SI4432_PWRSTATE_RX );
		k=spi_rw(0x07, 0);   
	spi_rw(0x05|0x80, SI4432_Rx_packet_received_interrupt);  	

		
}		


unsigned char tx_data(unsigned char *pt,unsigned char leg)
{

	unsigned char i,ItStatus,k;
	uint8_t Temp=0,cir=1;
	uint16_t ct=0;
	k=k;
	 
	spi_rw(0x05|0x80, SI4432_PACKET_SENT_INTERRUPT);
 		 
	spi_rw(0x07|0x80, SI4432_PWRSTATE_READY);	// rf ģ�����Ready ģʽ
	k=spi_rw(0x07, 0);
	k=spi_rw(0x02, 0); 	
	TX1_RX0;	
    spi_rw(0x08|0x80, 0x03);   
	spi_rw(0x08|0x80, 0x00); 

	spi_rw(0x34|0x80, 64); // 
	spi_rw(0x3e|0x80, leg); //
  	for (i = 0; i<leg; i++)
	{
		spi_rw(0x7f|0x80,*(pt+i));//
	}
  	 
     spi_rw(0x07|0x80, SI4432_PWRSTATE_TX);

 while(cir==1)
  {
     Temp=spi_rw(0x03,0x00);
     Temp=Temp&0x04;
     if(Temp!=0){cir=0;}
	 /*Operating Modes Response Time see datasheet p20 the TIMEMIN is 200us 
	 but in-severs use we mesurment time is min 350us that in M051 seril MCUs 
	 thus WE need 1000us TIME  make enough time conver Mode
   */
     DrvSYS_Delay(350);
     ct++;
     if(ct>=350){cir=0;}
  }
 
  if(ct>=350)
  {

 	 spi_rw(0x07|0x80,0x01);
	 SI4432_init();
	 rx_data();
     return 0; 	    //  TX sent fail
  }
  else 
  {
     ItStatus = spi_rw(0x03,0x00); //read the Interrupt Status1 register
     ItStatus = spi_rw(0x04,0x00); //read the Interrupt Status2 register
	 //read 03 04 REG by clear tx interruput status 
     spi_rw(0x07|0x80,0x01);	   //tx sent success		  
     SI4432_init();
   	 rx_data();
     return 1;
  }


	 
}

void Si4432RegisterSetV26()
{
 

 //����ʹ��Si4432-Register-Settings_RevV-v26������


   uint8_t RF_Chl= usSRegHoldBuf[20];//ȡ�������λ8bit ͨ����
              spi_rw(0x1c|0x80, 0xac);
			  spi_rw(0x1d|0x80, 0x40);
			
			  spi_rw(0x20|0x80, 0x9c);
			  spi_rw(0x21|0x80, 0x00);
			  spi_rw(0x22|0x80, 0xd1);
			  spi_rw(0x23|0x80, 0xb7);
			  spi_rw(0x24|0x80, 0x00);
			  spi_rw(0x25|0x80, 0x53);
			
			
			  spi_rw(0x30|0x80, 0xac);
			  spi_rw(0x32|0x80, 0x8c);
			  spi_rw(0x33|0x80, 0x02);
			  spi_rw(0x34|0x80, 0x08);
			  spi_rw(0x35|0x80, 0x2a);
			  spi_rw(0x36|0x80, 0x2d);
			  spi_rw(0x37|0x80, 0xd4);
			  spi_rw(0x38|0x80, 0x0);
			  spi_rw(0x39|0x80, 0x0);
			  spi_rw(0x3a|0x80, 0x0);
			  spi_rw(0x3b|0x80, 0x0);
			  spi_rw(0x3c|0x80, 0x0);
			  spi_rw(0x3d|0x80, 0x0);
			  spi_rw(0x3e|0x80, 0x0);
			  spi_rw(0x3f|0x80, 0x0);
			  spi_rw(0x40|0x80, 0x0);
			  spi_rw(0x41|0x80, 0x0);
			  spi_rw(0x42|0x80, 0x0);
			  spi_rw(0x43|0x80, 0xff);
			  spi_rw(0x44|0x80, 0xff);
			  spi_rw(0x45|0x80, 0xff);
			  spi_rw(0x46|0x80, 0xff);
			  spi_rw(0x56|0x80, 0x00);
			
			
			  spi_rw(0x6e|0x80, 0x9d);
			  spi_rw(0x6f|0x80, 0x49);
			
			
			  spi_rw(0x70|0x80, 0x2c);
			  spi_rw(0x71|0x80, 0x2b);
			  spi_rw(0x72|0x80, 0x50);
			
   
	switch(RF_Chl){
		  case 0:{
			 	  //����Ƶ��433.0MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x4b);
			  spi_rw(0x77|0x80, 0x00);
			break;}

		   case 1:{

		   	  //����Ƶ��433.1MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x4d);
			  spi_rw(0x77|0x80, 0x80);
		   
		    break;}
			case 2:{

		   	  //����Ƶ��433.2MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x50);
			  spi_rw(0x77|0x80, 0x00);
		   
		    break;}
			case 3:{

		   	  //����Ƶ��433.3MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x52);
			  spi_rw(0x77|0x80, 0x80);
		   
		    break;}
			case 4:{
			    //����Ƶ��433.4MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x55);
			  spi_rw(0x77|0x80, 0x00);
			
			
			break;}
			case 5:{
				   //����Ƶ��433.5MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x57);
			  spi_rw(0x77|0x80, 0x80);
			break;}
			case 6:{
				  //����Ƶ��433.6MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x5A);
			  spi_rw(0x77|0x80, 0x00);
			break;}
			case 7:{
				   //����Ƶ��433.7MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x5C);
			  spi_rw(0x77|0x80, 0x80);
			break;}
			case 8:{
				 //����Ƶ��433.8MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x5F);
			  spi_rw(0x77|0x80, 0x00);
			break;}
			case 9:{
			    //����Ƶ��433.9MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x61);
			  spi_rw(0x77|0x80, 0x80);
			break;}
			case 10:{
			//����Ƶ��432.0MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x32);
			  spi_rw(0x77|0x80, 0x00);
			break;}
			case 11:{
				//����Ƶ��432.1MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x34);
			  spi_rw(0x77|0x80, 0x80);
			break;}
			case 12:{
				  //����Ƶ��432.2MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x37);
			  spi_rw(0x77|0x80, 0x00);
			break;}
			case 13:{
				//����Ƶ��432.3MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x39);
			  spi_rw(0x77|0x80, 0x80);
			break;}
			case 14:{
			   //����Ƶ��432.4MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x3C);
			  spi_rw(0x77|0x80, 0x00);

			break;}
			case 15:{
			   //����Ƶ��432.5MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x3E);
			  spi_rw(0x77|0x80, 0x80);
			
			break;}
			case 16:{
				//����Ƶ��432.6MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x41);
			  spi_rw(0x77|0x80, 0x00);
			break;}
			case 17:{
			   //����Ƶ��432.7MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x43);
			  spi_rw(0x77|0x80, 0x80);
			break;}
			case 18:{
			   //����Ƶ��432.8MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x46);
			  spi_rw(0x77|0x80, 0x00);
			
			break;}
			case 19:{
				 //����Ƶ��432.9MHZ
			  spi_rw(0x75|0x80, 0x53);
			  spi_rw(0x76|0x80, 0x48);
			  spi_rw(0x77|0x80, 0x80);
			break;}


		 }


 //����ʹ��Si4432-Register-Settings_RevV-v26������


}
//REG����		
void SI4432_init(void)
{

  	clr_interruput_si4432();

	spi_rw(0x06|0x80, 0x00);  //  �رղ���Ҫ���ж�
	
	spi_rw(0x07|0x80, 1);   // ���� Ready ģʽxton=1
	 


	spi_rw(0x09|0x80, 0x64);  //  ���ص���


	spi_rw(0x0a|0x80, 0x05);	// �رյ�Ƶ���
	spi_rw(0x0b|0x80, 0xea);  // GPIO 0 ������ͨ�����
	spi_rw(0x0c|0x80, 0xea);  //GPIO 1 ������ͨ�����
	spi_rw(0x0d|0x80, 0xea);  // /GPIO 2 ����յ�������

	Si4432RegisterSetV26();	

    spi_rw(0x6d|0x80, 0x07);  // set power  00:Min sent power 07:MAX sent Power

    spi_rw(0x79|0x80, 0x0);  // ����Ҫ��Ƶ
    spi_rw(0x7a|0x80, 0x0);  // ����Ҫ��Ƶ		  
}

 //check the SI4432 chip is connect to us or check the SPI conmmucation is ok 
 unsigned char Check_si4432_HW(void)
 {
 	 unsigned char state;
	state = spi_rw(0,0);//read chip ID that always is 0X08 more ref SII443x datasheet REG discription  
    if(state!=0x08) 
	{
		return 0; // no device or the SPI read fail 
	}

	 return 1;	  // the chip is running fine  
 }

 /*
   read 8bit data 
 
 */
unsigned char spi_byte(unsigned char data)
{

	unsigned char i;
	
	for (i = 0; i < 8; i++)		// ����SCK �� SDI������һ���ֽڵ����ͬ�¶�ȡ1���ֽڵ�����
	{				// û�а���nSEL�Ŀ���
		if (data & 0x80)
			SDI_UP;
		else
			SDI_DOWN;
			
		data <<= 1;
		SCK_UP;
		
		if (GET_SDO)
			data |= 0x01;
		else
			data &= 0xfe;
			
		SCK_DOWN;
	}
	
	return (data);
}

/*--------------------
  read/write by SPI function  NOW we just used SI4432 SPI
  eg:
  write: spi_rw(reg|0x80, data)
  reade: data = spi_rw(reg, 0)

-----------------------*/
unsigned char spi_rw(unsigned char addr, unsigned char data)
{

	unsigned char i;
	SCK_DOWN;
	nSEL_DOWN;
	
	for (i = 0; i < 8; i++) 
	{
		if (addr & 0x80)
			SDI_UP;
		else
			SDI_DOWN;
		addr <<= 1;
		SCK_UP;
	
		SCK_DOWN;
	 
	}
	  // 	DrvSYS_Delay(2);

	for (i = 0; i < 8; i++) 
	{
		if (data & 0x80)
			SDI_UP;
		else
			SDI_DOWN;
		data <<= 1;
		SCK_UP;
		if (GET_SDO)
			data |= 0x01;
		else
			data &= 0xfe;
		 
		SCK_DOWN;
	}
	nSEL_UP;
	SCK_UP;
	return data;
}

#endif