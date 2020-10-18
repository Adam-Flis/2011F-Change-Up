#include "main.h"

#ifndef PID_HPP
#define PID_HPP

class PID {
public:
  PID();
  ~PID();

  void drivePID(float x, float y, float maxSpeed);
  void turnPID(float theta, float maxSpeed);

private:

}

#endif
