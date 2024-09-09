#include "bsp.h"



void disp_time_or_timer_handler(void)
{


    Display_WorksTimingr_Handler(gkey_t.key_mode);
    Record_WorksOr_Timer_Timing_DonotDisp_Handler();
   
    LCD_Timer_Colon_Flicker(gkey_t.key_mode);

   

   

}

