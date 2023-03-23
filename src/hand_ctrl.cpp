//ここでは、ハンド機構(主として電磁弁/シリンダ)の制御を行う
#include <Arduino.h>

#include "hand_ctrl.h"

//カウンター
static int seq_count = 0;

//static関数のプロトタイプ宣言はどこへ？
static void blue_open();
static void yellow_open();
static void red_open();
static void blue_close();
static void yellow_close();
static void red_close();

void hand_seq_manage(){
    //swich-case? (どっちがいいのか？)
    if(seq_count == 0){
        //アイデアシート状態:2 多分青(2つ)のシリンダ動作
        blue_open();
    }else if(seq_count == 1){
        //アイデアシート状態:3 多分黄(1つ)のシリンダ動作
        yellow_open();
    }else if(seq_count == 2){
        //アイデアシート状態:4 多分黄(1つ)のシリンダ動作
        yellow_close();
    }else if(seq_count == 3){
        //アイデアシート状態:5 多分 青 赤 の順(1つずつ)でシリンダ動作
        blue_close();
        red_open();
        //射出後の待機時間をどうするか...delay以外である方法...
        delay(1000);
        red_close();
    }

    //カウントアップ
    seq_count ++;

    if(seq_count > 3){
        seq_count = 0;
    }
}

//inlineをつけたら何か変わるのだろうか。
static inline void blue_open(){
    digitalWrite(VALVE_SIGN1, HIGH);
    digitalWrite(VALVE_SIGN2, HIGH);
}

static inline void yellow_open(){
    digitalWrite(VALVE_SIGN3, HIGH);
}

static inline void red_open(){
    digitalWrite(VALVE_SIGN4, HIGH);
}

static inline void blue_close(){
    digitalWrite(VALVE_SIGN1, LOW);
    digitalWrite(VALVE_SIGN2, LOW);
}

static inline void yellow_close(){
    digitalWrite(VALVE_SIGN3, LOW);
}

static inline void red_close(){
    digitalWrite(VALVE_SIGN4, LOW);
}