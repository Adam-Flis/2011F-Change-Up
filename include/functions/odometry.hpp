#include "main.h"

#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

class Odom {
public:
  Odom();
  ~Odom();

  int inchToTicks(int ticks);
  void reset();
  void track();




private:
  float x, y, theta;
};

#endif
