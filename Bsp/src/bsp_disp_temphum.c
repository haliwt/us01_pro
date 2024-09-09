#include "bsp.h"


static void LCD_Disp_Humidity_value_Handler(uint8_t hum_value);

static void lcd_disp_ptc_value(uint8_t value);


void disp_temp_humidity_init(void)
{
    Update_DHT11_Value();
    lcd_disp_ptc_value(gctl_t.dht11_temp_value);
    LCD_Disp_Humidity_value_Handler(gctl_t.dht11_humidity_value);


}







/*****************************************************************************
 * 
 * Function Name:  void LCD_Disp_Humidity_value_Handler(void)
 * Function: read humidity of value from sensor of temperature
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Disp_Humidity_value_Handler(uint8_t hum_value)
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



static void lcd_disp_ptc_value(uint8_t value)
{
     
   glcd_t.number1_low =  value   / 10 ;
   //glcd_t.number1_high = value   / 10 ;
   glcd_t.number1_high =   glcd_t.number1_low;


   glcd_t.number2_low  =  value   % 10; //
   //glcd_t.number2_high =  value   % 10; //
   glcd_t.number2_high = glcd_t.number2_low ;
  LCD_Disp_Temperature_Value_Handler();
}


