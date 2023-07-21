#include "./HTTP/bsp_HTTP.h" 

void HTTPPack(char * json, char *httppack)
{
    sprintf(httppack,"%s",HTTP_HEAD);
    strcat(httppack,json);
    printf(httppack);
}

