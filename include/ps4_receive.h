#pragma once
#ifndef PS4_RECEIVE_H
#define PS4_RECEIVE_H

//includes
#include <PS4BT.h>
#include <usbhub.h>
#include <SPI.h>

//変数
extern USB Usb;
extern PS4BT PS4;
struct vec2{
    uint8_t x;
    uint8_t y;
};
struct vec2p{
    int size;
    int deg;
};
enum order_num{
    SPD_UP,
    SPD_DWN,
    PWR,
    TUNO_UP,
    TUNO_DWN,
    TUNO_STOP,
    M_ANGLE_UP,
    M_ANGLE_DWN,
    M_ANGLE_STOP
};

typedef struct vec2 vec2_t;
typedef struct vec2p vec2p_t;
typedef enum order_num orders_t;
//関数
void ps4_receive();

#endif