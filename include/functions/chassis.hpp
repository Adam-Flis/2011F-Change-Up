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

  void setFinalVL(float finalVL_);
  void setFinalVR(float finalVR_);
  void setStuckTimer(float stuckTimer_);

  static void startTask();
  static void endTask();

  Chassis& driveToPoint(float targetX_, float targetY_, float maxVel_,
                        float pctCutoff_, char errorType_, bool reversed_ = false);

  Chassis& arcToPoint(float targetX_, float targetY_, float targetVelocity_, bool reversed_ = false);

  Chassis& turnToAngle(float targetTheta_, float maxVel_, float pctCutoff_, char side_ = 'B', bool longestPath_ = false);

  void waitUntilSettled();

private:
  static bool isRunning, isSettled, isTurning, isDriving, isArcing;
  float finalVL, finalVR, stuckTimer;

};

#endif
