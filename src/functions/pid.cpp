#include "main.h"
#include "define.hpp"
#include "functions/pid.hpp"
#include "functions/math.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

PID pid; // Class definition

float* PID::arc(float errorX_, float errorY_, float maxVelocity_) {
  float velocityArr[2];
  velocityArr[0] = 1;
  velocityArr[1] = 2;

  return velocityArr;
}
