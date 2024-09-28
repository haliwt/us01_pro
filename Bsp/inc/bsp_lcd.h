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


#define WIFI_Symbol     		0x01 //addr 0xC5
#define WIFI_NO_Symbol 

#define LINE_Symbol             0x01 //addr  0xC2


#define AI_Symbol    			0x01 //addr 0xC3
#define AI_NO_Symbol            0x0


#define  T3                     0X01

#define DRY_Symbol              0x02  //addr 0xC2 ->T4
#define DRY_NO_Symbol           0x0

#define KILL_Symbol             0x04  //addr 0xC2 ->T5
#define KILL_NO_Symbol           0x0

#define BUG_Symbol            0x08   //addr 0xC2 ->T6
#define BUG_NO_Symbol         0x0

#define TEMP_Symbol              0x01     //addr 0xC4
#define HUMI_Symbol              0x01      //addr  0xC9

#define TWO_DOT_Symbol           0x01       //addr 0xCB

#define T9                       0x01
#define T10                      0x08      //addr 0xCF
#define T11                      0x04      //addr 0xCF
#define T12                      0x02      //addr 0xCF
#define T16                      0x01     //addr 0xCF

#define T13                      0x01      //addr 0xCE
#define T14                      0x01      //addr 0xCC
#define T15                      0x01      //addr 0xCA
#define WIND_T16                 0x01      //addr 0xCF

#define T17_T18_T19				 0xE0  
#define GLASS_T17                0x80
#define GLASS_T18                0x40
#define GLASS_T19                0x20
#define WIND_SPEED_ONE           0x80
#define WIND_SPEED_TWO           0xC0
#define WIND_SPEED_FULL          0xE0

//Low 4bit 
#define seg_f   		0x02
#define seg_g   		0x04
#define seg_e	        0x08

//High 4bit
#define seg_a              0x10
#define seg_b              0x20
#define seg_c              0x40
#define seg_d              0x80

#define  COLON_SYMBOL                    0x01
#define  NO_COLON_SYMBOL                 0x00



#define LUM_VALUE      0X94//0x94//0x92//0x93//0x95//0x94//0x97(max)

#define MAX_LUM_VALUE  0x9F



extern const uint8_t lcdNumber1_Low[] ;// ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern  const uint8_t  lcdNumber1_High[];//={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};


extern const uint8_t lcdNumber2_Low[] ;// ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern const uint8_t lcdNumber2_High[] ;//={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

extern const uint8_t lcdNumber3_Low[]  ;//={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern const uint8_t lcdNumber3_High[] ;//={0xF0,0,0xD0, 0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

extern const uint8_t lcdNumber4_Low[]  ;//={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern const uint8_t lcdNumber4_High[] ;//={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

extern const uint8_t lcdNumber5_Low[]  ;//={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern const uint8_t lcdNumber5_High[] ;//={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

extern const uint8_t lcdNumber6_Low[]  ;//={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern const uint8_t lcdNumber6_High[] ;//={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

extern const uint8_t lcdNumber7_Low[]  ;//={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern const uint8_t lcdNumber7_High[] ;//={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

extern const uint8_t lcdNumber8_Low[] ;// ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
extern const uint8_t lcdNumber8_High[] ;//={0xF0,  0, 0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

//"Er" ->digital positon '5''6'

extern const uint8_t lcdNumber5_Low_E[] ;// ={0x04};
extern const uint8_t lcdNumber5_High_E[];// ={0xF0};

extern const uint8_t lcdNumber6_Low_r[];//={0x04};
extern const uint8_t lcdNumber6_High_r[] ;//={0x40};





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
     uint8_t gTimer_disp_colon_icon;
	
	
}lcd_ref;



extern lcd_ref glcd_t; 

void LcdDisp_Init(void);




void LCD_Display_Wind_Icon_Handler(void);


void Wifi_Icon_FastBlink(void);
void Lcd_Display_Off(void);


void Lcd_Display_Off(void);


void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat);



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




void Set_LCD_Timer_Numbers_FiveSixSeveEight_Hours(void);

void lcd_power_off_handler(void);


void power_off_disp_fan_run_handler(void);


void numbers_six_seven_init(void);


void LCD_Disp_Temperature_Value_Handler(void);

void LCD_Timer_Colon_Flicker(uint8_t sel);



void LCD_disp_default_FiveSixSeveEight_Codes(void);



void fan_default_warning_fun(void);


void ptc_high_temp_warning_fun(void);


void set_timer_timing_blink_fun(uint8_t hours_n,uint8_t minutes_n);



#endif 


