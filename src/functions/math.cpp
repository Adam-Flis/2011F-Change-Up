#include "main.h"
#include "define.hpp"
#include "functions/math.hpp"

/* ********** Define variables ********** */

float wheelDiameter = 2.75; //In inches
double wheelCircumference = wheelDiameter * M_PI;
float ticksPerRevolution = 360; //Number of ticks in one full revolution of encoder/motor

/**
 * Returns and converts ticks to inches
 * @param ticks
 */
float Math::ticksToInch(float ticks) {
  float wheelRevolutions = ticks/ticksPerRevolution * 1/1; //Teeth of driven/Teeth of driver
  float inches = wheelRevolutions * wheelCircumference;
  return inches;
}

/**
 * Returns and converts inches to ticks
 * @param inches
 */
float Math::inchToTicks(float inches) {
  float motorRevolutions = inches/wheelCircumference * 1/1; //Teeth of driver/Teeth of driven
  float ticks = motorRevolutions * ticksPerRevolution;
  return ticks;
}

/**
 * Returns and converts percent value to velocity value
 * @param percent -100 to 100 (In percentage of max speed)
 * @param cartColor 'R', 'G', 'B' (Color cart of motor insert; Red, Green, Blue)
 */
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

/**
 * Returns and converts percent to voltage
 */
float Math::percentToVoltage(float percent) {
  return percent * 120;
}

/**
 * Returns an angle between -180 and 180 degress
 * @param angle (In degress)
 */
float Math::angleWrap(float angle) {
  angle = fmod(angle + 180, 360);
  if (angle < 0) {
      angle += 360;
    }
  return angle - 180;
}

/**
 * Returns the average left and right encoder values
 */
float Math::encoderAverage() {
  return ((LEnc.get_value() + REnc.get_value())/2) * 1000.07178/1000;
}

/**
 * Returns and converts seconds to milliseconds
 * @param seconds (In seconds)
 */
float Math::secToMillis(float seconds) {
  return seconds*1000;
}
