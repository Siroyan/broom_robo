#include "main.hpp"

Motor l_motor(L_M1, L_M2, 0, 1, L_ENC_A_PIN, L_ENC_B_PIN, PCNT_UNIT_0);
Motor r_motor(R_M1, R_M2, 2, 3, R_ENC_A_PIN, R_ENC_B_PIN, PCNT_UNIT_1);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	Serial.printf("%d\t%d\n", l_motor.get_count(), r_motor.get_count());
	l_motor.set_velocity(0);
	r_motor.set_velocity(0);
	delay(10);
}