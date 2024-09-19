#include "bsp.h"


BSP_process_t gpro_t;
static uint8_t Works_Time_Out(void);
static void Mainboard_Action_Fun(void);

static void Process_Dynamical_Action(void);
static void power_off_function(void);


static void interval_continuce_works_fun(void);

static void interval_two_hours_stop_action(void);


static void Detected_Fan_Works_State(void);
static void Detected_Ptc_Works_State(void);


//uint8_t power_off_flag;

uint8_t  fan_continue_flag;

uint8_t fan_high_flag,fan_low_flag,fan_middle_flag;


/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{



    if(gkey_t.key_power == power_on){

        // Function to display the wind run icon based on the wind speed value set in the WiFi configuration
         if(gkey_t.key_mode  != mode_set_timer){
             LCD_Wind_Run_Icon(wifi_t.set_wind_speed_value);

         }
    }
	
}
/*
*********************************************************************************************************
*	函 数 名: void mainboard_process_handler(void)
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
//void mainboard_process_handler(void)
void power_off_run_handler(void)
{

  power_off_function();
		
   Breath_Led();

}
/*********************************************************************************************************
*	函 数 名: void power_on_run_handler(void)
*	功能说明: 
*			 
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************/
void power_on_run_handler(void)
{

 //   static uint8_t disp_hum_times;
     switch(gctl_t.step_process){


		  case 0:

            gctl_t.gSet_temperature_value =40;
            gpro_t.power_off_flag=1;

            gkey_t.set_timer_timing_success =0;
            //temperature value inti
            gpro_t.set_temperature_value_success=0;

            wifi_t.set_wind_speed_value=0; //init is wind speed is max

            //timig init
            gpro_t.gTimer_run_total=0;


            LCD_Wind_Run_Icon(0);
            disp_temp_humidity_init();
            gctl_t.ai_flag = 1; // AI DISPLAY AI ICON

            gkey_t.key_mode  = disp_works_timing;

            gpro_t.gTimer_timer_Counter =0;
            gpro_t.set_timer_timing_hours=0;
            gpro_t.set_timer_timing_minutes=0;


            glcd_t.gTimer_fan_blink =0;
            gpro_t.gTimer_run_dht11 = 20;



            if(gctl_t.get_beijing_time_success ==0){
               gpro_t.disp_works_hours_value  = 0 ;    
               gpro_t.disp_works_minutes_value = 0;

               gpro_t.gTimer_works_counter_sencods =  0;
              
            }
            glcd_t.gTimer_fan_blink =0;

            disp_fan_leaf_icon_handler();


            //fan on

            LED_Mode_On();
            LED_Power_On();
            Backlight_On();

            if(wifi_link_net_state() ==1){

                MqttData_Publish_SetOpen(1);  
                osDelay(50);//300
                Publish_Data_Warning(fan_warning,no_warning);
                osDelay(50);//HAL_Delay(100);//osDelay(350);//HAL_Delay(350);
                Publish_Data_Warning(ptc_warning,no_warning);
                osDelay(50);//HAL_Delay(100);//osDelay(350);//HAL_Delay(350);
            }

            if(wifi_t.smartphone_app_power_on_flag==0){
                main_fun_init();


            }


            gctl_t.step_process = 1;
         
		  break;


      case 1:   //run dht11 display 

          

     //    gctl_t.step_process=3;
		  
     // break;

        

	  case 3: //7

	  
	   if(wifi_link_net_state()==1 && wifi_t.smartphone_app_power_on_flag==0 && wifi_t.link_net_tencent_data_flag ==1){ //after send publish datat to tencent .){
             wifi_t.link_net_tencent_data_flag ++;
		 
		     MqttData_Publish_SetOpen(0x01);
		     HAL_Delay(200);
            

		}
		if(wifi_link_net_state()==1 && wifi_t.smartphone_app_power_on_flag==0 && wifi_t.link_net_tencent_data_flag ==2 ){
             wifi_t.link_net_tencent_data_flag ++;
		  
       
		    MqttData_Publish_Update_Data();
		     HAL_Delay(200);

		}

//        if(wifi_link_net_state()==1 && wifi_t.link_net_tencent_data_flag ==3 &&   gpro_t.gTimer_publish_tencent_dht11 > 12){
//             
//            gpro_t.gTimer_publish_tencent_dht11=0;
//            Update_Dht11_Totencent_Value();
//		    
//
//        }
//	 
	   
	      gctl_t.step_process=5;

	 break;

  case 5: //check works times 
		if(gpro_t.gTimer_run_total > 119){//119 //120 minutes 
			       gpro_t.gTimer_run_total =0;
				   gpro_t.gTimer_run_time_out=0;  //time out recoder start 10 minutes
				   gpro_t.gTimer_fan_run_one_minute =0;
				   fan_continue_flag=0;
                   gctl_t.step_process=7;
			       gctl_t.interval_stop_run_flag  =1 ;
		         
			    }
          else if(gctl_t.interval_stop_run_flag  ==1){
                 gctl_t.step_process=7;
                
          }
		  else{
				  gctl_t.step_process=1;
          }

		  break;

		  case 7: //works have a rest ten minutes
        if(gctl_t.interval_stop_run_flag  ==1){

		          Works_Time_Out();
              gpro_t.gTimer_fan_detected_adc=0;
              gctl_t.step_process=1;

		  }
        else 
            gctl_t.step_process=1;
                   
			break;

		}

 }      
/**********************************************************************************************************
*
*	函 数 名: void mainboard_active_handler(void)
*	功能说明: 
*			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
void mainboard_active_handler(void)
{
   static uint8_t flag_stop,stop_default= 0xff,flag_run,run_default=0xff;

  if(gpro_t.gTimer_mainboard_run_fun > 2){
    gpro_t.gTimer_mainboard_run_fun =0;
    if(gctl_t.interval_stop_run_flag  ==0){
        if(run_default != flag_run){
            run_default = flag_run;
            flag_stop++;

        }
        Process_Dynamical_Action();
    }
    else{

      if(stop_default !=flag_stop){
         stop_default=flag_stop;
          flag_run++;
         fan_high_flag++;
         fan_low_flag++;
         fan_middle_flag++;
        }
        interval_two_hours_stop_action();
    }
  }
}
/**********************************************************************************************************
*
*	函 数 名: void disp_works_or_timer_timing_fun(void)
*	功能说明: 
*			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
void disp_works_or_timer_timing_fun(void)
{

  Display_WorksTimingr_Handler(gkey_t.key_mode);
  Record_WorksOr_Timer_Timing_DonotDisp_Handler();
   

}
/**********************************************************************************************************
*
*	函 数 名: static uint8_t Works_Time_Out(void)
*	功能说明: 主板工作2小时，停止工作10分钟			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
static uint8_t Works_Time_Out(void)
{
	if(gpro_t.gTimer_run_time_out < 11){  
		
		interval_two_hours_stop_action();//Mainboard_Fun_Stop();
		 
    }

	if(gpro_t.gTimer_fan_run_one_minute < 60 && ( fan_continue_flag ==0)){

		Fan_Run();

	}

	if(gpro_t.gTimer_fan_run_one_minute > 60){

	     fan_continue_flag=1;

         Fan_Stop();
	 }


	if(gpro_t.gTimer_run_time_out > 10){// //10 minutes
		gpro_t.gTimer_run_time_out=0;
		gpro_t.gTimer_run_total=0;

        gctl_t.interval_stop_run_flag= 0;
		
        interval_continuce_works_fun();
		

		return 1;


	}
	else{
      
	  return 0;

	}

}
/**********************************************************************************************************
*
*	函 数 名: static void interval_two_hours_stop_action(void)
*	功能说明: 主板工作：功能动作输出			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
static void interval_two_hours_stop_action(void)
{
   Ptc_Off();

   Ultrasonic_Pwm_Stop();
  // Fan_Stop();
   Plasma_Off();

}
/**********************************************************************************************************
*
*	函 数 名: void Process_Dynamical_Action(void)
*	功能说明: 主板工作：功能动作输出			 
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
static void Process_Dynamical_Action(void)
{

  
    static uint8_t fan_max=0xff,fan_middle=  0xff,fan_low= 0xff ;
    
    if(gctl_t.ai_flag == 1){

            disp_ai_symbol();

     }
     else{
       donot_disp_ai_symbol();

     }

   
   if(ptc_state() ==1){


       Ptc_On();
      // Disp_Dry_Icon();


     }
    else{

           
     Ptc_Off();
     //Disp_Dry_Icon();
    }
       

    if(plasma_state() ==1){
		
       Plasma_On();
      // Disp_Kill_Icon();

    }
	else{

	   Plasma_Off();
       //Disp_Kill_Icon();

	}

    if(ultrasonic_state() ==1){

         Ultrasonic_Pwm_Output();
        // Disp_Ultrsonic_Icon();

    }
    else{

    Ultrasonic_Pwm_Stop();
    //Disp_Ultrsonic_Icon();


    }

  
    switch(wifi_t.set_wind_speed_value){
    
         case 0: //full speed

         if( fan_max != fan_high_flag){
                fan_max = fan_high_flag;
                fan_low_flag++;
                fan_middle_flag++;
                Fan_Run();
          }
    
         break;
    
         case 1 : //middle speed
          if(fan_middle_flag != fan_middle){
              fan_middle_flag= fan_middle;
               fan_low_flag++;
               fan_high_flag++;
              Fan_Run_Middle();

         }
    
         break;
    
         case 2: //lower speed
         if(fan_low != fan_low_flag){
            fan_low = fan_low_flag;
             fan_high_flag++;
             fan_middle_flag++;
            Fan_Run_Lower();

          }
         break;
    
    
       }

    
    Display_Kill_Dry_Ster_Icon();
    

}


static void interval_continuce_works_fun(void)
{
  
    if(ptc_state() ==1){
    
    
          Ptc_On();
       
    
    
        }
       else{
    
              
        Ptc_Off();
      
       }
               
    
      if(plasma_state() ==1){
           
          Plasma_On();
    
       }
       else{
    
          Plasma_Off();
    
       }
    
       if(ultrasonic_state() ==1){
    
            Ultrasonic_Pwm_Output();
    
    
       }
       else{
    
       Ultrasonic_Pwm_Stop();
    
    
       }
    
     
       switch(wifi_t.set_wind_speed_value){
       
            case 0: //full speed
       
       
              Fan_Run();
       
            break;
       
            case 1 : //middle speed
             Fan_Run_Middle();
       
            break;
       
            case 2: //lower speed
             Fan_Run_Lower();
            break;
       
       
          }


}

/***********************************************************************
*
*Function Name:static void power_off_function(void)
*Function: by key be pressed power off run process
*Input Ref:NO
*Return Ref:NO
*
************************************************************************/
static void power_off_function(void)
{

  static uint8_t fan_run_one_minute_flag ;
  if(gpro_t.power_off_flag == 1){
    		gpro_t.power_off_flag ++;
            fan_run_one_minute_flag =1;
    	    
           //key set ref 

          
           gkey_t.wifi_led_fast_blink_flag=0;
            gctl_t.ptc_flag =0;
            gctl_t.plasma_flag =0;
            
            gctl_t.fan_warning = 0;
            gctl_t.ptc_warning = 0;
            
            gkey_t.set_timer_timing_success =0;
            gpro_t.set_temperature_value_success=0;
    	   
    	  
    	    //control set ref
    	    wifi_t.link_net_tencent_data_flag =1;

             gctl_t.step_process=0;
             //cotrol displ dht11 value 
            

            //wifi set ref
    	 
           wifi_t.gTimer_linking_tencent_duration=0; //120s -2分7秒

          wifi_t.smartphone_app_power_on_flag=0;

            gpro_t.gTimer_run_dht11=20;
           

             gkey_t.gTimer_power_off_fan_run_times=0;
           
    	    //stop main board function ref.
    	    PowerOff_Off_Led();
            lcd_power_off_handler();
    	  
		
	  }

       if(fan_run_one_minute_flag ==1){
           if(gkey_t.gTimer_power_off_fan_run_times < 61){
                Fan_Run();
				power_off_disp_fan_run_handler();
               
				

		   }
		   else{
               fan_run_one_minute_flag++;
			   Fan_Stop();
		       Backlight_Off();
               Lcd_Display_Off();
		     
			   
		  }

	}

    if(wifi_link_net_state() ==1 && gpro_t.power_off_flag==2 ){
	
		gpro_t.power_off_flag++;
		MqttData_Publish_PowerOff_Ref();
        osDelay(200);
	}

}

/***********************************************************************
*
*Function Name:static void power_off_function(void)
*Function: by key be pressed power off run process
*Input Ref:NO
*Return Ref:NO
*
************************************************************************/

/***********************************************************************
*
*Function Name:void detected_fault_state(void)
*Function: 
*Input Ref:NO
*Return Ref:NO
*
************************************************************************/
void detected_fault_state(void)
{
    fan_run_state_handler();
    Detected_Fan_Works_State();
    Detected_Ptc_Works_State();



}

/**********************************************************************************
***********************************************************************************/
void Detected_Fan_Works_State(void)
{
    if(gpro_t.gTimer_fan_detected_adc > 60 && gctl_t.interval_stop_run_flag==0 && gctl_t.fan_warning ==0 &&  gctl_t.interval_stop_run_flag==0){ //2 minute 180s
		gpro_t.gTimer_fan_detected_adc=0;
      // fan_max_run();
      disp_fan_leaf_icon_handler();
      // osDelay(200);

        if( gctl_t.interval_stop_run_flag  ==0){
		   Get_Fan_Adc_Fun(ADC_CHANNEL_0,10);
        }
		
	    disp_fan_leaf_icon_handler();

   }

   fan_fault_buzzer_sound_warning_fun(gctl_t.fan_warning);

}

void Detected_Ptc_Works_State(void)
{

   if(gpro_t.gTimer_ptc_detected > 7 && gctl_t.ptc_warning == 0 ){ //3 minutes 120s
	   gpro_t.gTimer_ptc_detected =0;	
      disp_fan_leaf_icon_handler();
	   Get_PTC_Temperature_Voltage(ADC_CHANNEL_1,10);
       fan_run_state_handler();
              
					
     }

     ptc_fault_buzzer_sound_warning_fun(gctl_t.ptc_warning );
	



}

/***********************************************************************
************************************************************************/
void mode_key_adjust_fun(void)
{

  gpro_t.key_mode_be_pressed_flag=0;

  gpro_t.key_short_mode_flag = 1;
  gpro_t.long_key_mode_counter =0;
            

}

/***********************************************************************
************************************************************************/
void disp_fan_leaf_icon_handler(void)
{

  fan_run_state_handler();

}



