#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"
#include "functions/math.hpp"

Math math;
Uptake::Uptake(){}
Uptake::~Uptake(){}

void Uptake::move(float velocity) {
  BU.move_velocity(math.percentToVelocity(velocity, 'B'));
  TU.move_velocity(math.percentToVelocity(velocity, 'B'));
}

Uptake& Uptake::stop() {
  BU.move_velocity(0);
  TU.move_velocity(0);
  return *this;
}

void Uptake::brake() {
  BU.set_brake_mode(MOTOR_BRAKE_BRAKE);
  TU.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
