#include "bsp.h"
//#include "iwdg.h"




uint8_t power_key_long_conter;
uint8_t key_long_power_flag;



/*
**********************************************************************************************************
											宏定义
**********************************************************************************************************
*/
#define POWER_KEY_0	        (1 << 0)
#define MODE_KEY_1	        (1 << 1)
#define DEC_KEY_2           (1 << 2)
#define ADD_KEY_3           (1 << 3)

#define POWER_LONG_KEY_4         (1 << 4)
#define MODE_LONG_KEY_5          (1 << 5)
///#define RUN_DEC_6           (1 << 6)
//#define RUN_ADD_7           (1 << 7)

#define PHONE_POWER_ON_RX_8       (1<<8)
#define PHONE_POWER_OFF_9         (1<<9)

#define PHONE_POWER_ON_10         (1<<10)

/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
//static void vTaskTaskUserIF(void *pvParameters);
//static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);



/*
**********************************************************************************************************
											变量声明
**********************************************************************************************************
*/
//static TaskHandle_t xHandleTaskUserIF = NULL;
//static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

/**********************************************************************************************************
*	函 数 名: main
*	功能说明: 标准c程序入口。
*	形    参：无
*	返 回 值: 无
**********************************************************************************************************/
void freeRTOS_Handler(void)
{
	/* 创建任务 */
	AppTaskCreate();

	/* 创建任务通信机制 */
//	AppObjCreate();
	
    /* 启动调度，开始执行任务 */
    vTaskStartScheduler();
}


/**********************************************************************************************************
*	函 数 名: vTaskMsgPro
*	功能说明: 使用函数xTaskNotifyWait接收任务vTaskTaskUserIF发送的事件标志位设置
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 3  
**********************************************************************************************************/
static void vTaskMsgPro(void *pvParameters)
{
   // MSG_T *ptMsg;
    BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(30); /* 设置最大等待时间为50ms */
	uint32_t ulValue;
    static uint8_t smart_phone_sound;
   
    static uint8_t dc_power_on_first;
	
    while(1)
    {
		/*
			第一个参数 ulBitsToClearOnEntry的作用（函数执行前）：
		          ulNotifiedValue &= ~ulBitsToClearOnEntry
		          简单的说就是参数ulBitsToClearOnEntry那个位是1，那么notification value
		          的那个位就会被清零。

		          这里ulBitsToClearOnEntry = 0x00000000就是函数执行前保留所有位。
		
		    第二个参数 ulBitsToClearOnExit的作用（函数退出前）：			
				  ulNotifiedValue &= ~ulBitsToClearOnExit
		          简单的说就是参数ulBitsToClearOnEntry那个位是1，那么notification value
		          的那个位就会被清零。

				  这里ulBitsToClearOnExi = 0xFFFFFFFF就是函数退出前清楚所有位。
		
		    注：ulNotifiedValue表示任务vTaskMsgPro的任务控制块里面的变量。		
		*/
		
		xResult = xTaskNotifyWait(0x00000000,      
						          0xFFFFFFFF,      
						          &ulValue,        /* 保存ulNotifiedValue到变量ulValue中 */
						          xMaxBlockTime);  /* 最大允许延迟时间,等待时间 */
		
		if( xResult == pdPASS )
		{
			/* 接收到消息，检测那个位被按下 */
             
			if((ulValue & POWER_KEY_0) != 0)
			{
              if(gpro_t.shut_Off_backlight_flag == turn_off){

                     gpro_t.gTimer_shut_off_backlight =0;
                     wake_up_backlight_on();
                     buzzer_sound();

                }
                else{
            
                   
                    power_key_long_conter=0;
                    gpro_t.long_key_mode_counter=0; //WT.EIDT 2024.08.20 add new statement
                    gpro_t.gTimer_shut_off_backlight =0;
                }
                     
                
				                                    
			}
            else if((ulValue & PHONE_POWER_ON_RX_8 ) != 0)
            {
                 if(gpro_t.shut_Off_backlight_flag == turn_off){

                     gpro_t.gTimer_shut_off_backlight =0;
                     wake_up_backlight_on();
                       buzzer_sound();

                       power_on_key_handler();

                  }
                 else{
                    smart_phone_sound = 1;
                    power_key_long_conter=0;
                    gpro_t.long_key_mode_counter=0; //WT.EIDT 2024.08.20 add new statement
                    gpro_t.gTimer_shut_off_backlight =0;
                

                }
                       
            }
            else if((ulValue & POWER_LONG_KEY_4) != 0){

               if(gkey_t.key_power == power_on){

              if(gpro_t.shut_Off_backlight_flag == turn_off){

                     gpro_t.gTimer_shut_off_backlight =0;
                     wake_up_backlight_on();
                     buzzer_sound();

               }
              
               }
             }
            else if((ulValue & PHONE_POWER_OFF_9 ) != 0){
               if(gpro_t.shut_Off_backlight_flag == turn_off){

                     gpro_t.gTimer_shut_off_backlight =0;
                     wake_up_backlight_on();
                     buzzer_sound();
                }
                else{
                     buzzer_sound();
                     gkey_t.key_power=power_off;
                     gctl_t.step_process=0;
                   
                }
            }
        }
       else{ //超时，时间是50ms


           if(dc_power_on_first == 0){
                dc_power_on_first++;
                buzzer_sound();
            }
  
           if(gpro_t.key_power_flag == 1){

           if(KEY_POWER_VALUE()==KEY_UP){
             gpro_t.key_power_flag++;

             if(key_long_power_flag==0){
                
                power_key_long_conter=0;
                buzzer_sound();
                HAL_Delay(20);
                power_on_key_handler();

            }
             else{
                 power_key_long_conter=0;
                  Disip_Wifi_Icon_State();
                  //power_long_key_fun();
                 key_long_power_flag= 0;

               }
            }

           }
           else if(gpro_t.key_mode_flag== 1 && gkey_t.key_power==power_on){
                if(KEY_MODE_VALUE() == KEY_UP){
                 gpro_t.key_mode_flag++;

                  if(gpro_t.key_long_mode_flag ==0){
                       gpro_t.long_key_mode_counter=0;
                        buzzer_sound();
                        mode_key_fun();
                  }
                  else{
                      gpro_t.long_key_mode_counter=0;

                      mode_long_key_fun();
                      gpro_t.key_long_mode_flag =0;
                      

                  }

                 }
                
             }
             else if(gpro_t.key_add_flag==1){
                     
                   if(KEY_ADD_VALUE() == KEY_UP){
                       gpro_t.key_add_flag++;


                      buzzer_sound();
                      Add_Key_Fun(gkey_t.key_add_dec_mode);
                     
                    }
                    

             }
             else if(gpro_t.key_dec_flag ==1){
                     
                   if(KEY_DEC_VALUE()==KEY_UP){
                    gpro_t.key_dec_flag++;
                    buzzer_sound();
                     Dec_Key_Fun(gkey_t.key_add_dec_mode);
                     
                   }

             }
             else if(smart_phone_sound == 1){

                   smart_phone_sound++;
             
                  buzzer_sound();
                  smartphone_power_on_handler();

             }
 

            if(gkey_t.key_power==power_on){

             
               if(gpro_t.set_timer_timing_key_flag ==1){
                    gpro_t.set_timer_timing_key_flag ++;
                    Set_Timer_Timing_Lcd_Blink();

                }
             
              power_on_run_handler();
              lcd_disp_temperature_and_humidiy_handler();
              disp_time_or_timer_handler();
              Disip_Wifi_Icon_State();

              disp_fan_leaf_icon_handler();
              
             
              link_wifi_net_state(gkey_t.wifi_led_fast_blink_flag);
              once_again_link_net_fun();
              
              mainboard_active_handler();
        
              backlight_on_off_state();
              
              
            }
            else{
            
                power_off_run_handler();

            }
          if(gkey_t.wifi_led_fast_blink_flag==0){
                wifi_get_beijint_time_handler();
                MainBoard_Self_Inspection_PowerOn_Fun();
            }
            
       
        //  iwdg_feed();
          clear_rx_copy_data();
        }
        
    }
}

/**********************************************************************************************************
*	函 数 名: vTaskStart
*	功能说明: 启动任务，也就是最高优先级任务，这里用作按键扫描。
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 4  
**********************************************************************************************************/
static void vTaskStart(void *pvParameters)
{
 
     while(1)
    {
        if(KEY_POWER_VALUE()==KEY_DOWN){

        power_key_long_conter++;
        if(power_key_long_conter > 30 && gkey_t.key_power==power_on ){
                  
            power_key_long_conter=0;
            key_long_power_flag= 1;
            buzzer_sound();
            power_long_key_fun();
            Disip_Wifi_Icon_State();

        }
        gpro_t.key_power_flag = 1;

       }
       else if(KEY_MODE_VALUE() == KEY_DOWN){
        gpro_t.long_key_mode_counter ++ ;

          if(gpro_t.long_key_mode_counter > 30 && gkey_t.key_power==power_on && gctl_t.fan_warning==0 && gctl_t.ptc_warning==0){
            gpro_t.long_key_mode_counter=0;   
            gpro_t.key_long_mode_flag =1;
            gkey_t.gTimer_disp_set_timer=0;
            buzzer_sound();
              
        }
        gpro_t.key_mode_flag = 1;
        

      }
      else if(KEY_ADD_VALUE() == KEY_DOWN){
//         xTaskNotify(xHandleTaskMsgPro,  /* 目标任务 */
//                ADD_KEY_3,     /* 设置目标任务事件标志位bit0  */
//                eSetBits);  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
          gpro_t.key_add_flag = 1;
               
     }
     else if(KEY_DEC_VALUE() == KEY_DOWN){
//        xTaskNotify(xHandleTaskMsgPro,  /* 目标任务 */
//                DEC_KEY_2,     /* 设置目标任务事件标志位bit0  */
//                eSetBits);  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */
          gpro_t.key_dec_flag = 1;     
  
     }
        
     vTaskDelay(20);
    }

 }
  

/**********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：无
*	返 回 值: 无
**********************************************************************************************************/
static void AppTaskCreate (void)
{

	
	xTaskCreate( vTaskMsgPro,     		/* 任务函数  */
                 "vTaskMsgPro",   		/* 任务名    */
                 256,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 1,               		/* 任务优先级*/
                 &xHandleTaskMsgPro );  /* 任务句柄  */
	
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务名    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 2,              		/* 任务优先级*/
                 &xHandleTaskStart );   /* 任务句柄  */
}




/*********************************************************************
*
*Function Name: 
*Function :
*Input Ref:
*Return Ref:
*
*********************************************************************/
void smartphone_turn_on_handler(void)
{
   
    xTaskNotify(xHandleTaskMsgPro,  /* 目标任务 */
    PHONE_POWER_ON_RX_8,      /* 设置目标任务事件标志位bit0  */
    eSetBits);  /* 将目标任务的事件标志位与BIT_0进行或操作， 将结果赋值给事件标志位 */

}

/*****************************************************************************
 * 
 * Function Name: void App_PowerOff_Handler(void)
 * Function:
 * Input Ref: NO
 * Return Ref: NO
 * 
*****************************************************************************/
void App_PowerOff_Handler(void)
{
     
     xTaskNotify(xHandleTaskMsgPro, /* 目标任务 */
	 PHONE_POWER_OFF_9,            /* 设置目标任务事件标志位bit0  */
	 eSetBits);             /* 将目标任务的事件标志位与BIT_0进行或操作，  将结果赋值给事件标志位。*/
     

}


