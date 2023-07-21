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

extern char httppack[1024];
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
	printf("以下是ESP8266上电初始化打印信息\n\n");
  */
  //macESP8266_CH_ENABLE();     //记得一定要先使能
  ESP8266_StaTcpClient_Unvarnish_ConfigTest();
  printf("HTTP请求:\n%s\n",httppack);
  macESP8266_Usart( "%s", httppack);
  while(1)
	{	
		ESP8266_CheckRecvDataTest();
  }	

}



/*********************************************END OF FILE**********************/

