#pragma once

#include <assert.h>
#include <math.h>
#include "L6470_NITTC_A.h"

class L6470;

struct voltage_t{
    uint32_t accel_volgate;
    uint32_t normal_volgate;
    uint32_t decel_voltage;
};
class stepping_motor{
public: 
    const uint32_t pulse = 200;//一周に必要なパルス数(入れないと行けない。)
    voltage_t voltage_val;
    const uint32_t current_val;
    L6470& step_driver;

    stepping_motor(L6470& _step_driver, uint32_t _pulse, voltage_t _voltage_val, uint32_t _current_val)
    : step_driver(_step_driver),pulse(_pulse),voltage_val(_voltage_val),current_val(_current_val){
        assert(pulse>0);
    }
    void driver_setting(void);

    void accel_config_deg(float accel_deg,float decel_deg);
    void rotate_deg(float speed_deg);
    void rotate_deg(float speed_deg,float rotate_deg);
    
    void accel_config_rad(float accel_rad,float decel_rad);
    void rotate_rad(float speed_rad);
    void rotate_rad(float speed_rad,float rotate_rad);

    void stop(void);
};

static inline stepping_motor create_PK246PDA(L6470& step_driver){
    const static voltage_t PK246PDA_voltage = {0x40,0x30,0x40};
    return stepping_motor(step_driver,200, PK246PDA_voltage,0xF);
}