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
       Chassis::maxVelocity, Chassis::minVelocity, Chassis::leftVelocity, Chassis::rightVelocity,
       Chassis::angle;

char Chassis::errorType, Chassis::side;

double lastTheta, errorThetaL, errorDistanceL, errorDriftL, lastVelocity, intergralActive;

double turnVel, driveVel, driftVel,
       currentX, currentY, motorVoltage,
       errorTheta, errorX, errorY, errorDistance, errorDrift,
       minMovement = math.percentToVelocity(15, 'G');

Chassis& Chassis::stop() {
  leftVelocity = 0;
  rightVelocity = 0;
  minVelocity = 0;
  driftVel = 0;
  driveVel = 0;
  turnVel = 0;
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
  isSettled = false;
  side = side_;
  if (side_ == 'B') {
    rightVelocity = math.percentToVelocity(velocity_, 'G');
    leftVelocity = math.percentToVelocity(velocity_, 'G');
  } else if (side_ == 'L') {
    leftVelocity = math.percentToVelocity(velocity_, 'G');
  } else if (side_ == 'R') {
    rightVelocity = math.percentToVelocity(velocity_, 'G');
  }
  return *this;
}

Chassis& Chassis::driveToPoint(double targetX_, double targetY_, double maxVelocity_, char errorType_, double timeOut_, double angle_, bool reversed_) {
  targetX = targetX_;
  targetY = targetY_;
  maxVelocity = math.percentToVelocity(maxVelocity_, 'G');
  errorType = errorType_;
  angle = angle_;
  timeOut = math.secToMillis(timeOut_) + millis();
  reversed = reversed_;
  isDriving = true;
  isSettled = false;
  tolerance = 0.2;
  return *this;
}

Chassis& Chassis::arcToPoint(double targetX_, double targetY_, double maxVelocity_, char errorType_, double timeOut_, bool reversed_) {
  targetX = targetX_;
  targetY = targetY_;
  maxVelocity = math.percentToVelocity(maxVelocity_, 'G');
  errorType = errorType_;
  timeOut = math.secToMillis(timeOut_) + millis();
  reversed = reversed_;
  isArcing = true;
  isSettled = false;
  tolerance = 0.1;
  return *this;
}

Chassis& Chassis::turnToAngle(double targetTheta_, double maxVelocity_, double timeOut_, char side_, bool reversed_) {
  targetTheta = targetTheta_;
  maxVelocity = math.percentToVelocity(maxVelocity_, 'G');
  side = side_;
  timeOut = math.secToMillis(timeOut_) + millis();
  reversed = reversed_;
  isTurning = true;
  isSettled = false;
  tolerance = 0.025;
  return *this;
}

Chassis& Chassis::withMinVel(double minVelocity_) {
  minVelocity = math.percentToVelocity(minVelocity_, 'G');
  if (minVelocity <= minMovement) {
    minVelocity = minMovement;
  }
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
  while (!isSettled) delay(10);
  return *this;
}

void Chassis::reset() {
  isSettled = true;
  isDriving = isTurning = isArcing = false;
  targetX = targetY = targetTheta = timeOut = maxVelocity = 0;
  errorTheta = errorDistance = errorX = errorY = 0;
  lastTheta = errorThetaL = errorDistanceL = errorDriftL = lastVelocity = intergralActive = 0;
  errorType = 'N';
  multiplier = 1;
  first = true;
  minVelocity = minMovement;
}

void Chassis::start() {
  isRunning = true;
  isDriving = false;
  isTurning = false;
  isArcing = false;
  isSettled = true;
  chassis.stop().brake();
  while (isRunning) {
    if (!isSettled) {

      currentX = odom.getX();
      currentY = odom.getY();

      errorX = math.filter(targetX, currentX);
      errorY = math.filter(targetY, currentY);
      errorDistance = sqrt(pow(errorX, 2) + pow(errorY, 2));

      if (isTurning) {

        if (first) {
          math.intergral = 0;
          first = false;
        }

        errorTheta = math.filter(targetTheta, odom.getThetaDeg());

        if (side == 'B') {
          turnVel = math.pid(errorTheta, errorThetaL, 0.92, 0.012, 11.5, 15, "Turn");
        } else if (side == 'L') {
          turnVel = math.pid(errorTheta, errorThetaL, 0.92, 0.012, 11.5, 15, "Turn");
        } else if (side == 'R') {
          turnVel = math.pid(errorTheta, errorThetaL, 0.92, 0.012, 11.5, 15, "Turn");
        }

        errorThetaL = errorTheta;

        if (fabs(turnVel) > maxVelocity) {
          turnVel = maxVelocity;
        } else if (fabs(turnVel) < minVelocity) {
          turnVel = minVelocity;
        }

        if (minVelocity <= minMovement) {
          minVelocity = 0;
        }

        lcd::print(7, "%f", turnVel);

        cout<<turnVel<<endl;

        leftVelocity = turnVel * multiplier;
        rightVelocity = -turnVel * multiplier;

        if (side == 'L') {
          rightVelocity = 0;
        } else if (side == 'R') {
          leftVelocity = 0;
        }
      } else if (isDriving) {

        if (first) {
          math.intergral = 0;
          intergralActive = errorDistance * 0.25;
          first = false;
        }

        //driveVel = math.pid(errorDistance, errorDistanceL, 2.9, 0.01, 5.25, intergralActive, "Drive");
        driveVel = math.pid(errorDistance, errorDistanceL, 3.2, 0.01, 5.55, intergralActive, "Drive");
        errorDistanceL = errorDistance;

        errorDrift = odom.getThetaDeg() - angle;
        driftVel = errorDrift * 0.01;

        driveVel = math.slew(driveVel, lastVelocity);
        lastVelocity = driveVel;

        if (fabs(driveVel) > maxVelocity) {
          driveVel = maxVelocity;
        } else if (fabs(driveVel) < minVelocity) {
          driveVel = minVelocity;
        }

        lcd::print(7, "%f", driveVel);

        cout<<driveVel<<endl;

        // if (!reversed) {
        //   driveVel = math.slew(driveVel, lastVelocity);
        //   lastVelocity = driveVel;
        // }

        leftVelocity = (driveVel - driftVel) * multiplier;
        rightVelocity = (driveVel + driftVel) * multiplier;

      } else if (isArcing) {

        if (first) {
          targetTheta = math.radToDeg(atan2(targetX, targetY)) * 2;
          first = false;
        }

        if (targetTheta != math.angleWrap(odom.getThetaRad())) {
          errorTheta = math.filter(targetTheta, odom.getThetaDeg());
          //turnVel = math.pid(errorTheta, errorThetaL, 0.6, 0.025, 0.05, "Turn");
          errorThetaL = errorTheta;
        } else {
          turnVel = 0;
        }

        // lcd::print(6, "%f", errorTheta);

        //driveVel = math.pid(errorDistance, errorDistanceL, 2.9, 1.5, 2.0, "Drive");
        errorDistanceL = errorDistance;

        if (fabs(driveVel) > maxVelocity) {
          driveVel = maxVelocity;
        } else if (fabs(driveVel) < minVelocity) {
          driveVel = minVelocity;
        }

        if (errorTheta < 0) {
          turnVel *= -1;
        } else {
          turnVel *= 1;
        }

        // lcd::print(7, "%f", turnVel);

        leftVelocity = (driveVel + turnVel) * multiplier;
        rightVelocity = (driveVel - turnVel) * multiplier;
      }

      if (reversed) {
        leftVelocity *= -1;
        rightVelocity *= -1;
      }

      LFD.move_velocity(leftVelocity);
      RFD.move_velocity(rightVelocity);
      LBD.move_velocity(leftVelocity);
      RBD.move_velocity(rightVelocity);

      if (errorType == 'Y' && fabs(errorY) <= tolerance) {
        if (minVelocity <= minMovement) {
          chassis.stop();
        }
        chassis.reset();
      } else if (errorType == 'X' && fabs(errorX) <= tolerance) {
        if (minVelocity <= minMovement) {
          chassis.stop();
        }
        chassis.reset();
      } else if (errorType == 'D' && fabs(errorDistance) <= tolerance) {
        if (minVelocity <= minMovement) {
          chassis.stop();
        }
        chassis.reset();
      } else if (fabs(errorTheta) <= tolerance && isTurning) {
        chassis.stop();
        chassis.reset();
      }

      if (millis() > timeOut && timeOut != 0) {
         chassis.stop();
         chassis.reset();
      }
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
