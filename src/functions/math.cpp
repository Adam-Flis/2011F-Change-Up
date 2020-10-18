#include "main.h"
#include "define.hpp"
#include "functions/math.hpp"

Math::Math(){};
Math::~Math(){};

float wheelDiameter = 2.75; //In inches
float wheelCircumference = wheelDiameter * M_PI;
float ticksPerRevolution = 360; //Number of ticks in one full revolution of encoder/motor

float Math::ticksToInch(float ticks) {
  float wheelRevolutions = ticks/ticksPerRevolution * 1/1; //Teeth of driven/Teeth of driver
  float inches = wheelRevolutions * wheelCircumference;
  return inches;
}

float Math::inchToTicks(float inches) {
  float motorRevolutions = inches/wheelCircumference * 1/1; //Teeth of driver/Teeth of driven
  float ticks = motorRevolutions * ticksPerRevolution;
  return ticks;
}

float Math::percentToVoltage(float percent) {
  return percent * 120;
}

// Makes sure angle is between -180 & 180 degress
float Math::angleWrapper(float angle) {

  return angle;
}
