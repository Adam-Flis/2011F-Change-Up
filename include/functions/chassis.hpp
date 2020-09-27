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

  private:

};

#endif
