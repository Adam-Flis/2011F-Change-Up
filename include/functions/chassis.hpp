#include "main.h"

#ifndef CHASSIS_HPP
#define CHASSIS_HPP

class Chassis {
public:
  Chassis();
  ~Chassis();

  Chassis& stop();
  void brake();
  void hold();
  void coast();

  void move(float velocity, char side);
  void reset();

  static void startTask();
  static void endTask();

  Chassis& drive(float distance, float targetVelocity_, float timeOut_);
  Chassis& turn(float theta, float targetVelocity_, float timeOut_);
  Chassis& driveToPoint(float targetX_, float targetY_, float targetVelocity_, float timeOut_, bool reversed_ = false);
  Chassis& arcToPoint(float targetX_, float targetY_, float targetVelocity_, float timeOut_, bool reversed_ = false);
  Chassis& turnToPoint(float targetX_, float targetY_, float targetVelocity_, float timeOut_, bool longestPath_ = false);
  Chassis& turnToAngle(float targetTheta_, float targetVelocity_, float timeOut_, char side_ = 'B', bool longestPath_ = false);

  void waitUntilSettled();

private:
  static bool isRunning, isSettled, isTurning, isDriving, isArcing;

};

#endif
