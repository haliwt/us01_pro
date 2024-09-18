#ifndef __BSP_KEY_H_
#define __BSP_KEY_H_
#include "main.h"

#define KEY_POWER_VALUE()    HAL_GPIO_ReadPin(KEY_POWER_GPIO_Port, KEY_POWER_Pin)

#define KEY_MODE_VALUE()     HAL_GPIO_ReadPin(KEY_MODE_GPIO_Port, KEY_MODE_Pin)

#define KEY_DEC_VALUE()    HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin)

#define KEY_ADD_VALUE()    HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin)


typedef enum{

    
    KEY_DOWN,
    KEY_UP,
    

}key_pressed_t;

typedef enum{

  disp_normal_temp,
  disp_set_temp,
  disp_set_temp_numbe

}key_temp_mode;



typedef enum{

   power_off,
   power_on,

}power_state;


typedef enum mode_key_t{
    
   disp_works_timing,
   disp_timer_timing,

   set_temp_value_item,
   
   mode_set_timer,
   mode_confirm,
   mode_set_temp,
   set_timer_confirm,
   counter_up,
   counter_down,
   key_sound,
   fan_warning_item,
   ptc_warning_item,
  
   
}mode_state;

 typedef struct _key_fun{
   
   uint8_t  key_power;
   uint8_t  key_mode;

   uint8_t  key_mode_be_pressed;
   uint8_t key_disp_temp_hum_mode;

 
   uint8_t  key_add_dec_mode;
   uint8_t  set_timer_timing_success;

   uint8_t   key_mode_times;
   uint8_t   set_temp_value;
   uint8_t   key_mode_switch_flag;

   uint8_t  wifi_led_fast_blink_flag;
   
   uint8_t  gTimer_disp_set_timer_blink;
   uint8_t  gTimer_power_off;
   uint8_t  gTimer_disp_set_timer;
   uint8_t  gTimer_set_temp_blink;

   uint8_t gTimer_power_off_fan_run_times;
   uint8_t gTimer_key_temp_timing;

   uint8_t gTimer_power_key_counter;
 
	

}key_fun_t;


 extern key_fun_t gkey_t;

void power_long_key_fun(void);

void mode_long_key_fun(void);

void Dec_Key_Fun(uint8_t cmd);

void Add_Key_Fun(uint8_t cmd);

void  key_mode_be_pressed_send_data_wifi(void);

void smartphone_power_on_handler(void);

void power_on_key_handler(void);

void mode_key_fun(void);



#endif 

