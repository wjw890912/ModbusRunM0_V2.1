#ifndef __main_h
#define __main_h



/*ʹ����ʪ�ȴ��������壬��֮*/
#define USE_DHT11 

/*
ʹ��GPRSģ�����壬��֮
ʹ��CO2ģ��MH-14Aģ�����壬��֮
GPRS ��CO2 ͬʱʹ�ô���1����������Ŀǰ�ǻ����
GPRS ��������CO2�����ж��壬����ᶨ��CO2,Ĭ��ʹ��CO2
*/

#define USED_SI4432


//#define USE_GPRS 

#ifndef USE_GPRS
#define USE_CO2 
#endif


/*ʹ��KEY�������壬��֮*/
//#define USE_KEY 
/*ʹ��RELAY�������壬��֮*/
//#define USE_RELAY 


/*
���������ʾʹ��������õ�ַ�����������CO2+DHT11+����Modbus-RTU
#define USE_CO2DHT11_SW_ADDR_BOARD 
���������ʾʹ��Ӳ���������õ�ַ�����������CO2+1~8·Modbus-RTU
#define USE_CO2DHT11RELAY8_HW_ADDR_BOARD
*/

#define USE_CO2DHT11_SW_ADDR_BOARD

//#define USE_CO2DHT11RELAY8_HW_ADDR_BOARD


/*ʹ�ù��մ����� */
#ifdef USE_CO2DHT11_SW_ADDR_BOARD
#define USE_LUX
#endif


#ifdef   USE_LUX
#define  GET_SW_ADDR   //����ӻ���ַ
#else
#define  GET_HW_ADDR   //Ӳ�����뿪��
#endif



#endif