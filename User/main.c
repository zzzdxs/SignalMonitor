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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /* 初始化 */
	float ADC_value;
  Debug_USART_Config ();                                                //初始化USART 配置模式为 115200 8-N-1，中断接收
  CPU_TS_TmrInit();                                                     //初始化DWT计数器 延时函数用到
	ESP8266_Init ();  	//初始化WiFi模块使用的接口和外设
	LED_GPIO_Config();
	Rheostat_Init();
	
	ADC_value=(float) ADC_ConvertedValue/4096*(float)3.3;
	JSONPack(ADC_value);
	CPU_TS_Tmr_Delay_S(1);
	
	/*
	printf("欢迎使用野火STM32开发板\n\n");
	printf("这是一个ESP8266AT指令测试实验\n\n");
	printf("请使用串口调试助手发送\"AT+换行回车\"测试ESP8266是否准备好\n\n");
	printf("更多AT指令请参考模块资料\n\n");
	printf("以下是ESP8266上电初始化打印的信息\n\n");
  */
  //macESP8266_CH_ENABLE();     //记得一定要先使能
  ESP8266_StaTcpClient_Unvarnish_ConfigTest();
  while(1)
	{	
		if(strUSART_Fram_Record .InfBit .FramFinishFlag == 1)  //如果接收到了串口调试助手的数据
		{
			strUSART_Fram_Record .Data_RX_BUF[strUSART_Fram_Record .InfBit .FramLength] = '\0';
			Usart_SendString(macESP8266_USARTx ,strUSART_Fram_Record .Data_RX_BUF);      //数据从串口调试助手转发到ESP8266
			strUSART_Fram_Record .InfBit .FramLength = 0;                                //接收数据长度置零
			strUSART_Fram_Record .InfBit .FramFinishFlag = 0;                            //接收标志置零
	  }
		if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)                             //如果接收到了ESP8266的数据
		{                                                      
			 strEsp8266_Fram_Record .Data_RX_BUF[strEsp8266_Fram_Record .InfBit .FramLength] = '\0';
			 Usart_SendString(DEBUG_USART ,strEsp8266_Fram_Record .Data_RX_BUF);        //数据从ESP8266转发到串口调试助手
			 strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
			 strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
		}
  }	

}



/*********************************************END OF FILE**********************/

