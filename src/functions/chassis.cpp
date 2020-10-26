#include "main.h"
#include "define.hpp"

bool Chassis::isRunning = false,
     Chassis::isSettled = true,
     Chassis::isTurning = false,
     Chassis::isDriving = false;

Chassis::Chassis(){}
Chassis::~Chassis(){}

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
  LFD.move_voltage(voltage);
  LBD.move_voltage(voltage);
}

void Chassis::setRightVolt(float voltage) {
  RFD.move_voltage(voltage);
  RBD.move_voltage(voltage);
}

void Chassis::reset() {
  isSettled = true;
  leftVolt = rightVolt = maxSpeed = timeOut = 0;
  targetTheta = targetTicks = 0;
  chassis.brake();
}

void Chassis::startTask(void* param) {
  delay(300);
  isRunning = true;
  chassis.reset();
  cout<<"Chassis Task Started"<<endl;
  while(isRunning) {
    chassis.setLeftVolt(leftVolt);
    chassis.setRightVolt(rightVolt);
    if (!isSettled) {
      if (isTurning) {
        pid.turn(math.angleWrap(targetTheta), maxSpeed);
        if (targetTheta - 0.1 < odom.getTheta() < targetTheta + 0.1) {
         isTurning = false;
        }
      } else if (isDriving && !isTurning) {
        if (targetTicks - 0.1 < (LEnc.get_value() + REnc.get_value())/2 < targetTicks + 0.1) {
          isDriving = false;
        }
        pid.drive(targetTicks, maxSpeed);
      }
      if (millis() >= timeOut) {
        chassis.reset();
        isDriving = isTurning = false;
      } else if (!isTurning && !isDriving) {
        chassis.reset();
      }
    }
    delay(20);
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
    timeOut = math.timeOut(timeOut_);
    isDriving = true;
    isTurning = false;
  }
  return *this;
}

Chassis& Chassis::turn(float theta, float maxSpeed_, float timeOut_) {
  if (isRunning) {
  targetTheta = math.angleWrap(theta) + odom.getTheta();
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  isTurning = true;
  isDriving = false;
  }
  return *this;
}

Chassis& Chassis::driveToPoint(float x, float y, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    float targetX = x + odom.getX();
    float targetY = y + odom.getY();
    targetTheta = math.angleWrap(atan(targetY/targetX)*(180/M_PI)) - odom.getTheta();
    targetTicks = math.inchToTicks(sqrt((targetX*targetX) + (targetY*targetY)));
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.timeOut(timeOut_);
    isTurning = true;
    isDriving = true;
  }
  return *this;
}

Chassis& Chassis::turnToPoint(float x, float y, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    float targetX = x + odom.getX();
    float targetY = y + odom.getY();
    targetTheta = math.angleWrap(atan(targetY/targetX)*(180/M_PI)) - odom.getTheta();
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.timeOut(timeOut_);
    isTurning = true;
    isDriving = false;
  }
  return *this;
}

Chassis& Chassis::turnToAngle(float theta, float maxSpeed_, float timeOut_) {
  if (isRunning) {
    targetTheta = math.angleWrap(theta) - odom.getTheta();
    maxSpeed = math.percentToVoltage(maxSpeed_);
    timeOut = math.timeOut(timeOut_);
    isTurning = true;
    isDriving = false;
  }
  return *this;
}
