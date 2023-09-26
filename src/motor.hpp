#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <Arduino.h>
#include "driver/pcnt.h"

class Motor
{

public:
    Motor(uint8_t m1_pin, uint8_t m2_pin, uint8_t m1_chan, uint8_t m2_chan, uint8_t enc_a_pin, uint8_t enc_b_pin, pcnt_unit_t unit);
    void set_velocity(int16_t vel);
    int16_t get_count(void);

private:
    const int PWM_FREQ = 5000;
    const int PWM_RESO = 8;
    const int COUNTER_H_LIM = 32767;
    const int COUNTER_L_LIM = -32767;

    uint8_t m1_chan_;
    uint8_t m2_chan_;
    pcnt_unit_t unit_;
    pcnt_config_t pcnt_config_a;
    pcnt_config_t pcnt_config_b;
};

#endif