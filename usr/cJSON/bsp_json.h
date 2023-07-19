#ifndef __BSP_JSON_H
#define __BSP_JSON_H

#include "stm32f4xx.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include "../usart/bsp_debug_usart.h"

void JSONPack(float number);
void JSONRecv(char * recv);


#endif
