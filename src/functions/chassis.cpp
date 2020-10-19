#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"

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

void Chassis::drive(float distance, float maxSpeed, float timeOut) {

}

void Chassis::turn(float theta, float maxSpeed, float timeOut) {

}

void Chassis::driveToPoint(float x, float y, float maxSpeed, float timeOut) {

}

void Chassis::turnToPoint(float x, float y, float maxSpeed, float timeOut) {

}

void Chassis::turnToAngle(float theta, float maxSpeed, float timeOut) {

}
