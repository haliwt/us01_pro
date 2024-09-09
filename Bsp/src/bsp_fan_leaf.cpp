#include "bsp.h"




class fan_leaf_icon{


    public:

      void disp_fan_leaf_icon_fun(void);

      uint8_t read_fan_leaf_data(void);

      void write_fan_leaf_data(uint8_t data);


     private :

      uint8_t fan_leaf_grade_flag;



};



uint8_t fan_leaf_icon::read_fan_leaf_data(void)
{

       return fan_leaf_grade_flag;

}

void fan_leaf_icon::write_fan_leaf_data(uint8_t data)
{

       fan_leaf_grade_flag = data;


}

void fan_leaf_icon::disp_fan_leaf_icon_fun(void)
{
   

}


