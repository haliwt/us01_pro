#include "bsp_buzzer.h"
#include "bsp.h"


void (*buzzer_sound)(void);


void Buzzer_Sound_Init(void)
{

    Buzzer_Sound_Handler(Buzzer_KeySound);


}



static void Buzzer_KeySound_Off(void);
/**********************************************************************************************************
*	Function Name: MODH_Poll
*	Function: ???????. 1ms ?????
*	Input Ref: ?
*	Return Ref: 0 ????? 1????????
**********************************************************************************************************/
void Buzzer_KeySound(void)
{

  HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1);
  HAL_Delay(20);//60
  Buzzer_KeySound_Off();
       
}

static void Buzzer_KeySound_Off(void)
{
  HAL_TIM_PWM_Stop(&htim14,TIM_CHANNEL_1);
	
}

/*********************************************************************************************************
*	Function Name: MODH_Poll
*	Function: ???????. 1ms ?????
*	Input Ref: ?
*	Return Ref: 0 ????? 1????????
*********************************************************************************************************/

void Buzzer_Fan_Error_Sound(void)
{
   
 
	Buzzer_KeySound();
	HAL_Delay(100);
	Buzzer_KeySound();
	HAL_Delay(100);
	Buzzer_KeySound();
	HAL_Delay(100);
	Buzzer_KeySound();
	HAL_Delay(100);

}

void Buzzer_Ptc_Error_Sound(void)
{

	Buzzer_KeySound();
	HAL_Delay(50);
	Buzzer_KeySound();
	HAL_Delay(50);
	Buzzer_KeySound();
	HAL_Delay(50);
	Buzzer_KeySound();
	HAL_Delay(50);
	Buzzer_KeySound();
	HAL_Delay(50);


}


void Buzzer_Sound_Handler(void(*buzzer_handler)(void))
{
   buzzer_sound = buzzer_handler;

}


