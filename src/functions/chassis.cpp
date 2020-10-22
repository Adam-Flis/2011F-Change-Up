#include "main.h"
#include "define.hpp"

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

void Chassis::leftVolt(int voltage) {
  LFD.move_voltage(voltage);
  LBD.move_voltage(voltage);
}

void Chassis::rightVolt(int voltage) {
  RFD.move_voltage(voltage);
  RBD.move_voltage(voltage);
}

void Chassis::startTask(void* param) {

}

void Chassis::endTask() {

}

void Chassis::drive(float distance_, float maxSpeed_, float timeOut_) {
  distance = math.inchToTicks(distance_);
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  pid.drive(distance, maxSpeed);
}

void Chassis::turn(float theta_, float maxSpeed_, float timeOut_) {
  theta = math.angleWrap(theta_);
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
  pid.turn(theta, maxSpeed);
}

void Chassis::driveToPoint(float x_, float y_, float maxSpeed_, float timeOut_) {
  x_ = x_ - odom.getX();
  y_ = y_ - odom.getY();
  theta = math.angleWrap(atan(y_/x_)*(180/M_PI));
  distance = math.inchToTicks(sqrt((x_*x_) + (y_*y_)));
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
}

void Chassis::turnToPoint(float x_, float y_, float maxSpeed_, float timeOut_) {
  x_ = x_ - odom.getX();
  y_ = y_ - odom.getY();
  theta = math.angleWrap(atan(y_/x_)*(180/M_PI));
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
}

void Chassis::turnToAngle(float theta_, float maxSpeed_, float timeOut_) {
  theta = theta_;
  maxSpeed = math.percentToVoltage(maxSpeed_);
  timeOut = math.timeOut(timeOut_);
}
