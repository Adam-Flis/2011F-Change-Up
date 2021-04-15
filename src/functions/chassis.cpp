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

/**
* Stops the chassis
*/
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
 * Sets the brake mode of the chassis to coast
 */
void Chassis::coast() {
  LFD.set_brake_mode(MOTOR_BRAKE_COAST);
  LBD.set_brake_mode(MOTOR_BRAKE_COAST);
  RFD.set_brake_mode(MOTOR_BRAKE_COAST);
  RBD.set_brake_mode(MOTOR_BRAKE_COAST);
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
 * Sets the velocity of the chassis
 * @param velocity_ -100 to 100 (In percentage of max chassis speed)
 * @param side_ 'B', 'L', 'R' (Chassis side that will move; Both, Left, or Right)
 */
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

/**
 * Moves the robot to a specific point
 * @param targetX_ (In inches)
 * @param targetY_ (In inches)
 * @param maxVelocity_ 0 to 100 (In percentage of chassis max speed)
 * @param errorType_ 'X', 'Y', or 'D' (Breaking error type; X, Y, or Distance)
 * @param timeOut_ (In seconds)
 * @param angle_ (In degress; angle robot drives at)
 * @param reverse_ True or False (Perform action backwards; false by default)
 */
Chassis& Chassis::driveToPoint(double targetX_, double targetY_, double maxVelocity_, char errorType_,
                               double timeOut_, double angle_, bool reversed_) {
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

/**
 * Turns the robot to a specific angle
 * @param targetTheta (In degress)
 * @param maxVelocity_ 0 to 100 (In percentage of chassis max speed)
 * @param timeOut_ (In seconds)
 * @param side_ 'B', 'L', 'R' (Chassis side that will move; Both, Left, or Right)
 * @param reverse_ True or False (Perform action backwards; false by default)
 */
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

/**
 * Minimum velocity for movements
 * @param minVelocity_ 0 to 100 (In percentage of chassis max speed)
 */
Chassis& Chassis::withMinVel(double minVelocity_) {
  minVelocity = math.percentToVelocity(minVelocity_, 'G');
  if (minVelocity <= minMovement) {
    minVelocity = minMovement;
  }
  return *this;
}

/**
 * isSettled or break tolerance for movements
 * @param tolerance_ (In inches or degress)
 */
Chassis& Chassis::withTolerance(double tolerance_) {
  tolerance = tolerance_;
  return *this;
}

/**
 * Speed multiplier for movements
 * @param multiplier_
 */
Chassis& Chassis::withMultiplier(double multiplier_) {
  multiplier = multiplier_;
  return *this;
}

/**
 * Waits until the chassis has settled
 */
Chassis& Chassis::waitUntillSettled() {
  while (!isSettled) delay(10);
  return *this;
}

/**
 * Resets the chassis variables
 */
void Chassis::reset() {
  isSettled = true;
  isDriving = isTurning = false;
  targetX = targetY = targetTheta = timeOut = maxVelocity = 0;
  errorTheta = errorDistance = errorX = errorY = 0;
  lastTheta = errorThetaL = errorDistanceL = errorDriftL = lastVelocity = intergralActive = 0;
  errorType = 'N';
  multiplier = 1;
  first = true;
  minVelocity = minMovement;
}

/**
 * Starts the chassis drive task
 */
void Chassis::start() {
  isRunning = true;
  isDriving = false;
  isTurning = false;
  isSettled = true;
  chassis.stop().brake();
  while (isRunning) {
    if (!isSettled) {

      currentX = odom.getX();
      currentY = odom.getY();

      errorX = math.filter(targetX, currentX);
      errorY = math.filter(targetY, currentY);
      errorDistance = sqrt(pow(errorX, 2) + pow(errorY, 2)); // Calculate distance from target in inches

      if (isTurning) {

        if (first) {
          math.intergral = 0;
          first = false;
        }

        errorTheta = math.filter(targetTheta, odom.getThetaDeg());

        // Pass error into PID loop to calculate velocity
        if (side == 'B') {
          turnVel = math.pid(errorTheta, errorThetaL, 0.95, 0.0015, 7.9, 15, "Turn");
          // turnVel = math.pid(errorTheta, errorThetaL, 0.92, 0.012, 11.5, 15, "Turn");
        } else if (side == 'L') {
          turnVel = math.pid(errorTheta, errorThetaL, 0.92, 0.012, 11.5, 15, "Turn");
        } else if (side == 'R') {
          turnVel = math.pid(errorTheta, errorThetaL, 0.92, 0.012, 11.5, 15, "Turn");
        }

        errorThetaL = errorTheta; // Set last error to current error

        // Constrain velocity
        if (fabs(turnVel) > maxVelocity) {
          turnVel = maxVelocity;
        } else if (fabs(turnVel) < minVelocity) {
          turnVel = minVelocity;
        }

        if (minVelocity <= minMovement) {
          minVelocity = 0;
        }

        // Display velocity to lcd; useful for debugging
        // lcd::print(7, "%f", turnVel);

        // Set velocity variables
        leftVelocity = turnVel * multiplier;
        rightVelocity = -turnVel * multiplier;

        // Sets velocity of a side to 0 only if one side is set to move
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

        // Pass error into PID loop to calculate velocity
        driveVel = math.pid(errorDistance, errorDistanceL, 3.2, 0.01, 5.55, intergralActive, "Drive");
        // driveVel = math.pid(errorDistance, errorDistanceL, 2.9, 0.01, 5.25, intergralActive, "Drive");
        //driveVel = math.pid(errorDistance, errorDistanceL, 3.22, 0.02, 5.58, intergralActive, "Drive");

        errorDistanceL = errorDistance; // Set last error to current error

        // Calculate drift if the robot is not at desired angle
        errorDrift = odom.getThetaDeg() - angle;
        driftVel = errorDrift * 0.01;

        // Constain velocity to allow for smoother acceleration
        driveVel = math.slew(driveVel, lastVelocity);
        lastVelocity = driveVel;

        // Constrain velocity
        if (fabs(driveVel) > maxVelocity) {
          driveVel = maxVelocity;
        } else if (fabs(driveVel) < minVelocity) {
          driveVel = minVelocity;
        }

        // Display velocity to lcd; useful for debugging
        // lcd::print(7, "%f", driveVel);

        // Set velocity variables
        leftVelocity = (driveVel - driftVel) * multiplier;
        rightVelocity = (driveVel + driftVel) * multiplier;
      }

      // Inverses the velocity if reversed is true
      if (reversed) {
        leftVelocity *= -1;
        rightVelocity *= -1;
      }

      // Sets the velocity of the right and left drivetrain
      LFD.move_velocity(leftVelocity);
      RFD.move_velocity(rightVelocity);
      LBD.move_velocity(leftVelocity);
      RBD.move_velocity(rightVelocity);

      // Brake when robot reaches target based on errorType and tolerance
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

      // Brake when the robot when a certain amount of time has passed
      if (millis() > timeOut && timeOut != 0) {
         chassis.stop();
         chassis.reset();
      }
    }
    delay(10);
  }
}

/**
 * Ends the chassis drive task
 */
void Chassis::end() {
  if (isRunning) {
    chassis.stop().brake(); // Stops the drivetrain
    isRunning = false;
    chassisTask->remove(); // Removes memory stack task is occupying
    delete chassisTask; // Deletes task from memory
    chassisTask = nullptr;
  }
}
