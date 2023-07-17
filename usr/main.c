#include <stm32f4xx.h>
#include <stdio.h>

#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
//#include "./ESP8266/bsp_esp8266.h"
//#include "./ESP8266/bsp_esp8266_test.h"
#include "./dwt_delay/core_delay.h"


int main(void)
{
	CPU_TS_TmrInit();
	Debug_USART_Config();
	//ESP8266_Init();
	LED_GPIO_Config();
	
	LED1_ON;
	CPU_TS_Tmr_Delay_S(2);
	LED1_OFF;
	Usart_SendString(DEBUG_USART,"DEBUG_USART TEST\n");
	while(1);

}
