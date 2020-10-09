#include "main.h"

#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

class Odom {
public:
  Odom();
  ~Odom();

  static float ticksToInch(float ticks);
  void reset();
  float getX();
  float getY();
  float getTheta();
  float getIMURot();
  static void track(void* param);




private:
  float x, y, theta, IMURot;
};

#endif
