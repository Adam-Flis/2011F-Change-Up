#include "main.h"

#ifndef PID_HPP
#define PID_HPP

class PID {
public:
  PID();
  ~PID();

  void drive(float targetTicks_, float maxSpeed_);
  void turn(float targetTheta_, float maxSpeed_);

private:

};

#endif
