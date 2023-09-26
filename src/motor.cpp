#include "motor.hpp"

Motor::Motor(uint8_t m1_pin, uint8_t m2_pin, uint8_t m1_chan, uint8_t m2_chan, uint8_t enc_a_pin, uint8_t enc_b_pin, pcnt_unit_t unit)
{

	m1_chan_ = m1_chan;
	m2_chan_ = m2_chan;
    unit_ = unit;

    ledcSetup(m1_chan, PWM_FREQ, PWM_RESO);
    ledcSetup(m2_chan, PWM_FREQ, PWM_RESO);
    ledcAttachPin(m1_pin, m1_chan);
	ledcAttachPin(m2_pin, m2_chan);

	pcnt_config_a.pulse_gpio_num 	= enc_a_pin;
	pcnt_config_a.ctrl_gpio_num 	= enc_b_pin;
	pcnt_config_a.lctrl_mode		= PCNT_MODE_REVERSE;
	pcnt_config_a.hctrl_mode 		= PCNT_MODE_KEEP;
	pcnt_config_a.channel 		    = PCNT_CHANNEL_0;
	pcnt_config_a.unit 			    = unit_;
	pcnt_config_a.pos_mode 		    = PCNT_COUNT_INC;
	pcnt_config_a.neg_mode 		    = PCNT_COUNT_DEC;
	pcnt_config_a.counter_h_lim 	= COUNTER_H_LIM;
	pcnt_config_a.counter_l_lim 	= COUNTER_L_LIM;

	pcnt_config_b.pulse_gpio_num 	= enc_b_pin;
	pcnt_config_b.ctrl_gpio_num 	= enc_a_pin;
	pcnt_config_b.lctrl_mode 		= PCNT_MODE_KEEP;
	pcnt_config_b.hctrl_mode 		= PCNT_MODE_REVERSE;
	pcnt_config_b.channel 		    = PCNT_CHANNEL_1;
	pcnt_config_b.unit 			    = unit_;
	pcnt_config_b.pos_mode 		    = PCNT_COUNT_INC;
	pcnt_config_b.neg_mode 		    = PCNT_COUNT_DEC;
	pcnt_config_b.counter_h_lim 	= COUNTER_H_LIM;
	pcnt_config_b.counter_l_lim 	= COUNTER_L_LIM;

    pcnt_unit_config(&pcnt_config_a);
	pcnt_unit_config(&pcnt_config_b);
	
	pcnt_counter_pause(unit_);
	pcnt_counter_clear(unit_);
	pcnt_counter_resume(unit_);
}

void Motor::set_velocity(int16_t vel)
{
    if (vel < 0)
    {
        ledcWrite(m1_chan_, 0);
	    ledcWrite(m2_chan_, abs(vel));
    }
    else if (vel > 0)
    {
        ledcWrite(m1_chan_, abs(vel));
	    ledcWrite(m2_chan_, 0);
    }
    else
    {
        ledcWrite(m1_chan_, 0);
	    ledcWrite(m2_chan_, 0);
    }
}

int16_t Motor::get_count(void)
{
    int16_t count;
    pcnt_get_counter_value(unit_, &count);
	if(count > 32767) pcnt_counter_clear(unit_);
	if(count < -32767) pcnt_counter_clear(unit_);
    return count;
}