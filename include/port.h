#pragma once

//ポート番号設定
enum port{
    LED1_PIN = 23,
    LED2_PIN = 25,
    //電磁弁
    VALVE_SIGN1 = 26, //BLUE1
    VALVE_SIGN2 = 28, //BLUE2
    VALVE_SIGN3 = 30, //YELLOW
    VALVE_SIGN4 = 32, //RED
    //？
    EX_STOP = 36,
    //ソフトウェアSPI
    MOSI_SOFT = 33,
    MISO_SOFT = 35,
    SCK_SOFT = 37,
    //？
    POWER_SD = 40,
    SD_SIGN = 42,
    //SPI
    BUSY1_PIN = 41,
    BUSY2_PIN = 43,
    SS1_PIN = 47, //Left
    SS2_PIN = 49, //Right
    MISO_HARD = 50,
    SCK_HARD = 52,
    MOSI_HARD = 53
    
};

typedef port port_t;