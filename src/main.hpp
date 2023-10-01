#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "motor.hpp"

// Motor
const int L_M1 = 1;
const int L_M2 = 2;
const int R_M1 = 3;
const int R_M2 = 4;
// Encoder
const int L_ENC_A_PIN =  8;
const int L_ENC_B_PIN =  9;
const int R_ENC_A_PIN =  7;
const int R_ENC_B_PIN = 44;
// Imu
const int BNO055_SAMPLERATE_DELAY_MS = 100;

#endif