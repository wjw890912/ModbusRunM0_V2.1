
/*
******************************
*
*
*  ��Э��C����ʵ��
*
*	2013��5��11��
*
*	СARM�˲�
*
*
*******************************
*/
#include "stm32f10x.h"
unsigned char Data_Stream_Tx_Buf[5]={0};//�����������������
unsigned char Data_stream_Rx_Buf[5]={0};//�������������뻺��



 struct switch_struct
 {
 
   uint8_t Channel_number; //ͨ����
   uint8_t state;  //��״̬
   uint8_t Spare;  //����
 
 };

struct Protocol_Structure
{

  uint16_t  dst;  //Ŀ���ַ
  uint16_t  src;  //Դ��ַ
  uint8_t  dev_type; //�豸����
  struct switch_struct s;

};



/*
  ����ֵ�� ָ�����ݺ�������ָ��
  ���룺   �ṹ�����ͻ���
  ���ܣ�	 һ����װ���ܵ�СС����һ��
  ������This functionality is encapsulated data stream and intends to send the next step, 
        and returns a pointer to a pointer to the data to be transmitted handle by СARM�˲�

*/
uint8_t *Package_Data_Stream(struct Protocol_Structure*pbuf,uint8_t *buf)
{
				 uint16_t dst,src;
				 uint8_t  lsb,msb;
				 uint8_t  lsb1,msb1;
				 uint8_t  type;
				 uint8_t  chnl;
				 uint8_t state;
                 uint8_t temp;
				
			 //��ʼ��.......
				dst=pbuf->dst;
				dst&=0x0fff;
			
				src=pbuf->src;			//��ȡ����������
				src&=0x0fff;


				lsb=dst;
				msb=(dst>>8)&0x00ff;
				msb<<=4;   //Դ��ַ����λ��ǰ�����ֽ�

			    lsb1=src;
				msb1=(src>>8)&0x00ff;

				temp=msb+msb1;//�������

				//�ڽ���ʱҪע��˴�������߼�

				*buf=lsb;  //��8λĿ���ַ
				*(buf+1)=temp; //��4λĿ���Դ�����
				*(buf+2)=lsb1; //��8λԴ��ַ



			    type  =	pbuf->dev_type;
				type&=0x07;

				chnl  =	 pbuf->s.Channel_number;
				chnl &=	0x07;

				state =	pbuf->s.state;
				state &=0x03;

				 temp=0;

				 temp= (type<<5)+(chnl<<2)+state;

				*(buf+3)=temp; //D3����
				*(buf+4)='W'; //D4���ݱ���
				return buf;

}
  /*
  ����ֵ�� ��
  ���룺   �ṹ�����ջ���
  ���ܣ�	 һ�����װ���ܵ�СС����һ��
  ������Solution will match the data packet processing, 
        and reported to the application layer data by СARM�˲�

*/
void  Unpack_data_stream (struct Protocol_Structure*pbuf,uint8_t *buf)
  {
  
  
				 uint16_t dst,src;
				 uint8_t  lsb,msb;
				 uint8_t  lsb1,msb1;
				 uint8_t  type;
				 uint8_t  chnl;
				 uint8_t state;
                 uint8_t temp;




				lsb=*buf;  //��8λĿ���ַ
				temp=*(buf+1); //��4λĿ���Դ�����
			    lsb1=*(buf+2); //��8λԴ��ַ

			   msb=(temp>>4)&0x0f;
			   msb1=temp&0x0f;

				dst=(uint16_t)msb+lsb;
				src=(uint16_t)msb1+lsb1;

				   pbuf->dst=dst;
			       pbuf->src=src;


				temp=*(buf+3);

				 type  = (temp>>5)&0x7;

				 chnl  = (temp>>2)&0x7;
		
				 state = (temp)&0x3;

				
				 pbuf->dev_type  =  type ;
				 pbuf->s.Channel_number = chnl;
				 pbuf->s.state = state;

  
  }





















