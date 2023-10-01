#include "main.hpp"

Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);

Motor l_motor(L_M1, L_M2, 0, 1, L_ENC_A_PIN, L_ENC_B_PIN, PCNT_UNIT_0);
Motor r_motor(R_M1, R_M2, 2, 3, R_ENC_A_PIN, R_ENC_B_PIN, PCNT_UNIT_1);

void setup()
{
	Serial.begin(115200);
	if(!bno.begin())
	{
		Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
		while(1);
	}
	delay(1000);
	bno.setExtCrystalUse(true);
}

void loop()
{
	Serial.printf("%d\t%d\n", l_motor.get_count(), r_motor.get_count());
	l_motor.set_velocity(0);
	r_motor.set_velocity(0);

	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	Serial.print(euler.y());

	uint8_t vel = min(abs(20.0 * euler.y()), 255.0);
	if (euler.y() > 0.0)
	{
		l_motor.set_velocity(-vel);
		r_motor.set_velocity(-vel);
	}
	else
	{
		l_motor.set_velocity(vel);
		r_motor.set_velocity(vel);
	}

	delay(BNO055_SAMPLERATE_DELAY_MS);
}