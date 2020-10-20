#include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"
#include "functions/math.hpp"

Math math;
Intake::Intake(){}
Intake::~Intake(){}

void Intake::move(float velocity) {
  LI.move_velocity(math.percentToVelocity(velocity, 'B'));
  RI.move_velocity(math.percentToVelocity(velocity, 'B'));
}

Intake& Intake::stop() {
  LI.move_velocity(0);
  RI.move_velocity(0);
  return *this;
}

void Intake::brake() {
  LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
