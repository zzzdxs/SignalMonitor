#include "bsp_json.h"

void JSONPack(float number)
{
    uint8_t ucTemp;
    cJSON * usr;
    char * data;
    double nnumber=1.234;
    ucTemp=ucTemp+1;
    if(ucTemp>100)
    {
        ucTemp=0;
    }
    
    usr=cJSON_CreateObject();
    cJSON_AddItemToObject(usr,"A",cJSON_CreateNumber(ucTemp));
    cJSON_AddItemToObject(usr,"≤‚ ‘",cJSON_CreateNumber(number));
    cJSON_AddItemToObject(usr,"name",cJSON_CreateString("ok"));
    cJSON_AddItemToObject(usr,"1234",cJSON_CreateNumber(nnumber));
    data=cJSON_Print(usr);
    printf("%s",data);

    cJSON_Delete(usr);
    free(data);

}


void JSONRecv(void)
{
    printf("test\n");
}

