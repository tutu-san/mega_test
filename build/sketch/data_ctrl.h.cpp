#include <Arduino.h>
#line 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\data_ctrl.h"
#ifndef DATA_CTRL_H
#define DATA_CTRL_H
//変数

//関数
void wheel_data(int, int);

#endif
#line 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\data_ctrl.ino"
//ここでは、コントローラーからのデータを処理して、ステッピングモーターの制御関数orSTMとのシリアル通信関数との橋渡し役を担うつもり
#include <Arduino.h>
#include <math.h>

#include "ps4_receive.h"

void wheel_data(int x_value, int y_value){ //やること ベクトルの大きさを出す ベクトルの角度を出す
    //ベクトルの大きさ
    float x_squre, y_squre, vector_size;
    int vector_size_int;
    x_squre = pow(x_value, 2.0);

}
#line 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\main.ino"
//ここでは、それぞれの関数を動かす処理を行う
#include <Arduino.h>

#include "ps4_init.h"
#include "ps4_receive.h"
#include "data_ctrl.h"

void setup(){
	Serial.begin(115200); //PCで状況を見るためにポートを開けている
    ps4_init();
}

void loop(){
	ps4_receive();
}

#line 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino"
//ここでは、PS4コントローラーとのペアリング関連の処理を行う

#include <Arduino.h>
#include <PS4BT.h>
#include <usbhub.h>

#ifdef doboguinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;

BTD Btd(&Usb);

PS4BT PS4(&Btd, PAIR);

void ps4_init(){

#if !defined(__MIPSEL__)
    while(!Serial);
#endif
    if(Usb.Init() == -1){
        Serial.print(F("\r\n did not start"));
        while(1);
    }
    Serial.print(F("\r\nPS4 lib started"));

}

#line 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
//ここでは、PS4コントローラーからデータを受け取る。
#include <Arduino.h>
#include <PS4BT.h>
#include <usbhub.h>

#ifdef doboguinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include "ps4_init.h"
#include "data_ctrl.h"

void ps4_receive(){
    Usb.Task();

    if(PS4.connected()){
        if(PS4.getButtonClick(PS)){
            Serial.print(F("\r\nPS"));
            PS4.disconnect();
        }
        if(PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117){ //オムニホイールのベクトルをとりたい。 
            int x_value, y_value;
            Serial.print(F("\r\nLeftHatX: "));
            Serial.print(PS4.getAnalogHat(LeftHatX));
            Serial.print(F("\tLeftHatY: "));
            Serial.print(PS4.getAnalogHat(LeftHatY));
            x_value = PS4.getAnalogHat(LeftHatX);
            y_value = PS4.getAnalogHat(LeftHatY);
            wheel_data(x_value, y_value);
        }
        if(PS4.getButtonClick(L2)){ //アナログボタンもデジタル入力で対応可能。
            Serial.print(F("\r\nL2"));
        }
    }
}
