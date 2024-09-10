#include "bsp.h"



void disp_time_or_timer_handler(void)
{

    

    Display_WorksTimingr_Handler(gkey_t.key_mode);
    Record_WorksOr_Timer_Timing_DonotDisp_Handler();
   
   // LCD_Timer_Colon_Flicker(gkey_t.key_mode);

   

   

}



void disp_time_number_567_fun_init(void)
{
//     glcd_t.number5_low = gpro_t.disp_works_hours_value  /10 ;   //gpro_t.disp_works_hours_value,gpro_t.disp_works_minutes_value
//  
//	glcd_t.number5_high = glcd_t.number5_low ;//gpro_t.disp_works_hours_value /10 ;
//
//
//	glcd_t.number6_low = gpro_t.disp_works_hours_value  %10 ;
//   
//	glcd_t.number6_high = glcd_t.number6_low ;
//
//    //display minutes
//    glcd_t.number7_low = gpro_t.disp_works_minutes_value / 10 ;
//   
//	glcd_t.number7_high =  glcd_t.number7_low ;
//
//
//	glcd_t.number8_low = gpro_t.disp_works_minutes_value% 10 ;
//    
//	glcd_t.number8_high = glcd_t.number8_low ;
//
//
 //   glcd_t.number4_low =  gctl_t.dht11_humidity_value %10;
   
    //FAN LEAF T14

  //   TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[gctl_t.dht11_humidity_value]+lcdNumber5_High[0]));
     TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) );
     TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) );
    // TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[0]+lcdNumber8_High[0]) & 0xff);
      



}



void disp_speical_time_number_fun(void)
{
    switch(gkey_t.key_mode){

   case disp_works_timing :

     glcd_t.number5_low = gpro_t.disp_works_hours_value  /10 ;   //gpro_t.disp_works_hours_value,gpro_t.disp_works_minutes_value
  
	glcd_t.number5_high = glcd_t.number5_low ;//gpro_t.disp_works_hours_value /10 ;


	glcd_t.number6_low = gpro_t.disp_works_hours_value  %10 ;
   
	glcd_t.number6_high = glcd_t.number6_low ;

    //display minutes
    glcd_t.number7_low = gpro_t.disp_works_minutes_value / 10 ;
   
	glcd_t.number7_high =  glcd_t.number7_low ;


	glcd_t.number8_low = gpro_t.disp_works_minutes_value% 10 ;
    
	glcd_t.number8_high = glcd_t.number8_low ;

  //   glcd_t.number4_low =  gctl_t.dht11_humidity_value %10;


    break; 


    case disp_timer_timing:

         glcd_t.number5_low = gpro_t.set_timer_timing_hours  /10 ;   //gpro_t.set_timer_timing_hours,gpro_t.set_timer_timing_minutes
      
    	glcd_t.number5_high = glcd_t.number5_low;//hours_n  /10 ;


    	glcd_t.number6_low = gpro_t.set_timer_timing_hours %10 ;
       
    	glcd_t.number6_high = glcd_t.number6_low ;

        //display minutes
        glcd_t.number7_low =gpro_t.set_timer_timing_minutes / 10 ;
       
    	glcd_t.number7_high =  glcd_t.number7_low ;


    	glcd_t.number8_low = gpro_t.set_timer_timing_minutes % 10 ;
        
    	glcd_t.number8_high = glcd_t.number8_low ;

       // glcd_t.number4_low =  gctl_t.dht11_humidity_value %10;


    break;


    }


}
