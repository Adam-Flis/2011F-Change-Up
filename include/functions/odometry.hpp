#include "main.h"

#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

class Odom {
public:
  void reset();

  double getX();
  double getY();
  double getThetaRad();
  double getThetaDeg();

  static void start();
  void end();

private:
  static bool isRunning;
  static double x, y, thetaRad, thetaDeg;
};

#endif
