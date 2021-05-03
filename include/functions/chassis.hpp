#include "main.h"

#ifndef CHASSIS_HPP
#define CHASSIS_HPP

class Chassis {
public:
  Chassis();
  ~Chassis();

  Chassis& stop();
  void brake();
  void coast();
  void hold();

  void reset();

  Chassis& move(double speed_, char side_ = 'B');

  Chassis& driveToPoint(double targetX_, double targetY_, double maxSpeed_,
                        char errorType_, double timeOut_, double angle_, bool reversed_ = false);

  Chassis& turnToAngle(double targetTheta_, double maxSpeed_, double timeOut_, char side_ = 'B', bool reversed_ = false);

  Chassis& withMinSpeed(double minSpeed_);
  Chassis& withTolerance(double tolerance_);
  Chassis& withMultiplier(double multiplier_);

  Chassis& waitUntillSettled();

  static void start();
  void end();

private:
  static bool isRunning, isSettled, isTurning, isDriving, reversed, first;
  static double targetTheta, targetX, targetY, timeOut, tolerance, multiplier,
                maxSpeed, minSpeed, leftSpeed, rightSpeed;
  static char errorType, side;
};

#endif
