#include "main.h"

#ifndef MATH_HPP
#define MATH_HPP

class Math {
public:

  static float ticksToInch(float ticks);
  static float inchToTicks(float inches);
  static float filter(float current, float last);

  static float percentToVelocity(float percent, char cartColor);
  static float percentToVoltage(float percent);

  static float angleWrap(float angle);
  static float angleIn180(float angle);
  static float degToRad(float angle);
  static float radToDeg(float angle);

  static float secToMillis(float seconds);

};

#endif
