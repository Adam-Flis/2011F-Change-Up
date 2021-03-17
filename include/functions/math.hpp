#include "main.h"

#ifndef MATH_HPP
#define MATH_HPP

class Math {
public:
  static double ticksToInch(double ticks);
  static double inchToTicks(double inches);
  static double filter(double current, double last);

  static double percentToVelocity(double percent, char cartColor);
  static double percentToVoltage(double percent);

  static double angleWrap(double rad);
  static double angleIn180(double rad);
  static double degToRad(double deg);
  static double radToDeg(double rad);

  static double secToMillis(double seconds);

};

#endif
