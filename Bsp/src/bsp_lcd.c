#include "bsp_lcd.h"
#include "bsp.h"

lcd_ref glcd_t; 


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




const unsigned char segNumber_Low[]={
 
         seg_b+seg_c,        		      	// char "0"  	0x00
		 seg_b+seg_c,                      	// char "1"  	0x01
		 seg_b+seg_g,              		  	// char "2"  	0x02
		 seg_b+seg_g+seg_c,               	// char "3"  	0x03
		 seg_b+seg_g+seg_c,               	// char "4"  	0x04
		 seg_g+seg_c,              			// char "5"  	0x05
		 seg_g+seg_c,              			// char "6"  	0x06
		 seg_b+seg_c,                    	// char "7"  	0x07
		 seg_b+seg_g+seg_c,  		        // char "8"  	0x08
		 seg_b+seg_g+seg_c,        			// char "9"  	0x09
	     0                                  // char "null"  0x0A



};


const unsigned char segNumber_High[]={
         seg_a+seg_f+seg_e+seg_d,        // char "0"  		0x00
		 0,                				 // char "1"  		0x01
		 seg_a+seg_e+seg_d,              // char "2"  		0x02
		 seg_a+seg_d,                    // char "3"  		0x03
		 seg_f,                          // char "4"  		0x04
		 seg_a+seg_f+seg_d,              // char "5"  		0x05
		 seg_a+seg_f+seg_e+seg_d,        // char "6"  		0x06
		 seg_a,                    		 // char "7"  		0x07
		 seg_a+seg_f+seg_e+seg_d,  		 // char "8"  		0x08
		 seg_a+seg_f+seg_d,        		 // char "9"  		0x09
         0                               // char "NLL"  	0x16



};

static const uint8_t lcdNumber1_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t  lcdNumber1_High[]={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};


static const uint8_t lcdNumber2_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber2_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber3_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber3_High[] ={0xF0,0,0xD0, 0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber4_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber4_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber5_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber5_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber6_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber6_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber7_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber7_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber8_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber8_High[] ={0xF0,  0, 0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

//"Er" ->digital positon '5''6'

static const uint8_t lcdNumber5_Low_E[]  ={0x04};
static const uint8_t lcdNumber5_High_E[] ={0xF0};

static const uint8_t lcdNumber6_Low_r[]={0x04};
static const uint8_t lcdNumber6_High_r[] ={0x40};







lcd_ref glcd_t; 

static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);
static void TIM1723_Write_Cmd(uint8_t cmd);
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat);



//static void LCD_Disp_Temperature_Value_Handler(void);

/*****************************************************
 * 
 * Function Name:
 * Function:
 * Input Ref:
 * Return Ref:
 * 
******************************************************/
static void TM1723_Start(void)
{
  TM1723_STB_SetLow();
	
}
static void TM1723_Stop(void)
{
   TM1723_STB_SetHigh();

}

static void TM1723_Write_OneByte(uint8_t data)
{
	uint8_t i; 
	
	for(i=0;i<8;i++){
		
	TM1723_CLK_SetLow();
	 if(data & 0x01){
	     TM1723_DIO_SetHigh(); //TM1723 high of data to IC
		  
	 }
	 else{
	     TM1723_DIO_SetLow(); //TM1723 low level of data to IC
		  
	 }
   
    delay_us(100);
    data =data>>1;//
	 
	 TM1723_CLK_SetHigh();
	 //data =data>>1;//
	  delay_us(2);
	// data >>=1;//
	
  
     
 }

}
static void TIM1723_Write_Cmd(uint8_t cmd)
{
    TM1723_CLK_SetHigh();
	TM1723_Start();
	TM1723_Write_OneByte(cmd);

	TM1723_Stop();
 
}
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat)
{
  
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   TM1723_Write_OneByte(addr);
  
   TM1723_Write_OneByte(dat);
   
   TM1723_STB_SetHigh();

}





/*****************************************************
 * 
 * Function Name:  void lcd_disp_ai_icon(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
******************************************************/
void lcd_disp_ai_icon(void)
{

  if(ai_mode_state()== 1){ //AI state 
 
  
    TM1723_Write_Display_Data(0xC3,lcdNumber1_Low[glcd_t.number1_low]+AI_Symbol+lcdNumber2_High[glcd_t.number2_high] & 0xFF);//display  "AI icon"
  }
  else{
    
     
     TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[glcd_t.number1_low])+lcdNumber2_High[glcd_t.number2_high] & 0xFE);//don't display "AI icon"
  }


}

/********************************************************************
 * 
 * Function Name: void Disip_Wifi_Icon_State(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
************************************************************************/
void Disip_Wifi_Icon_State(void)
{
   static uint8_t disp_wifi_icon_flag;

   if(gkey_t.wifi_led_fast_blink_flag==0){
   if(wifi_link_net_state() ==0){

      if(gctl_t.gTimer_wifi_blink < 1  ){
         
          TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi
      }
      else if(gctl_t.gTimer_wifi_blink  > 0 && gctl_t.gTimer_wifi_blink  < 2){
        
          TM1723_Write_Display_Data(0xC5,(WIFI_NO_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi 
      }
      else if(gctl_t.gTimer_wifi_blink  > 1){

        gctl_t.gTimer_wifi_blink =0;

      }
      

     }
     else if(wifi_link_net_state() ==1){

         
         TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi
      }
  }
  else{
    if(wifi_link_net_state() ==0){
    
          if(gctl_t.gTimer_wifi_fast_blink < 19  ){ //9 * 10ms
             
              TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi
      
          }
          else if(gctl_t.gTimer_wifi_fast_blink  > 18 && gctl_t.gTimer_wifi_fast_blink < 28){
              
                TM1723_Write_Display_Data(0xC5,(WIFI_NO_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi 
          }
          else if(gctl_t.gTimer_wifi_fast_blink > 27){
    
           gctl_t.gTimer_wifi_fast_blink =0;
           disp_wifi_icon_flag=0;
    
          }
          
    
       }
       else if(wifi_link_net_state() ==1 && disp_wifi_icon_flag==0){

            disp_wifi_icon_flag ++;
            TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi

       }
    }


}
/*****************************************************************************
 * 
 * Function Name:  void LCD_Disp_Temperature_Value_Handler(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Disp_Temperature_Value_Handler(void)
{
  //number '3' 
   if(gctl_t.ptc_flag==1 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag==1){
		 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
    }
    else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag ==1 && gctl_t.ultrasonic_flag==1){
		 	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
    }
    else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag ==0 && gctl_t.ultrasonic_flag==1){
		 	TM1723_Write_Display_Data(0xC2,(0X01+BUG_Symbol+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
    }else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag==0){
		 	TM1723_Write_Display_Data(0xC2,(0X01+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==1 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag==0){
     	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol)+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag ==1 && gctl_t.ultrasonic_flag==0){
     	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol)+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==1 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag==0){
     	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol)+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==1 && gctl_t.plasma_flag ==0 && gctl_t.ultrasonic_flag==1){
     	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+BUG_Symbol)+lcdNumber1_High[glcd_t.number1_high]) & 0xff);//display digital "temp
     }
		 //display addres 0xC3 -> AI icon
		 if(gctl_t.ai_flag ==1)
	        TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[glcd_t.number1_low]+AI_Symbol+lcdNumber2_High[glcd_t.number2_high]) & 0xff);//display  "AI icon
         else
		 	TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[glcd_t.number1_low]+AI_NO_Symbol+lcdNumber2_High[glcd_t.number2_high]) & 0xff);//display  "AI icon

		 //display address 0xC4 -> temperature icon T7
		 TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber2_Low[glcd_t.number2_low]+lcdNumber3_High[glcd_t.number3_high])&0xff);//display "t,c"


}


void lcd_donot_temp_value_fun(void)
{

    //number '3' 
   if(gctl_t.ptc_flag==1 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag==1){
		 	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
    }
    else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag ==1 && gctl_t.ultrasonic_flag==1){
		 	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
    }
    else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag ==0 && gctl_t.ultrasonic_flag==1){
		 	TM1723_Write_Display_Data(0xC2,(0X01+BUG_Symbol+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
    }else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag==0){
		 	TM1723_Write_Display_Data(0xC2,(0X01+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==1 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag==0){
     	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol)+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==0 && gctl_t.plasma_flag ==1 && gctl_t.ultrasonic_flag==0){
     	TM1723_Write_Display_Data(0xC2,((0X01+KILL_Symbol)+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==1 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag==0){
     	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol)+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
     }
     else if(gctl_t.ptc_flag ==1 && gctl_t.plasma_flag ==0 && gctl_t.ultrasonic_flag==1){
     	TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+BUG_Symbol)+lcdNumber1_High[0x0A]) & 0xff);//display digital "temp
     }
		 //display addres 0xC3 -> AI icon
		 if(gctl_t.ai_flag ==1)
	        TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[0x0A]+AI_Symbol+lcdNumber2_High[0x0A]) & 0xff);//display  "AI icon
         else
		 	TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[0x0A]+AI_NO_Symbol+lcdNumber2_High[0x0A]) & 0xff);//display  "AI icon

		 //display address 0xC4 -> temperature icon T7
		 TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber2_Low[0x0A]+lcdNumber3_High[glcd_t.number3_high])&0xff);//display "t,c"


}
/*****************************************************************************
 * 
 * Function Name:  void LCD_Disp_Humidity_value_Handler(void)
 * Function: read humidity of value from sensor of temperature
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Disp_Humidity_value_Handler(uint8_t hum_value)
{

    glcd_t.number3_high =  hum_value /10;
    //glcd_t.number3_low  =   hum_value /10;
    glcd_t.number3_low =  glcd_t.number3_high ;

   glcd_t.number4_low =   hum_value %10;
   //glcd_t.number4_high =  hum_value  %10;
    glcd_t.number4_high =    glcd_t.number4_low;

   if(gkey_t.key_mode != mode_set_timer){


   TM1723_Write_Display_Data(0xC4,(0x01+lcdNumber2_Low[glcd_t.number2_low]+lcdNumber3_High[glcd_t.number3_high])&0xff);

   if(wifi_link_net_state()==1){

      TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi
   }
   else{
       TM1723_Write_Display_Data(0xC5,(WIFI_NO_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi 

   }
   
   if( gkey_t.key_mode == disp_works_timing){
       
     if((gpro_t.global_temporary_set_timer_flag == 1) &&   gpro_t.gTimer_set_timer_times <  11 ){
          glcd_t.number5_high = 0;
          TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);

       }
       else{
       glcd_t.number5_high = gpro_t.disp_works_hours_value /10;
       TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);

       }
    }
   else if(gkey_t.key_mode  == disp_timer_timing){
        
        if(gkey_t.set_timer_timing_success ==0){
            glcd_t.number5_high = 0;

         }
        else
          glcd_t.number5_high =  gpro_t.set_timer_timing_hours /10;
        
        TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);

   }

    }
    
}

/*****************************************************************************
 * 
 * Function Name:  void LCD_Number_FiveSixSeveEight_Hours(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Number_FiveSixSeveEight_Hours(uint8_t hours_n,uint8_t minutes_n)
{

   static uint8_t alternate_flag;

    glcd_t.number5_low = hours_n  /10 ;
  
	glcd_t.number5_high = hours_n  /10 ;


	glcd_t.number6_low = hours_n  %10 ;
   
	glcd_t.number6_high = glcd_t.number6_low ;

    //display minutes
    glcd_t.number7_low = minutes_n / 10 ;
   
	glcd_t.number7_high =  glcd_t.number7_low ;


	glcd_t.number8_low = minutes_n % 10 ;
    
	glcd_t.number8_high = glcd_t.number8_low ;
   
    //FAN LEAF T14

    if(gctl_t.ptc_warning ==1 || gctl_t.fan_warning ==1){


              if(gctl_t.ptc_warning ==1 &&  gctl_t.fan_warning ==0){
        		
        	       TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]+WIND_SPEED_ONE);//
              }
              else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0){

                   TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[2]+WIND_SPEED_ONE);//display "t,c"


              }
              else if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==1){

                  if(glcd_t.gTimer_fan_blink < 50){
                      if(alternate_flag==0){
                        alternate_flag++;
                        TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]+WIND_SPEED_ONE);//display "t,c"

                      }
                  }
                  else if(glcd_t.gTimer_fan_blink >50 && glcd_t.gTimer_fan_blink < 100){

                     if(alternate_flag > 0){
                         alternate_flag=0;
                         TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[2]+WIND_SPEED_ONE);//display "t,c"
                     }


                  }
                  else if(glcd_t.gTimer_fan_blink > 100){
                      glcd_t.gTimer_fan_blink =0;


                  }

                  


              }

     }
     else if(wifi_t.set_wind_speed_value == 0){
        if(glcd_t.gTimer_fan_blink < 15){

            

                  
              TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
              TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);
                  

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
              // TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//

                
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

                 /*******************************/

                
              
                  TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
                  TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);  
                  TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);

        
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "close"
                
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//
                

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
         
        
    }
    else if(wifi_t.set_wind_speed_value== 1){
         if(glcd_t.gTimer_fan_blink < 15){


               
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
      
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

                TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
                 TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "close"
                 TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
        
    }
    else if(wifi_t.set_wind_speed_value==2){
         if(glcd_t.gTimer_fan_blink < 15){


                TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
              
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

                   TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "close"
                
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
        
    }

}

/*****************************************************************************
 * 
 * Function Name:  void LCD_disp_default_FiveSixSeveEight_Codes(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_disp_default_FiveSixSeveEight_Codes(void)
{

   static uint8_t alternate_flag;
   //FAN LEAF T14

    if(gctl_t.ptc_warning ==1 || gctl_t.fan_warning ==1){


              if(gctl_t.ptc_warning ==1 &&  gctl_t.fan_warning ==0){
        		
        	       TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]+WIND_SPEED_ONE);//
              }
              else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0){

                   TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[2]+WIND_SPEED_ONE);//display "t,c"


              }
              else if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==1){

                  if(glcd_t.gTimer_fan_blink < 50){
                      if(alternate_flag==0){
                        alternate_flag++;
                        TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]+WIND_SPEED_ONE);//display "t,c"

                      }
                  }
                  else if(glcd_t.gTimer_fan_blink >50 && glcd_t.gTimer_fan_blink < 100){

                     if(alternate_flag > 0){
                         alternate_flag=0;
                         TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[2]+WIND_SPEED_ONE);//display "t,c"
                     }


                  }
                  else if(glcd_t.gTimer_fan_blink > 100){
                      glcd_t.gTimer_fan_blink =0;


                  }

                  


              }

     }
     else if(wifi_t.set_wind_speed_value == 0){
        if(glcd_t.gTimer_fan_blink < 15){

            

                  
              TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
              TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);
                  

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
              // TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//

                
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

                 /*******************************/

                
              
                  TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
                  TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);  
                  TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);

        
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "close"
                
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//
                

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
         
        
    }
    else if(wifi_t.set_wind_speed_value== 1){
         if(glcd_t.gTimer_fan_blink < 15){


               
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
      
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

                TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
                 TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "close"
                 TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
        
    }
    else if(wifi_t.set_wind_speed_value==2){
         if(glcd_t.gTimer_fan_blink < 15){


                TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
              
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

                   TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "close"
                
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
        
    }

}


/*****************************************************************************
 * 
 * Function Name:  void Set_LCD_Timer_Numbers_FiveSixSeveEight_Hours(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void Set_LCD_Timer_Numbers_FiveSixSeveEight_Hours(void)
{


    static uint8_t alternate_flag;
   
    //FAN LEAF T14

    

    if(gctl_t.ptc_warning ==1 || gctl_t.fan_warning ==1){


              if(gctl_t.ptc_warning ==1 &&  gctl_t.fan_warning ==0){
        		
        	       TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]+WIND_SPEED_ONE);//display "t,c"
              }
              else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0){

                   TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[2]+WIND_SPEED_ONE);//display "t,c"


              }
              else if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==1){

                  if(glcd_t.gTimer_fan_blink < 50){
                      if(alternate_flag==0){
                        alternate_flag++;
                        TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]+WIND_SPEED_ONE);//display "t,c"

                      }
                  }
                  else if(glcd_t.gTimer_fan_blink >50 && glcd_t.gTimer_fan_blink < 100){

                     if(alternate_flag > 0){
                         alternate_flag=0;
                         TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[2]+WIND_SPEED_ONE);//display "t,c"
                     }


                  }
                  else if(glcd_t.gTimer_fan_blink > 100){
                      glcd_t.gTimer_fan_blink =0;


                  }

                  


              }

     }
     else if(wifi_t.set_wind_speed_value == 0){
        if(glcd_t.gTimer_fan_blink < 15){

              if(gkey_t.key_mode == mode_set_timer && gpro_t.gTimer_timer_led_blink < 2){

                 glcd_t.number5_low =  0x0A ;
                  glcd_t.number5_high =  0x0A ;
               
                  glcd_t.number6_low  =  0x0A; //
                  glcd_t.number6_high =  0x0A; //
                  
                   //dispaly minutes 
                  glcd_t.number7_low =   0x0A;
                  glcd_t.number7_high =   0x0A;
               
                  glcd_t.number8_low =   0x0A;
                  glcd_t.number8_high =   0x0A;

                  
                  
               TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
    
               TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);

                TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
              
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//


              }
              else if(gkey_t.key_mode == mode_set_timer &&  gpro_t.gTimer_timer_led_blink > 1  &&   gpro_t.gTimer_timer_led_blink < 10){
                
                    glcd_t.number5_low =  gpro_t.set_timer_timing_hours  / 10 ;
                    glcd_t.number5_high =  glcd_t.number5_low;// gpro_t.set_timer_timing_hours  / 10 ;
              
                    glcd_t.number6_low  = gpro_t.set_timer_timing_hours% 10; //
                    glcd_t.number6_high =   glcd_t.number6_low ;//gpro_t.set_timer_timing_hours % 10; //
                    
                     //dispaly minutes 
                    glcd_t.number7_low =  0;
                    glcd_t.number7_high =  0;
              
                    glcd_t.number8_low = 0;
                    glcd_t.number8_high =   0;

                    TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
    
                     TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);

                     TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
                    TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
                    TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "t,c"
                    TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//

                    


              }
              else if(gkey_t.key_mode != mode_set_timer ){

              TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
    
              TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);
                  

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//

                }
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

                 /*******************************/

                  if(gkey_t.key_mode == mode_set_timer && gpro_t.gTimer_timer_led_blink < 1){

                 glcd_t.number5_low =  0x0A ;
                  glcd_t.number5_high =  0x0A ;
               
                  glcd_t.number6_low  =  0x0A; //
                  glcd_t.number6_high =  0x0A; //
                  
                   //dispaly minutes 
                  glcd_t.number7_low =   0x0A;
                  glcd_t.number7_high =   0x0A;
               
                  glcd_t.number8_low =   0x0A;
                  glcd_t.number8_high =   0x0A;

                 TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
    
                TM1723_Write_Display_Data(0xCB,(lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);



                TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "close"
                 TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//


              }
              else if(gkey_t.key_mode == mode_set_timer &&   gpro_t.gTimer_timer_led_blink > 0  &&   gpro_t.gTimer_timer_led_blink < 2){
                
                    glcd_t.number5_low =  gpro_t.set_timer_timing_hours  / 10 ;
                    glcd_t.number5_high =  glcd_t.number5_low; //gpro_t.set_timer_timing_hours  / 10 ;
              
                    glcd_t.number6_low  = gpro_t.set_timer_timing_hours% 10; //
                    glcd_t.number6_high =  glcd_t.number6_low;//gpro_t.set_timer_timing_hours % 10; //
                    
                     //dispaly minutes 
                    glcd_t.number7_low =  0;
                    glcd_t.number7_high =  0;
              
                    glcd_t.number8_low = 0;
                    glcd_t.number8_high =   0;

                    TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
    
                    TM1723_Write_Display_Data(0xCB,(lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);

                   TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "close"
                 TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

                    


              }
              else if(gkey_t.key_mode != mode_set_timer ){
              
                  TM1723_Write_Display_Data(0xC9,(HUM_T8+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High[glcd_t.number5_high]) & 0xff);//display digital '4,5'
                      
                      TM1723_Write_Display_Data(0xCB,(T9+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]) & 0xff);

        
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "close"
                 TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//
                }

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
         
        
    }
    else if(wifi_t.set_wind_speed_value== 1){
         if(glcd_t.gTimer_fan_blink < 15){


               

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "close"
                 TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
        
    }
    else if(wifi_t.set_wind_speed_value==2){
         if(glcd_t.gTimer_fan_blink < 15){

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "close"
                 TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
        
    }

}


/*****************************************************************************
 * 
 * Function Name:  
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/


/*****************************************************************************
 * 
 * Function Name: static LCD_Fault_Numbers_Code(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/

/*************************************************************************************
	*
	*Function Name: LCD_Fault_Numbers_Code(void)
	*Function : display error of code
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void LCD_Fault_Numbers_Code(void)
{

  static uint8_t alternate_flag ;
 // display "E"

glcd_t.number7_low = 0;
glcd_t.number7_high = 0;



  TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High_E[0]));//display digital 'E'
   
 
 //display 'r' 
 

 //display error code "01"--ptc_warning , "02"--fan_warning

//number '1' or '2'
 
  //"01" or "o2" blink
  if(glcd_t.gTimer_error_times < 2){ //500ms
  	if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==0){ //code is "02" ==1){ 

         //TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xffff); //numbers : '2' addr: 0xC
         glcd_t.number8_low = 1;
        glcd_t.number8_high = 1;
        
        TM1723_Write_Display_Data(0xCA,lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'
         
         TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[glcd_t.number7_high]);//
         TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]);//display "1"
         TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+ WIND_SPEED_FULL);//display "t,c
        TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));// display fan of run leaf .
      
     }
	  else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0){ //code is "02"){

        glcd_t.number8_low = 2;
        glcd_t.number8_high = 2;
        
      TM1723_Write_Display_Data(0xCA,lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r' 
  	   TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[glcd_t.number7_high]);// 
       TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[ glcd_t.number8_high]);//display "t,c
       TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+ T17_T18_T19);//display "t,c

       

     }
     else if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==1){ //code is "02" ==1){ 

          if(alternate_flag ==0 ){
                alternate_flag =1;
             glcd_t.number7_low = 0;
             glcd_t.number7_high = 0;

              glcd_t.number8_low = 1;
             glcd_t.number8_high = 1;
             TM1723_Write_Display_Data(0xCA,lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'
             TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[glcd_t.number7_high]);//
             TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]);//display "1"
             TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+ T17_T18_T19);//display "t,c
            }
            else if(alternate_flag == 2){
             alternate_flag =3;
             glcd_t.number7_low = 0;
             glcd_t.number7_high = 0;
             glcd_t.number8_low = 2;
             glcd_t.number8_high = 2;
            TM1723_Write_Display_Data(0xCA,lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'
            TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[glcd_t.number7_high]);// 
            TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[2]);//display "t,c
            TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+ T17_T18_T19);//display "t,c
            }

       

         

      }
   }
  else if(glcd_t.gTimer_error_times > 1 && glcd_t.gTimer_error_times < 4){


   if(gctl_t.ptc_warning ==1 && gctl_t.fan_warning ==0 ){ //code is "02" ==1){ 
      
      TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'

       TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[10]);//
       TM1723_Write_Display_Data(0xCC,lcdNumber7_Low[10]+lcdNumber8_High[0x0A]);//display "t,c
       TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[0x0A]+ WIND_SPEED_FULL);//display "t,c
       TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//display fan of leaf .

     }
     else if(gctl_t.fan_warning ==1 && gctl_t.ptc_warning ==0 ){ //code is "02"){
               
      TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r' 

       TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[10]);//
       TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[10]+lcdNumber8_High[10]);//display "t,c
       TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[10]+ T17_T18_T19);//display "t,c
       

     }
     else if(gctl_t.ptc_warning==1 &&  gctl_t.fan_warning ==1 ){

       if(alternate_flag ==1) alternate_flag =2;
       else if(alternate_flag ==3) alternate_flag =0;
      TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'
      
       TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[10]);//
       TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[10]+lcdNumber8_High[10]);//display
       TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[10]+T17_T18_T19);//display
            
       
       }
   }
   else if(glcd_t.gTimer_error_times > 3){
      glcd_t.gTimer_error_times =0;
      

  }

}
 
/*****************************************************************************
 * 
 * Function Name:  void LCD_Wind_Icon(uint8_t wind_sppeed)
 * Function: run wind speed value 
 * Input Ref:  wind_speed =0, is max ,wind_speed= 1, middle, wind_speed =2 is low
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Wind_Run_Icon(uint8_t wind_speed)
{

   //wind run icon
  if(gctl_t.fan_warning ==0  && gctl_t.ptc_warning ==0){

   switch(wind_speed){


    case 0: //max wind speed.
         if(glcd_t.gTimer_fan_blink < 15){

               
          
                TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
                
                TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
                TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "t,c"
                TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//

            
           

        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close

            TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
              
            TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
            TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_FULL);//display "close"
            TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//
          
              

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
            
             
        }
         
    break;

    case 1: //middle 
         if(glcd_t.gTimer_fan_blink < 15){

               
            
               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
               
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close
             
             
        		TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	    TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_TWO);//display "close"
                TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        	    TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

              

        }
        else if(glcd_t.gTimer_fan_blink > 29){
            
        	glcd_t.gTimer_fan_blink=0;
        }
        
        


    break;


    case 2: //lowd 

      if(glcd_t.gTimer_fan_blink < 15){

               TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
               TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
               TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "t,c"
               TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
        }
        else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close
        		  TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[glcd_t.number7_low]+lcdNumber8_High[glcd_t.number8_high]) & 0xff);
        	     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[glcd_t.number8_low]+WIND_SPEED_ONE);//display "close"
                 TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[glcd_t.number5_low]+lcdNumber6_High[glcd_t.number6_high]) & 0xff);
        	      TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//

        }
        else if(glcd_t.gTimer_fan_blink > 29){
        	glcd_t.gTimer_fan_blink=0;
        }
        
    break;

   }
	  
  }
}
/*****************************************************************************
 * 
 * Function Name: void Display_Wind_Icon_Inint(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/

/*****************************************************************************
 * 
 * Function Name:  static LCD_Timer_Colon_Flicker(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Timer_Colon_Flicker(void)
{
//  if(gpro_t.power_on_every_times < 20 &&  gkey_t.key_mode != mode_set_timer ){
//       gpro_t.power_on_every_times++;
//
//
//       LCD_Number_FiveSixSeveEight_Hours(gpro_t.disp_works_hours_value,gpro_t.disp_works_minutes_value);
//
//  }
//  else{


  
   if(gkey_t.key_mode != mode_set_timer || (gkey_t.key_mode != fan_warning  || gkey_t.key_mode != ptc_warning)){

   if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
   if(glcd_t.gTimer_colon_blink < 20){ 

        
         if(gkey_t.key_mode  == disp_works_timing){

                 if((gpro_t.global_temporary_set_timer_flag == 1) &&   gpro_t.gTimer_set_timer_times <  11 ){

                       glcd_t.number6_low = 0 ;
                       glcd_t.number7_high = 0 ;

                       TM1723_Write_Display_Data(0xCB,COLON_SYMBOL+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]);//display "6,7"
                 }
                 else{
              	   glcd_t.number6_low = gpro_t.disp_works_hours_value %10 ;
                  glcd_t.number7_high = gpro_t.disp_works_minutes_value /10 ;
                  TM1723_Write_Display_Data(0xCB,COLON_SYMBOL+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]);//display "6,7"
                }
           }
           else if(gkey_t.key_mode  == disp_timer_timing){
              	glcd_t.number6_low = gpro_t.set_timer_timing_hours %10 ;
                glcd_t.number7_high = gpro_t.set_timer_timing_minutes / 10 ;
              TM1723_Write_Display_Data(0xCB,COLON_SYMBOL+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]);//display "6,7"
         }

        }
       else if(glcd_t.gTimer_colon_blink > 19  && glcd_t.gTimer_colon_blink < 41){

    
     
           if(gkey_t.key_mode  == disp_works_timing){

                  if((gpro_t.global_temporary_set_timer_flag == 1) &&   gpro_t.gTimer_set_timer_times <  11 ){

                       glcd_t.number6_low = 0 ;
                       glcd_t.number7_high = 0 ;

                       TM1723_Write_Display_Data(0xCB,NO_COLON_SYMBOL+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]);//display "6,7"
                 }
                 else{

               	    glcd_t.number6_low = gpro_t.disp_works_hours_value %10 ;
                    glcd_t.number7_high = gpro_t.disp_works_minutes_value / 10 ;

                    TM1723_Write_Display_Data(0xCB,NO_COLON_SYMBOL+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]);//display "6,7"
                }
            }
            else  if(gkey_t.key_mode  == disp_timer_timing){

               	glcd_t.number6_low = gpro_t.set_timer_timing_hours %10 ;
                glcd_t.number7_high =  gpro_t.set_timer_timing_minutes / 10 ;
                
               TM1723_Write_Display_Data(0xCB,NO_COLON_SYMBOL+lcdNumber6_Low[glcd_t.number6_low]+lcdNumber7_High[glcd_t.number7_high]);//display "6,7"
            }
     }
     else if(glcd_t.gTimer_colon_blink > 40){

      glcd_t.gTimer_colon_blink =0;

   }
  
   
   TIM1723_Write_Cmd(LUM_VALUE);//(0x9B);
   }
    }
 }





/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Off(void)
	*Function : don't display any one
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void Lcd_Display_Off(void)
{

	 TIM1723_Write_Cmd(CloseDispTM1723);//(0x80);

}

/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Off(void)
	*Function : don't display any one
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void Disp_HumidityTemp_Value(void)
{


    lcd_disp_ptc_value(gctl_t.dht11_temp_value);
    LCD_Disp_Humidity_value_Handler(  gctl_t.dht11_humidity_value);
   
}







/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Dry_Icon(void)
	*Function : display dry of symbol
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void disp_ai_iocn(void)
{

    if(ai_mode_state()== 1){ //AI state 
     //number '1'
        TM1723_Write_Display_Data(0xC3,AI_Symbol+lcdNumber1_Low[glcd_t.number1_low]+lcdNumber2_High[glcd_t.number2_high]);//display  "AI icon"
     }
     else{
           //number '1'
       TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[glcd_t.number1_low])+lcdNumber2_High[glcd_t.number2_high]);//don't display "AI icon"

     }

}

void disp_ai_symbol(void)
{
  TM1723_Write_Display_Data(0xC3,AI_Symbol+lcdNumber1_Low[glcd_t.number1_low]+lcdNumber2_High[glcd_t.number2_high]);//display  "AI icon"

}

void donot_disp_ai_symbol(void)
{

   TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[glcd_t.number1_low])+lcdNumber2_High[glcd_t.number2_high]);//don't display "AI icon"

}
/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Dry_Icon(void)
	*Function : display dry of symbol
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void Disp_Dry_Icon(void)
{
  
   Display_Kill_Dry_Ster_Icon();

}

/*************************************************************************************
	*
	*Function Name: void Wifi_Icon_FastBlink(void)
	*Function : 
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void Wifi_Icon_FastBlink(void)
{
    if(gkey_t.wifi_led_fast_blink_flag==1){
    if(wifi_link_net_state() ==0){
    
          if(gctl_t.gTimer_wifi_blink < 1  ){
              TM1723_Write_Display_Data(0xC5,(WIFI_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi
          }
          else if(gctl_t.gTimer_wifi_blink  > 0 && gctl_t.gTimer_wifi_blink  < 2){
               TM1723_Write_Display_Data(0xC5,(WIFI_NO_Symbol+lcdNumber3_Low[glcd_t.number3_low] + lcdNumber4_High[glcd_t.number4_high]) & 0xff); //Wifi
    
          }
          else if(gctl_t.gTimer_wifi_blink  > 1){
    
            gctl_t.gTimer_wifi_blink =0;
    
          }
          
    
       }
    }

}

/*************************************************************************************
	*
	*Function Name: void LcdDisp_Init(void)
	*Function : 
	*Input Ref:
	*Return Ref:NO
	*
*************************************************************************************/
void LcdDisp_Init(void)
{
    
        TM1723_Write_Display_Data(0xC2,0x0);
        TM1723_Write_Display_Data(0xC3,0x0);
        TM1723_Write_Display_Data(0xC4,0x0);
        TM1723_Write_Display_Data(0xC5,0x0);
    
        TM1723_Write_Display_Data(0xC9,0x0);
    
        TM1723_Write_Display_Data(0xCA,0x0);
        TM1723_Write_Display_Data(0xCB,0x0);
    
        TM1723_Write_Display_Data(0xCC,0x0);
    
       TM1723_Write_Display_Data(0xCE,0x0);
       TM1723_Write_Display_Data(0xCF,0x0); 
       
    



}


/******************************************************************************
	*
	*Function Name:static void Display_Kill_Dry_Ster_Icon(void)
	*Function: display of icon , "1" -> ON ,"0"-> OFF
	*
	*
	*
******************************************************************************/
void Display_Kill_Dry_Ster_Icon(void)
{

   //number "1,2" -> temperature

	  if(gctl_t.ptc_flag==1 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag==1){

	     //display address 0xc2
	     TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[glcd_t.number1_high])&0xff);//display digital "temp
	     
		 
	  }
	  else if(gctl_t.ptc_flag==0 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag==1){

	      TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_Symbol+BUG_Symbol))+lcdNumber1_High[glcd_t.number1_high]);//display digital "temp
	    
	   }
	   else if(gctl_t.ptc_flag==0 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag ==1){

	        TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_NO_Symbol+BUG_Symbol))+lcdNumber1_High[glcd_t.number1_high]);//display digit
	        
	   }
	  else if(gctl_t.ptc_flag==0 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag ==0){

	        TM1723_Write_Display_Data(0xC2,0X01+DRY_NO_Symbol+KILL_NO_Symbol+BUG_NO_Symbol+lcdNumber1_High[glcd_t.number1_high]);//display digit
	       
	  }
	  else if(gctl_t.ptc_flag==1 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag ==1){

	        TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_NO_Symbol+BUG_Symbol))+lcdNumber1_High[glcd_t.number1_high]);//display digit
	       
	  }
	  else if(gctl_t.ptc_flag==1 && gctl_t.plasma_flag==0 && gctl_t.ultrasonic_flag ==0){

	        TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_NO_Symbol+BUG_NO_Symbol))+lcdNumber1_High[glcd_t.number1_high]);//display digit
	       
	  }
	  else if(gctl_t.ptc_flag==0 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag ==0){
	   
			  TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_Symbol+BUG_NO_Symbol))+lcdNumber1_High[glcd_t.number1_high]);//display digit
			  
	 }
	  else if(gctl_t.ptc_flag==1 && gctl_t.plasma_flag==1 && gctl_t.ultrasonic_flag ==0){
		 
				TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_NO_Symbol))+lcdNumber1_High[glcd_t.number1_high]);//display digit
			
	   }

  
   TIM1723_Write_Cmd(LUM_VALUE);
   
}


/**********************************************************************************************************
*
*	函 数 名: void lcd_power_off_handler(void)
*	功能说明:
*	形    参: 无
*	返 回 值: 无
*
**********************************************************************************************************/
void lcd_power_off_handler(void)
{
    

    TM1723_Write_Display_Data(0xC2,0x0);
    TM1723_Write_Display_Data(0xC3,0x0);
    TM1723_Write_Display_Data(0xC4,0x0);
    TM1723_Write_Display_Data(0xC5,0x0);

    TM1723_Write_Display_Data(0xC9,0x0);

    TM1723_Write_Display_Data(0xCA,0x0);
    TM1723_Write_Display_Data(0xCB,0x0);

    TM1723_Write_Display_Data(0xCC,0x0);

   TM1723_Write_Display_Data(0xCE,0x0);
  // TM1723_Write_Display_Data(0xCF,0x0); 


   
    power_off_disp_fan_run_handler();

 }

/**********************************************************************************************************
*
*	Function Name: void power_off_disp_fan_run_handler(void)
*	Function:
*	Input Ref: NO
*	Return Ref: NO
*
**********************************************************************************************************/
void power_off_disp_fan_run_handler(void)
{
    if(glcd_t.gTimer_fan_blink < 15){

           TM1723_Write_Display_Data(0xCA,(lcdNumber5_Low[0x0A]+lcdNumber6_High[0x0A]) & 0xff);
           TM1723_Write_Display_Data(0xCB,(lcdNumber6_Low[0x0A]+lcdNumber7_High[0x0A]) & 0xff);
           TM1723_Write_Display_Data(0xCC,(T14+lcdNumber7_Low[0x0A]+lcdNumber8_High[0x0A]) & 0xff);
          
           TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[0x0A]+WIND_SPEED_FULL);//display "t,c"
           TM1723_Write_Display_Data(0xCF,((T16+T12+T10)& 0x0B));//
                    
         }
         else if(glcd_t.gTimer_fan_blink > 14 && glcd_t.gTimer_fan_blink   < 30){ //close
                
                      TM1723_Write_Display_Data(0xCA,(T15+lcdNumber5_Low[0x0A]+lcdNumber6_High[0x0A]) & 0xff);

                     TM1723_Write_Display_Data(0xCB,(lcdNumber6_Low[0x0A]+lcdNumber7_High[0x0A]) & 0xff);
                     TM1723_Write_Display_Data(0xCC,(lcdNumber7_Low[0x0A]+lcdNumber8_High[0x0A]) & 0xff);
                     TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[0x0A]+WIND_SPEED_FULL);//display "close"
                    
                     TM1723_Write_Display_Data(0xCF,((T11+T16) & 0x05));//
                  
    
         }
         else if(glcd_t.gTimer_fan_blink > 29){
                glcd_t.gTimer_fan_blink=0;
         }






}

void numbers_six_seven_init(void)
{

    TM1723_Write_Display_Data(0xCA,0x01);
    TM1723_Write_Display_Data(0xCB,0x01);
    
    TM1723_Write_Display_Data(0xCC,0x01);


}

/**************************************************************************************************
*
*Function Name:void fan_default_warning_fun(void)
*Function : fan of warning ,fan of leaf stop
*
*
****************************************************************************************************/
void fan_default_warning_fun(void)
{

   TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High_E[0]));//display digital 'E'
   TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'  
    if(glcd_t.gTimer_colon_blink < 20){           
         TM1723_Write_Display_Data(0xCB,0x01+lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//display "6,7"
    }
   else if(glcd_t.gTimer_colon_blink > 19 && glcd_t.gTimer_colon_blink < 41){
      TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//
   }
   else if(glcd_t.gTimer_colon_blink > 40)
   {
      glcd_t.gTimer_colon_blink = 0;
   }
   TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[0]+lcdNumber8_High[2]);//display "02'
   TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[2]);//display "t,c"
   TM1723_Write_Display_Data(0xCF,(T10+T11+T12+T16));//

}
/**************************************************************************************************
*
*Function Name:static void ptc_high_temp_warning_fun(void)
*Function : fan of warning ,fan of leaf stop
*Input Ref:
*Return Ref:
*
****************************************************************************************************/
void ptc_high_temp_warning_fun(void)
{
   
    TM1723_Write_Display_Data(0xC9,(0x01+lcdNumber4_Low[glcd_t.number4_low]+lcdNumber5_High_E[0]));//display digital 'E'
   // TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital 'r'  
    if(glcd_t.gTimer_colon_blink < 20 ){           
        TM1723_Write_Display_Data(0xCB,0x01+lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//display "6,7"
    }
    else if(glcd_t.gTimer_colon_blink > 19 && glcd_t.gTimer_colon_blink < 41){
        TM1723_Write_Display_Data(0xCB,lcdNumber6_Low_r[0]+lcdNumber7_High[0]);//
    }
    else if(glcd_t.gTimer_colon_blink > 40)
    {
        glcd_t.gTimer_colon_blink= 0;
    }

    if(glcd_t.gTimer_colon_blink >19 && glcd_t.gTimer_colon_blink<41){

  

    
        TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display 
        TM1723_Write_Display_Data(0xCC,lcdNumber7_Low[0]+lcdNumber8_High[1]);//display "7,8'
        TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[1]);//display "t,c"
        TM1723_Write_Display_Data(0xCF,((T11+T16)& 0x05));//
               
   }
   else if(glcd_t.gTimer_colon_blink <20){
                
   
    TM1723_Write_Display_Data(0xCA,lcdNumber5_Low_E[0]+lcdNumber6_High_r[0]);//display digital '5,6'
    TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[0]+lcdNumber8_High[1]);//display "t,c
    TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[1]);//display "1"
   
    TM1723_Write_Display_Data(0xCF,((T16+T12+T10)&0x0B));//
              
  }
//  else if(glcd_t.gTimer_colon_blink > 40){
//             glcd_t.gTimer_colon_blink=0;
//  }

}


