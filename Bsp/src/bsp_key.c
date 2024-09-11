#include "bsp_key.h"
#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


key_fun_t gkey_t;

uint8_t add_dec_key_set_timer_flag;

/*********************************************************************************
*
*	函 数 名:static void mode_long_short_key_fun(void)
*	功能说明: 
*	形    参: 
*	返 回 值: 无
*   
*********************************************************************************/
void power_long_key_fun(void)
{
//WIFI CONNCETOR process
    gkey_t.wifi_led_fast_blink_flag=1;


    //WIFI CONNCETOR process
    wifi_t.link_tencent_cloud_success =0;
    gpro_t.link_net_step=0;

    wifi_t.auto_link_tencent_step=0;



    wifi_t.gTimer_linking_tencent_duration=0; //120 -2分0秒
    gpro_t.gTimer_get_data_from_tencent_data=0;
         
}
   
void power_on_key_handler(void)
{
        

      
           if(gkey_t.key_power==power_off){
              gkey_t.key_power=power_on;
              gkey_t.key_mode = disp_timer_timing;
               gctl_t.ai_flag = 1;
               gctl_t.ptc_warning =0;
               gctl_t.fan_warning =0;
              
              gctl_t.step_process=0;
              gpro_t.power_off_flag =1;
            }
           else{
              gkey_t.key_power=power_off;
              gctl_t.step_process=0;

           }
          
}
     /*********************************************************************************
*
*	函 数 名:void smartphone_power_on_handler(uint8_t phone_on)
*	功能说明: 
*	形    参: 
*	返 回 值: 无
*   
*********************************************************************************/
void smartphone_power_on_handler(void)
{

      
  

      gkey_t.key_power=power_on;
      gkey_t.key_mode = disp_timer_timing;
       gctl_t.ai_flag = 1;
       gctl_t.ptc_warning =0;
       gctl_t.fan_warning =0;
      
        gctl_t.step_process=0;
        gpro_t.power_off_flag =1;
            
          
    //   Buzzer_KeySound();

      
       
      
}

/*********************************************************************************
*
*	函 数 名:static void mode_long_short_key_fun(void)
*	功能说明: 
*	形    参: 
*	返 回 值: 无
*   
*********************************************************************************/
void mode_long_key_fun(void)
{
    gkey_t.key_mode = mode_set_timer;
 
    gkey_t.key_add_dec_mode = mode_set_timer;
    gctl_t.ai_flag = 0; //timer tiiming model
    gkey_t.gTimer_disp_set_timer = 0;       //counter exit timing this "mode_set_timer"
    

    gpro_t.gTimer_timer_led_blink =0;
           

}

/*********************************************************************************
*
*	函 数 名:void mode_key_fun(void)
*	功能说明: 
*	形    参: 
*	返 回 值: 无
*   
*********************************************************************************/
void mode_key_fun(void)
{
        if(gkey_t.key_mode  == disp_works_timing && gpro_t.global_temporary_set_timer_flag !=1){
             gkey_t.key_mode  = disp_timer_timing;
           
          //   gctl_t.ai_flag = 0; // DON'T DISP AI ICON
               //counter exit timing this "mode_set_timer"
            gpro_t.gTimer_disp_humidity =0;
            gkey_t.key_mode_switch_flag++;
            gkey_t.key_add_dec_mode = set_temp_value_item;

         
            gkey_t.key_mode_be_pressed = 2;

        }
        else if( gkey_t.key_mode  == disp_timer_timing){ //定时 时间
       
            gkey_t.key_mode  = disp_works_timing;
            gkey_t.key_mode_switch_flag++;
            gkey_t.key_add_dec_mode = set_temp_value_item;
            gpro_t.gTimer_disp_humidity =0;

            gpro_t.global_temporary_set_timer_flag =0;  //timer timing 定时时间
             
            gpro_t.gTimer_set_timer_times = 30;
            gkey_t.key_mode_be_pressed = 1;
             
        }
        else if(gpro_t.global_temporary_set_timer_flag ==1){

            gkey_t.key_mode  = disp_works_timing;
            gkey_t.key_mode_switch_flag++;
            gkey_t.key_add_dec_mode = set_temp_value_item;
            gpro_t.gTimer_disp_humidity =0;

            gpro_t.global_temporary_set_timer_flag =0;
             
            gpro_t.gTimer_set_timer_times = 30;
            gkey_t.key_mode_be_pressed = 1;
        }

        key_mode_be_pressed_send_data_wifi();

         gpro_t.gTimer_mode_key_time = 0;
}

void  key_mode_be_pressed_send_data_wifi(void)
{
   
   if(gkey_t.key_mode_be_pressed == 1){ //display works_timing 

         gkey_t.key_mode_be_pressed= 0xfe;
         gkey_t.key_mode_switch_flag++;
   
         gctl_t.ai_flag = 1;
         disp_ai_iocn();

       
        LCD_Number_FiveSixSeveEight_Hours(gpro_t.disp_works_hours_value,gpro_t.disp_works_minutes_value);

       
          
           
        if(wifi_link_net_state()==1){
            MqttData_Publish_SetState(1); //timer model  = 2, works model = 1
            osDelay(20);
        }
     }
     else if(gkey_t.key_mode_be_pressed == 2  ){  // display timer timing 
            gkey_t.key_mode_be_pressed= 0xff;
            gkey_t.key_mode_switch_flag++;

            gctl_t.ai_flag = 0;
            disp_ai_iocn();

         if(gkey_t.set_timer_timing_success ==0){
            gpro_t.set_timer_timing_hours = 0;
            gpro_t.set_timer_timing_minutes=0;
            gpro_t.global_temporary_set_timer_flag = 1;
            gpro_t.gTimer_set_timer_times=0;
            LCD_Number_FiveSixSeveEight_Hours(0,0);

         }
         else{
            gpro_t.global_temporary_set_timer_flag = 2;
            LCD_Number_FiveSixSeveEight_Hours(gpro_t.set_timer_timing_hours,gpro_t.set_timer_timing_minutes);
          }
     
            

         if(wifi_link_net_state()==1){
            MqttData_Publish_SetState(2); //timer model  = 2, works model = 1
            osDelay(20);

          }
       }


}


/***************************************************************************
    *
    *Function Name:void Dec_Key_Fun(uint8_t cmd)
    *Function : key down function 
    *Input Ref: run cmd
    *Return Ref : NO
    *
***************************************************************************/
void Dec_Key_Fun(uint8_t cmd)
{

  

    switch(cmd){

         case set_temp_value_item: //set temperature 

             gpro_t.gTimer_run_main_fun =0;
             gpro_t.gTimer_run_dht11=0; //不显示，实际的温度值，显示设置的温度
             gctl_t.gTimer_compare_ptc_value=0;
         
             gctl_t.gSet_temperature_value  --;
			if( gctl_t.gSet_temperature_value  <20)  gctl_t.gSet_temperature_value  =40;
	        else if( gctl_t.gSet_temperature_value   >40) gctl_t.gSet_temperature_value  =40;

           if( gctl_t.gSet_temperature_value   > 40) gctl_t.gSet_temperature_value  = 20;
				
			glcd_t.number1_low =  gctl_t.gSet_temperature_value   / 10 ;
            glcd_t.number1_high =  gctl_t.gSet_temperature_value   / 10 ;
           
			glcd_t.number2_low  = gctl_t.gSet_temperature_value   % 10; //
            glcd_t.number2_high =  gctl_t.gSet_temperature_value   % 10; //

        

           gctl_t.gTimer_set_temp_value =0;

         
           gctl_t.smart_phone_manual_on_off=0; //unfreeze maybe turn on PTC heat 
           gkey_t.key_disp_temp_hum_mode= disp_set_temp;
      
         //   LCD_Disp_Temperature_Value_Handler();
         break;

         case mode_set_timer: //set timer timing value 


              gkey_t.gTimer_disp_set_timer = 0; 

              gpro_t.set_timer_timing_minutes =0;
              if(add_dec_key_set_timer_flag==0){
                  add_dec_key_set_timer_flag++;

                  gpro_t.set_timer_timing_hours =24;  

              }
              else
                  gpro_t.set_timer_timing_hours -- ;//run_t.dispTime_minutes = run_t.dispTime_minutes - 1;
                  
				if(gpro_t.set_timer_timing_hours < 0){//if(run_t.dispTime_minutes < 0){

				    gpro_t.set_timer_timing_hours =24;//run_t.dispTime_hours --;
					
					
				}
            

             //display hours
                  glcd_t.number5_low =  gpro_t.set_timer_timing_hours / 10 ;
                  glcd_t.number5_high =  gpro_t.set_timer_timing_hours / 10 ;

                  glcd_t.number6_low  = gpro_t.set_timer_timing_hours % 10; //
                  glcd_t.number6_high =  gpro_t.set_timer_timing_hours % 10; //
                   //dispaly minutes 
                  glcd_t.number7_low =  0;
                  glcd_t.number7_high =   0;

                  glcd_t.number8_low = 0;
                  glcd_t.number8_high =   0;

                
                gpro_t.gTimer_timer_led_blink =2;

                gpro_t.set_timer_timing_key_flag =1;
               


                //Set_Timer_Timing_Lcd_Blink();
        
                gkey_t.key_disp_temp_hum_mode= disp_normal_temp;

         break;
 
         }
}

/***************************************************************************
    *
    *Function Name:void Dec_Key_Fun(uint8_t cmd)
    *Function : key down function 
    *Input Ref: run cmd
    *Return Ref : NO
    *
***************************************************************************/
void Add_Key_Fun(uint8_t cmd)
{

 // static uint8_t add_key;
   switch(cmd){
        
    case set_temp_value_item:  //set temperature value 

         gpro_t.gTimer_run_main_fun=0;
         gpro_t.gTimer_run_dht11=0;
        gctl_t.gTimer_compare_ptc_value=0;
       
        gctl_t.gSet_temperature_value   ++;
        
        if(gctl_t.gSet_temperature_value   < 20){
            gctl_t.gSet_temperature_value  =20;
        }
        else if(gctl_t.gSet_temperature_value   > 40)gctl_t.gSet_temperature_value  = 20;

        glcd_t.number1_low = gctl_t.gSet_temperature_value   / 10 ;
        glcd_t.number1_high = gctl_t.gSet_temperature_value   / 10 ;
        glcd_t.number2_low  =gctl_t.gSet_temperature_value   % 10; //
        glcd_t.number2_high = gctl_t.gSet_temperature_value  % 10; //

         //add_key = 1;

        gctl_t.gTimer_set_temp_value =0;

       
       gctl_t.smart_phone_manual_on_off=0; //unfreeze maybe turn on PTC heat 
      
        gkey_t.key_disp_temp_hum_mode= disp_set_temp;
    break;

    case mode_set_timer: //set timer timing value 



         gkey_t.gTimer_disp_set_timer = 0; 

         gpro_t.set_timer_timing_minutes=0;

         if(add_dec_key_set_timer_flag==0){
            add_dec_key_set_timer_flag++;
           gpro_t.set_timer_timing_hours =24;


        }
        else 
            gpro_t.set_timer_timing_hours++ ;//run_t.dispTime_minutes = run_t.dispTime_minutes + 60;
            
		   if(gpro_t.set_timer_timing_hours > 24){ //if(run_t.dispTime_minutes > 59){

		          gpro_t.set_timer_timing_hours=0;//run_t.dispTime_hours =0;
		                
             }
	    //display hours
        glcd_t.number5_low =  gpro_t.set_timer_timing_hours / 10 ;
        //glcd_t.number5_high =  gpro_t.set_timer_timing_hours / 10 ;
        glcd_t.number5_high = glcd_t.number5_low ;

        glcd_t.number6_low  = gpro_t.set_timer_timing_hours% 10; //
        //glcd_t.number6_high =  gpro_t.set_timer_timing_hours % 10; //
        glcd_t.number6_high =  glcd_t.number6_low;
        //dispaly minutes 
        glcd_t.number7_low =  0;
        glcd_t.number7_high = 0;

        glcd_t.number8_low = 0;
        glcd_t.number8_high =  0;

        gpro_t.gTimer_timer_led_blink =2;

        gpro_t.set_timer_timing_key_flag =1;
      
        gkey_t.key_disp_temp_hum_mode= disp_normal_temp;
        
     break;
        
    }

}


//void key_add_dec_set_temp_value_fun(void)
//{
//
//    // 如果gkey_t结构体中的set_temp_value_be_pressed成员的值为1
//
//        gpro_t.gTimer_run_dht11=0; 
//        gctl_t.gTimer_compare_ptc_value=0;
//       LCD_Disp_Temperature_Value_Handler();
//    }
//}
//    
// 





