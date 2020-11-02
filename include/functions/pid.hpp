#include "main.h"

#ifndef PID_HPP
#define PID_HPP

class PID {
public:

  float drive(float targetTicks_, float maxSpeed_);
  float drift();
  float turn(float targetTheta_, float maxSpeed_);

private:

};

#endif
