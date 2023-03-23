//ここでは、PS4コントローラーとのペアリング関連の処理を行う

#include <Arduino.h>
#include <PS4BT.h>
#include <usbhub.h>

#ifdef doboguinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include "ps4_init.h"

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
