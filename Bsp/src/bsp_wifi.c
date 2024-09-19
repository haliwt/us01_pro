
#include "bsp.h"

uint8_t sub_send_power_on_times;
uint8_t get_rx_beijing_time_enable;


uint8_t beijing_step;
uint8_t auto_det_flag;

uint8_t wifi_again_link_step;

uint8_t get_beijing_flag;

///********************************************************************************
//	*
//	*Functin Name:void WIFI_Process_Handler(void)
//	*Functin :
//	*Input Ref: NO
//	*Return Ref:NO
//	*
//********************************************************************************/

/**********************************************************************
	*
	*Functin Name: void MainBoard_Itself_PowerOn_Fun(void)
	*Function :
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
 void MainBoard_Self_Inspection_PowerOn_Fun(void)
{
   
     static uint8_t power_on_dc_power;
	if(wifi_t.auto_link_tencent_step!=0xff && wifi_link_net_state()==0 && power_on_dc_power ==0){
	
       gpro_t.gTimer_get_data_from_tencent_data=0;

      auto_link_tencent_cloud_fun();
      wifi_t.linking_tencent_cloud_doing = 1;

    }
    if(wifi_link_net_state()==1    && power_on_dc_power ==0){
              power_on_dc_power++;
   
           gpro_t.gTimer_get_data_from_tencent_data=0; //don't send dato to tencent .waiting .
       
             
           wifi_t.linking_tencent_cloud_doing = 0;

           wifi_t.auto_link_tencent_step =0;
           wifi_t.link_net_tencent_data_flag=1;
  
        
          if(gpro_t.gPower_On == power_off){
		     MqttData_Publish_PowerOff_Ref();
               HAL_Delay(200);

          }
          else{
             MqttData_Publish_Update_Data();
		     HAL_Delay(100);


          }
          Subscriber_Data_FromCloud_Handler();
          HAL_Delay(200);
		
	}


	
}

/********************************************************************************
	*
	*Functin Name:void void wifi_get_beijint_time_handler(void)
	*Functin :
	*Input Ref: NO
	*Return Ref:NO
	*
********************************************************************************/
void wifi_get_beijint_time_handler(void)
{

   static uint8_t alternate_flag,flag_switch,auto_link_net_flag;

   if(wifi_t.get_rx_beijing_time_enable==0){
    
         Tencent_Cloud_Rx_Handler();
    	 Json_Parse_Command_Fun();
  
   }

 
  if(gkey_t.key_power== power_off){
     gkey_t.key_mode = disp_timer_timing;

     Record_WorksOr_Timer_Timing_DonotDisp_Handler();

  }

  

  switch(get_beijing_flag){


  case 0:


  if(wifi_link_net_state()==1 && gpro_t.gTimer_get_data_from_tencent_data > 9){
       
       gpro_t.gTimer_get_data_from_tencent_data =0;
       flag_switch++;
       if(flag_switch ==1){
           Subscriber_Data_FromCloud_Handler();
           osDelay(100);//HAL_Delay(200)
           get_beijing_flag =1;
        }
      
       
       if(flag_switch > 1 && gpro_t.gPower_On == power_off){
            flag_switch=0;
            Update_Dht11_Totencent_Value(); // Update_Dht11_Totencent_Value();
            osDelay(100);//HAL_Delay(200)
            get_beijing_flag =1;

       }
       else{
           if(flag_switch > 1){ //WT.EDIT 2024.08.17
               flag_switch=0;
               get_beijing_flag =1;

           }


       }
       
       
    }
    else{
       
        get_beijing_flag =1;

    }


  break;


   case 1:

        if(wifi_t.gTimer_get_beijing_time > 100){

         wifi_t.gTimer_get_beijing_time=0;
        
          if(wifi_link_net_state()==1){

     
    		    get_beijing_flag = 2;
         
                alternate_flag++;
                wifi_t.linking_tencent_cloud_doing  =0; //receive from tencent command state .
               

            }
            else{
               gctl_t.get_beijing_time_success = 0; //WT.2024.04.25
               get_beijing_flag = 10;
               wifi_t.linking_tencent_cloud_doing  =1; //receive from tencent command state .
             }
	
       }
       else{
          
         get_beijing_flag =0;
       }

      break;


      case 2:


	  if(gctl_t.get_beijing_time_success == 0){
		

         get_beijing_flag = 3;
	     beijing_step =0;
	
	
		wifi_t.get_rx_beijing_time_enable=0;//disenable get beijing timing
		
	
       }
	   else{

          
         if(alternate_flag == 1){
		  
			wifi_t.link_beijing_times_flag =1;
			
		
			wifi_t.get_rx_beijing_time_enable=0;//disenable get beijing timing
		
		    get_beijing_flag = 3;
			beijing_step =0;
	

        }
		else{
              alternate_flag=0;
              
			   get_beijing_flag = 6;

		}

	   }
       
      
     
    break;


     case 3:

     switch(beijing_step){

        case 0:

            //disable publish data to tencent cloud.
            gpro_t.gTimer_get_data_from_tencent_data=0;
         
        
    		
    		Get_BeiJing_Time_Cmd();
    	    osDelay(20);
    		wifi_t.gTimer_read_beijing_time=0;
    		

            wifi_t.link_beijing_times_flag ++;
            beijing_step =1;

           
         break;

         case 1:
     
           if(wifi_t.gTimer_read_beijing_time > 0){//
    		
            wifi_t.gTimer_read_beijing_time=0;
             //disable publish data to tencent cloud.
            gpro_t.gTimer_get_data_from_tencent_data=0;
         
          
    		
    		Get_Beijing_Time();
            wifi_t.get_rx_beijing_time_enable=1; //enable beijing times
    		wifi_t.wifi_uart_counter=0;
    		osDelay(200);//HAL_Delay(200);
            
    		wifi_t.gTimer_read_beijing_time=0;
             beijing_step =2;
          
            }


          break;

          case 2:
        
              if(wifi_t.wifi_data[50] > 0x31 ){ //data:1970 

                wifi_t.real_hours = (wifi_t.wifi_data[41]-0x30)*10 + wifi_t.wifi_data[42]-0x30;
                wifi_t.real_minutes =(wifi_t.wifi_data[44]-0x30)*10 + wifi_t.wifi_data[45]-0x30;
                wifi_t.real_seconds = (wifi_t.wifi_data[47]-0x30)*10 + wifi_t.wifi_data[48]-0x30;

                wifi_t.get_rx_beijing_time_enable=0; //enable beijing times

                 gpro_t.disp_works_hours_value  = wifi_t.real_hours ;    
                 gpro_t.disp_works_minutes_value = wifi_t.real_minutes;

                 gpro_t.gTimer_works_counter_sencods =  wifi_t.real_seconds;

                  gctl_t.get_beijing_time_success = 1; //WT.2024.04.25
                    if(gkey_t.key_mode == disp_works_timing  && gctl_t.ai_flag == 1){

                        LCD_Number_FiveSixSeveEight_Hours(gpro_t.disp_works_hours_value,gpro_t.disp_works_minutes_value);

                    }
                   
                     get_beijing_flag = 0;
                }
                else if(wifi_t.wifi_data[50] == 0x31 && gctl_t.get_beijing_time_success ==0){  //"0x31" ASCII = '1'
                  
                   wifi_t.get_rx_beijing_time_enable=0; //enable beijing times
                   if(wifi_link_net_state()==1){
                       get_beijing_flag = 0;
                       gpro_t.gTimer_get_data_from_tencent_data =0;
                       wifi_t.gTimer_get_beijing_time = 70;
                       beijing_step =0;

                    }
                    else 
                       get_beijing_flag = 0;

                }
                else{

                    get_beijing_flag = 0;

                }
         
         break;
       }
    break;


    case 6:

    
     
       Wifi_Link_Tencent_Net_State();
    
       wifi_t.gTimer_publish_dht11=0;
       

       get_beijing_flag = 0;
    
     


    break;

    //auto link net 

    case 10:

     
        if(wifi_t.gTimer_get_beijing_time > 100){
		
            wifi_t.gTimer_get_beijing_time  =0;
            if(wifi_link_net_state()==0){
              get_beijing_flag = 11;
           
            wifi_t.linking_tencent_cloud_doing  =1; //receive from tencent command state .
            wifi_t.wifi_uart_counter=0;
          }
          else{

             wifi_t.linking_tencent_cloud_doing  =0; //receive from tencent command state .
             get_beijing_flag = 0;

          }
        
       }

     
     if(wifi_link_net_state()==1){
          get_beijing_flag = 0;

       }
       
     break;


     case 11:
         if(wifi_link_net_state()==0){

            wifi_t.linking_tencent_cloud_doing =1;
            get_beijing_flag = 12;

            WIFI_IC_ENABLE();
       
    		at_send_data("AT+RST\r\n", strlen("AT+RST\r\n"));
            
            osDelay(1000);//HAL_Delay(1000);
           
            
           
           
            
            
           
            auto_link_net_flag =1;

         }
         else {

             get_beijing_flag = 10;


         }
        
               

     break;


     case 12:

        if(wifi_t.gTimer_auto_link_net_time > 2 &&    auto_link_net_flag ==1 ){

            auto_link_net_flag =2;
              get_beijing_flag = 13;

            wifi_t.gTimer_auto_link_net_time=0;
            wifi_t.wifi_uart_counter=0;
	        wifi_t.soft_ap_config_flag =0;
      
	        HAL_UART_Transmit(&huart2, "AT+TCMQTTCONN=1,5000,240,0,1\r\n", strlen("AT+TCMQTTCONN=1,5000,240,0,1\r\n"), 0xffff);//开始连接
            //HAL_Delay(1000);
            
            //HAL_Delay(1000);
             osDelay(100);//HAL_Delay(1000);
            
          
           
		
	    }

    break;
        
    case 13:

        if(wifi_t.gTimer_auto_link_net_time > 4 && auto_link_net_flag==2){

            auto_link_net_flag=0 ;
            get_beijing_flag = 14;
           
        }


     break;


     case 14:
       if(wifi_link_net_state()==1){
       
        

        wifi_t.linking_tencent_cloud_doing  =0; //receive from tencent command state .
		wifi_t.wifi_uart_counter=0; //clear USART2 counter is zero
		  
		

         wifi_t.linking_tencent_cloud_doing = 0;

          if(power_on_state() == power_on){
                MqttData_Publish_Update_Data();//Publish_Data_ToTencent_Initial_Data();
                osDelay(200);//HAL_Delay(200);

            }
            else if(power_on_state() == power_off){

               MqttData_Publish_PowerOff_Ref();
               osDelay(200);//HAL_Delay(200);


            }
            Subscriber_Data_FromCloud_Handler();
            osDelay(200);//HAL_Delay(200);

             get_beijing_flag = 0;
		
         }
         else{

             get_beijing_flag = 10;
         }

       break;
	}

}
/*****************************************************************************
    *
    *Function Name: static void AutoReconnect_Wifi_Neware_Function(void)
    *Function: 
    *Input Ref: NO
    *Return Ref:NO
    *
*****************************************************************************/	 	
void link_wifi_net_handler(void)
{
  

    uint8_t  device_massage[100];

    if(wifi_link_net_state()==0){
		if(wifi_t.gTimer_linking_tencent_duration < 120 ){
		   gctl_t.get_beijing_time_success = 0; 
           Disip_Wifi_Icon_State();
          
		}
		else if(wifi_link_net_state()==0 && wifi_t.gTimer_linking_tencent_duration >120){
		    //at once repeat auto link wifi net.
		  	wifi_t.gTimer_linking_tencent_duration=0;
		    gkey_t.wifi_led_fast_blink_flag=0; //fast blink wifi of dication led
			wifi_t.link_tencent_cloud_success =0; //link tencent cloud flag  
            wifi_t.link_net_fail_flag = 1;  //again link net flag.flag bit
            wifi_again_link_step=0;
            wifi_t.get_rx_beijing_time_enable=0;
            wifi_t.gTimer_get_beijing_time =0;
           
        }
       }

 

        switch( gpro_t.link_net_step){

            case 0: //one step

                WIFI_IC_DISABLE();
        		HAL_Delay(300);
        		Disip_Wifi_Icon_State();
                HAL_Delay(300);
                Disip_Wifi_Icon_State();
                HAL_Delay(300);
                Disip_Wifi_Icon_State();
                
        		WIFI_IC_ENABLE();
        		//at_send_data("AT+RESTORE\r\n", strlen("AT+RESTORE\r\n"));
        		at_send_data("AT+RST\r\n", strlen("AT+RST\r\n"));
        		HAL_Delay(300);
        		Disip_Wifi_Icon_State();
                HAL_Delay(300);
                Disip_Wifi_Icon_State();
                HAL_Delay(300);
                Disip_Wifi_Icon_State();

                 gpro_t.link_net_step = 1;

            break;

            case 1:
                Disip_Wifi_Icon_State();
                WIFI_IC_ENABLE();
                HAL_UART_Transmit(&huart2, "AT+CWMODE=3\r\n", strlen("AT+CWMODE=3\r\n"), 5000);

                gctl_t.randomName[0]=HAL_GetUIDw0();
                gpro_t.gTimer_link_net_timer_time = 0;

                gpro_t.link_net_step = 2;

            break;

            case 2:
                 if(gpro_t.gTimer_link_net_timer_time  > 3){
                     gpro_t.gTimer_link_net_timer_time = 0;

                         WIFI_IC_ENABLE();
            			
                        sprintf((char *)device_massage, "AT+TCPRDINFOSET=1,\"%s\",\"%s\",\"UYIJIA01-%d\"\r\n", PRODUCT_ID, DEVICE_SECRET,gctl_t.randomName[0]);
            			at_send_data(device_massage, strlen((const char *)device_massage));
            	  		//HAL_Delay(1000);
            	  		HAL_Delay(300);
                		Disip_Wifi_Icon_State();
                        HAL_Delay(300);
                        Disip_Wifi_Icon_State();
                        HAL_Delay(300);
                        Disip_Wifi_Icon_State();
                    
                       gpro_t.link_net_step = 3;

                 }

            break;


            case 3:
                 Disip_Wifi_Icon_State();
            if(gpro_t.gTimer_link_net_timer_time  > 3){
                 Disip_Wifi_Icon_State();
                      gpro_t.gTimer_link_net_timer_time = 0;
                   gpro_t.link_net_step = 4;
             WIFI_IC_ENABLE();
		      HAL_UART_Transmit(&huart2, "AT+TCDEVREG\r\n", strlen("AT+TCDEVREG\r\n"), 0xffff); //动态注册 
	  		//HAL_Delay(1000);
	  		HAL_Delay(300);
    		Disip_Wifi_Icon_State();
            HAL_Delay(300);
            Disip_Wifi_Icon_State();
            HAL_Delay(300);
            Disip_Wifi_Icon_State();
        
          
            }



            break;


            case 4:
                 Disip_Wifi_Icon_State();
                 if(gpro_t.gTimer_link_net_timer_time  > 10){
                      gpro_t.gTimer_link_net_timer_time = 0;
                       Disip_Wifi_Icon_State();

                  // net_t.linking_tencent_cloud_doing =1;
                   wifi_t.linking_tencent_cloud_doing  =1;
                  wifi_t.soft_ap_config_flag =1; //WE.EIDT 
	            sprintf((char *)device_massage, "AT+TCSAP=\"UYIJIA01-%d\"\r\n",gctl_t.randomName[0]);
                 at_send_data(device_massage, strlen((const char *)device_massage));


                   gpro_t.link_net_step = 5;


                    }

            break;


            case 5:
                
                    Disip_Wifi_Icon_State();
                   if(wifi_t.soft_ap_config_success==1){//if(net_t.soft_ap_config_success==1){

                      // net_t.soft_ap_config_success=0;
                      wifi_t.soft_ap_config_success=0;
                	   HAL_UART_Transmit(&huart2, "AT+TCMQTTCONN=1,5000,240,0,1\r\n", strlen("AT+TCMQTTCONN=1,5000,240,0,1\r\n"), 5000);//开始连接
                       //HAL_Delay(1000);
                      // HAL_Delay(1000);
                       ///HAL_Delay(1000);
                        Disip_Wifi_Icon_State();
	                    gpro_t.link_net_step = 6;
                        gpro_t.gTimer_link_net_timer_time = 0;
                    }

                   
               
               
            break;

            case 6:
                 Disip_Wifi_Icon_State();

            if( gpro_t.gTimer_link_net_timer_time  > 4){
           

               if(wifi_t.link_tencent_cloud_success==1){//if(net_t.wifi_link_net_success==1){
			    
			
			//	gctl_t.first_link_tencent_cloud_flag =1;
				wifi_t.get_rx_beijing_time_enable=0;
                gkey_t.wifi_led_fast_blink_flag=0;
                
                //SendWifiData_To_Data(0x1F,0x01); //link wifi order 1 --link wifi net is success.
			    gpro_t.link_net_step = 7;
              
				
		     }
		     else{

                  gkey_t.wifi_led_fast_blink_flag=0;
               
                  gpro_t.link_net_step = 0xff; //need fast repeat link wifi net.
              
                
           
                }
                
               }

            break;

            case 7:

              gkey_t.wifi_led_fast_blink_flag=0;
              gpro_t.gTimer_get_data_from_tencent_data=0;
			 
				 MqttData_Publish_SetOpen(0x01);
		         HAL_Delay(20);
		       
		         Publish_Data_ToTencent_Initial_Data();
				 HAL_Delay(20);
                  //osDelay(100);

				Subscriber_Data_FromCloud_Handler();
				HAL_Delay(20);
	             //osDelay(100);

			 gpro_t.link_net_step = 0xfe;

                   
            break;


            default:


            break;


        }

}
/*****************************************************************************
    *
    *Function Name: static void AutoReconnect_Wifi_Neware_Function(void)
    *Function: 
    *Input Ref: NO
    *Return Ref:NO
    *
*****************************************************************************/	 
void once_again_link_net_fun(void)
{
   if(wifi_t.link_net_fail_flag == 1){


      switch(wifi_again_link_step){

      case 0:
         if(wifi_link_net_state()==0){

            wifi_t.linking_tencent_cloud_doing =1;
        

            WIFI_IC_ENABLE();
       
    		at_send_data("AT+RST\r\n", strlen("AT+RST\r\n"));
            osDelay(1000);//HAL_Delay(1000);
            
          

           
            wifi_again_link_step =1;

         }
         else {

             wifi_again_link_step = 0;
             wifi_t.link_net_fail_flag ++;

         }
        
               

     break;


     case 1:

        if(wifi_t.gTimer_auto_link_net_time > 2 ){

      
      

            wifi_t.gTimer_auto_link_net_time=0;
            wifi_t.wifi_uart_counter=0;
	        wifi_t.soft_ap_config_flag =0;
      
	        HAL_UART_Transmit(&huart2, "AT+TCMQTTCONN=1,5000,240,0,1\r\n", strlen("AT+TCMQTTCONN=1,5000,240,0,1\r\n"), 0xffff);//开始连接
            //HAL_Delay(1000);
            osDelay(1000);
            //HAL_Delay(1000);
          
          
           wifi_again_link_step =2;
		
	    }

    break;
        
    case 2:

        if(wifi_t.gTimer_auto_link_net_time > 5){

           
            wifi_again_link_step =3;
           
        }


     break;


     case 3:
       if(wifi_link_net_state()==1){
       
        

        wifi_t.linking_tencent_cloud_doing  =0; //receive from tencent command state .
		wifi_t.wifi_uart_counter=0; //clear USART2 counter is zero
		  
		

         wifi_t.linking_tencent_cloud_doing = 0;

          if(power_on_state() == power_on){
                MqttData_Publish_Update_Data();//Publish_Data_ToTencent_Initial_Data();
                osDelay(200);//HAL_Delay(200);

            }
            else if(power_on_state() == power_off){

               MqttData_Publish_PowerOff_Ref();
               osDelay(200);//HAL_Delay(200);


            }
            Subscriber_Data_FromCloud_Handler();
            osDelay(200);//HAL_Delay(200);

            wifi_t.link_net_fail_flag ++;
              wifi_again_link_step=0;
              
		
         }
         else{
              wifi_again_link_step =0;

             wifi_t.link_net_fail_flag ++;
         }

       break;

   }
    }

}

