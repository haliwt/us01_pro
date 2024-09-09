#ifndef  	__BSP_H_
#define 	__BSP_H_
#include "main.h"


#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"






#include "interrupt_manager.h"
#include "adc.h"

#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"




//maiboard
#include "bsp_adc.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_buzzer.h"
#include "bsp_key.h"
#include "bsp_sensor.h"
#include "bsp_ultrasonic.h"
#include "bsp_delay.h"
#include "bsp_ctl.h"
#include "bsp_fan.h"
#include "bsp_plasma.h"
#include "bsp_ptc.h"
#include "bsp_usart.h"
#include "bsp_lcd_app.h"
#include "bsp_freertos_app.h"

//wifi
#include "bsp_wifi.h"
#include "bsp_wifi_fun.h"
#include "bsp_esp8266.h"
#include "bsp_publish.h"
#include "bsp_subscription.h"
#include "bsp_mqtt_iot.h"


#define  USE_FreeRTOS      1

#if USE_FreeRTOS == 1
	#include "FreeRTOS.h"
	#include "task.h"
	#define DISABLE_INT()    taskENTER_CRITICAL()
	#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
	/* ¿ª¹ØÈ«¾ÖÖÐ¶ÏµÄºê */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* enable global interrupter */
	#define DISABLE_INT()	__set_PRIMASK(1)	/*  */
#endif




typedef struct {


   uint8_t gPower_On ;

   uint8_t key_power_flag;
   uint8_t key_mode_flag;
   uint8_t key_add_flag;
   uint8_t key_dec_flag;

   uint8_t power_off_flag;
   uint8_t shut_Off_backlight_flag;

   uint8_t link_net_step;
  
  
   uint8_t  set_timer_timing_key_flag ;
   //WIFI
   uint8_t run_process_step;
   uint8_t disp_dht11_value;
   uint8_t power_on_every_times;
   uint8_t long_key_mode_counter;
   uint8_t key_long_mode_flag ;
   uint8_t key_mode_be_pressed_flag;
   uint8_t key_short_mode_flag;
 
  
   uint8_t disp_works_hours_value;
   uint8_t disp_works_minutes_value;
   uint8_t gTimer_run_main_fun;
   uint8_t set_temperature_value_success;

   uint8_t disp_timer_switch_time_flag;
   uint8_t global_temporary_set_timer_flag ;
 



   int8_t set_timer_timing_hours;
   int8_t set_timer_timing_minutes;


   uint8_t gTimer_run_adc;
   uint8_t gTimer_run_dht11;

   uint8_t gTimer_run_one_mintue ;
   
   uint8_t gTimer_run_total;
   uint16_t gTimer_run_time_out;

   uint8_t gTimer_works_counter_sencods;
  
   uint8_t gTimer_timer_Counter;
  
   uint8_t gTimer_disp_set_timer_blink ;

   uint8_t gTimer_pro_action_publis;
   uint8_t gTimer_publish_tencent_dht11;
   uint8_t gTimer_compare_temp;
   uint8_t gTimer_ptc_detected;
   uint8_t gTimer_shut_off_backlight;
   uint8_t gTimer_timer_led_blink;
   uint8_t gTimer_get_data_from_tencent_data;
 
   uint8_t gTimer_set_timer_times;
   
   uint8_t gTimer_disp_humidity;
   uint8_t gTimer_power_off_run_times;
   uint8_t gTimer_link_net_timer_time;
   uint8_t gTimer_fan_to_ptc_warning ;
   uint8_t gTimer_fan_waring_time ;
   uint8_t gTimer_mode_key_time ;
   uint8_t gTimer_ptc_waring_time;
        
}BSP_process_t;

extern BSP_process_t gpro_t;

void bsp_Idle(void);





void power_off_run_handler(void);


void power_on_run_handler(void);

void mainboard_active_handler(void);



void disp_works_or_timer_timing_fun(void);

void mode_key_adjust_fun(void);

void detected_fault_state(void)
;

#endif 

