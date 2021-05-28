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
       Chassis::maxSpeed, Chassis::minSpeed, Chassis::leftSpeed, Chassis::rightSpeed;

char Chassis::errorType, Chassis::side;

double errorTheta, errorThetaAbs, errorThetaL,
       currentDistance, errorX, errorY, errorDistance, errorDistanceL,
       turnSpeed, driveSpeed, driftSpeed, lastSpeed, intergralActive,
       minMovement = math.percentToVoltage(17.5);

/**
* Stops the chassis
*/
Chassis& Chassis::stop() {
  leftSpeed = 0;
  rightSpeed = 0;
  maxSpeed = 0;
  minSpeed = 0;
  driftSpeed = 0;
  driveSpeed = 0;
  turnSpeed = 0;
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
 * Sets the speed of the chassis
 * @param velocity_ -100 to 100 (In percentage of max chassis speed)
 * @param side_ 'B', 'L', 'R' (Chassis side that will move; Both, Left, or Right)
 */
Chassis& Chassis::move(double speed_, char side_) {
  isSettled = false;
  side = side_;
  if (side_ == 'B') {
    rightSpeed = math.percentToVoltage(speed_);
    leftSpeed = math.percentToVoltage(speed_);
  } else if (side_ == 'L') {
    leftSpeed = math.percentToVoltage(speed_);
  } else if (side_ == 'R') {
    rightSpeed = math.percentToVoltage(speed_);
  }
  return *this;
}

/**
 * Moves the robot to a specific point
 * @param targetX_ (In inches)
 * @param targetY_ (In inches)
 * @param maxSpeed_ 0 to 100 (In percentage of chassis max speed)
 * @param errorType_ 'X', 'Y', or 'D' (Breaking error type; X, Y, or Distance)
 * @param timeOut_ (In seconds)
 * @param angle_ (In degress; angle robot drives at)
 * @param reverse_ True or False (Perform action backwards; false by default)
 */
Chassis& Chassis::driveToPoint(double targetX_, double targetY_, double maxSpeed_, char errorType_,
                               double timeOut_, double angle_, bool reversed_) {
  targetX = targetX_;
  targetY = targetY_;
  maxSpeed = math.percentToVoltage(maxSpeed_);
  minSpeed = minMovement;
  errorType = errorType_;
  targetTheta = angle_;
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
 * @param maxSpeed_ 0 to 100 (In percentage of chassis max speed)
 * @param timeOut_ (In seconds)
 * @param side_ 'B', 'L', 'R' (Chassis side that will move; Both, Left, or Right)
 * @param reverse_ True or False (Perform action backwards; false by default)
 */
Chassis& Chassis::turnToAngle(double targetTheta_, double maxSpeed_, double timeOut_, char side_, bool reversed_) {
  targetTheta = targetTheta_;
  maxSpeed = math.percentToVoltage(maxSpeed_);
  minSpeed = minMovement;
  side = side_;
  timeOut = math.secToMillis(timeOut_) + millis();
  reversed = reversed_;
  isTurning = true;
  isSettled = false;
  tolerance = 0.01;
  return *this;
}

/**
 * Minimum speed for movements
 * @param minSpeed_ 0 to 100 (In percentage of chassis max speed)
 */
Chassis& Chassis::withMinSpeed(double minSpeed_) {
  minSpeed = math.percentToVoltage(minSpeed_);
  if (minSpeed < minMovement) {
    minSpeed = minMovement;
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
  isSettled = first = true;
  isDriving = isTurning = false;
  targetX = targetY = targetTheta = timeOut = maxSpeed = 0;
  errorTheta = errorDistance = errorX = errorY = 0;
  errorThetaL = errorDistanceL = lastSpeed = intergralActive = 0;
  errorType = 'N';
  multiplier = 1.0;
  minSpeed = minMovement;
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
  delay(300);

  while (isRunning) {

    if (!isSettled) {

      if (isTurning) {
        errorTheta = math.filter(targetTheta, odom.getThetaDeg()); // Calculate theta error in degress
        errorThetaAbs = fabs(errorTheta);

        if (first) {
          math.intergral = 0;
          intergralActive = errorThetaAbs * 0.2;
          first = false;
        }

        // Pass error into PID loop to calculate speed
        if (side == 'B') {
          turnSpeed = math.pid(errorThetaAbs, errorThetaL, 250, 2.3, 2830, intergralActive, "Turn");
          //turnSpeed = math.pid(errorTheta, errorThetaL, 250, 2.3, 2830, intergralActive, "Turn");
          // turnSpeed = math.pid(errorTheta, errorThetaL, 0.6, 0.002, 1.42, 15, "Turn");
        } else if (side == 'L') {
          turnSpeed = math.pid(errorThetaAbs, errorThetaL, 250, 2.3, 2830, intergralActive, "Turn");
        } else if (side == 'R') {
          turnSpeed = math.pid(errorThetaAbs, errorThetaL, 250, 2.3, 2830, intergralActive, "Turn");
        }

        errorThetaL = errorThetaAbs; // Set last error to current error

        // Constrain speed
        if (fabs(turnSpeed) >= maxSpeed) {
          turnSpeed = maxSpeed;
        } else if (fabs(turnSpeed) <= minSpeed) {
          turnSpeed = minMovement;
        }

        if (errorTheta < 0) {
          turnSpeed *= -1;
        }

        // Display speed to lcd; useful for debugging
        // lcd::print(7, "%f", turnSpeed);

        // Set speed variables
        leftSpeed = turnSpeed * multiplier;
        rightSpeed = -turnSpeed * multiplier;

        // Sets velocity of a side to 0 only if one side is set to move
        if (side == 'L') {
          rightSpeed = 0;
        } else if (side == 'R') {
          leftSpeed = 0;
        }
      } else if (isDriving) {

        errorX = math.filter(targetX, odom.getX());
        errorY = math.filter(targetY, odom.getY());
        errorDistance = sqrt(pow(errorX, 2) + pow(errorY, 2)); // Calculate distance error in inches

        errorTheta = math.filter(targetTheta, odom.getThetaDeg()); // Calculate theta error in degress
        errorThetaAbs = fabs(errorTheta);

        if (first) {
          math.intergral = 0;
          intergralActive = errorDistance * 0.25;
          first = false;
        }

        // Pass error into PID loop to calculate speed
        driveSpeed = math.pid(errorDistance, errorDistanceL, 340, 0.04, 700, intergralActive, "Drive");
        //driveSpeed = math.pid(errorDistance, errorDistanceL, 3.2, 0.01, 5.55, intergralActive, "Drive");
        // driveSpeed = math.pid(errorDistance, errorDistanceL, 2.9, 0.01, 5.25, intergralActive, "Drive");
        //driveSpeed = math.pid(errorDistance, errorDistanceL, 3.22, 0.02, 5.58, intergralActive, "Drive");

        errorDistanceL = errorDistance; // Set last error to current error

        // Calculate drift if the robot is not at desired angle
        driftSpeed = errorTheta * 250;
        if (reversed) {
          driftSpeed *= -1;
        }

        // Constrain speed to allow for smoother acceleration
        driveSpeed = math.slew(driveSpeed, lastSpeed);
        lastSpeed = driveSpeed;

        // Constrain speed
        if (fabs(driveSpeed) >= maxSpeed) {
          driveSpeed = maxSpeed;
        } else if (fabs(driveSpeed) <= minSpeed) {
          driveSpeed = minMovement;
        }

        // Display speed to lcd; useful for debugging
        // lcd::print(7, "%f", driveSpeed);

        // Set speed variables
        leftSpeed = (driveSpeed + driftSpeed)  * multiplier;
        rightSpeed = (driveSpeed - driftSpeed) * multiplier;
      }

      // Inverses the speed if reversed is true
      if (reversed) {
        leftSpeed *= -1;
        rightSpeed *= -1;
      }

      // Sets the speed of the right and left drivetrain
      LFD.move_voltage(leftSpeed);
      RFD.move_voltage(rightSpeed);
      LBD.move_voltage(leftSpeed);
      RBD.move_voltage(rightSpeed);

      // Brake when robot reaches target based on errorType and tolerance
      if (errorType == 'Y' && fabs(errorY) <= tolerance) {
        if (minSpeed <= minMovement) {
          chassis.stop();
        }
        chassis.reset();
      } else if (errorType == 'X' && fabs(errorX) <= tolerance) {
        if (minSpeed <= minMovement) {
          chassis.stop();
        }
        chassis.reset();
      } else if (errorType == 'D' && fabs(errorDistance) <= tolerance) {
        if (minSpeed <= minMovement) {
          chassis.stop();
        }
        chassis.reset();
      } else if (fabs(errorTheta) <= tolerance && isTurning) {
        chassis.stop();
        chassis.reset();
      }

      // Brake when the robot when a certain amount of time has passed
      if (millis() > timeOut && timeOut != 0) {
        if (minSpeed <= minMovement) {
            chassis.stop();
         }
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
