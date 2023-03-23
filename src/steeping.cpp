//for L6470
#include <Arduino.h>

#include "stepping.h"
#include "main.h"
#include "ps4_receive.h"

void l6470_send(orders_t order){
    
    if(order == M_ANGLE_UP){
        M_angle_Left.rotate_rad(1);
        M_angle_Right.rotate_rad(1);
    }

    if(order == M_ANGLE_DWN){
        M_angle_Left.rotate_rad(1);
        M_angle_Right.rotate_rad(1);
    }

   //これ急停止？
    if(order == M_ANGLE_STOP){
        M_angle_Left.stop();
        M_angle_Right.stop();
    }
}