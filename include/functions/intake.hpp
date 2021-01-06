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

  void waitUntilColor(char color, float timeOut);

};

#endif
