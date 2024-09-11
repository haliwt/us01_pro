#include "bsp.h"



static void disp_set_temperature_value_handler(void);


static void lcd_disp_humidity_value(uint8_t hum_value);



void disp_temp_humidity_init(void)
{
    Update_DHT11_Value();
    lcd_disp_ptc_value(gctl_t.dht11_temp_value);
    lcd_disp_humidity_value(gctl_t.dht11_humidity_value);


}


static void lcd_disp_humidity_value(uint8_t hum_value)
{
   glcd_t.number3_high =  hum_value /10;
    //glcd_t.number3_low  =   hum_value /10;
    glcd_t.number3_low =  glcd_t.number3_high ;

   glcd_t.number4_low =   hum_value %10;
   //glcd_t.number4_high =  hum_value  %10;
    glcd_t.number4_high =    glcd_t.number4_low;

   if(gkey_t.key_mode != mode_set_timer){


   TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber2_Low[glcd_t.number2_low]+lcdNumber3_High[glcd_t.number3_high])&0xff);

   if(wifi_link_net_state()==1){

      TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi
   }
   else{
       TM1723_Write_Display_Data(0xC5,(WIFI_NO_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi 

   }
   
   if( gkey_t.key_mode == disp_works_timing){
       
     if((gpro_t.global_temporary_set_timer_flag == 1) &&   gpro_t.gTimer_set_timer_times <  11 ){
          glcd_t.number5_high = 0;
          TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);

       }
       else{
       glcd_t.number5_high = gpro_t.disp_works_hours_value /10;
       TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);

       }
    }
   else if(gkey_t.key_mode  == disp_timer_timing){
        
        if(gkey_t.set_timer_timing_success ==0){
            glcd_t.number5_high = 0;

         }
        else
          glcd_t.number5_high =  gpro_t.set_timer_timing_hours /10;
        
        TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);

   }

    }


}




/*****************************************************************************
 * 
 * Function Name:  void LCD_Disp_Humidity_value_Handler(void)
 * Function: read humidity of value from sensor of temperature
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void lcd_disp_temperature_and_humidiy_handler(void)
{

      switch(gkey_t.key_disp_temp_hum_mode){


       case disp_normal_temp:

          if(gpro_t.gTimer_run_dht11 > 5){
             gpro_t.gTimer_run_dht11=0;  
             disp_temp_humidity_init();
                   
                   
          }

           //display set temperature value 
         if(gctl_t.gTimer_compare_ptc_value > 11 && gctl_t.interval_stop_run_flag  ==0 && gctl_t.ptc_warning == 0 && gctl_t.fan_warning ==0){

            gctl_t.gTimer_compare_ptc_value=0;
            SetTemp_Compare_SensoTemp();

          }
      break;


      case disp_set_temp:

     

         LCD_Disp_Temperature_Value_Handler();
         gkey_t.key_disp_temp_hum_mode = disp_set_temp_numbe;
      
     break;


      case disp_set_temp_numbe:

           disp_set_temperature_value_handler();

      break;


     }
      
}
    




void lcd_disp_ptc_value(uint8_t value)
{
     
   glcd_t.number1_low =  value   / 10 ;
   //glcd_t.number1_high = value   / 10 ;
   glcd_t.number1_high =   glcd_t.number1_low;


   glcd_t.number2_low  =  value   % 10; //
   //glcd_t.number2_high =  value   % 10; //
   glcd_t.number2_high = glcd_t.number2_low ;
  LCD_Disp_Temperature_Value_Handler();
}
/*****************************************************************************
 * 
 * Function Name:  static void disp_set_temperature_value_handler(void)
 * Function: 
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
static void disp_set_temperature_value_handler(void)
{

    
    //set temperature value 
     if(gctl_t.gTimer_set_temp_value  > 2 ){
       
       gctl_t.gTimer_compare_ptc_value =0;
       gkey_t.key_disp_temp_hum_mode= disp_normal_temp; //WT.EIDT 2024.09.11

   
        set_ptc_value_conifrm_handler(gctl_t.gSet_temperature_value);
        gpro_t.set_temperature_value_success=1;


        if(gpro_t.set_temperature_value_success==1){

         //compare with by read temperature of sensor value  
         if(gctl_t.gSet_temperature_value > gctl_t.dht11_temp_value){

            
                
                gctl_t.ptc_flag = 1;
                Ptc_On();
                if(wifi_link_net_state()==1){
                         MqttData_Publish_SetPtc(gctl_t.ptc_flag);
                         osDelay(100);
                    }
                

            }
            else if(gctl_t.gSet_temperature_value <   gctl_t.dht11_temp_value || gctl_t.gSet_temperature_value ==   gctl_t.dht11_temp_value){

                gctl_t.ptc_flag = 0;
                Ptc_Off();
  
                 if(wifi_link_net_state()==1){ //逻辑错误
                 

                    MqttData_Publish_SetPtc(gctl_t.ptc_flag);
                    osDelay(100);
                  }


           }
          
          if(wifi_link_net_state()==1){
        
                MqttData_Publis_SetTemp(gctl_t.gSet_temperature_value);
                osDelay(100);

             
        
         }

        // lcd_disp_ptc_value(gctl_t.gSet_temperature_value);

        }
        //   gkey_t.set_temp_value_be_pressed++ ;
        gpro_t.gTimer_run_dht11 = 4;

     }


   


}

