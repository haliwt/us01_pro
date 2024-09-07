#ifndef __BSP_LCD_H
#define __BSP_LCD_H
#include "main.h"

//#define TM1723_POWER_ON()				HAL_GPIO_WritePin(LCD_POWER_GPIO_Port, LCD_POWER_Pin,GPIO_PIN_SET)
//#define TM1723_POWER_OFF()             HAL_GPIO_WritePin(LCD_POWER_GPIO_Port, LCD_POWER_Pin,GPIO_PIN_RESET)


#define LCD_BACK_LIGHT_ON()				HAL_GPIO_WritePin(LCD_LIGHT_GPIO_Port,LCD_LIGHT_Pin,GPIO_PIN_SET)
#define LCD_BACK_LIGHT_OFF()            HAL_GPIO_WritePin(LCD_LIGHT_GPIO_Port,LCD_LIGHT_Pin,GPIO_PIN_RESET)




#define TM1723_CLK_SetHigh()            HAL_GPIO_WritePin(TM1723_SCLK_GPIO_Port,TM1723_SCLK_Pin ,GPIO_PIN_SET)    // ����ߵ�ƽ
#define TM1723_CLK_SetLow()             HAL_GPIO_WritePin(TM1723_SCLK_GPIO_Port,TM1723_SCLK_Pin ,GPIO_PIN_RESET)  // ����͵�ƽ

#define TM1723_DIO_SetHigh()            HAL_GPIO_WritePin(TM1723_DIO_GPIO_Port,TM1723_DIO_Pin,GPIO_PIN_SET)    // ����ߵ�ƽ
#define TM1723_DIO_SetLow()             HAL_GPIO_WritePin(TM1723_DIO_GPIO_Port,TM1723_DIO_Pin,GPIO_PIN_RESET)    // output low level

#define TM1723_STB_SetHigh()            HAL_GPIO_WritePin(TM1723_STB_GPIO_Port,TM1723_STB_Pin,GPIO_PIN_SET)
#define TM1723_STB_SetLow()             HAL_GPIO_WritePin(TM1723_STB_GPIO_Port,TM1723_STB_Pin,GPIO_PIN_RESET)

//extern volatile uint8_t DispData[3];//??LED??
#define		BitSET(x,y)		x|=(1<<y)				//?1
#define		BitCLR(x,y)		x&=~(1<<y)				//?0


#define HUM_T8           0x01


#define FAN_DIS_T15        0x01
#define FAN_NO_DIS_T15     0




#define DisplayReg           0x40// to write display register 
  
#define AddrFixed 	         0x44// 
#define AddrAutoAdd         0x40 
 
   
  
#define OpenDispTM1723          0x97 // full screen is tunr on light
#define OpenDispTM1723_5        0X9f
#define TM1723Default          	0x87
#define CloseDispTM1723		    0x80//  



 //Display Address 
#define Addr00H  		0xC0//??00H  -> Write display address 0xC0 
#define Addr01H  		0xC1//??01H

#define Addr02H  		0xC2//??02H
#define Addr03H  		0xC3//??03H
//digital 3
#define Addr04H  		0xC4//??03H
#define Addr05H  		0xC5//??03H
//digital 4
#define Addr06H  		0xC6//??00H
#define Addr07H  		0xC7//??01H


//Humidity SMG address
#define Addr08H  		0xC8//??02H
#define Addr09H  		0xC9//??03H

#define Addr0AH  		0xCA//??03H
#define Addr0BH  		0xCB//??03H

//temperature SMG address
#define Addr0CH         0xCC//??0CH
#define Addr0DH         0xCD//??0DH

#define Addr0EH         0xCE//??0CH
#define Addr0FH         0xCF//??0DH




typedef struct _LCD_Ref{

     uint8_t number1_low;
	 uint8_t number1_high;
	 
	 uint8_t number2_low;
	 uint8_t number2_high;
	 
	 uint8_t number3_low;
	 uint8_t number3_high;
	 
	 uint8_t number4_low;
	 uint8_t number4_high;
	 
	 uint8_t number5_low;
	 uint8_t number5_high;

	 uint8_t number6_low;
	 uint8_t number6_high;

	 uint8_t number7_low;
	 uint8_t number7_high;

	 uint8_t number8_low;
	 uint8_t number8_high;

	 

	 uint8_t gTimer_colon_blink;
	 uint8_t gTimer_fan_blink;
	 uint8_t gTimer_error_times;
	 uint8_t gTimer_lcd_blink;
     uint8_t gTimer_wifi_fast_blink ;
	
	
}lcd_ref;



extern lcd_ref glcd_t; 

void LcdDisp_Init(void);




void LCD_Display_Wind_Icon_Handler(void);


void Wifi_Icon_FastBlink(void);
void Lcd_Display_Off(void);


void Lcd_Display_Off(void);
void LCD_Timer_Colon_Flicker(void);

void Disp_HumidityTemp_Value(void);



void LCD_Number_FiveSixSeveEight_Hours(uint8_t numbers,uint8_t number2);


void LCD_Wind_Run_Icon(uint8_t speed_valu);



void Disip_Wifi_Icon_State(void  );



void lcd_disp_ai_icon(void);



void lcd_donot_temp_value_fun(void);



void LCD_Fault_Numbers_Code(void);

void disp_ai_iocn(void);

void disp_ai_symbol(void);

void donot_disp_ai_symbol(void);

void Display_Kill_Dry_Ster_Icon(void);

void LCD_Disp_Humidity_value_Handler(uint8_t hum_value);


void Set_LCD_Timer_Numbers_FiveSixSeveEight_Hours(void);

void lcd_power_off_handler(void);


void power_off_disp_fan_run_handler(void);


void numbers_six_seven_init(void);


void LCD_Disp_Temperature_Value_Handler(void);


void LCD_disp_default_FiveSixSeveEight_Codes(void);

void fan_default_warning_fun(void);



void ptc_high_temp_warning_fun(void);


#endif 


