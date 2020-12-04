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

  static void startTask(void *param);
  static void endTask();

  Chassis& drive(float distance, float targetVoltage_, float timeOut_);
  Chassis& turn(float theta_, float targetVoltage_, float timeOut_);
  Chassis& driveToPoint(float x, float y, float targetVoltage_, float timeOut_, bool reverse = false);
  Chassis& turnToPoint(float x, float y, float targetVoltage_, float timeOut_);
  Chassis& turnToAngle(float theta_, float targetVoltage_, float timeOut_);

  void waitUntilSettled();

private:
  static float leftVoltage, rightVoltage, timeOut;
  static float targetTheta, targetTicks, targetVoltage;
  static bool isRunning, isSettled, isTurning, isDriving;
  
};

#endif
