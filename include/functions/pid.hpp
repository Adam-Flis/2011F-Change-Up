#include "main.h"

#ifndef PID_HPP
#define PID_HPP

class PID {
public:

  float drive(float errorTicks_, float maxVelocity_);
  float drift();
  float turn(float errorTheta_, float maxVelocity_);
  float* arc(float errorX_, float errorY_, float maxVelocity_);

private:

};

#endif
