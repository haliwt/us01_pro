#ifndef __BSP_ADC_H_
#define __BSP_ADC_H_
#include "main.h"

#define  UNIT_TEST     1


void Judge_PTC_Temperature_Value(void);
void Get_PTC_Temperature_Voltage(uint32_t channel,uint8_t times);


void Get_Fan_Adc_Fun(uint32_t channel,uint8_t times);


#endif
