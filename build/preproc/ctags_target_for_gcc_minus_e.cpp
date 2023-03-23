# 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\data_ctrl.h"


//変数

//関数
void wheel_data(int, int);
# 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\data_ctrl.ino"
//ここでは、コントローラーからのデータを処理して、ステッピングモーターの制御関数orSTMとのシリアル通信関数との橋渡し役を担うつもり
# 3 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\data_ctrl.ino" 2
# 4 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\data_ctrl.ino" 2

# 6 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\data_ctrl.ino" 2

void wheel_data(int x_value, int y_value){ //やること ベクトルの大きさを出す ベクトルの角度を出す
    //ベクトルの大きさ
    float x_squre, y_squre, vector_size;
    int vector_size_int;
    x_squre = pow(x_value, 2.0);

}
# 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\main.ino"
//ここでは、それぞれの関数を動かす処理を行う
# 3 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\main.ino" 2

# 5 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\main.ino" 2
# 6 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\main.ino" 2
# 7 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\main.ino" 2

void setup(){
 Serial.begin(115200); //PCで状況を見るためにポートを開けている
    ps4_init();
}

void loop(){
 ps4_receive();
}
# 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino"
//ここでは、PS4コントローラーとのペアリング関連の処理を行う

# 4 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 2
# 5 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 2
# 6 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 2




# 11 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 2

USB Usb;

BTD Btd(&Usb);

PS4BT PS4(&Btd, 1);

void ps4_init(){


    while(!Serial);

    if(Usb.Init() == -1){
        Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino"
                    "\r\n did not start"
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 3
                    ); &__c[0];}))
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino"
                    )));
        while(1);
    }
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 27 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 27 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino"
                "\r\nPS4 lib started"
# 27 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino" 3
                ); &__c[0];}))
# 27 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_jnit.ino"
                )));

}
# 1 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
//ここでは、PS4コントローラーからデータを受け取る。
# 3 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 2
# 4 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 2
# 5 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 2




# 10 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 2

# 12 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 2


void ps4_receive(){
    Usb.Task();

    if(PS4.connected()){
        if(PS4.getButtonClick(PS)){
            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 19 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 19 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        "\r\nPS"
# 19 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        ); &__c[0];}))
# 19 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        )));
            PS4.disconnect();
        }
        if(PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117){ //オムニホイールのベクトルをとりたい。 
            int x_value, y_value;
            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        "\r\nLeftHatX: "
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        ); &__c[0];}))
# 24 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        )));
            Serial.print(PS4.getAnalogHat(LeftHatX));
            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 26 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 26 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        "\tLeftHatY: "
# 26 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        ); &__c[0];}))
# 26 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        )));
            Serial.print(PS4.getAnalogHat(LeftHatY));
            x_value = PS4.getAnalogHat(LeftHatX);
            y_value = PS4.getAnalogHat(LeftHatY);
            wheel_data(x_value, y_value);
        }
        if(PS4.getButtonClick(L2)){ //アナログボタンもデジタル入力で対応可能。
            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 33 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 33 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        "\r\nL2"
# 33 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino" 3
                        ); &__c[0];}))
# 33 "d:\\robocon_kounai_2023\\main_program_files\\arduino_mega\\ps4_receive.ino"
                        )));
        }
    }
}
