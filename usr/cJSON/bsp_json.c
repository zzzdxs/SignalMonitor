#include "stm32f4xx.h"
#include "cJSON.h"

void JSONPack(float number)
{
    uint8_t ucTemp;
    cJSON * usr;
    char * data;
    ucTemp=ucTemp+1;
    if(ucTemp>100)
    {
        ucTemp=0;
    }

    usr=cJSON_CreateObject();
    cJSON_AddItemToObject(usr,"模拟数字",cJSON_CreateNumber(ucTemp));
    cJSON_AddItemToObject(usr,"模拟信号",cJSON_CreateNumber(number));
    cJSON_AddItemToObject(usr,"测试",cJSON_CreateString("okk"));
    data=cJSON_Print(usr);
    printf("%s",data);

    cJSON_Delete(usr);
    free(data);

}

void JSONRecv()
{}