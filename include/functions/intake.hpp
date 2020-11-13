#include "main.h"

#ifndef INTAKE_HPP
#define INTAKE_HPP

class Intake {
public:
  Intake();
  ~Intake();

  void move(float velocity);
  Intake& stop();
  void brake();
  void waitUntillColor(char color, float timeOut);
};

#endif
