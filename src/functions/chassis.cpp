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
     Chassis::isArcing = false,
     Chassis::reversed,
     Chassis::first;

double Chassis::targetTheta, Chassis::targetX, Chassis::targetY,
       Chassis::timeOut, Chassis::tolerance, Chassis::multiplier,
       Chassis::maxVelocity, Chassis::minVelocity, Chassis::leftVelocity, Chassis::rightVelocity;

char Chassis::errorType, Chassis::side;

double lastTheta, errorThetaL, errorDistanceL, errorDriftL;

Chassis& Chassis::stop() {
  leftVelocity = 0;
  rightVelocity = 0;
  LFD.move_velocity(0);
  LBD.move_velocity(0);
  RFD.move_velocity(0);
  RBD.move_velocity(0);
  chassis.reset();
  return *this;
}

void Chassis::brake() {
  LFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  LBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void Chassis::coast() {
  LFD.set_brake_mode(MOTOR_BRAKE_COAST);
  LBD.set_brake_mode(MOTOR_BRAKE_COAST);
  RFD.set_brake_mode(MOTOR_BRAKE_COAST);
  RBD.set_brake_mode(MOTOR_BRAKE_COAST);
}

void Chassis::hold() {
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
  maxVelocity = math.percentToVelocity(maxVelocity_, 'G');
  errorType = errorType_;
  reversed = reversed_;
  isDriving = true;
  isTurning = false;
  isArcing = false;
  isSettled = false;
  minVelocity = tolerance = 0;
  multiplier = 1;
  return *this;
}

Chassis& Chassis::arcToPoint(double targetX_, double targetY_, double maxVelocity_, char errorType_, bool reversed_) {
  targetX = targetX_;
  targetY = targetY_;
  maxVelocity = math.percentToVelocity(maxVelocity_, 'G');
  errorType = errorType_;
  reversed = reversed_;
  isDriving = false;
  isTurning = false;
  isArcing = true;
  isSettled = false;
  first = true;
  minVelocity = tolerance = 0;
  multiplier = 1;
  return *this;
}

Chassis& Chassis::turnToAngle(double targetTheta_, double maxVelocity_, char side_, bool reversed_) {
  targetTheta = targetTheta_;
  maxVelocity = math.percentToVelocity(maxVelocity_, 'G');
  side = side_;
  reversed = reversed_;
  isDriving = false;
  isTurning = true;
  isArcing = false;
  isSettled = false;
  first = true;
  minVelocity = tolerance = 0;
  multiplier = 1;
  return *this;
}

Chassis& Chassis::withMinVel(double minVelocity_) {
  minVelocity = math.percentToVelocity(minVelocity_, 'G');
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
  while(!isSettled) delay(10);
  return *this;
}

void Chassis::reset() {
  isSettled = true;
  first = isDriving = isTurning = isArcing = false;
  lastTheta = errorThetaL = errorDistanceL, errorDriftL = 0;
  minVelocity = tolerance = 0;
  multiplier = 1;
}

void Chassis::start() {

  isRunning = true;
  isDriving = false;
  isTurning = false;
  isArcing = false;
  isSettled = true;
  chassis.stop().brake();
  double turnVel, driveVel, driftVel, numOfTurns,
         currentX, currentY,
         errorTheta, errorX, errorY, errorDistance, errorDrift;

  while (isRunning) {
    if (!isSettled) {

      currentX = odom.getX();
      currentY = odom.getY();

      errorX = math.filter(targetX, currentX);
      errorY = math.filter(targetY, currentY);
      errorDistance = sqrt(pow(errorX, 2) + pow(errorY, 2));

      numOfTurns = fabs(odom.getThetaDeg() / 360);
      lcd::print(6, "%f", numOfTurns);

      if (first) { 
        if (numOfTurns > 1 && !isArcing) {
          targetTheta = fabs(odom.getThetaDeg()) + targetTheta;
        }
        if (isArcing) {
          targetTheta = math.radToDeg(atan2(errorX, errorY)) * numOfTurns * 2;
        }
        first = false;
      }


      if (isTurning) {
        errorTheta = math.filter(targetTheta, odom.getThetaDeg());

        if (reversed) {
          errorTheta = 360 - fabs(errorTheta);
        }
        lcd::print(7, "%f", errorTheta);

        if (side == 'B') {
          turnVel = math.pid(errorTheta, errorThetaL, 0.1, 0, 0, "Turn");
        } else if (side == 'L') {
          turnVel = math.pid(errorTheta, errorThetaL, 1, 0, 0, "Turn");
        } else if (side == 'R') {
          turnVel = math.pid(errorTheta, errorThetaL, 1, 0, 0, "Turn");
        }

        errorThetaL = errorTheta;

        if (fabs(turnVel) > maxVelocity) {
          turnVel = maxVelocity;
        } else if (fabs(turnVel) < minVelocity) {
          turnVel = minVelocity;
        }

        leftVelocity = turnVel;
        rightVelocity = -turnVel;

        if (side == 'L') {
          rightVelocity = 0;
        } else if (side == 'R') {
          leftVelocity = 0;
        }
      } else if (isDriving) {
        targetTheta = math.radToDeg(atan2(errorX, errorY)) * numOfTurns;
        errorDrift = math.filter(targetTheta, odom.getThetaDeg());
        driveVel = math.pid(errorDistance, errorDistanceL, 4.0, 1.0, 2.0, "Drive");
        driftVel = math.pid(errorDrift, errorDriftL, 0, 0, 0, "Drift");

        if (fabs(driveVel) > maxVelocity) {
          driveVel = maxVelocity;
        } else if (fabs(driveVel) < minVelocity) {
          driveVel = minVelocity;
        }

        leftVelocity = driveVel + driftVel;
        rightVelocity = driveVel - driftVel;

      } else if (isArcing) {

        errorTheta = math.filter(targetTheta, odom.getThetaDeg());
        errorDrift = math.filter(odom.getThetaDeg(), lastTheta);

        // Start turn component of arc
        if ((targetTheta / 2) < math.radToDeg(atan2(errorX, errorY))) {
          turnVel = math.pid(errorTheta, errorThetaL, 1, 0, 0, "Turn");
          driftVel = 0;
        } else {
          driftVel = math.pid(errorDrift, errorDriftL, 1, 0, 0, "Drift");
          turnVel = 0;
        }

        driveVel = math.pid(errorDistance, errorDistanceL, 1, 0, 0, "Drive");

        errorDistanceL = errorDistance;
        errorThetaL = errorTheta;
        errorDriftL = errorDrift;

        if (fabs(driveVel) > maxVelocity) {
          driveVel = maxVelocity;
        } else if (fabs(driveVel) < minVelocity) {
          driveVel = minVelocity;
        }

        if (errorTheta < 0) {
          turnVel *= -1;
        }

        leftVelocity = driveVel + turnVel + driftVel;
        rightVelocity = driveVel - turnVel - driftVel;
      }

      if (reversed) {
        leftVelocity *= -1;
        rightVelocity *= -1;
      }

      leftVelocity *= multiplier;
      rightVelocity *= multiplier;

      LFD.move_velocity(leftVelocity);
      LBD.move_velocity(leftVelocity);
      RFD.move_velocity(rightVelocity);
      RBD.move_velocity(rightVelocity);

      if (errorType == 'Y') {
        if (fabs(errorY) <= tolerance) {
          chassis.reset();
        }
      } else if (errorType == 'X') {
        if (fabs(errorX) <= tolerance) {
          chassis.reset();
        }
      } else if (errorType == 'D') {
        if (fabs(errorDistance) <= tolerance) {
          chassis.reset();
        }
      } else {
        if (fabs(errorTheta) <= tolerance) {
          chassis.stop();
          chassis.reset();
        }
      }

      // if (millis() >= stuckTimer) {
      //   chassis.reset();
      // }

      lastTheta = odom.getThetaDeg();

    }
    delay(10);
  }
}

void Chassis::end() {
  if (isRunning) {
    chassis.stop().brake(); // Stops the drivetrain
    isRunning = false;
    chassisTask->remove(); // Removes memory stack task is occupying
    delete chassisTask; // Deletes task from memory
    chassisTask = nullptr;
  }
}
