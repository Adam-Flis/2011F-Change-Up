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
    void drive(float distance, float maxSpeed, float timeOut);
    void turn(float theta, float maxSpeed, float timeOut);
    void driveToPoint(float x, float y, float maxSpeed, float timeOut);
    void turnToPoint(float x, float y, float maxSpeed, float timeOut);
    void turnToAngle(float theta, float maxSpeed, float timeOut);


  private:
    static bool isRunning, isSettled;
};

#endif
