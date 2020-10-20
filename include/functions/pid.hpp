#include "main.h"

#ifndef PID_HPP
#define PID_HPP

class PID {
public:
  PID();
  ~PID();

  void drive(float distance, float maxSpeed);
  void turn(float theta, float maxSpeed);

private:

};

#endif
