#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/pid.hpp"
#include "functions/math.hpp"


Chassis::Chassis(){}
Chassis::~Chassis(){}

Chassis chassis;
static Math math;
static PID pid;
static Odom odom;

bool Chassis::isRunning = false,
     Chassis::isSettled = true,
     Chassis::isTurning = false,
     Chassis::isDriving = false;

float Chassis::targetTheta = 0,
      Chassis::targetTicks = 0;

float Chassis::leftVolt = 0,
      Chassis::rightVolt = 0,
      Chassis::maxSpeed = 0,
      Chassis::timeOut = 0;

float targetX = 0, targetY = 0;

/**
 * Stops the drivetrain
 */
Chassis& Chassis::stop() {
  LFD.move_velocity(0);
  LBD.move_velocity(0);
  RFD.move_velocity(0);
  RBD.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the drivetrain to brake
 */
void Chassis::brake() {
  LFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  LBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the brake mode of the drivetrain to hold
 */
void Chassis::hold() {
  LFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  LBD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RBD.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Sets the brake mode of the drivetrain to coast
 */
void Chassis::coast() {
  LFD.set_brake_mode(MOTOR_BRAKE_COAST);
  LBD.set_brake_mode(MOTOR_BRAKE_COAST);
  RFD.set_brake_mode(MOTOR_BRAKE_COAST);
  RBD.set_brake_mode(MOTOR_BRAKE_COAST);
}

void Chassis::setLeftVolt(float voltage) {
  leftVolt = voltage;
}

void Chassis::setRightVolt(float voltage) {
  rightVolt = voltage;
}

void Chassis::reset() {
  isSettled = true;
  leftVolt = rightVolt = maxSpeed = timeOut = 0;
  targetTheta = targetTicks = 0;
  chassis.stop().brake();
}

void Chassis::startTask(void* param) {
  delay(300);
  isRunning = true;
  chassis.reset();
  cout<<"Chassis Task Started"<<endl;
  while(isRunning) {
    LFD.move_voltage(leftVolt);
    LBD.move_voltage(leftVolt);
    RFD.move_voltage(rightVolt);
    RBD.move_voltage(rightVolt);
    if (!isSettled) {
      if (isTurning) {
        pid.turn(math.angleWrap(targetTheta), maxSpeed);
        if (abs(targetTheta) <= odom.getTheta()) {
          isTurning = false;
        }
      }
      if (isDriving && !isTurning) {
        pid.drive(targetTicks, maxSpeed);
        if (abs(targetTicks) <= abs(LEnc.get_value() + REnc.get_value())/2) {
          isDriving = false;
        }
      }
      if (millis() >= timeOut) {
        chassis.reset();
        isDriving = isTurning = false;
      } else if (!isTurning && !isDriving) {
        chassis.reset();
      }
    }
    delay(10);
  }
}

void Chassis::endTask() {
  isRunning = false;
  chassis.reset();
  cout<<"Chassis task ended"<<endl;
}

Chassis& Chassis::drive(float distance, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    targetTicks = math.inchToTicks(distance);
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isDriving = true;
    isTurning = false;
    isSettled = false;
  }
  return *this;
}

Chassis& Chassis::turn(float theta, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    targetTheta = math.angleWrap(theta);
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isTurning = true;
    isDriving = false;
    isSettled = false;
  }
  return *this;
}

Chassis& Chassis::driveToPoint(float x, float y, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    targetX = x + odom.getX();
    targetY = y + odom.getY();
    if (targetY != 0) {
      targetTheta = math.angleWrap(atan(targetX/targetY)*(180/M_PI)) - odom.getTheta();
    }
    targetTicks = math.inchToTicks(sqrt((targetX*targetX) + (targetY*targetY)));
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isTurning = true;
    isDriving = true;
    isSettled = false;
  }
  return *this;
}

Chassis& Chassis::turnToPoint(float x, float y, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    targetX = x + odom.getX();
    targetY = y + odom.getY();
    if (targetY != 0) {
      targetTheta = math.angleWrap(atan(targetX/targetY)*(180/M_PI)) - odom.getTheta();
    }
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isTurning = true;
    isDriving = false;
    isSettled = false;
  }
  return *this;
}

Chassis& Chassis::turnToAngle(float theta, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    targetTheta = math.angleWrap(theta) - odom.getTheta();
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.secToMillis(timeOut_) + millis();
    isTurning = true;
    isDriving = false;
    isSettled = false;
  }
  return *this;
}

void Chassis::waitUntilSettled() {
  while(!isSettled) {
    delay(10);
  }
}
