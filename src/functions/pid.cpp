#include "main.h"
#include "define.hpp"
#include "functions/pid.hpp"
#include "functions/math.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

PID pid; // Class definition
Math math;
Odom odom;
Chassis chassis;

float kP_D = 9.0,
      kI_D = 2.6,
      kD_D = 8.0,

      kP_T = 2.8,
      kI_T = 0.75,
      kD_T = 2.1,

      kP_DA = 5.9,
      kI_DA = 1.0,
      kD_DA = 5.6,

      kP_TA = 2.5,
      kI_TA = 0.3972,
      kD_TA = 2.370,

      drift = 0.01,

      integralZone_D = 13,

      integralZone_T = 5,

      integralZone_DA = 13,

      integralZone_TA = 3,

      stuckTime = 250,

      proportion_D,
      proportion_T,

      PID::intergral_D,
      PID::intergral_T,

      derivative_D,
      derivative_T,

      driveVel,
      turnVel,

      PID::lErrorDistance,
      PID::lErrorTheta;

void PID::drive(float errorDistance, float errorTheta, float maxVel, bool reversed) {
  float intergralLimit_D = (maxVel/kI_D)/50;

  proportion_D = errorDistance;

  if (fabs(errorDistance) < integralZone_D && errorDistance != 0) {
    intergral_D += errorDistance;
  } else {
    intergral_D = 0;
  }

  if (intergral_D > intergralLimit_D) {
    intergral_D = intergralLimit_D;
  }

  derivative_D = errorDistance - lErrorDistance;
  lErrorDistance = errorDistance;

  if (math.filter(errorDistance, lErrorDistance) > 0) {
    chassis.setStuckTimer(millis() + stuckTime);
  }

  driveVel = (kP_D * proportion_D + kI_D * intergral_D + kD_D * derivative_D);

  if (driveVel > maxVel) {
    driveVel = maxVel;
  } else if (driveVel < -maxVel) {
    driveVel = -maxVel;
  }

  if (reversed) {
    driveVel = -driveVel;
  }

  derivative_T = fabs(errorTheta) - lErrorTheta;
  lErrorTheta = fabs(errorTheta);
  turnVel = derivative_T * drift;

  chassis.setFinalVL(driveVel + turnVel);
  chassis.setFinalVR(driveVel - turnVel);
}

void PID::arc(float errorDistance, float errorTheta, float maxVel, bool reversed) {

}

void PID::turn(float errorTheta, float maxVel, char side, bool longestPath) {
  float intergralLimit_T = (maxVel/kI_T)/50;
  proportion_T = errorTheta;

  if (errorTheta < integralZone_T && errorTheta != 0) {
    intergral_T += errorTheta;
  } else {
    intergral_T = 0;
  }

  if (intergral_T > intergralLimit_T) {
    intergral_T = intergralLimit_T;
  }

  derivative_T = errorTheta - lErrorTheta;
  lErrorTheta = errorTheta;

  if (math.filter(errorTheta, lErrorTheta) > 0) {
    chassis.setStuckTimer(millis() + stuckTime);
  }

  if (side == 'B') {
    turnVel = (kP_T * proportion_T + kI_T * intergral_T + kD_T * derivative_T) * 1;
  } else {
    turnVel = (kP_T * proportion_T + kI_T * intergral_T + kD_T * derivative_T) * 2;
  }

  if (turnVel > maxVel) {
    turnVel = maxVel;
  } else if (turnVel < -maxVel) {
    turnVel = -maxVel;
  }

  if (side == 'B') {
    chassis.setFinalVL(turnVel);
    chassis.setFinalVR(-turnVel);
  } else if (side == 'L') {
    chassis.setFinalVL(turnVel);
    chassis.setFinalVR(0);
  } else if (side == 'R') {
    chassis.setFinalVL(0);
    chassis.setFinalVR(-turnVel);
  }
}
