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

//Fix this; bad logical sense, need to wait for turn to finish then drive.

void Chassis::startTask(void* param) {
  delay(300);
  isRunning = true;
  chassis.reset();
  cout<<"Chassis Task Started"<<endl;
  while(isRunning) {
    chassis.setLeftVolt(leftVolt);
    chassis.setRightVolt(rightVolt);
    if (!isSettled) {
      if (isTurning == true) {
        pid.turn(math.angleWrap(targetTheta), maxSpeed);
      } else if (isDriving == true) {
        pid.drive(targetTicks, maxSpeed);
      }
      if (targetTicks - 0.1 < (LEnc.get_value() + REnc.get_value())/2 < targetTicks + 0.1) {
        chassis.reset();
        isDriving = false;
      } else if (targetTheta - 0.1 < odom.getTheta() < targetTheta + 0.1) {
        chassis.reset();
        isTurning = false;
      } else if (millis() >= timeOut) {
        chassis.reset();
        isDriving = isTurning = false;
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

void Chassis::drive(float distance_, float maxSpeed_, float timeOut_) {
  targetTicks = math.inchToTicks(distance_);
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  isDriving = true;
  isTurning = false;
}

void Chassis::turn(float theta_, float maxSpeed_, float timeOut_) {
  targetTheta = math.angleWrap(theta_) + odom.getTheta();
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  isTurning = true;
  isDriving = false;
}

void Chassis::driveToPoint(float x_, float y_, float maxSpeed_, float timeOut_) {
  float targetX = x_ + odom.getX();
  float targetY = y_ + odom.getY();
  targetTheta = math.angleWrap(atan(targetY/targetX)*(180/M_PI)) - odom.getTheta();
  targetTicks = math.inchToTicks(sqrt((targetX*targetX) + (targetY*targetY)));
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  isTurning = true;
  isDriving = true;
}

void Chassis::turnToPoint(float x_, float y_, float maxSpeed_, float timeOut_) {
  float targetX = x_ + odom.getX();
  float targetY = y_ + odom.getY();
  targetTheta = math.angleWrap(atan(targetY/targetX)*(180/M_PI)) - odom.getTheta();
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  isTurning = true;
  isDriving = false;
}

void Chassis::turnToAngle(float theta_, float maxSpeed_, float timeOut_) {
  targetTheta = math.angleWrap(theta_) - odom.getTheta();
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  isTurning = true;
  isDriving = false;
}
