#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>

#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./dwt_delay/core_delay.h"
#include "./ADC/bsp_adc.h"
//#include "./ESP8266/bsp_esp8266.h"
//#include "./ESP8266/bsp_esp8266_test.h"

#include "./cJSON/bsp_json.h"
//#include "./cJSON/test.h"

extern __IO uint16_t ADC_ConvertedValue;
extern char Data_RX[RX_BUF_MAX_LEN];
int main(void)
{
	//char* out="{\"A\":\"long\",\"模拟信号\":\"2\",\"数字信号\":3}";
	
	//u8 Res;
	CPU_TS_TmrInit();
	Debug_USART_Config();
	//ESP8266_Init();
	LED_GPIO_Config();
	/*
	LED1_ON;
	CPU_TS_Tmr_Delay_S(2);
	LED1_OFF;
	*/
	
	Usart_SendString(DEBUG_USART,"DEBUG_USART START\n");

	Rheostat_Init();
	//create_objects();
	float ADC_value=(float) ADC_ConvertedValue/4096*(float)3.3;
	JSONPack(ADC_value);
	CPU_TS_Tmr_Delay_S(1);

	/*printf("%s\n",out);
	JSONRecv(out);*/
	while(1)
	{
	}

}
