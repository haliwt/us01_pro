#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp.h"




#define TOKEN_ID      "123"


//char *tx_data={"AT+TCMQTTPUB=\"$thing/up/property/EHQB1P53IH/UYIJIA01-a0005\",0,\"{\"method\":\"report\"\,\"clientToken\":\"up01\"\,\"params\":\"{\"open\":1\,\"temperature\":26}}\"\r\n"};
//char *tx_data={"AT+TCMQTTPUB=\"$thing/up/property/EHQB1P53IH/UYIJIA01-a0005\",0,\"{\\\"method\\\":\\\"report\\\"\\\,\\\"clientToken\\\":\\\"up01\\\"\\,\\\"params\\\":{\\\"open\\\":1\\,\\\"temperature\\\":26}}\"\r\n"};

/* MAX size of client ID */


static void Mqtt_power_off_Value(void);



static void property_report_SetOpen(uint8_t open);
static void Mqtt_Value_update_data(void);
static void mqtt_smart_phone_power_on_ref(void);




static void property_report_state(void);


static void property_report_ReadTempHum(uint8_t tempvalue,uint8_t humvalue);

static void property_report_SetTemp(uint8_t temp);
static void property_report_SetFan(uint8_t fan);
static void property_report_SetTime(uint8_t time);
static void property_report_SetState(uint8_t dat);
static void property_report_power_off_state(void);


static void property_report_update_data(void);
static void property_report_smartphone_power_on_init(void);


typedef struct {
    
    bool     open;
	bool     sonic;
	
	bool     ptc;
	bool     anion;

	uint8_t     state ; //
    
	uint8_t  find;
	uint8_t  set_temperature;

} serviceInfo;


static serviceInfo    sg_info;


// led attributes, corresponding to struct LedInfo
//static char *sg_property_name[] = {"opne", "sonic", "find", "nowtemperature","state","ptc","Anion","temperature","Humidity"};
void Mqtt_Value_Init(void)
{

    static uint8_t wind_speed_grade;
    if(wifi_t.set_wind_speed_value==0){
        wind_speed_grade=100;
     }
   
    gctl_t.gSet_temperature_value =40;
   	sg_info.open=1;
    sg_info.state=1;
    sg_info.ptc=1; 
    sg_info.anion=1;  //灭菌
	sg_info.sonic =1;  //驱虫
    sg_info.find= wind_speed_grade;
	sg_info.set_temperature = gctl_t.gSet_temperature_value ;
	
}
static void Mqtt_Value_update_data(void)
{
    
    sg_info.open = 1;
	if(gctl_t.ai_flag==0)gctl_t.ai_flag =1;
	sg_info.state = gctl_t.ai_flag;
	sg_info.ptc  = gctl_t.ptc_flag;
	sg_info.anion =gctl_t.plasma_flag;
	sg_info.sonic = gctl_t.ultrasonic_flag ;
    sg_info.find =  wifi_t.wind_txdata_tencent ; //100;//wifi_t.set_wind_speed_value;
	if(gpro_t.set_temperature_value_success==1){

         sg_info.set_temperature=  gctl_t.gSet_temperature_value;
    }
    else{
       sg_info.set_temperature = 40;

    }

}

static void Mqtt_power_off_Value(void)
{

   static uint8_t wind_speed_grade;
   wifi_t.set_wind_speed_value=0;
   if(wifi_t.set_wind_speed_value==0){
        wind_speed_grade=100;
    }
	gctl_t.gSet_temperature_value=20;
   	sg_info.open=0;
    sg_info.state=1;
    sg_info.ptc=0; 
    sg_info.anion=0;  //灭菌
	sg_info.sonic =0;  //驱虫
    sg_info.find= wind_speed_grade;
	if(gctl_t.gSet_temperature_value <20)gctl_t.gSet_temperature_value = 20;
	else if(gctl_t.gSet_temperature_value > 40 )gctl_t.gSet_temperature_value = 40;
	sg_info.set_temperature =  gctl_t.gSet_temperature_value ;
	
}

static void mqtt_smart_phone_power_on_ref(void)
{
		
    static uint8_t wind_speed_grade;
    if(wifi_t.set_wind_speed_value==0){
        wind_speed_grade=100;
     }

       sg_info.open = 1;
	   if(gctl_t.ai_flag==0)gctl_t.ai_flag =1;
	   sg_info.state = gctl_t.ai_flag;
	   sg_info.ptc	= gctl_t.ptc_flag;
	   sg_info.anion =gctl_t.plasma_flag;
	   sg_info.sonic = gctl_t.ultrasonic_flag ;
	   sg_info.find =  100;//wifi_t.set_wind_speed_value;
	   
	   sg_info.set_temperature = gctl_t.gSet_temperature_value=40;//gpro_t.gDht11_humidity;




}

/********************************************************************************
	*
	*Function Name:static void property_report_Temp_Humidity(void)
	*Function :send data to tencent cloud only read temperature and humidity of data
	*Input Ref: only read temperature value and humidiy value
	*           
	*Return Ref:
	*
********************************************************************************/
void property_topic_publish(void)
{
    static uint32_t ic_id;

    char topic[128] = {0};
    int  size;

    ic_id=HAL_GetUIDw0();
    size = snprintf(topic, sizeof(topic), "AT+TCMQTTPUB=\"$thing/up/property/%s/UYIJIA01-%d\",0,", PRODUCT_ID,ic_id);
    at_send_data((uint8_t *)topic, size);
 
   
}
/********************************************************************************
	*
	*Function Name:static void property_report_state(void)
	*Function : publis to tencent cloud data 
	*Input Ref: 
	*           
	*Return Ref:
	*
********************************************************************************/
static void property_report_state(void)
{
    char       message[256]    = {0};
    int        message_len     = 0;

    Mqtt_Value_Init();
   message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up01\\\"\\,\\\"params\\\":{\\\"open\\\":%d\\,\\\"Anion\\\":%d\\,\\\"ptc\\\":%d\\,\\\"sonic\\\":%d\\,\\\"state\\\":%d\\,\\\"find\\\":%d\\,\\\"temperature\\\":%d}}\"\r\n",
                             sg_info.open,sg_info.anion,sg_info.ptc,sg_info.sonic,sg_info.state,sg_info.find,sg_info.set_temperature);
                               
 
	at_send_data((uint8_t *)message, message_len);
   
}


static void property_report_update_data(void)
{
	char  message[256]    = {0};
	int   message_len	   = 0;
	
	 Mqtt_Value_update_data();
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up02\\\"\\,\\\"params\\\":{\\\"open\\\":%d\\,\\\"Anion\\\":%d\\,\\\"ptc\\\":%d\\,\\\"sonic\\\":%d\\,\\\"state\\\":%d\\,\\\"find\\\":%d\\,\\\"temperature\\\":%d}}\"\r\n",
								 sg_info.open,sg_info.anion,sg_info.ptc,sg_info.sonic,sg_info.state,sg_info.find,sg_info.set_temperature);
								   
	 
	at_send_data((uint8_t *)message, message_len);


}

static void property_report_smartphone_power_on_init(void)
{
	char  message[256]    = {0};
	int   message_len	   = 0;
	
	// Mqtt_Value_update_data();
	  mqtt_smart_phone_power_on_ref();
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up02\\\"\\,\\\"params\\\":{\\\"open\\\":%d\\,\\\"Anion\\\":%d\\,\\\"ptc\\\":%d\\,\\\"sonic\\\":%d\\,\\\"state\\\":%d\\,\\\"find\\\":%d\\,\\\"temperature\\\":%d}}\"\r\n",
								 sg_info.open,sg_info.anion,sg_info.ptc,sg_info.sonic,sg_info.state,sg_info.find,sg_info.set_temperature);
								   
	 
	at_send_data((uint8_t *)message, message_len);


}


//static void property_report_power_on_state(void)
//{

//	char       message[256]    = {0};
//    int        message_len     = 0;

//   Mqtt_Value_Init();
//   message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up01\\\"\\,\\\"params\\\":{\\\"open\\\":%d\\,\\\"Anion\\\":%d\\,\\\"ptc\\\":%d\\,\\\"sonic\\\":%d\\,\\\"state\\\":%d\\,\\\"find\\\":%d\\,\\\"temperature\\\":%d}}\"\r\n",
//                             sg_info.open,sg_info.anion,sg_info.ptc,sg_info.sonic,sg_info.state,sg_info.find,sg_info.set_temperature);
//                               
// 
//  at_send_data((uint8_t *)message, message_len);


//}


static void property_report_power_off_state(void)
{

	char       message[256]    = {0};
    int        message_len     = 0;

   Mqtt_power_off_Value();
   message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up01\\\"\\,\\\"params\\\":{\\\"open\\\":%d\\,\\\"Anion\\\":%d\\,\\\"ptc\\\":%d\\,\\\"sonic\\\":%d\\,\\\"state\\\":%d\\,\\\"find\\\":%d\\,\\\"temperature\\\":%d}}\"\r\n",
                             sg_info.open,sg_info.anion,sg_info.ptc,sg_info.sonic,sg_info.state,sg_info.find,sg_info.set_temperature);
                               
 
  at_send_data((uint8_t *)message, message_len);


}

/********************************************************************************
	*
	*Function Name:static void property_report_Temp_Humidity(void)
	*Function :send data to tencent cloud only read temperature and humidity of data
	*Input Ref: only read temperature value and humidiy value
	*           
	*Return Ref:
	*
********************************************************************************/
static void property_report_ReadTempHum(uint8_t tempvalue,uint8_t humvalue)
{

	   char	message[128]    = {0};
	   int	message_len	  = 0;
	   message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up00\\\"\\,\\\"params\\\":{\\\"nowtemperature\\\":%d\\,\\\"Humidity\\\":%d}}\"\r\n"
								,tempvalue,humvalue);
								  
		at_send_data((uint8_t *)message, message_len);
}

static void property_report_SetState(uint8_t dat)
{
     char	message[128]    = {0};
	 int	message_len	  = 0;
	
	
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up04\\\"\\,\\\"params\\\":{\\\"state\\\":%d}}\"\r\n",dat);
								  
	at_send_data((uint8_t *)message, message_len);

}
/********************************************************************************
	*
	*Function Name:static void property_report_SetTempFan(void)
	*Function : sensor of data to tencent cloud  temperature and humidity of data
	*Input Ref: write temperature value          
	*Return Ref:
	*
********************************************************************************/
static void property_report_SetTemp(uint8_t temp)
{
     char	message[128]    = {0};
	 int	message_len	  = 0;
	
	
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up03\\\"\\,\\\"params\\\":{\\\"temperature\\\":%d}}\"\r\n",temp);
								  
	at_send_data((uint8_t *)message, message_len);

}
static void property_report_SetOpen(uint8_t open)
{
     char	message[128]    = {0};
	 int	message_len	  = 0;
	
	
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up04\\\"\\,\\\"params\\\":{\\\"open\\\":%d}}\"\r\n",open);
								  
	at_send_data((uint8_t *)message, message_len);

}
/********************************************************************************
	*
	*Function Name:static void property_report_SetSonic(uint8_t datsonic)
	*Function : "驱虫"
	*Input Ref: bool-> 1 ->on ,0 -> off
	*Return Ref:
	*
********************************************************************************/
static void property_report_SetSonic(uint8_t datsonic)
{
     char	message[128]    = {0};
	 int	message_len	  = 0;
	
	
	message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up02\\\"\\,\\\"params\\\":{\\\"sonic\\\":%d}}\"\r\n"
								,datsonic);
								  
	at_send_data((uint8_t *)message, message_len);

}
/********************************************************************************
	*
	*Function Name:static void property_report_SetAnion(uint8_t datsonic)
	*Function : "灭菌"
	*Input Ref: bool-> 1 ->on ,0 -> off
	*Return Ref:
	*
********************************************************************************/
static void property_report_SetAnion(uint8_t datanion)
{
     char	message[128]    = {0};
	 int	message_len	  = 0;
	
	
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up03\\\"\\,\\\"params\\\":{\\\"Anion\\\":%d}}\"\r\n"
								,datanion);
								  
	at_send_data((uint8_t *)message, message_len);

}
/********************************************************************************
	*
	*Function Name:static void property_report_SetPtc(uint8_t datsonic)
	*Function : "驱虫"
	*Input Ref: bool-> 1 ->on ,0 -> off
	*Return Ref:
	*
********************************************************************************/
static void property_report_SetPtc(uint8_t datptc)
{
     char	message[128]    = {0};
	 int	message_len	  = 0;
	
	
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up04\\\"\\,\\\"params\\\":{\\\"ptc\\\":%d}}\"\r\n"
								,datptc);
								  
	at_send_data((uint8_t *)message, message_len);

}


/********************************************************************************
	*
	*Function Name:static void property_report_SetTempFan(void)
	*Function : sensor of data to tencent cloud  temperature and humidity of data
	*Input Ref: only read temperature value and humidiy value
	*           
	*Return Ref:
	*
********************************************************************************/
static void property_report_SetFan(uint8_t fan)
{
     char	message[128]    = {0};
	 int	message_len	  = 0;
	
	
	 message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up05\\\"\\,\\\"params\\\":{\\\"find\\\":%d}}\"\r\n",fan);
	at_send_data((uint8_t *)message, message_len);

}
/********************************************************************************
	*
	*Function Name:static void property_report_SetTempFan(void)
	*Function : sensor of data to tencent cloud  temperature and humidity of data
	*Input Ref: only read temperature value and humidiy value
	*           
	*Return Ref:
	*
********************************************************************************/
static void property_report_SetTime(uint8_t time)
{

	char   message[128]    = {0};
	int    message_len	 = 0;
	   
	   
	message_len = snprintf(message, sizeof(message),"\"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"up05\\\"\\,\\\"params\\\":{\\\"find\\\":%d}}\"\r\n",
								   time);
	  at_send_data((uint8_t *)message, message_len);
}

/********************************************************************************
	*
	*Function Name:void IOT_MQTT_Publish(pClient, topic, &pubParams)
	*Function :send data to tencent cloud 
	*Input Ref: pClient ->client data array ,topic->tencent register topic name,
	*           &pubParams -> topic of reference
	*Return Ref:
	*
********************************************************************************/
void MqttData_Publish_Init(void)
{
	 property_topic_publish();

	 property_report_state();

}

void MqttData_Publish_Update_Data(void)
{
    property_topic_publish();
	property_report_update_data();

}

void MqttData_Publish_SetOpen(uint8_t dop)
{
   property_topic_publish();
   property_report_SetOpen(dop);
}

void MqttData_Publish_SetPtc(uint8_t dptc)
{
   property_topic_publish();
    property_report_SetPtc(dptc);

}

void MqttData_Publish_SetPlasma(uint8_t pla) //杀菌
{
   property_topic_publish();
   property_report_SetAnion(pla);

}

void MqttData_Publish_SetUltrasonic(uint8_t datsonic) //超声波
{
   property_topic_publish();
   property_report_SetSonic(datsonic);

}

void MqttData_Publish_SetState(uint8_t sdat) //Ai model
{
   property_topic_publish();
   property_report_SetState(sdat);

}



void MqttData_Publish_PowerOff_Ref(void) //
{
   property_topic_publish();

   property_report_power_off_state();

}

void MqttData_Publis_App_PowerOn_Ref(void)
{
   property_topic_publish();

   property_report_smartphone_power_on_init();

}

/********************************************************************************
	*
	*Function Name:void MqttData_Publis_TempHumidity(void)
	*Function : publis data to tencent cloud 
	*Input Ref: pClient ->client data array ,topic->tencent register topic name,
	*           &pubParams -> topic of reference
	*Return Ref:
	*
********************************************************************************/
void MqttData_Publis_ReadTempHum(uint8_t tempvalue,uint8_t humvalue)
{

	property_topic_publish(); 
	property_report_ReadTempHum(tempvalue,humvalue);


}

void MqttData_Publis_SetFan(uint8_t fan)
{
	property_topic_publish(); 
    property_report_SetFan(fan);

}
void MqttData_Publis_SetTemp(uint8_t temp)
{
	property_topic_publish(); 
    property_report_SetTemp(temp);


}


void MqttData_Publis_SetTime(uint8_t time)
{
	property_topic_publish(); 
    property_report_SetTime(time);


}



