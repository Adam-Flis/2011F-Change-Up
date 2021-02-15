#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/pid.hpp"
#include "functions/math.hpp"

Chassis::Chassis(){}
Chassis::~Chassis(){}

Chassis chassis; // Class definition
static Math math;
static PID pid;
static Odom odom;

/* ********** Define variables ********** */




float targetX,
      targetY,
      targetTheta,
      maxVel,
      pctCutoff,

      errorX,
      errorY,
      errorDistance,
      errorTheta,
      aTan;

bool reversed, longestPath, first;

char side, errorType;

/**
 * Stops the chassis
 */
Chassis& Chassis::stop() {
  LFD.move_velocity(0);
  LBD.move_velocity(0);
  RFD.move_velocity(0);
  RBD.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the chassis to brake
 */
void Chassis::brake() {
  LFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  LBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the brake mode of the chassis to hold
 */
void Chassis::hold() {
  LFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  LBD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RBD.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Sets the brake mode of the chassis to coast
 */
void Chassis::coast() {
  LFD.set_brake_mode(MOTOR_BRAKE_COAST);
  LBD.set_brake_mode(MOTOR_BRAKE_COAST);
  RFD.set_brake_mode(MOTOR_BRAKE_COAST);
  RBD.set_brake_mode(MOTOR_BRAKE_COAST);
}

/**
 * Sets velocity of chassis side/s
 * @param velocity -100 to 100 (In percentage of drive max speed)
 * @param side 'L', 'R', or 'B' (Side of drive that will move; Left, Right, or Both)
 */
void Chassis::move(float velocity, char side) {
  if (side == 'L') {
    LFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    LBD.move_velocity(math.percentToVelocity(velocity, 'G'));
  } else if (side == 'R') {
    RFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    RBD.move_velocity(math.percentToVelocity(velocity, 'G'));
  } else if (side == 'B') {
    LFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    RFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    LBD.move_velocity(math.percentToVelocity(velocity, 'G'));
    RBD.move_velocity(math.percentToVelocity(velocity, 'G'));
  }
}

void Chassis::setFinalVL(float finalVL_) {
  chassis.finalVL = finalVL_;
}

void Chassis::setFinalVR(float finalVR_) {
  chassis.finalVR = finalVR_;
}

void Chassis::setStuckTimer(float stuckTimer_) {
  chassis.stuckTimer = stuckTimer_;
}

/**
 * Resets the chassis variables
 */
void Chassis::reset() {
  finalVR = finalVL = stuckTimer = 0;
  PID::intergral_T = PID::intergral_D = PID::lErrorTheta = PID::lErrorDistance = 0;
  chassis.brake();
  chassis.move(chassis.finalVL, 'L');
  chassis.move(chassis.finalVR, 'R');
  first = true;
  isSettled = true;
  isTurning = false;
  isDriving = false;
  isArcing = false;
}

/**
 * Starts the chassis drive task
 */
void Chassis::startTask() {
  first = false;
  isRunning = true;
  isSettled = false;
  isTurning = false;
  isDriving = false;
  isArcing = false;

  chassis.reset();
  cout<<"Chassis Task Started"<<endl;

  while(isRunning) {
    if (!isSettled) {
      errorX = math.filter(targetX, odom.getX());

      errorY = math.filter(targetY, odom.getY());

      errorDistance = sqrt(errorX * errorX + errorY * errorY);

      if (isDriving) {
        errorTheta = math.radToDeg(math.angleIn180(atan2(errorX, errorY))) -
                      math.radToDeg((math.angleIn180(odom.getTheta())));
        pid.drive(errorDistance, errorTheta, maxVel, reversed);
      } else if (isArcing) {
        if (first) {
          aTan = 2 * math.radToDeg(math.angleIn180(atan2(errorX, errorY)));
          first = false;
        }
        errorTheta = fabs(aTan - math.radToDeg((math.angleIn180(odom.getTheta()))));
        pid.arc(errorDistance, errorTheta, maxVel, reversed);
      } else if (isTurning) {
        errorTheta = math.radToDeg(math.angleWrap(fabs(math.degToRad(targetTheta) - odom.getTheta())));
        pid.turn(errorTheta, maxVel, side, longestPath);
      }

      if (errorType == 'Y' && fabs(errorY) < pctCutoff) {
          chassis.reset();
      } else if (errorType == 'X' && fabs(errorX) < pctCutoff) {
          chassis.reset();
      } else if (errorType == 'D' && fabs(errorDistance) < pctCutoff) {
          chassis.reset();
      } else if (errorTheta < 0.2 && isTurning) {
          chassis.reset();
      } else if (millis() > chassis.stuckTimer) {
        chassis.reset();
      }
      chassis.move(chassis.finalVL, 'L');
      chassis.move(chassis.finalVR, 'R');
    }
    delay(10);
  }
}

Chassis& Chassis::driveToPoint(float targetX_, float targetY_, float maxVel_,
                               float pctCutoff_, char errorType_, bool reversed_) {
  if (isRunning) {
    targetX = targetX_;
    targetY = targetY_;

    maxVel = math.percentToVelocity(maxVel_, 'G');

    pctCutoff = pctCutoff_;

    errorType = errorType_;

    reversed = reversed_;

    isDriving = true;
    isTurning = false;
    isArcing = false;
    isSettled = false;
  }
  return *this;
}

Chassis& Chassis::turnToAngle(float targetTheta_, float maxVel_, float pctCutoff_, char side_, bool longestPath_) {
  if (isRunning) {
    targetTheta = targetTheta_;

    maxVel = math.percentToVelocity(maxVel_, 'G');

    pctCutoff = pctCutoff_;

    side = side_;

    longestPath = longestPath_;

    isDriving = false;
    isTurning = true;
    isArcing = false;
    isSettled = false;
  }
  return *this;
}

/**
 * Ends the chassis drive task
 */
void Chassis::endTask() {
  if (chassisTask != nullptr) {
    chassisTask->remove(); // Removes memory stack task is occupying
    delete chassisTask; // Deletes the task from memory
    chassisTask = nullptr;
    cout<<"Chassis task ended"<<endl;
  }
}

/**
 * Waits until the chassis has settled
 */
void Chassis::waitUntilSettled() {
  while(!isSettled) {
    delay(10); // Loop speed, prevent overload
  }
}
