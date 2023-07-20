#ifndef __BSP_ESP8266_TCP_H
#define __BSP_ESP8266_TCP_H

#include "stm32f4xx.h"
#include "bsp_esp8266.h"
#include "../usart/bsp_debug_usart.h"
/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "HBIS-WLAN"                //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "hbishbis"           //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP                "172.168.112.71" //"172.168.112.88"  "192.168.0.45"     要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port               "8000"               //要连接的服务器的端口



/********************************** 外部全局变量 *****************'**********************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** 测试函数声明 ***************************************/
void ESP8266_CheckRecvDataTest(void);
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);

#endif
