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

bool Chassis::isRunning = false,
     Chassis::isSettled = true,
     Chassis::isTurning = false,
     Chassis::isDriving = false;

float Chassis::targetTheta,
      Chassis::targetTicks,
      Chassis::targetVoltage;

float Chassis::leftVoltage,
      Chassis::rightVoltage,
      Chassis::timeOut;

float targetX,
      targetY,
      finalVoltage,
      ticks,
      drift;

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

/**
 * Resets the chassis variables
 */
void Chassis::reset() {
  isSettled = true;
  targetX = targetY = finalVoltage = ticks = drift = 0;
  leftVoltage = rightVoltage = timeOut = 0;
  targetTheta = targetTicks = targetVoltage = 0;
  chassis.stop().brake();
}

/**
 * Starts the chassis drive task
 */
void Chassis::startTask(void* param) {
  delay(300);
  isRunning = true;
  chassis.reset();
  cout<<"Chassis Task Started"<<endl;
  while(isRunning) {
    if (!isSettled) {
      if (isTurning) { // Run the turn function when the robot is called to turn
        finalVoltage = pid.turn(targetTheta, targetVoltage);
        leftVoltage = finalVoltage;
        rightVoltage = -finalVoltage;
        if (millis() >= timeOut/2 && isDriving) { // Allocates enough time for the robot to be able
                                                  // to turn then drive when driveToPoint function is used
          isTurning = false;
        }
      } else if (isDriving && !isTurning) { // Run the drive function when the robot is called to drive and not to turn
        finalVoltage = pid.drive(targetTicks, targetVoltage);
        drift = pid.drift();
        if (finalVoltage > 0) { // Adds drift correction for when the robot travels forward
          leftVoltage = finalVoltage - drift;
          rightVoltage = finalVoltage + drift;
        }
        else {
          leftVoltage = finalVoltage;
          rightVoltage = finalVoltage;
        }
      }

      if (odom.getTheta() == targetTheta && isTurning && targetTheta != 0) { // When robot reaches turn target stop turning
          isTurning = false;
        } // else if (math.encoderAverage() == targetTicks && isDriving && targetTicks != 0) { // When robot reaches drive target stop driving
        //   isDriving = false;
        // }
      if (millis() >= timeOut) { // When timeout is reached stop the robot and reset variables
        isDriving = isTurning = false;
        chassis.reset();
      } else if (!isTurning && !isDriving) { // Stops the robot when it reaches its target
        chassis.reset();
      }

      LFD.move_voltage(leftVoltage); // Sets voltage of chassis motors
      RFD.move_voltage(rightVoltage);
      LBD.move_voltage(leftVoltage);
      RBD.move_voltage(rightVoltage);
    }
    delay(10); // Loop speed, prevent overload
  }
}

/**
 * Ends the chassis drive task
 */
void Chassis::endTask() {
  isRunning = false;
  chassis.reset();
  cout<<"Chassis task ended"<<endl;
}

/**
 * Moves the chassis a certain distance using a PID loop
 * @param distance (In inches -backwards +forwards)
 * @param targetVoltage_ 0 to 100 (In percentage of drive max speed)
 * @param timeOut_ (In seconds)
 */
Chassis& Chassis::drive(float distance, float targetVoltage_, float timeOut_) {
  if (isRunning) {
    ticks = math.inchToTicks(distance);
    targetTicks = ticks; //+ math.encoderAverage();
    targetVoltage = math.percentToVoltage(targetVoltage_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isDriving = true;
    isTurning = false;
    isSettled = false;
  }
  return *this;
}

/**
 * Truns the chassis a certain degress using a PID loop
 * @param theta_ (In degress -180 to 180)
 * @param targetVoltage_ 0 to 100 (In percentage of drive max speed)
 * @param timeOut_ (In seconds)
 */
Chassis& Chassis::turn(float theta_, float targetVoltage_, float timeOut_) {
  if (isRunning) {
    targetTheta = math.angleWrap(theta_) + odom.getTheta();
    targetVoltage = math.percentToVoltage(targetVoltage_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isTurning = true;
    isDriving = false;
    isSettled = false;
  }
  return *this;
}

/**
 * Moves the robot to a certain point on the field
 * @param x (In inches)
 * @param y (In inches)
 * @param targetVoltage_ 0 to 100 (In percentage of drive max speed)
 * @param timeOut_ (In seconds)
 * @param reverse True or False (Perform action backwards)
 */
Chassis& Chassis::driveToPoint(float x, float y, float targetVoltage_, float timeOut_, bool reverse) {
  if (isRunning) {
    targetX = x - odom.getX();
    targetY = y - odom.getY();

    // Calculates if the robot needs to turn before moving in the x/y direction
    if (targetY != 0) {
      targetTheta = math.angleWrap(atan(targetX/targetY)*(180/M_PI));
      isTurning = true;
    } else {
      isTurning = false;
    }

    ticks = math.inchToTicks(sqrt(pow(targetX, 2) + pow(targetY, 2))); // Calculates the hypotenuse of triangle, distance robot will travel
    if (reverse == true) { // Sets ticks to negative if the robot will drive backwards to point
      ticks = -ticks;
    }

    // Sets the global variables that are used to move the robot in the chassis task
    targetTicks = ticks; //+ math.encoderAverage();
    targetVoltage = math.percentToVoltage(targetVoltage_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isDriving = true;
    isSettled = false;
    isTurning = false;
  }
  return *this;
}

/**
 * Turns the robot to a certain point on the field
 * @param x (In inches)
 * @param y (In inches)
 * @param targetVoltage_ 0 to 100 (In percentage of drive max speed)
 * @param timeOut_ (In seconds)
 */
Chassis& Chassis::turnToPoint(float x, float y, float targetVoltage_, float timeOut_) {
  if (isRunning) {
    targetX = x - odom.getX();
    targetY = y - odom.getY();

    // Calculates the angle the robot has to turn to face the desired poinnt
    if (targetY != 0) {
      targetTheta = math.angleWrap(atan(targetX/targetY)*(180/M_PI));
    }

    // Sets the global variables that are used to move the robot in the chassis task
    targetVoltage = math.percentToVoltage(targetVoltage_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isTurning = true;
    isDriving = false;
    isSettled = false;
  }
  return *this;
}

/**
 * Turns the robot to a certain angle
 * @param theta_ (In degress)
 * @param targetVoltage_ 0 to 100 (In percentage of drive max speed)
 * @param timeOut_ (In seconds)
 */
Chassis& Chassis::turnToAngle(float theta_, float targetVoltage_, float timeOut_) {
  if (isRunning) {
    // Sets the global variables that are used to move the robot in the chassis task
    targetTheta = math.angleWrap(theta_);
    targetVoltage = math.percentToVoltage(targetVoltage_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isTurning = true;
    isDriving = false;
    isSettled = false;
  }
  return *this;
}

/**
 * Waits untill the chassis has settled
 */
void Chassis::waitUntilSettled() {
  while(!isSettled) {
    delay(10); // Loop speed, prevent overload
  }
}
