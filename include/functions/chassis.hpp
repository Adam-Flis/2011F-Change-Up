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
    void leftVolt(int voltage);
    void rightVolt(int voltage);
    static void startTask(void *param);
    static void endTask();
    void drive(float distance_, float maxSpeed_, float timeOut_);
    void turn(float theta_, float maxSpeed_, float timeOut_);
    void driveToPoint(float x_, float y_, float maxSpeed_, float timeOut_);
    void turnToPoint(float x_, float y_, float maxSpeed_, float timeOut_);
    void turnToAngle(float theta_, float maxSpeed_, float timeOut_);

  private:
    static float distance, theta, maxSpeed, timeOut;
    static bool isRunning, isSettled;
};

#endif
