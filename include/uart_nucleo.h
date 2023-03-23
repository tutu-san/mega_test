#pragma once
#ifndef UART_NUCLEO_H
#define UART_NUCLEO_H

//includes
#include "ps4_receive.h"
#include "main.h"
//変数
//from receive
extern vec2_t Left_vec;
extern orders_t order;


//関数
void send_serial3();
void send_serial2(orders_t);

void send_led_serial2();
void send_led_serial3();
#endif