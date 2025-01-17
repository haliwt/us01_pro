#include "bsp.h"


void key_handler(void)
{

    if(gpro_t.key_power_flag == 1){

        if(KEY_POWER_VALUE()==KEY_UP){
            gpro_t.key_power_flag++;


                if(gpro_t.key_long_power_flag==1){
                    gpro_t.power_key_long_conter=0;
                    gpro_t.key_long_power_flag= 0;

                }
                else if(gpro_t.key_long_power_flag==0){

                    gpro_t.power_key_long_conter=0;
                    buzzer_sound();

                    power_on_key_handler();

                }
         }

    }
    else if(gpro_t.key_mode_flag== 1 && gkey_t.key_power==power_on){
        if(KEY_MODE_VALUE() == KEY_UP){
        gpro_t.key_mode_flag++;

        if(gpro_t.key_long_mode_flag ==0){
        gpro_t.long_key_mode_counter=0;
        buzzer_sound();
        mode_key_fun();
        }
        else{
        gpro_t.long_key_mode_counter=0;
        gpro_t.power_key_long_conter=0;
        mode_long_key_fun();
        gpro_t.key_long_mode_flag =0;
        }

        }

    }
    else if(gpro_t.key_add_flag==1){

        if(KEY_ADD_VALUE() == KEY_UP){
        gpro_t.key_add_flag++;


        buzzer_sound();
        Add_Key_Fun(gkey_t.key_add_dec_mode);

        }
    }
    else if(gpro_t.key_dec_flag ==1){

        if(KEY_DEC_VALUE()==KEY_UP){
        gpro_t.key_dec_flag++;
        buzzer_sound();
        Dec_Key_Fun(gkey_t.key_add_dec_mode);

        }
    }
    else if(gpro_t.smart_phone_sound == 1){

        gpro_t.smart_phone_sound++;

        buzzer_sound();
        smartphone_power_on_handler();

    }


}

