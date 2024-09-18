#include "bsp_fan.h"
#include "bsp.h"

/********************************************************
*
*Function Name:void SetLevel_Fan_PWMA(uint8_t levelval)
*Function: 
*
*
********************************************************/
static void SetLevel_Fan_PWMA(uint8_t levelval)
{
     gctl_t.gFan_pwm_duty_level = levelval;
     FAN_COM_SetLow(); //PA6
	 MX_TIM16_Init();
	 HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
}





void Fan_Run(void)
{
  
	 SetLevel_Fan_PWMA(10);

}

void fan_max_run(void)
{
   SetLevel_Fan_PWMA(10);
  
}




void Fan_Run_Middle(void)
{

  
    SetLevel_Fan_PWMA(9);


}

void Fan_Run_Lower(void)
{
   
    
    SetLevel_Fan_PWMA(8);

}

 
void Fan_Stop(void)
{
   FAN_COM_SetLow(); //PA6
   SetLevel_Fan_PWMA(0);//SetLevel_Fan_PWMA(16);
}




void fan_run_state_handler(void)
{
      

       switch(gkey_t.key_mode){


        case disp_works_timing:

            LCD_Wind_Run_Icon(wifi_t.set_wind_speed_value);


        break;


        case disp_timer_timing :
            LCD_Wind_Run_Icon(wifi_t.set_wind_speed_value);

        break;

        case mode_set_timer :

           //  LCD_Wind_Run_Icon(wifi_t.set_wind_speed_value);

        break;


        

       




       }


  }




