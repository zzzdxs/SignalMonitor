#include "bsp_json.h"

void JSONPack(float number)
{
    static uint8_t ucTemp;
    cJSON * usr;
    char * data;
    int nnumber=1;
    ucTemp=ucTemp+1;
    if(ucTemp>100)
    {
        ucTemp=0;
    }
    //free(data);free(usr);
    usr=cJSON_CreateObject();
    
    cJSON_AddItemToObject(usr,"A",cJSON_CreateNumber(ucTemp));
    cJSON_AddItemToObject(usr,"模拟信号",cJSON_CreateNumber(number));
    cJSON_AddItemToObject(usr,"数字信号",cJSON_CreateNumber(nnumber));
    data=cJSON_Print(usr);
    printf("发送json信息:\n %s",data);

    cJSON_Delete(usr);
    free(data);
	data=NULL;
}


void JSONRecv(char * recv)
{
    cJSON * json, * json1, * json2, * json3;
    json=cJSON_Parse(recv);
    json1=cJSON_GetObjectItem(json,"A");
    json2=cJSON_GetObjectItem(json,"模拟信号");
    json3=cJSON_GetObjectItem(json,"数字信号");
    printf("接收json信息:\n A:%s \n 模拟信号:%f \n 数字信号:%d \n",json1->valuestring,json2->valuedouble,json3->valueint);

    cJSON_Delete(json);
}

