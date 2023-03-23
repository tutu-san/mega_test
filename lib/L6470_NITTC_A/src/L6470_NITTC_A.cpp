#include "..\include\L6470_NITTC_A.h"

#include <Arduino.h>
#include <SPI.h>
#include <math.h>

#include <assert.h>
using namespace std;

static constexpr uint32_t timeout_us = 10;

L6470::L6470(uint8_t _ss_num, uint8_t _busy_num)
    : ss_pin(_ss_num), busy_pin(_busy_num) {
    pinMode(ss_pin, OUTPUT);
    pinMode(busy_pin, INPUT);
}

//driver config/////////////////////////////////////////

//どこにこの関数を置くべきなのだろうか。
static uint8_t log_2(uint8_t value){
    unsigned char value_bit = value;
    
    for(int i = 7; i>= 0; i--){
        uint8_t calc_tmp;
        calc_tmp = ((value_bit >> i) & 0x01); //それぞれの桁ごとに抽出
        if(calc_tmp){ //もし1(立っている)ならば //0の時はtrueにならない
            return i; //解の i を返す (早期リターン？)
            
        }
    }

    return 0;
}

void L6470::microstep_config(uint8_t step_val){//2^n
    free(); //set HiZ

    microstep_val = step_val; //uint8_t
    
    step_val = log_2(step_val);

    //step_val = (uint8_t)log2(step_val); //これを変えた(つつさん)

    send_config(L6470_register::STEP_MODE);//WH register
    send_config(&step_val, sizeof(step_val));
}

void L6470::current_config(uint8_t I_val) {
    send_config(L6470_register::OCD_TH);
    send_config(&I_val, sizeof(I_val));
}

void L6470::voltage_config(uint8_t accel_V_val, uint8_t normal_V_val,uint8_t decel_V_val) {
    send_config(L6470_register::KVAL_ACC);
    send_config(&accel_V_val, sizeof(accel_V_val));

    send_config(L6470_register::KVAL_RUN);
    send_config(&normal_V_val, sizeof(normal_V_val));

    send_config(L6470_register::KVAL_DEC);
    send_config(&decel_V_val, sizeof(decel_V_val));
}

void L6470::reset_position(void) {
    send_config(0xD8);  //現在の位置をホームポジションとして設定
}
void L6470::reset_device(void) { 
    send_config(0xC0); 
}

void L6470::accel_config(uint16_t accel_val, uint16_t decel_val) {
    send_config(L6470_register::ACC);
    send_config(&accel_val, sizeof(accel_val));

    send_config(L6470_register::DECELERATION);
    send_config(&decel_val, sizeof(decel_val));
}

//drive order functions///////////////////////////////
void L6470::rotate(int32_t speed, int32_t angle) {
    int32_t direction = 0;
    direction = ((speed >= 0) ? 1 : -1) * ((angle >= 0) ? 1 : -1);
    direction = (direction >= 0);

    speed = abs(speed) >> 10;

    send_config(L6470_register::MAX_SPEED);
    send_config(&speed, 2);

    angle = angle / (128/microstep_val);
    send_config(0x68 | direction);
    send_config(&angle, 3);
}

void L6470::rotate(int32_t speed) {
    uint32_t direction = (speed >= 0);
    speed = abs(speed);

    uint16_t max_speed = 0xFFFF;  // avoid Conflict max_speed and target_speed
    send_config(L6470_register::MAX_SPEED);
    send_config(&max_speed, sizeof(max_speed));

    send_config(0x50 | direction);
    send_config(&speed, 3);
}

void L6470::soft_stop(void) {
    send_config(0xB0);  // stop with decel_val
}
void L6470::hard_stop(void) {
    send_config(0xB8);  // hard stop immediately
}
void L6470::free(void) {
    send_config(0xA8);  // HiZ(Do not lock the motor)
}

 //check motor statue functions////////////////////////////
uint16_t L6470::read_status(void){
    driver_statue = 0;

    send_config(0b11010000); //get_status_command

    for (uint8_t i = 0; i < 2; i++) {
        digitalWrite(ss_pin, LOW);
        delayMicroseconds(1);
        driver_statue = (driver_statue << 8) | SPI.transfer(0x00);
        digitalWrite(ss_pin, HIGH);
        delayMicroseconds(1);
    }
    return driver_statue;
}

//このへん
bool L6470::is_accelerating(void){
    read_status();
    uint16_t mortion = driver_statue & (uint16_t)STATUS_register::MOT_STATUS;
    return mortion == (0b01 << (uint16_t)STATUS_register::MOT_STATUS);
}
bool L6470::is_decelerating(void){
    read_status();
    uint16_t mortion = driver_statue & (uint16_t)STATUS_register::MOT_STATUS;
    return mortion == (0b10 << (uint16_t)STATUS_register::MOT_STATUS);
}
bool L6470::is_constant_speed(void){
    read_status();
    uint16_t mortion = driver_statue & (uint16_t)STATUS_register::MOT_STATUS;
    return mortion == (0b11 << (uint16_t)STATUS_register::MOT_STATUS);
}
bool L6470::is_moving(void){
    read_status();
    uint16_t mortion = driver_statue & (uint16_t)STATUS_register::MOT_STATUS;
    return mortion != (0b00 << (uint16_t)STATUS_register::MOT_STATUS);
}
bool L6470::is_stoped(void){
    read_status();
    uint16_t mortion = driver_statue & (uint16_t)STATUS_register::MOT_STATUS;
    return mortion == (0b00 << (uint16_t)STATUS_register::MOT_STATUS);
}
bool L6470::is_HiZ(void){
    read_status();
    uint16_t hiz = driver_statue & (uint16_t)STATUS_register::HiZ;
    return hiz == (1 << (uint16_t)STATUS_register::HiZ);
}
bool L6470::is_low_volgate(void){
    read_status();
    uint16_t uvlo = driver_statue & (uint16_t)STATUS_register::UVLO;
    return uvlo == (1 << (uint16_t)STATUS_register::UVLO);
}
bool L6470::is_stalling(void){
    read_status();
    uint16_t stall = (driver_statue & (uint16_t)STATUS_register::STEP_LOSS_A)
                      | (driver_statue & (uint16_t)STATUS_register::STEP_LOSS_B);
    return stall != (0b11 << (uint16_t)STATUS_register::STEP_LOSS_B);
}
bool L6470::is_rotating_CW(void){
    read_status();
    uint16_t direction = driver_statue & (uint16_t)STATUS_register::DIR;
    return direction == (1 << (uint16_t)STATUS_register::DIR);
}
bool L6470::is_rotating_CCW(void){
    read_status();
    uint16_t direction = driver_statue & (uint16_t)STATUS_register::DIR;
    return direction == (0 << (uint16_t)STATUS_register::DIR);
}


uint32_t L6470::get_angle(void) {
    return read_register(L6470_register::ABS_POS, 3);
}

uint32_t L6470::get_speed(void) {
    return read_register(L6470_register::SPEED, 3);
}

void L6470::send_config(void *send_data, size_t len) {
    uint8_t *data_ptr = (uint8_t *)send_data;

    for (int8_t i = len - 1; i >= 0; i--) {
        digitalWrite(ss_pin, LOW);
        delayMicroseconds(1);
        SPI.transfer(*(data_ptr + i));
        digitalWrite(ss_pin, HIGH);
        delayMicroseconds(1);
    }
}

void L6470::send_config(uint8_t byte_data) {
    digitalWrite(ss_pin, LOW);
    delayMicroseconds(1);
    SPI.transfer(byte_data);
    digitalWrite(ss_pin, HIGH);
    delayMicroseconds(1);
}

uint32_t L6470::read_register(L6470_register reg, size_t len) {
    assert(0 < len && len <= sizeof(uint32_t));

    const uint8_t address = (uint8_t)reg;
    uint32_t get_val = 0;

    send_config(0x20 | address);

    for (uint8_t i = 0; i < len; i++) {
        digitalWrite(ss_pin, LOW);
        delayMicroseconds(1);
        get_val = (get_val << 8) | SPI.transfer(0x00);
        digitalWrite(ss_pin, HIGH);
        delayMicroseconds(1);
    }

    return get_val;
}
