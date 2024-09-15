#include "bsp_esp8266.h"
#include "bsp.h"

uint8_t *sub_buf;
uint8_t usart2_flag;




/*********************************************************
 *
 *pdata: pointer of data for send
 *len:  len of data to be sent
 *return: the len of data send success
 * @brief hal api for at data send
***********************************************************/
uint8_t at_send_data(uint8_t* pdata, uint16_t len)
{
	if(HAL_OK == HAL_UART_Transmit(&huart2, pdata, len, 0xffff))
	{
		return len;
	}
	else
	{
		return 0;
	}	
}


/****************************************************************************************************
**
*Function Name:static void initBtleModule(void)
*Function: 
*Input Ref: 
*Return Ref:NO
*
****************************************************************************************************/
void auto_link_tencent_cloud_fun(void)
{


   switch(wifi_t.auto_link_tencent_step){

   case 0:

	WIFI_IC_ENABLE();
   
	  // at_send_data("AT+RESTORE\r\n", strlen("AT+RESTORE\r\n"));
	   at_send_data("AT+RST\r\n", strlen("AT+RST\r\n"));
       HAL_Delay(1000);

	  wifi_t.auto_link_tencent_step=1;
      wifi_t.gTimer_power_first_link_tencent=0;

    break;

    case 1:
    
	if(wifi_t.gTimer_power_first_link_tencent > 1 ){
	   wifi_t.gTimer_power_first_link_tencent=0;
	    wifi_t.auto_link_tencent_step=2;
	   
	   

	}
    break;
    
    case 2:

    wifi_t.linking_tencent_cloud_doing =1; //enable usart2 receive wifi  data
    wifi_t.wifi_uart_counter=0;
	wifi_t.soft_ap_config_flag =0;
  
   wifi_t.auto_link_tencent_step =3;

   break;

   case 3:
  
        HAL_UART_Transmit(&huart2, "AT+TCMQTTCONN=1,5000,240,0,1\r\n", strlen("AT+TCMQTTCONN=1,5000,240,0,1\r\n"), 0xffff);//开始连接
       HAL_Delay(1000);
       wifi_t.gTimer_power_first_link_tencent=0;
	
      wifi_t.auto_link_tencent_step=4; //4

   break;

   case 4:
	if(wifi_t.gTimer_power_first_link_tencent >4 ){
		wifi_t.gTimer_power_first_link_tencent=0;
		wifi_t.auto_link_tencent_step=0xff; //5
	

		if(wifi_link_net_state()==1){
			wifi_t.linking_tencent_cloud_doing =0;
	    }

	}
    break;

    }

}

/****************************************************************************************************
**
*Function Name:void Wifi_Link_SmartPhone_Fun(void)
*Function: dy
*Input Ref: 
*Return Ref:NO
*
****************************************************************************************************/
void SmartPhone_LinkTencent_Cloud(void)
{
   
    if(wifi_t.soft_ap_config_success==1){

       wifi_t.soft_ap_config_success++;
	   wifi_t.gTimer_login_tencent_net=0;
       gpro_t.gTimer_get_data_from_tencent_data=0;
	    HAL_UART_Transmit(&huart2, "AT+TCMQTTCONN=1,5000,240,0,1\r\n", strlen("AT+TCMQTTCONN=1,5000,240,0,1\r\n"), 5000);//开始连接
	    HAL_Delay(1000);
	

	}

    if(wifi_t.gTimer_login_tencent_net >3 && (wifi_t.soft_ap_config_success==2)){
	   	  wifi_t.gTimer_login_tencent_times =0;
	     if(wifi_link_net_state()==1){
			   
				wifi_t.get_rx_beijing_time_enable=0;
			    
            }
        
    }
	
}



void wifi_Disconnect_Fun(void)
{

  HAL_UART_Transmit(&huart2, "AT+TCMQTTDISCONN\r\n", strlen("AT+TCMQTTDISCONN\r\n"), 5000);//开始连接

}

void Get_BeiJing_Time_Cmd(void)
{

 // HAL_UART_Transmit(&huart2, "AT+CIPSNTPCFG=1,8,\"cn.ntp.org.cn\",\"ntp.sjtu.edu.cn\"\r\n", strlen("AT+CIPSNTPCFG=1,8,\"cn.ntp.org.cn\",\"ntp.sjtu.edu.cn\"\r\n"), 5000);//开始连接
    HAL_UART_Transmit(&huart2, "AT+CIPSNTPCFG=1,8\r\n", strlen("AT+CIPSNTPCFG=1,8\r\n"), 5000);//开始连接

}

void Get_Beijing_Time(void)
{

   HAL_UART_Transmit(&huart2, "AT+CIPSNTPTIME?\r\n", strlen("AT+CIPSNTPTIME?\r\n"), 5000);//开始连接


}

void PowerOn_Self_Auto_Link_Tencent_Cloud(void)
{

	 uint8_t auto_link_cloud_flag=0;
    

   // device_massage = (uint8_t *)malloc(128);


   switch (auto_link_cloud_flag)
  {

    case 0:
           auto_link_tencent_cloud_fun();//InitWifiModule();
        
		   HAL_Delay(1000);

           auto_link_cloud_flag =wifi_set_cwmode;
	break;


	 case wifi_set_cwmode:
    	    WIFI_IC_ENABLE();
         	HAL_UART_Transmit(&huart2, "AT+CWMODE=3\r\n", strlen("AT+CWMODE=3\r\n"), 5000);
     
            HAL_Delay(1000);
	
			 wifi_t.randomName[0]=HAL_GetUIDw0();
		

	 break;
	 default:
        
	 break;

}
 // free(device_massage);

}




void Wifi_Link_Tencent_Net_State(void)
{

   HAL_UART_Transmit(&huart2, "AT+TCMQTTSTATE?\r\n", strlen("AT+TCMQTTSTATE?\r\n"), 0xffff);

  
 
  
}

void Wifi_Reconnect_Tencent_Net(void)
{

   HAL_UART_Transmit(&huart2, "AT+CWJAP\r\n", strlen("AT+CWJAP\r\n"), 0xffff);

   //AT+CWRECONNCFG?
 //  HAL_UART_Transmit(&huart2, "AT+CWRECONNCFG?\r\n", strlen("AT+CWRECONNCFG?\r\n"), 5000);
 
  
}





