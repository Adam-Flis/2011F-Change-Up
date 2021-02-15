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

  static float angleWrap(float rad);
  static float angleIn180(float rad);
  static float degToRad(float deg);
  static float radToDeg(float rad);

  static float secToMillis(float seconds);

};

#endif
