#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./esp8266/bsp_esp8266.h"
#include "./dwt_delay/core_delay.h"   
#include "./ESP8266/bsp_esp8266_tcp.h"
#include "./cJSON/bsp_json.h"
#include <stdio.h>
#include <stdlib.h>
#include "./led/bsp_led.h"
#include "./ADC/bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue;
extern char Data_RX[RX_BUF_MAX_LEN];
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /* ��ʼ�� */
	float ADC_value;
  Debug_USART_Config ();                                                //��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���
  CPU_TS_TmrInit();                                                     //��ʼ��DWT������ ��ʱ�����õ�
	ESP8266_Init ();  	//��ʼ��WiFiģ��ʹ�õĽӿں�����
	LED_GPIO_Config();
	Rheostat_Init();
	
	ADC_value=(float) ADC_ConvertedValue/4096*(float)3.3;
	JSONPack(ADC_value);
	CPU_TS_Tmr_Delay_S(1);
	
	/*
	printf("��ӭʹ��Ұ��STM32������\n\n");
	printf("����һ��ESP8266ATָ�����ʵ��\n\n");
	printf("��ʹ�ô��ڵ������ַ���\"AT+���лس�\"����ESP8266�Ƿ�׼����\n\n");
	printf("����ATָ����ο�ģ������\n\n");
	printf("������ESP8266�ϵ��ʼ����ӡ����Ϣ\n\n");
  */
  //macESP8266_CH_ENABLE();     //�ǵ�һ��Ҫ��ʹ��
  ESP8266_StaTcpClient_Unvarnish_ConfigTest();
  while(1)
	{	
		if(strUSART_Fram_Record .InfBit .FramFinishFlag == 1)  //������յ��˴��ڵ������ֵ�����
		{
			strUSART_Fram_Record .Data_RX_BUF[strUSART_Fram_Record .InfBit .FramLength] = '\0';
			Usart_SendString(macESP8266_USARTx ,strUSART_Fram_Record .Data_RX_BUF);      //���ݴӴ��ڵ�������ת����ESP8266
			strUSART_Fram_Record .InfBit .FramLength = 0;                                //�������ݳ�������
			strUSART_Fram_Record .InfBit .FramFinishFlag = 0;                            //���ձ�־����
	  }
		if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)                             //������յ���ESP8266������
		{                                                      
			 strEsp8266_Fram_Record .Data_RX_BUF[strEsp8266_Fram_Record .InfBit .FramLength] = '\0';
			 Usart_SendString(DEBUG_USART ,strEsp8266_Fram_Record .Data_RX_BUF);        //���ݴ�ESP8266ת�������ڵ�������
			 strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //�������ݳ�������
			 strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //���ձ�־����
		}
  }	

}



/*********************************************END OF FILE**********************/

