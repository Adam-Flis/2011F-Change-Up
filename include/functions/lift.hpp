#include "main.h"

#ifndef LIFT_HPP
#define LIFT_HPP


class Lift {
  public:
    Lift();
    ~Lift();

    Lift& stop();
    Lift& move(int target_, int velocity_, float timeOut_);

    void waitUntillSettled();

    void setBrakeMode();

    static void start(void *ignore);
    void run();
    void move(int velocity);

    static int top;
    static int bottom;

  private:
    static int target, velocity;
    static float timeOut;
    static int hold;
    static bool isRunning, isSettled;
};

#endif
