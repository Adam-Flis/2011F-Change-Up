#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Chassis::Chassis(){}
Chassis::~Chassis(){}

Chassis chassis;
static Math math;
static Odom odom;

// Define variables
bool Chassis::isRunning = false,
     Chassis::isSettled = true,
     Chassis::isTurning = false,
     Chassis::isDriving = false,
     Chassis::isArching = false,
     Chassis::reversed,
     Chassis::first;

double Chassis::targetTheta, Chassis::targetX, Chassis::targetY,
       Chassis::timeOut, Chassis::tolerance, Chassis::multiplier,
       Chassis::maxVelocity, Chassis::minVelocity, Chassis::leftVelocity, Chassis::rightVelocity;

char Chassis::errorType, Chassis::side;

Chassis& Chassis::stop() {
  leftVelocity = 0;
  rightVelocity = 0;
  LFD.move_velocity(0);
  LBD.move_velocity(0);
  RFD.move_velocity(0);
  RBD.move_velocity(0);
  return *this;
}

void brake() {
  LFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  LBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void coast() {
  LFD.set_brake_mode(MOTOR_BRAKE_COAST);
  LBD.set_brake_mode(MOTOR_BRAKE_COAST);
  RFD.set_brake_mode(MOTOR_BRAKE_COAST);
  RBD.set_brake_mode(MOTOR_BRAKE_COAST);
}

void hold() {
  LFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  LBD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RBD.set_brake_mode(MOTOR_BRAKE_HOLD);
}

Chassis& Chassis::moveVel(double velocity_, char side_) {
  side = side_;
  if (side_ == 'B') {
    rightVelocity = math.percentToVelocity(velocity_, 'G');
    leftVelocity = math.percentToVelocity(velocity_, 'G');
  } else if (side_ == 'L') {
    rightVelocity = 0;
    leftVelocity = math.percentToVelocity(velocity_, 'G');
  } else if (side_ == 'R') {
    rightVelocity = math.percentToVelocity(velocity_, 'G');
    leftVelocity = 0;
  }
  return *this;
}

Chassis& Chassis::driveToPoint(double targetX_, double targetY_, double maxVelocity_, char errorType_, bool reversed_) {
  targetX = targetX_;
  targetY = targetY_;
  maxVelocity = maxVelocity_;
  errorType = errorType_;
  reversed = reversed_;
  return *this;
}

Chassis& Chassis::arcToPoint(double targetX_, double targetY_, double maxVelocity_, char errorType_, bool reversed_) {
  targetX = targetX_;
  targetY = targetY_;
  maxVelocity = maxVelocity_;
  errorType = errorType_;
  reversed = reversed_;
  return *this;
}

Chassis& Chassis::turnToAngle(double targetTheta_, double maxVelocity_, char side_, bool reversed_) {
  targetTheta = targetTheta_;
  maxVelocity = maxVelocity_;
  side = side_;
  reversed = reversed_;
  return *this;
}

Chassis& Chassis::withMinVel(double minVelocity_) {
  minVelocity = minVelocity_;
  return *this;
}

Chassis& Chassis::withTolerance(double tolerance_) {
  tolerance = tolerance_;
  return *this;
}

Chassis& Chassis::withMultiplier(double multiplier_) {
  multiplier = multiplier_;
  return *this;
}

Chassis& Chassis::waitUntillSettled() {
  while(isSettled) delay(10);
  return *this;
}

void Chassis::start() {
  isRunning = true;
  isSettled = true;
  chassis.stop().brake();
  double turnVel, driveVel, driftVel, numOfTurns,
         errorTheta, errorX, errorY, errorDistance;
  while(isRunning) {
    if (!isSettled) {

      errorX = math.filter(targetX, odom.getX());
      errorY = math.filter(targetY, odom.getY());
      errorDistance = sqrt(pow(errorX, 2) * pow(errorY, 2));

      numOfTurns = fabs(odom.getThetaDeg() / 360);

      if (numOfTurns > 1) {
        targetTheta *= numOfTurns;
      }

      //Turn logic for when gyro > 360

      if (isTurning) {
        errorTheta = targetTheta - odom.getThetaDeg();
        if (reversed) {
          errorTheta = (ceil(numOfTurns) * 360) - abs(errorTheta);
        }
        if (side == 'B') {
          //turnVel = math.pid(errorTheta, kp, kd, ki, "Turn");
        } else if (side == 'L') {
          //turnVel = math.pid(errorTheta, kp, kd, ki, "Turn");
        } else if (side == 'R') {
          //turnVel = math.pid(errorTheta, kp, kd, ki, "Turn");
        }

        if (abs(turnVel) > maxVelocity) {
          turnVel = maxVelocity;
        } else if (abs(turnVel) < minVelocity) {
          turnVel = minVelocity;
        }

        leftVelocity = turnVel;
        rightVelocity = -turnVel;

        if (side == 'L') {
          rightVelocity = 0;
        } else if (side == 'R') {
          leftVelocity = 0;
        }

      }
      else if (isDriving) {
        targetTheta = math.radToDeg(math.angleIn180(atan2(errorX, errorY)));
        errorTheta = targetTheta - math.radToDeg(math.angleIn180(odom.getThetaRad()));
        //driveVel = math.pid(errorDistance, kp, kd, ki, "Drive");
        //driftVel = math.pid(errorDistance, kp, kd, ki, "Drift");

        if (abs(driveVel) > maxVelocity) {
          turnVel = maxVelocity;
        } else if (abs(driveVel) < minVelocity) {
          turnVel = minVelocity;
        }

        leftVelocity = (driveVel + driftVel);
        rightVelocity = (driveVel - driftVel);

      }
      else if (isArching) {
        if (first) {
          targetTheta = math.radToDeg(math.angleIn180(atan2(errorX, errorY)));
          first = false;
        }
        errorTheta = targetTheta - math.radToDeg(math.angleIn180(odom.getThetaRad()));
        //driveVel = math.pid(errorDistance, kp, kd, ki, "Drive");
        //turnVel = math.pid(errorTheta, kp, kd, ki, "Turn");

        if (abs(driveVel) > maxVelocity) {
          driveVel = maxVelocity;
        } else if (abs(driveVel) < minVelocity) {
          driveVel = minVelocity;
        }

        leftVelocity = (driveVel + turnVel);
        rightVelocity = (driveVel - turnVel);
      }

      leftVelocity *= multiplier;
      rightVelocity *= multiplier;

      LFD.move_velocity(leftVelocity);
      LBD.move_velocity(leftVelocity);
      RFD.move_velocity(rightVelocity);
      RBD.move_velocity(rightVelocity);
    }
  }
  delay(10);
}
