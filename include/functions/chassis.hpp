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
  void setLeftVolt(float voltage);
  void setRightVolt(float voltage);
  void reset();
  static void startTask(void *param);
  static void endTask();
  Chassis& drive(float distance, float maxSpeed_, float timeOut_);
  Chassis& turn(float theta, float maxSpeed_, float timeOut_);
  Chassis& driveToPoint(float x, float y, float maxSpeed_, float timeOut_);
  Chassis& turnToPoint(float x, float y, float maxSpeed_, float timeOut_);
  Chassis& turnToAngle(float theta, float maxSpeed_, float timeOut_);
  void waitUntilSettled();

private:
  static float leftVolt, rightVolt, maxSpeed, timeOut;
  static float targetTheta, targetTicks;
  static bool isRunning, isSettled, isTurning, isDriving;
};

#endif
