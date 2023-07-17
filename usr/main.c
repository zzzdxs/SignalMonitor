#include <stm32f4xx.h>
#include <stdio.h>

#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
//#include "./ESP8266/bsp_esp8266.h"
//#include "./ESP8266/bsp_esp8266_test.h"
#include "./dwt_delay/core_delay.h"
#include "./ADC/bsp_adc.h"
#include "./cJSON/cJSON.h"
#include <stdlib.h>

extern __IO uint16_t ADC_ConvertedValue;

int main(void)
{
	CPU_TS_TmrInit();
	Debug_USART_Config();
	//ESP8266_Init();
	LED_GPIO_Config();
	
	LED1_ON;
	CPU_TS_Tmr_Delay_S(2);
	LED1_OFF;
	Usart_SendString(DEBUG_USART,"DEBUG_USART START\n");

	Rheostat_Init();

	float ADC_value=(float) ADC_ConvertedValue;
	printf("%f\n",ADC_value);



	while(1);

}
