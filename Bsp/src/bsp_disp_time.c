#include "bsp.h"



void disp_time_or_timer_handler(void)
{

    

    Display_WorksTimingr_Handler(gkey_t.key_mode);
    Record_WorksOr_Timer_Timing_DonotDisp_Handler();
   
}






void disp_speical_time_number_fun(void)
{
    switch(gkey_t.key_mode){

   case disp_works_timing :

      glcd_t.number4_low = gctl_t.dht11_humidity_value %10;
   

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

    case mode_set_timer :

           glcd_t.number4_low = gctl_t.dht11_humidity_value %10;
           
          glcd_t.number5_low = gpro_t.set_timer_timing_hours  /10 ;   //gpro_t.set_timer_timing_hours,gpro_t.set_timer_timing_minutes
         
           glcd_t.number5_high = glcd_t.number5_low;//hours_n  /10 ;
    
    
           glcd_t.number6_low = gpro_t.set_timer_timing_hours %10 ;
          
           glcd_t.number6_high = glcd_t.number6_low ;
    
           //display minutes
           glcd_t.number7_low = 0;
          
           glcd_t.number7_high = 0;
    
    
           glcd_t.number8_low = 0;
           
           glcd_t.number8_high =0;

    break;


    case disp_timer_timing:


        glcd_t.number4_low = gctl_t.dht11_humidity_value %10;

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
