#include "main.h"
#include "define.hpp"
#include "functions/math.hpp"

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

float Math::percentToVelocity(float percent, char cartColor) {
  int multiplier;
  if (cartColor == 'R') {
    multiplier = 1;
  }
  else if (cartColor == 'G') {
    multiplier = 2;
  }
  else if (cartColor == 'B') {
    multiplier = 6;
  }
  return percent * multiplier;
}

float Math::percentToVoltage(float percent) {
  return percent * 120;
}

// Makes sure angle is between -180 & 180 degress
float Math::angleWrap(float angle) {
  angle = fmod(angle + 180, 360);
  if (angle < 0) {
      angle += 360;
    }
  return angle - 180;
}

float Math::encoderAverage() {
  return (LEnc.get_value() + REnc.get_value())/2;
}

float Math::secToMillis(float seconds) {
  return seconds*1000;
}
