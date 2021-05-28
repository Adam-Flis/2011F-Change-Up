#include "main.h"

#ifndef INTAKE_HPP
#define INTAKE_HPP

class Intake {
public:
  Intake();
  ~Intake();

  Intake& stop();
  void brake();
  void coast();
  void hold();

  Intake& moveVel(double velocity);
  Intake& moveVolt(double voltage);

private:

};

#endif
