#pragma once

#include <stddef.h>
#include <stdint.h>

#include "failable.h"
enum class L6470_register : uint8_t {
    ABS_POS = 0x01,  //現在位置 22bit
    MARK_POS = 0x03,
    SPEED = 0x04,         //現在速度 20bit
    ACC = 0x05,           //加速度 12bit
    DECELERATION = 0x06,  //減速度 12bit
    MAX_SPEED = 0x07,     //最高速度設定 10bit
    KVAL_HOLD = 0x09,     // 8bit
    KVAL_RUN = 0x0A,      // 8bit
    KVAL_ACC = 0x0b,      // 8bit
    KVAL_DEC = 0x0c,      // 8bit
    OCD_TH = 0x13,        // 4bit current_limit
    STEP_MODE = 0x16,     //マイクロステップ設定　ハイインピーダンス状態でのみ書き込み可
    STATUS = 0x19         // 16bit
};

enum class STATUS_register : uint16_t{
    SCK_MOD = 1UL << 15,
    STEP_LOSS_B = 1 << 14,
    STEP_LOSS_A = 1 << 13,
    OCD = 1 << 12,
    TH_SD = 1 << 11,
    TH_WRN = 1 << 10,
    UVLO = 1 << 9,
    WRONG_CMD = 1 << 8,
    
    NOTPERF_CMD = 1 << 7,
    MOT_STATUS = 0b11 << 5,
    DIR = 1 << 4,
    SW_EVN = 1 << 3,
    SW_F = 1 << 2,
    BUSY = 1 << 1,
    HiZ = 1 << 0,
};

class L6470 {
private:
    const uint8_t ss_pin;
    const uint8_t busy_pin;
    uint8_t microstep_val;
    uint16_t driver_statue;

public:
    L6470(uint8_t ss_pin, uint8_t busy_pin);

    //driver config 
    void microstep_config(uint8_t step_val); 
    void current_config(uint8_t I_val);  //過電流閾値
    void voltage_config(uint8_t accel_V_val, uint8_t normal_V_val,uint8_t decel_V_val);  //加速時電圧,定速電圧,減速時電圧

    void reset_position(void);                 //現在位置を座標0に設定
    void reset_device(void);

    void accel_config(uint16_t accrel_val,uint16_t decel_val);  //加速度,減速度

    //drive order functions
    void rotate(int32_t speed,int32_t angle);  //速さ,角度
    void rotate(int32_t speed);

    void hard_stop(void);
    void soft_stop(void);
    void free(void);


    //check motor statue functions
    uint16_t read_status(void);

    bool is_accelerating(void); //MOT_STATUE
    bool is_decelerating(void);
    bool is_constant_speed(void);
    bool is_moving(void);
    bool is_stoped(void);
    bool is_HiZ(void);
    bool is_low_volgate(void);
    bool is_stalling(void);
    bool is_rotating_CW(void);
    bool is_rotating_CCW(void);

    uint32_t get_angle(void);
    uint32_t get_speed(void);

private:
    void send_config(void* send_data, size_t len);  //送る値,命令長(byte)
    void send_config(uint8_t send_data);            //送る値
    inline void send_config(L6470_register r) {
        return send_config((uint8_t)r);
    }

    uint32_t read_register(L6470_register reg, size_t len);
};