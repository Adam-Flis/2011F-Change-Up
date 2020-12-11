#include "main.h"
#include "define.hpp"
#include "functions/math.hpp"

/* ********** Define variables ********** */

float wheelDiameter = 2.75; //In inches
double wheelCircumference = wheelDiameter * M_PI;
float ticksPerRevolution = 360; //Number of ticks in one full revolution of encoder/motor

/**
 * Converts ticks to inches, then returns
 * @param ticks
 */
float Math::ticksToInch(float ticks) {
  float wheelRevolutions = ticks/ticksPerRevolution * 1/1; //Teeth of driven/Teeth of driver
  float inches = wheelRevolutions * wheelCircumference;
  return inches;
}

/**
 * Converts inches to ticks, then returns
 * @param inches
 */
float Math::inchToTicks(float inches) {
  float motorRevolutions = inches/wheelCircumference * 1/1; //Teeth of driver/Teeth of driven
  float ticks = motorRevolutions * ticksPerRevolution;
  return ticks;
}

/**
 * Filters sensor values
 * @param current (Current sensor value)
 * @param last (Last sensor value)
 */
float Math::filter(float current, float last) {
  float filteredVal = (current - last);
  if (fabs(filteredVal) < 0.01) {
    filteredVal = 0;
  }
  return filteredVal;
}

/**
 * Converts percent value to velocity value, then returns
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
 * Converts percent to voltage, then returns
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
 * Converts degress to radians, then returns
 * @param angle (In degress)
 */
float Math::degToRad(float angle) {
  return angle * M_PI / 180.0;
}

/**
 * Converts radians to degress, then returns
 * @param angle (In radians)
 */
float Math::radToDeg(float angle) {
  return angle / M_PI * 180.0;
}

/**
 * Converts seconds to milliseconds, then returns
 * @param seconds (In seconds)
 */
float Math::secToMillis(float seconds) {
  return seconds * 1000;
}
