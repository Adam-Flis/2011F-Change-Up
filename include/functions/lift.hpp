#include "main.h"

#ifndef LIFT_HPP
#define LIFT_HPP

class Lift{
  public:
    Lift();
    ~Lift();

    static void startTask(void *param);
    void endTask();

    Lift& move(int velocity_, int target_, int timeOut_);
    Lift& setVelocity(int velocity_);
    Lift& setTarget(int target_);
    Lift& setTimeOut(int timeOut_);

    int getVelocity();
    int getTarget();
    int getTimeOut();

    void reset();
    void waitUntilTime(int time_);
    void waitUntilTarget(int target_);
    void waitUntilSettled();

    Lift& stop();
    int getPot();
    void setBrakeMode();

    static int topLimit, bottomLimit, bothIntakesLimit;

  private:
    static int target, velocity, timeOut;
    static int hold;
    static bool isRunning, isSettled;
};

#endif
