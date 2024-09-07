#ifndef __BSP_BUZZER_H
#define __BSP_BUZZER_H
#include "main.h"


extern void (*buzzer_sound)(void);

void Buzzer_Sound_Init(void);

void Buzzer_KeySound(void);

void Buzzer_Fan_Error_Sound(void);
void Buzzer_Ptc_Error_Sound(void);

void Buzzer_Sound_Handler(void(*buzzer_handler)(void));

#endif 


