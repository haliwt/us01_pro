#include "bsp_ptc.h"
#include "bsp.h"



void Ptc_On(void)
{

   PTC_SetHigh();


}

void Ptc_Off(void)
{

   PTC_SetLow();

}


void set_ptc_value_conifrm_handler(uint8_t value)
{

   lcd_donot_temp_value_fun();
   osDelay(500);

  // lcd_disp_ptc_value(value);
}





