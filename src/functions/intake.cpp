#include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"
#include "functions/math.hpp"

Intake::Intake(){}
Intake::~Intake(){}

Intake intake;
static Math math;

/**
 * Stops the intakes
 */
Intake& Intake::stop() {
  LI.move_velocity(0);
  RI.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the intakes to brake
 */
void Intake::brake() {
  LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the brake mode of the intakes to coast
 */
void Intake::coast() {
  LI.set_brake_mode(MOTOR_BRAKE_COAST);
  RI.set_brake_mode(MOTOR_BRAKE_COAST);
}

/**
 * Sets the brake mode of the intakes to hold
 */
void Intake::hold() {
  LI.set_brake_mode(MOTOR_BRAKE_HOLD);
  RI.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Sets the voltage of the intakes
 * @param voltage -100 to 100 (In percentage of max intake speed)
 */
Intake& Intake::moveVolt(double voltage) {
  voltage = math.percentToVoltage(voltage);
  LI.move_voltage(voltage);
  RI.move_voltage(voltage);
  return *this;
}

/**
 * Sets the velocity of the intakes
 * @param velocity -100 to 100 (In percentage of max intake speed)
 */
Intake& Intake::moveVel(double velocity) {
  velocity = math.percentToVelocity(velocity, 'B');
  LI.move_velocity(velocity);
  RI.move_velocity(velocity);
  return *this;
}
