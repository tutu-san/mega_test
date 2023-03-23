#pragma once
#ifndef MAIN_H
#define MAIN_H
//includes
#include <SPI.h>
#include "port.h"
#include "../lib/L6470_NITTC_A/include/L6470_NITTC_A.h"
#include "../lib/L6470_NITTC_A/include/stepping_motor.h"
//変数
extern stepping_motor M_angle_Right;
extern stepping_motor M_angle_Left;
//関数
void setup(void);
void loop(void);

#endif