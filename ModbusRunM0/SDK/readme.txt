






	  ������־

 MODBUS RTU ��Ҫ����˻���RS485�� M0�ϵĲ�Ʒ�������д��
 �����Ѿ�˳������ ARM ��˾�� M3�ں�CPU��M4�ں�CPU���У�
 ����M4�ں�CPU��MODBUS ���Ѿ�������Ŀ��ȥ�ˡ�

1����ֲMODBUS1.60��M051ϵ���ϡ�
1�����޸�MODBUSЭ��ջ���ϲ�Ӧ����Ȧ�ͱ��ּĴ���ȫ����Ϊ8���ֽ�
/* -----------------------Slave Defines -------------------------------------*/
#define S_DISCRETE_INPUT_START        1
#define S_DISCRETE_INPUT_NDISCRETES   8
#define S_COIL_START                  1
#define S_COIL_NCOILS                 8
#define S_REG_INPUT_START             1
#define S_REG_INPUT_NREGS             8
#define S_REG_HOLDING_START           1
#define S_REG_HOLDING_NREGS           8
/* -----------------------Master Defines -------------------------------------*/
#define M_DISCRETE_INPUT_START        1
#define M_DISCRETE_INPUT_NDISCRETES   8
#define M_COIL_START                  1
#define M_COIL_NCOILS                 8
#define M_REG_INPUT_START             1
#define M_REG_INPUT_NREGS             8
#define M_REG_HOLDING_START           1
#define M_REG_HOLDING_NREGS           8
2�����޸Ķ�ʱ���ļ�������20KHZ�Ķ�ʱ��1.
3�����޸Ĵ����շ��Լ����Ϳ��жϺͽ����жϡ�
4����Ԥ��������Ϊ9600  NONEУ�� ����λ8 ֹͣ1 
20160902

2��Ӳ����ʹ�õ����ڱ��ص�����Ƶ�4·�ƿؼ̵�����PCB�塣
1��RS485�������Զ��ģ������ǿ��·��Ҧ��ԭ������ƣ������⡣
���͵�ʱ����տ����յ������ֽڡ�����������MODBUSЭ��ջ���ϱ�һ������Ĵ��롣
����ѭ�������������ͷ籩����������·�޸��˴�����쳣�����֣���ǿ�ƹرմ���MODBUS�����ϱ���
ֵ��ע����ǣ������Լ��������Ӧ��ȥ������Ķ�����Ϊ�ҵ��Ǹ���·��OK�ġ����޸�Ҳ���Ե��Ǿ�û���˴�����ϵĹ��ܡ�
�޸���
/* If the request was not sent to the broadcast address we
             * return a reply. */
            if( ucRcvAddress != MB_ADDRESS_BROADCAST )
            {
                if( eException != MB_EX_NONE )
                {
                    /* An exception occured. Build an error frame. */
                    usLength = 0;
                    ucMBFrame[usLength++] = ( UCHAR )( ucFunctionCode | MB_FUNC_ERROR );
                    ucMBFrame[usLength++] = eException;
					break;
					/*��Ϊ����ӦҦ����·�����ķ��ͽ��տ����յ��������ղ�ȫ����
					���break��Ϊ�˱���MODBUS���յ��������ݶ��ϱ�����״̬�롣
					���Լ����Զ��շ���·�����޸ġ�
                	*/
				}
                eStatus = peMBFrameSendCur( ucMBAddress, ucMBFrame, usLength );


����Ĵ�����м�����һ��break���Ǵ�����ǰ������:)


2����ʹ��MODBUS poll ���ж�ȡHOLD�Ĵ���ֵ0-5 OK ����OK ��
20160902



3�����Ӵű��̵ּ�����������ͨ���޸�HOLD�Ĵ�������4·�̵����Ŀ�ܳ����ļ� realyctrl.c
ʹ�õ�PCB��Ϊ���ؿ�����GLCS207-ER4GS T1 V1

 usSRegHoldBuf[0] ֵ��0��ʾ��һ·�ű��̵ּ����ر� 1��ʾ��1·�̵�����
 usSRegHoldBuf[1] ֵ��0��ʾ��һ·�ű��̵ּ����ر� 1��ʾ��2·�̵�����
 usSRegHoldBuf[2] ֵ��0��ʾ��һ·�ű��̵ּ����ر� 1��ʾ��3·�̵�����
 usSRegHoldBuf[3] ֵ��0��ʾ��һ·�ű��̵ּ����ر� 1��ʾ��4·�̵�����

 20160907

 3�����Ӵӻ���ַ�����ã���Ӳ���ı��뿪�ض�ȡ������Ϊ��ַʹ�á�
 ����2����ֱ�֧��2����ͬ��PCB�������
 /*

#define GTLCS207_ER4GS_V1  ʹ��PCB��Ϊ���ؿ����� GTLCS207-ER4GS MB V1  ��4·�ű��̵ּ�������

*/
//#define GTLCS207_ER4GS_V1
#define GTRMS107_ER4AS_V10

 20160908

4�����Ӷ԰���������ӳ�䡣�ֱ����Ĵ������¡�ʹ�ö�ȡ�Ĵ����Ϳ��Ի�ȡ�ⲿ������״̬

		/*sample key data in idle*/
	usSRegHoldBuf[10] = P17;
	usSRegHoldBuf[11] = P16;
	usSRegHoldBuf[12] = P15;
	usSRegHoldBuf[13] = P14;
20160909

5���޸�����̵�����IO��λ���޸ı��뿪�صĽ�λ������޸���Ϊ��Ϊ�����̵����������ġ������Լ��İ��ӣ����ͣ�
GTRMS107_ER4AS_V10���������
201707


6������C02�������ӿڣ����������ڽӿڣ��ļ�Uart3th.c��Uart3th.h

  CO2������ʹ��MH-Z14A������MH-Z14���Աȷ���ƫ��Լ200ppm,�����������۲����

  ʹ��14�żĴ������洢������̼Ũ��
  usSRegHoldBuf[14]= (UartReciveBuf[2]<<8)+UartReciveBuf[3];//get CO2	MSB and LSB

  (int16_t)usSRegHoldBuf[8];//CO2����,

20180318

7������DHT11��������

   ʹ��15\16�żĴ������洢��ʪ��DHT11
		   usSRegHoldBuf[15]=(Dht11>>8)&0xff; //ʪ��
		   usSRegHoldBuf[16]=Dht11&0xff;	  //�¶�
		   usSRegHoldBuf[16]=Dht11;//�洢��ʪ��ֵ


20180320

8���޸�8·�̵����ͱ��뿪���Լ�KEY4·������Ӳ��������ַ������CO2+1-8·MODBUS-RTU����
	 usSRegHoldBuf[0] ֵ��0��ʾ��1·�̵����� 1��ʾ��1·�̵�����
	 usSRegHoldBuf[1] ֵ��0��ʾ��2·�̵����� 1��ʾ��2·�̵�����
	 usSRegHoldBuf[2] ֵ��0��ʾ��3·�̵����� 1��ʾ��3·�̵�����
	 usSRegHoldBuf[3] ֵ��0��ʾ��4·�̵����� 1��ʾ��4·�̵�����
	 usSRegHoldBuf[4] ֵ��0��ʾ��5·�̵����� 1��ʾ��5·�̵�����
	 usSRegHoldBuf[5] ֵ��0��ʾ��6·�̵����� 1��ʾ��6·�̵�����
	 usSRegHoldBuf[6] ֵ��0��ʾ��7·�̵����� 1��ʾ��7·�̵�����
	 usSRegHoldBuf[7] ֵ��0��ʾ��8·�̵����� 1��ʾ��8·�̵�����



1·��
7165989-Tx:01 10 00 00 00 01 02 00 01 67 90 
7165990-Rx:01 10 00 00 00 01 01 C9 
2·��
7165991-Tx:01 10 00 01 00 01 02 00 01 66 41 
7165992-Rx:01 10 00 01 00 01 50 09 
3·��
7165993-Tx:01 10 00 02 00 01 02 00 01 66 72 
7165994-Rx:01 10 00 02 00 01 A0 09 
4·��
7165995-Tx:01 10 00 03 00 01 02 00 01 67 A3 
7165996-Rx:01 10 00 03 00 01 F1 C9 
5·��
7165997-Tx:01 10 00 04 00 01 02 00 01 66 14 
7165998-Rx:01 10 00 04 00 01 40 08 
6·��
7165999-Tx:01 10 00 05 00 01 02 00 01 67 C5 
7166000-Rx:01 10 00 05 00 01 11 C8 
7·��
7166001-Tx:01 10 00 06 00 01 02 00 01 67 F6 
7166002-Rx:01 10 00 06 00 01 E1 C8 
8·��
7166003-Tx:01 10 00 07 00 01 02 00 01 66 27 
7166004-Rx:01 10 00 07 00 01 B0 08 

1·�ر�
7166005-Tx:01 10 00 00 00 01 02 00 00 A6 50 
7166006-Rx:01 10 00 00 00 01 01 C9 
2·�ر�
7166007-Tx:01 10 00 01 00 01 02 00 00 A7 81 
7166008-Rx:01 10 00 01 00 01 50 09 
3·�ر�
7166009-Tx:01 10 00 02 00 01 02 00 00 A7 B2 
7166010-Rx:01 10 00 02 00 01 A0 09 
4·�ر�
7166011-Tx:01 10 00 03 00 01 02 00 00 A6 63 
7166012-Rx:01 10 00 03 00 01 F1 C9 
5·�ر�
7166013-Tx:01 10 00 04 00 01 02 00 00 A7 D4 
7166014-Rx:01 10 00 04 00 01 40 08 
6·�ر�
7166015-Tx:01 10 00 05 00 01 02 00 00 A6 05 
7166016-Rx:01 10 00 05 00 01 11 C8 
7·�ر�
7166017-Tx:01 10 00 06 00 01 02 00 00 A6 36 
7166018-Rx:01 10 00 06 00 01 E1 C8 
8·�ر�
7166019-Tx:01 10 00 07 00 01 02 00 00 A7 E7 
7166020-Rx:01 10 00 07 00 01 B0 08 

ȫ����
7166021-Tx:01 10 00 00 00 08 10 00 01 00 01 00 01 00 01 00 01 00 01 00 01 00 01 6E 20
7166022-Rx:01 10 00 00 00 08 C1 CF
ȫ�أ�
7166023-Tx:01 10 00 00 00 08 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 19 CD
7166024-Rx:01 10 00 00 00 08 C1 CF


20180320

9������GPRSģ�飬����������ӣ����Գ�һ��Ū��Ŀǰ�Ѿ���ͨ����ATָ������ӵ���������DEMO�����滹���޸ġ�
20180401
10������main.h�ļ�������δ������������ģ��̫�ࡣ��������صĶ��ƣ����������涨��һЩ�꣬��������Щ����ѡ��
��Ҫ�������У�ά��һ������
20180402
11���޸�KEYɨ�貿�֣��޸�ΪKey�����Ƽ̵���1-4·������·��ֻ��ͨ��MODBUS����
    �߼��ǣ�����̵�����ǰ�ǿ�������ô����֮��رգ������ǰ�ǹرգ���ô����֮���ǿ�����
	MCU���ǵ͵�ƽ��Ч�����ˣ�getbutton ��ʱ����1�ˣ����ǰ��������£��ĳɣ�GETBUTTON
20180402
12������I2C�ӿڹ��մ�����
����ֵ��
	  usSRegHoldBuf[17]=m_Lux>>16 ; //��16bit
   	  usSRegHoldBuf[18]=m_Lux ;	  //��16bit

	  ��λ����ȡ��֮����Ҫ/1000

���洢
���յĲ�����Ҫ��main.h���涨��ĺ꿪�أ��ͼ̵���ģ���HW��ַ�趨��
20180403

13������FMC�������洢����趨�ӻ���ַ��

�����û�����ù��ĵ�ַĬ����254
�����Ҫ���õ�ֱַ�Ӷ� usSRegHoldBuf[19]����д���ݼ��ɣ�ע����Ч��ַ1-254 ��
������ϵ�ַ�������Զ�������ִ���µ�ַ,
static uint8_t newid=0,oldid=0;
uint8_t InitSlaveAddr()
{
   uint32_t u32d;
	    /* Enable FMC ISP function */
    FMC_Open();
 u32d = FMC_ReadData(DATA_FLASH_TEST_BASE);

	    /* Disable FMC ISP function */
    FMC_Close();
	 if(u32d==0xffffffff)
	 {
	 	 usSRegHoldBuf[19]=254 ;
		 newid=254;
		 oldid=254;	//ͬ��
	 	 return 254;//Ĭ�Ͽյĵ�ַΪ1
	 }
	 else
	 {
	 	  usSRegHoldBuf[19]=u32d ;
		  newid=u32d;
		  oldid=u32d;//ͬ��
	 	 return  u32d;//���ش洢�ĵ�ַ
	 }



}

void SlaveAddrPoll()
{
  

     newid=	usSRegHoldBuf[19]; //��Ч��ַ1-254 ��

			if (newid!=oldid)
			{
				if((usSRegHoldBuf[19]<255)&&(usSRegHoldBuf[19]>0)) //��ַ�����Գ���254������������Ч
				{
			   SaveUserSlaveAddr(usSRegHoldBuf[19]&0x00ff);	//�߰�λ����
			    }
			
				   oldid=newid;
			}
}


20180403


14��ʹ����һ�����ӱ���꿪�أ���main.h��  Ĭ���Ƕ���Ӳ�����뿪�صļ̵�������

/*
���������ʾʹ��������õ�ַ�����������CO2+DHT11+����Modbus-RTU
#define USE_CO2DHT11_SW_ADDR_BOARD 
���������ʾʹ��Ӳ���������õ�ַ�����������CO2+1~8·Modbus-RTU
#define USE_CO2DHT11RELAY8_HW_ADDR_BOARD
*/

//#define USE_CO2DHT11_SW_ADDR_BOARD

#define USE_CO2DHT11RELAY8_HW_ADDR_BOARD
20180405
15��������һ��UART1��UART2���ж����ȼ���UART1��ԭ����3����Ϊ2��UART0��ԭ����2����Ϊ3
Ϊ�˹��MOdbus���ٶ�ȡ����ʱ ��UART1�ĳ�ͻ����ɵ�Modbus��֡
20180406

16��������SI4432�Լ�Э�����
20180805
17\usSRegHoldBuf[20]�����洢����Ƶ����
20180815
