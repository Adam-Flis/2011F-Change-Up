#include "main.h"

#ifndef PID_HPP
#define PID_HPP

class PID {
public:

  static float intergral_D, intergral_T, lErrorDistance, lErrorTheta;

  void drive(float errorDistance, float errorTheta, float maxVel, bool reversed);
  void arc(float errorDistance, float errorTheta, float maxVel, bool reversed);
  void turn(float errorTheta, float maxVel, char side = 'B', bool longestPath = false);

private:

};

#endif
