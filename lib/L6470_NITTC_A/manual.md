# L6470用ライブラリマニュアル  

## 使い方（設定編）  
- `L6470_NITTC_A.h`、`stepping_motor.h`、`SPI.h`をインクルードする  

- ステッピングドライバ、ステッピングモーターのインスタンスを生成する
  ```c
  L6470 stepping_driver("slave select pin", "busy pin");
  stepping_motor my_motor1(create_"モーター品番"(stepping_driver));
  ```  
- SPIモジュールをMODE2で起動する（`void setup`内）  

  ```c
  SPI.setDataMode(SPI_MODE2);
  SPI.begin();
  ```

- ドライバの初期設定をする  
  ```c
  my_motor1.stop(); //一応動作を停止
  my_motor.driver_setting(); //電圧、電流を設定（モータごとの最適値が自動で代入される）
  ```

- 加速度、（＋マイクロステップ角）を設定する  
  ```c
  //ラジアンで設定
  my_motor1.accel_config_rad("加速度","減速度"); //rad/s^2

  //何も設定しないと128マイクロステップとなる
  //高トルクが必要とされる場では1とするとよい
  my_motor1.step_driver.microstep_config("マイクロステップ");
  ```

- 回す
  ```c
  //速度（rad/s）を指定して回転　無限回転する
  my_motor1.rotate_rad("速度");

  //速度（rad/s）、移動角を指定して回転
  my_motor1.rotate_rad("速度","移動角");

  //回転角、速度ともに正負入力可能
  //10π(rad)回転させたいなら　
  my_motor1.rotate_rad(1*M_PI,10*M_PI);
  //-10π(rad)逆回転させたいなら　
  my_motor1.rotate_rad(-1*M_PI,-10*M_PI);
  ```

## 使いそうなコマンド  
- 動作中か確認するとき  
    ```c
    bool my_motor1.step_driver.is_moving(void);
    ```
  - 動作中なら`true`が返される  


具体的な書き方を見たいならmain.cppを見やがれ
