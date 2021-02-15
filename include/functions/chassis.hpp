#include "main.h"

#ifndef CHASSIS_HPP
#define CHASSIS_HPP

class Chassis {
public:
  Chassis();
  ~Chassis();

  Chassis& stop();
  void brake();
  void hold();
  void coast();

  void move(float velocity, char side);

  void driveToPoint(float targetX, float targetY, float maxVel,
                        float pctCutoff, char errorType, bool reversed = false);

  void arcToPoint(float targetX, float targetY, float minVel, bool reversed = false);

  void turnToAngle(float targetTheta, float maxVel, float pctCutoff = 0.2, char side = 'B');

};

#endif
