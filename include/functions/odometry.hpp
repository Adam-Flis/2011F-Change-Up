#include "main.h"

#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

class Odom {
public:
  Odom();
  ~Odom();

  static double ticksToInch(int ticks);
  void reset();
  double getX();
  double getY();
  double getTheta();
  static void track(void* param);




private:
  float x, y, theta;
};

#endif
