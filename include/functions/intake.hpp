#include "main.h"

#ifndef INTAKE_HPP
#define INTAKE_HPP

class Intake {
  public:
    Intake();
    ~Intake();

    void move(int velocity);
    Intake& stop();
    void brake();
};

#endif
