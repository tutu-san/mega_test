//ここ以外に意味はない！
#include <Arduino.h>

#include "main.h"

//ステッピングモーター用のやつっぽい(ロボAにあったものを取ってきた) //機構角度 (_Left, _Rightのほうがいいかも)
static L6470 driver1(SS1_PIN, BUSY1_PIN);
stepping_motor M_angle_Left(create_PK246PDA(driver1)); //static消していいのか？(extern??)
static L6470 driver2(SS2_PIN, BUSY2_PIN);
stepping_motor M_angle_Right(create_PK246PDA(driver2));

void setup(){
	//UART(シリアル)通信関係
	Serial.begin(115200); //PCで状況を見るためにポートを開けている
	Serial2.begin(115200);//機構
	Serial3.begin(115200);//足回り

	//SPI(ステッピングモーター向け)通信設定。 (ホストシールドと競合しないかな？)
	SPI.setDataMode(SPI_MODE2);
	SPI.begin();

	//ステッピング関係
	M_angle_Left.stop();
	M_angle_Left.driver_setting();
	M_angle_Right.stop();
	M_angle_Right.driver_setting();
	//参考例から取ってきたよ (この辺はどうやって調整しようか。)
	M_angle_Left.accel_config_rad(22*M_PI,22*M_PI);
	M_angle_Left.step_driver.microstep_config(128); 
	M_angle_Right.accel_config_rad(22*M_PI,22*M_PI);
	M_angle_Right.step_driver.microstep_config(128);


}

//ライブラリのテストコードから一部改変したうえで持ってきた。
void loop(){
	Serial.println("start");

    M_angle_Left.rotate_rad(14*M_PI,20*M_PI);

    while(driver1.is_moving()){
        //
    }

    Serial.println("rotate1 finish");
    delay(500);


////////////////////////////////////////////////////////////////
    M_angle_Left.rotate_deg(-360*2, 0);

    while(driver1.is_moving()){
        //
    }
    Serial.println("rotate2 finish");
    delay(500);
}
