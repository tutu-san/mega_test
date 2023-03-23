//ここでは、STM32にUARTで通信することを行う
#include <Arduino.h>

#include "uart_nucleo.h"
#include "ps4_receive.h" //これいる？




void send_led_serial2(){ //ピン番号等は仮なものであることに留意
    /*
    digitalWrite(LED1_PIN, HIGH);
    delay(10);
    digitalWrite(LED1_PIN,LOW);
    */
}

void send_led_serial3(){
    /*
    digitalWrite(LED2_PIN, HIGH);
    delay(10);
    digitalWrite(LED2_PIN, LOW);
    */
}

void send_serial3(){
    //ヘッター、チェックサム(どうするかわからん)つける
    
    const static uint8_t start3 = '!'; //header

    Serial3.write(start3);
    Serial3.write(Left_vec.x);
    Serial3.write(Left_vec.y);

    Serial.print(F("\r\nLeftHatX: "));
    Serial.print(Left_vec.x); //0-255
    Serial.print(F("\tLeftHatY: "));
    Serial.print(Left_vec.y); //0-255

    send_led_serial3();
}

void send_serial2(orders_t order){
    const static uint8_t start2 = '!'; //header

    Serial2.write(start2);
    Serial2.write(order);

    send_led_serial2();
}