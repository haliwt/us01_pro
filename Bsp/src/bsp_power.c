#include "bsp.h"


void power_handler(void)
{
    switch(gkey_t.key_power){ //EDIT add "else "


    case power_on:

        if(gpro_t.set_timer_timing_key_flag ==1){
            gpro_t.set_timer_timing_key_flag ++;
            Set_Timer_Timing_Lcd_Blink();

        }
         
        power_on_run_handler();
        lcd_disp_temperature_and_humidiy_handler();
        lcd_disp_time_or_timer_handler();
        LCD_Disp_Wifi_Icon_State();

        fan_run_state_handler();//disp_fan_leaf_icon_handler();


        link_wifi_net_state(gkey_t.wifi_led_fast_blink_flag);


        mainboard_active_handler();

        backlight_on_off_state();
              
              
         

       break;



       case power_off:
          gkey_t.key_mode  = disp_works_timing;
          gkey_t.key_disp_temp_hum_mode = disp_normal_temp;
          power_off_run_handler();
       break;

            


   }
}

