#include "..\include\stepping_motor.h"
#include "..\include\L6470_NITTC_A.h"
#include <math.h>

// 1.8°.stepモータ（一周200パルス）だと一回転25600（128（マイクロステップ角）*200）
// step/s = speed_val * 0.01490...
// 1.8°.stepモータなら rotate/s = speed_val * 7.4505...x10^-5
// PK246PDA（ステア制御用）は無負荷時speed_val=42000で脱調（約3.12r/s)


static constexpr float angle_deg_to_step = 128 / 360;
static constexpr float angle_rad_to_step = 128 /(2*M_PI);

static constexpr float speed_deg_to_step = (67.108864)/360;
static constexpr float speed_rad_to_step = (67.108864)/(2*M_PI);

static constexpr float accel_deg_to_step = 0.0687195/360;
static constexpr float accel_rad_to_step = 0.0687195/(2*M_PI);

void stepping_motor::driver_setting(void){
    step_driver.reset_device();
    step_driver.voltage_config(
        voltage_val.accel_volgate, voltage_val.normal_volgate,
        voltage_val.decel_voltage);
    step_driver.current_config(current_val);
    step_driver.reset_position();
}

void stepping_motor::accel_config_deg(float accel_deg,float decel_deg){
    uint16_t accel_step = accel_deg * accel_deg_to_step * pulse;
    uint16_t decel_step = decel_deg * accel_deg_to_step * pulse;
    step_driver.accel_config(accel_step,decel_step);
}

void stepping_motor::rotate_deg(float speed_deg){
    int32_t step_speed = speed_deg * speed_deg_to_step * pulse;

    step_driver.rotate(step_speed);
}

void stepping_motor::rotate_deg(float speed_deg,float rotate_deg){
    int32_t step_speed = speed_deg * speed_deg_to_step * pulse;
    int32_t rotate_step = rotate_deg * angle_deg_to_step * pulse;

    step_driver.rotate(step_speed,rotate_step);
}

void stepping_motor::accel_config_rad(float accel_rad,float decel_rad){
    uint16_t accel_step = accel_rad * accel_rad_to_step * pulse;
    uint16_t decel_step = decel_rad * accel_rad_to_step * pulse;
    step_driver.accel_config(accel_step,decel_step);
}

void stepping_motor::rotate_rad(float speed_rad){
    int32_t step_speed = speed_rad * speed_rad_to_step * pulse;

    step_driver.rotate(step_speed);
}

void stepping_motor::rotate_rad(float speed_rad,float rotate_rad){
    int32_t step_speed = speed_rad * speed_rad_to_step * pulse;
    int32_t rotate_step = rotate_rad * angle_rad_to_step * pulse;

    step_driver.rotate(step_speed, rotate_step);
}

void stepping_motor::stop(void){
    step_driver.hard_stop();
}