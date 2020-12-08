#include "main.h"

#ifndef INTAKE_HPP
#define INTAKE_HPP

class Intake {
public:
  Intake();
  ~Intake();

  Intake& stop();
  void brake();

  void move(float velocity);

  void waitUntillColor(char color, float timeOut, bool atGoal = true);

};

#endif
