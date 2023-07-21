#ifndef __BSP_HTTP_H
#define __BSP_HTTP_H

#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "../usart/bsp_debug_usart.h"

#define HTTP_HEAD  "POST /api/\"DEVICE_TYPE\"/messages HTTP/1.1\r\n" \
				   "Host: 47.107.99.203:8003\r\n"  \
				   "Connection:keep-alive\r\n"  \
			       "Content-Type: application/json\r\n" \
			       "content-length:1024\r\n\r\n"  

void HTTPPack(char *json,char *httppack);

#endif
