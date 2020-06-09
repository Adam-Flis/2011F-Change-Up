#include "main.h"

#ifndef CHASSIS_HPP
#define CHASSIS_HPP

class Chassis {
  public:

    Chassis& stop();
    void brake();
    void hold();
    void coast();
    void move(string side, int voltage);

};

#endif
