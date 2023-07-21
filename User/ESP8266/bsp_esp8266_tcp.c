#include "bsp_esp8266_tcp.h"

volatile uint8_t ucTcpClosedFlag = 0;


/*
ESP8266透传准备：
无线网 ssid+password+安全模式
TCP 协议类型TCP/UDP+连接类型client+目的IP+目的端口
串口参数 波特率+数据位+校验位+停止位+硬件流控*/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
  printf( "\r\n正在配置 ESP8266 ......\r\n" );
  printf( "\r\n使能 ESP8266 ......\r\n" );
	macESP8266_CH_ENABLE();                                //CH-PE2-WIFI_EN
	while( ! ESP8266_AT_Test() );                //"AT" 
  while( ! ESP8266_DHCP_CUR () );              //AT+CWDHCP_CUR=1,1
  printf( "\r\n正在配置工作模式 STA ......\r\n" );
	while( ! ESP8266_Net_Mode_Choose ( STA ) );   //"AT+CWMODE=3"

  printf( "\r\n正在连接 WiFi ......\r\n" );
  while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	//"AT+CWJAP="SSID","PASSWORD""
	
  //printf( "\r\n 禁止多连接 ......\r\n" );
	while( ! ESP8266_Enable_MultipleId ( DISABLE ) );  //"AT+CIPMUX=0"
	
  printf( "\r\n正在连接 Server ......\r\n" );
	while( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	//"AT+CIPSTART=TCP,"IP",PORT"
  //printf( "\r\n进入透传发送模式 ......\r\n" );
	while( ! ESP8266_UnvarnishSend () );//"AT+CIPMODE=1"  "AT+CIPSEND"
	
	printf( "\r\n配置 ESP8266 完毕\r\n" );
	printf ( "\r\n开始透传......\r\n" );
  
}
/**
  * @brief  ESP8266 检查是否接收到了数据，检查连接和掉线重连
  * @param  无
  * @retval 无
  */
void ESP8266_CheckRecvDataTest(void)
{
  uint8_t ucStatus;
  uint16_t i;
  
  /* 如果接收到了串口调试助手的数据 */
  if(strUSART_Fram_Record.InfBit.FramFinishFlag == 1)
  {
	  for(i = 0;i < strUSART_Fram_Record.InfBit.FramLength; i++)
    {
       USART_SendData( macESP8266_USARTx ,strUSART_Fram_Record.Data_RX_BUF[i]); //转发给ESP82636
       while(USART_GetFlagStatus(macESP8266_USARTx,USART_FLAG_TC)==RESET){}      //等待发送完成
    }  
    strUSART_Fram_Record .InfBit .FramLength = 0;                                //接收数据长度置零
    strUSART_Fram_Record .InfBit .FramFinishFlag = 0;                            //接收标志置零
  }
  
  /* 如果接收到了ESP8266的数据 */
  if(strEsp8266_Fram_Record.InfBit.FramFinishFlag)
  {                                                     
    for(i = 0;i < strEsp8266_Fram_Record .InfBit .FramLength; i++)               
    {
       USART_SendData( DEBUG_USART ,strEsp8266_Fram_Record .Data_RX_BUF[i]);    //转发给ESP8266
       while(USART_GetFlagStatus(DEBUG_USART,USART_FLAG_TC)==RESET){}
    }
    strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
    strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
  }
  if ( ucTcpClosedFlag )                                             //检测是否失去连接
  {
    ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //确认失去连接后重连
    {
      printf ( "\r\n正在重连热点和服务器 ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      printf ( "\r\n重连热点和服务器成功\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
 
  
    
  } 
}

