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
#include "ps4_receive.h"
#include "uart_nucleo.h"
#include "stepping.h"
#include "hand_ctrl.h"

//定数
const int center = 127;
orders_t inc_order; //これいる？

//Lスティックの座標
vec2_t Left_vec;

void ps4_receive(){
    Usb.Task();

    if(PS4.connected()){
        if(PS4.getButtonClick(PS)){
            Serial.print(F("\r\nPS"));
            PS4.disconnect();
        }
        //アナログスティックの値を取得する。
        const int lx = PS4.getAnalogHat(LeftHatX);
        const int ly = PS4.getAnalogHat(LeftHatY);
        
        //移動用ベクトルの取得
        if(abs(lx-center)>30 || abs(ly-center)>30){ //オムニホイールのベクトルをとりたい。 
            Left_vec.x = lx; //uint8_t
            Left_vec.y = ly; //uint8_t
            send_serial3();
        }
        //機構モーターの速度制御(予定)
        if(PS4.getButtonClick(UP)){
            Serial.print(F("\r\nUP"));
            send_serial2(SPD_UP);
        }else if(PS4.getButtonClick(DOWN)){
            Serial.print(F("\r\nDOWN"));
            send_serial2(SPD_DWN);
        }
        
        //ツノの角度制御 (ボタンに変更) 
        //(Arduinoのタイムラグと大量の信号が送られるスティックの組み合わせは危険と判断)
        if(PS4.getButtonClick(L2)){
            Serial.print(F("\r\nL2"));
            send_serial2(TUNO_DWN);
        }else if(PS4.getButtonClick(R2)){
            Serial.print(F("\r\nR2"));
            send_serial2(TUNO_UP);
        }

        if(PS4.getButtonClick(R1)){
            Serial.print(F("\r\nR1"));
            send_serial2(TUNO_STOP);
        }

        //機構ローラーon/off
        if(PS4.getButtonClick(L1)){
            Serial.print(F("\r\nL1"));
            send_serial2(PWR);
        }
        
        //電磁弁を使用した、制御(射出)のボタン
        if(PS4.getButtonClick(CIRCLE)){
            Serial.print(F("\r\nCIRCLE"));
            //電磁弁の制御
            //おそらくtutu-san担当
            hand_seq_manage();
        }

        //SPI通信を使って、ステッピングモタドラ(L6470)の制御
        //本体機構角度調節用だからどうしようかね。
        if(PS4.getButtonClick(TRIANGLE)){
            Serial.print(F("\r\nTRIANGLE"));
            l6470_send(M_ANGLE_UP);

        }

        if(PS4.getButtonClick(CROSS)){
            Serial.print(F("\r\nCROSS"));
            l6470_send(M_ANGLE_DWN);

        }

        if(PS4.getButtonClick(SQUARE)){
            Serial.print(F("\r\nSQARE"));
            l6470_send(M_ANGLE_STOP);
        }
    }
}