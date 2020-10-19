#include "main.h"

#ifndef MATH_HPP
#define MATH_HPP

class Math {
public:
  Math();
  ~Math();

  static float percentToVoltage(float percent);
  static float ticksToInch(float ticks);
  static float inchToTicks(float inches);
  static float angleWrap(float angle);

private:
};

#endif
