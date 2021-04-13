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

  Chassis& moveVel(double velocity_, char side_ = 'B');

  Chassis& driveToPoint(double targetX_, double targetY_, double maxVelocity_,
                        char errorType_, double timeOut_, double angle_, bool reversed_ = false);

  Chassis& arcToPoint(double targetX_, double targetY_, double maxVelocity_,
                      char errorType_, double timeOut_, bool reversed_ = false);

  Chassis& turnToAngle(double targetTheta_, double maxVelocity_, double timeOut_, char side_ = 'B', bool reversed_ = false);

  Chassis& withMinVel(double minVelocity_);
  Chassis& withTolerance(double tolerance_);
  Chassis& withMultiplier(double multiplier_);

  Chassis& waitUntillSettled();

  static void start();
  void end();

private:
  static bool isRunning, isSettled, isTurning, isDriving, isArcing, reversed, first;
  static double targetTheta, targetX, targetY, timeOut, tolerance, multiplier,
                maxVelocity, minVelocity, leftVelocity, rightVelocity, angle;
  static char errorType, side;
};

#endif
